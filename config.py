from enum import Enum
from multiprocessing import Value, Event
import random

STADIUM_CAPACITY = 10
VIP_PROBABILITY = 0.05
GATES_QTY = 3
MAX_FANS_IN_GATE = 3
ADULT_AGE = 15

team_in_gate = [Value('i', 0) for _ in range(GATES_QTY)]  # 0 means no team, 1 team A, 2 team B
fans_in_gate = [Value('i', 0) for _ in range(GATES_QTY)]  # Fans qty on gates



security_check_event = Event()
end_match_event = Event()
stadium_is_full = Event()
fans_on_stadium_counter = Value('i', 0)


class FanType(Enum):
    VIP = "VIP"
    STANDARD = "STANDARD"


class Fan:
    def __init__(self, index, age, team, with_child, fan_type):
        self.index = index
        self.age = age
        self.team = team
        self.with_child = with_child
        self.postpone_qty = 0
        self.fan_type = fan_type



    def increment_postponed_qty(self):
        self.postpone_qty += 1

    def is_adult(self):
        return self.age > ADULT_AGE

    def is_with_child(self):
        return self.with_child

    def has_no_weapon(self):
        return random.random() >= 0.1
