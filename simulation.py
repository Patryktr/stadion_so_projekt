import multiprocessing
import os
import signal
import random
import time
from collections import deque
from time import sleep

from Logger import log
from config import STADIUM_CAPACITY, end_match_event, FanType, security_check_event, Fan, VIP_PROBABILITY, \
    append_PID, allocated_PIDs
from distibutor import distributor_process
from worker import stadium_worker


def run_simulation():
    security_check_event.clear()

    try:
        check_configuration()

        worker_pid = create_worker_process()

        vip_queue = deque()
        standard_queue = deque()
        fan_next_index = 0
        while fan_next_index <= STADIUM_CAPACITY + 15:
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

        create_distributor_process(vip_queue, standard_queue)

        while not end_match_event.is_set():
            command = input("Input command (sygnał1, sygnał2, sygnał3): ").strip()

            if command == "sygnał1":
                os.kill(worker_pid, signal.SIGUSR1)
                print("Wysłano SIGUSR1")
            elif command == "sygnał2":
                os.kill(worker_pid, signal.SIGUSR2)
                print("Wysłano SIGUSR2")
            elif command == "sygnał3":
                os.kill(worker_pid, signal.SIGTERM)
                print("Wysłano SIGTERM")
            else:
                print("Nieznana komenda!")



    except KeyboardInterrupt:
        log("Program interrupted by the User.")
    except OSError as e:
        log(f"Syntax error: {e}")
    except Exception as e:
        print(f"Unexpected exception: {e}")
    finally:
        clean()


def check_configuration():
    # Basic validation of STADIUM_CAPACITY
    if STADIUM_CAPACITY <= 0:
        log("STADIUM_CAPACITY need to be greater than 0.")
        os._exit(-1)


def create_distributor_process(vip_queue, standard_queue):
    pid = os.fork()
    if pid == 0:
        distributor_process(vip_queue, standard_queue)
        os._exit(0)

    append_PID(pid)


def generate_random_fan(index):
    type = FanType.STANDARD if random.random() >= VIP_PROBABILITY else FanType.VIP

    if type == FanType.STANDARD:
        age = random.randint(7, 80)
        team = random.choice([1, 2])
        return Fan(index, age, team, False, FanType.STANDARD)

    else:
        return Fan(index, 30, 0, False, FanType.VIP)


def generate_adult_fan_for_child(index, team):
    return Fan(index, 30, team, True, FanType.STANDARD)


def create_worker_process():
    """ Tworzy proces worker i zwraca jego PID """
    pid = os.fork()
    if pid == 0:
        stadium_worker()  # Worker nie potrzebuje argumentu, bo czyta sygnały
        os._exit(0)
    append_PID(pid)
    return pid  # Zwracamy PID worker'a


def clean():
    """ Zamyka procesy w allocated_PIDs """
    while not allocated_PIDs.empty():
        try:
            pid = allocated_PIDs.get()
            os.waitpid(pid, 0)
        except OSError as e:
            log(f"Error occurred while killing process: {e}")
