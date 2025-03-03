import os
import signal
from config import security_check_event, end_match_event


def handle_signal(signum, frame):
    if signum == signal.SIGUSR1:
        print("Received SIGUSR1 (sygnał1), clearing security check event.")
        security_check_event.clear()
    elif signum == signal.SIGUSR2:
        print("Received SIGUSR2 (sygnał2), setting security check event.")
        security_check_event.set()
    elif signum == signal.SIGTERM:
        print("Received SIGTERM (sygnał3), terminating work.")
        end_match_event.set()
        print("End match event has been set. Exiting...")
        os._exit(0)


def stadium_worker():
    signal.signal(signal.SIGUSR1, handle_signal)
    signal.signal(signal.SIGUSR2, handle_signal)
    signal.signal(signal.SIGTERM, handle_signal)

    print(f"Worker process {os.getpid()} is waiting for signals...")
    while not end_match_event.is_set():
        signal.pause()  # Wait for a signal

    print("Worker process exiting...")