import os
import random
import time
from time import sleep

from Logger import log
from config import team_in_gate, fans_in_gate, fans_on_stadium_counter, \
    end_match_event, STADIUM_CAPACITY, stadium_is_full


def fan_process(fan, adult_finished_check, adult_check_result):
    adult_finished_check.wait()

    if adult_check_result.value == -1:
        log(f"There is no space left on the stadium for fan {fan.index}")
        return
    elif adult_check_result.value == -2:
        if fan.is_adult():
            log(f"Adult {fan.index} was rejected on security gate")
        else:
            log(f"Adult was rejected on security gate, child {fan.index} cannot enter too ")
        return
    else:
        if fan.is_adult():
            log(f"Adult {fan.index} from team {fan.team} entered in the stadium.")
        else:
            log(f"Child fan {fan.index} from team {fan.team} entered in the stadium.")

    end_match_event.wait()
    sleep(1)


    with fans_on_stadium_counter.get_lock():
        fans_on_stadium_counter.value -= 1
        log(f"Fan {fan.index} left stadium. There are {fans_on_stadium_counter.value} fans left on the stadium.")
    return
