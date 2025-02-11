import os
import random
import time
from time import sleep

from Logger import log
from config import team_in_gate, fans_in_gate, fans_on_stadium_counter, \
    end_match_event, STADIUM_CAPACITY, stadium_is_full


def fan_process(fan, gate_number, adult_finished_check=None, adult_check_result=None):
    time.sleep(random.uniform(2, 3))

    fan_qty = 2 if fan.with_child else 1



    if fan.is_adult():
        with fans_in_gate[gate_number].get_lock():
            fans_in_gate[gate_number].value -= fan_qty
        if fans_in_gate[gate_number].value == 0:
            team_in_gate[gate_number].value = 0

        if random.random() >= 0.1:
            with fans_on_stadium_counter.get_lock():
                if fans_on_stadium_counter.value + fan_qty <= STADIUM_CAPACITY:
                    fans_on_stadium_counter.value += fan_qty
                    log(f"Fan {fan.index} from team {fan.team} entered in the stadium.")
                    if fan.with_child:
                        adult_check_result.value = 1
                        adult_finished_check.set()
                else:
                    log(f"There is no space left on the stadium for fan {fan.index}")
                    stadium_is_full.set()
                    if fan.with_child:
                        adult_check_result.value = -1
                        adult_finished_check.set()
                    return
        else:
            log(f"Fan {fan.index} from team {fan.team} was rejected on security gate.")
            if fan.with_child:
                adult_check_result.value = -2
                adult_finished_check.set()
            return
    else:
        adult_finished_check.wait()
        if adult_check_result.value == -1:
            log(f"There is no space left on the stadium for fan {fan.index}")
            return
        elif adult_check_result.value == -2:
            log(f"Adult was rejected on security gate, child {fan.index} cannot enter too ")
            return
        else:
            log(f"Child fan {fan.index} from team {fan.team} entered in the stadium.")

    end_match_event.wait()
    sleep(1)

    with fans_on_stadium_counter.get_lock():
        fans_on_stadium_counter.value -= 1
        log(f"Fan {fan.index} left stadium. There are {fans_on_stadium_counter.value} fans left on the stadium.")
    return
