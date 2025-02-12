from config import security_check_event, end_match_event


def stadium_worker(read_fd):
    try:
        while True:
            command = read_fd.readline().strip()
            if command:
                if command == "sygnał1":
                    # Handling signal 1
                    print("Received signal 1")
                    security_check_event.clear()
                elif command == "sygnał2":
                    # Handling signal 2
                    print("Received signal 2")
                    security_check_event.set()
                elif command == "sygnał3":
                    # Handling signal 3 and terminating work
                    print("Received signal 3, terminating work")
                    end_match_event.set()
                    print("End match event has been set")
                    break
                else:
                    print(f"Unknown command: {command}")
    except OSError as e:
        print(f"Error while reading from pipe: {e}")
