import os
import random
import time
from time import sleep

from Logger import log
from config import team_in_gate, fans_in_gate, fans_on_stadium_counter, \
    end_match_event, STADIUM_CAPACITY, stadium_is_full


def security_check_process(adult_fan, gate_number, adult_finished_check=None, adult_check_result=None):
    time.sleep(random.uniform(2, 3))
    fan_qty = 2 if adult_fan.with_child else 1

    with fans_in_gate[gate_number].get_lock():
        fans_in_gate[gate_number].value -= fan_qty
    if fans_in_gate[gate_number].value == 0:
        team_in_gate[gate_number].value = 0

    if adult_fan.has_no_weapon():
        with fans_on_stadium_counter.get_lock():
            if fans_on_stadium_counter.value + fan_qty <= STADIUM_CAPACITY:
                fans_on_stadium_counter.value += fan_qty
                adult_check_result.value = 1
                adult_finished_check.set()
                return
            else:
                stadium_is_full.set()
                adult_check_result.value = -1
                adult_finished_check.set()
                return
    else:
        log(f"Fan {adult_fan.index} from team {adult_fan.team} was rejected on security gate.")
        adult_check_result.value = -2
        adult_finished_check.set()
        return