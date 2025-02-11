from config import security_check_event, end_match_event

def stadium_worker(read_fd):
    try:
        while True:
            command = read_fd.recv()
            if command:
                if command == "sygnał1":
                    # Obsługa sygnału 1
                    print("Otrzymano sygnał 1")
                    security_check_event.clear()
                elif command == "sygnał2":
                    # Obsługa sygnału 2
                    print("Otrzymano sygnał 2")
                    security_check_event.set()
                elif command == "sygnał3":
                    # Obsługa sygnału 3 i zakończenie pracy
                    print("Otrzymano sygnał 3, zakończenie pracy")
                    end_match_event.set()
                    break
                else:
                    print(f"Nieznane polecenie: {command}")
    except OSError as e:
        print(f"Błąd podczas odczytu z rury: {e}")


