import os
import random
import time
from multiprocessing import Event, Value

from Logger import log
from config import team_in_gate, fans_in_gate, security_check_event, end_match_event, GATES_QTY, stadium_is_full
from fan import fan_process
from vip_fan import vip_fan_process


def distributor_process(vip_queue, standard_queue, allocated_PIDs):
    for index in range(len(vip_queue)):
        pid = os.fork()
        if pid == 0:
            vip_fan_process(index)
            os._exit(0)
        allocated_PIDs.append(pid)

    while not security_check_event.is_set():
        time.sleep(0.1)

    last_picked_fan_indexes = []

    while not end_match_event.is_set() and not stadium_is_full.is_set():
        fans = pick_next_fans(standard_queue, last_picked_fan_indexes)
        last_picked_fan_indexes = [fan_item.index for fan_item in fans]
        if len(fans) == 0:
            log(f"No more fans in the queue")
            return

        fans_team = fans[0].team
        fan_qty = len(fans)
        gate_indices = list(range(GATES_QTY))
        random.shuffle(gate_indices)
        for gate_number in gate_indices:
            with team_in_gate[gate_number].get_lock():
                may_enter = team_in_gate[gate_number].value in [0, fans_team]
                if may_enter:
                    with fans_in_gate[gate_number].get_lock():
                        may_enter = fans_in_gate[gate_number].value + fan_qty <= 3
                        if may_enter:
                            fans_in_gate[gate_number].value += fan_qty
                            team_in_gate[gate_number].value = fans_team
                            for fan in fans:
                                log(f"Fan {fan.index} from team {fan.team} is in security gate {gate_number}. There are {fans_in_gate[gate_number].value}.")
                            picked_gate_number = gate_number
            break

        if may_enter:
            if len(fans) == 1:
                pid = os.fork()
                if pid == 0:
                    fan_process(fans[0], picked_gate_number)
                    os._exit(0)
                allocated_PIDs.append(pid)

            if len(fans) == 2:
                adult_finished_check = Event()
                adult_finished_check.clear()
                adult_check_result = Value('i', 0)
                pid = os.fork()
                if pid == 0:
                    fan_process(fans[1], picked_gate_number, adult_finished_check, adult_check_result)
                    os._exit(0)
                allocated_PIDs.append(pid)

                pid = os.fork()
                if pid == 0:
                    fan_process(fans[0], picked_gate_number, adult_finished_check, adult_check_result)
                    os._exit(0)
                allocated_PIDs.append(pid)

            for fan in list(standard_queue):
                if fan.index < fans[0].index:
                    fan.increment_postponed_qty()
                elif fan.index in last_picked_fan_indexes:
                    standard_queue.remove(fan)
                else:
                    break

        time.sleep(0.2)


def pick_next_fans(standard_queue, last_picked_fan_indexes):
    picked_fans = []
    for fan in standard_queue:
        if fan.postpone_qty == 5:
            if fan.is_adult():
                picked_fans.append(fan)
                return picked_fans
            else:
                picked_fans.append(fan)
        else:
            if fan.index not in last_picked_fan_indexes:
                if fan.is_adult():
                    picked_fans.append(fan)
                    return picked_fans
                else:
                    picked_fans.append(fan)

    return picked_fans
