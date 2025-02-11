import multiprocessing
import os
import random
import time
from collections import deque
from time import sleep

from Logger import log
from config import STADIUM_CAPACITY, end_match_event, FanType, security_check_event, Fan
from distibutor import distributor_process
from worker import stadium_worker


def run_simulation():
    allocated_PIDs = []
    security_check_event.clear()
    write_fd = None
    try:
        check_configuration()
        read_fd, write_fd = create_pipe()
        create_worker_process(read_fd, allocated_PIDs)
        vip_queue = deque()
        standard_queue = deque()
        fan_next_index = 0
        while fan_next_index <= STADIUM_CAPACITY + 50:
            fan = generate_random_fan(fan_next_index)
            if fan.fan_type == FanType.STANDARD:
                if fan.is_adult():
                    standard_queue.append(fan)
                else:
                    standard_queue.append(fan)
                    fan_next_index += 1
                    adult_fan_for_child = generate_adult_fan_for_child(fan_next_index, fan.team)
                    standard_queue.append(adult_fan_for_child)
            else:
                vip_queue.append(fan)
            fan_next_index += 1

        create_distributor_process(vip_queue, standard_queue, allocated_PIDs)

        while not end_match_event.is_set():
            command = input("Input command (sygnał1, sygnał2, sygnał3): ").strip()
            write_fd.send(command)
            time.sleep(0.2)

    except KeyboardInterrupt:
        log("Program interrupted by the User.")
    except OSError as e:
        log(f"Syntax error: {e}")
    except Exception as e:
        print(f"Unexpected exception: {e}")
    finally:
        clean(allocated_PIDs, write_fd)


def check_configuration():
    # Basic validation of STADIUM_CAPACITY
    if STADIUM_CAPACITY <= 0:
        log("STADIUM_CAPACITY need to be greater than 0.")
        os._exit(-1)


def create_distributor_process(vip_queue, standard_queue, allocated_PIDs):
    pid = os.fork()
    if pid == 0:
        distributor_process(vip_queue, standard_queue, allocated_PIDs)
        os._exit(0)
    allocated_PIDs.append(pid)


def generate_random_fan(index):
    type = FanType.STANDARD if random.random() >= 0.05 else FanType.VIP

    if type == FanType.STANDARD:
        age = random.randint(-20, 80)
        team = random.choice([1, 2])
        return Fan(index, age, team, False, FanType.STANDARD)

    else:
        return Fan(index, 30, 0, False, FanType.VIP)


def generate_adult_fan_for_child(index, team):
    return Fan(index, 30, team, True, FanType.STANDARD)


def create_worker_process(read_fd, allocated_PIDs):
    try:
        pid = os.fork()
    except OSError as e:
        log(f"Error occurred on creating worker process: {e}")
        os._exit(-1)

    if pid == 0:
        stadium_worker(read_fd)
        os._exit(0)
    allocated_PIDs.append(pid)


def create_pipe():
    try:
        return multiprocessing.Pipe()
    except OSError as e:
        log(f"Error occurred on pipe processing: {e}")
        return


def clean(allocated_PIDs, write_fd):
    clean_processes(allocated_PIDs)
    try:
        if write_fd is not None:
            write_fd.close()

    except Exception as e:
        log(f"Error occurred while closing pipe: {e}")


def clean_processes(allocated_PIDs):
    for pid in allocated_PIDs:
        try:
            os.waitpid(pid, 0)
            # os.kill(pid, 9)
        except OSError as e:
            log(f"Error occurred while killing fan process: {e}")
