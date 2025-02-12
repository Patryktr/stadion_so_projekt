from time import sleep

from Logger import log
from config import fans_on_stadium_counter, \
    end_match_event


def vip_fan_process(i):
    log(f"VIP Fan {i} enter stadium without security check.")
    with fans_on_stadium_counter.get_lock():
        fans_on_stadium_counter.value += 1
    end_match_event.wait()
    sleep(1)

    with fans_on_stadium_counter.get_lock():
        fans_on_stadium_counter.value -= 1
        log(f"VIP Fan {i} left stadium. There are  {fans_on_stadium_counter.value} fans left on the stadium.")

    return
