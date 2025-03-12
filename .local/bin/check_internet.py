#!/usr/bin/env python3
import socket
from subprocess import run

DONE = "✅"
WARN = "⚠️"
NOTIFY = True


def shell(command: str) -> None:
    run(command, shell=True)


def check_internet(host="8.8.8.8", port=53, timeout=3) -> bool:
    try:
        socket.setdefaulttimeout(timeout)
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect((host, port))
        return True
    except socket.error:
        return False


if __name__ == "__main__":
    if check_internet():
        print(f"{DONE} Internet is connected!")
        if NOTIFY:
            shell(f"notify-send '{DONE} Internet is connected!'")
    else:
        print(f"{WARN} No internet connection!")
        if NOTIFY:
            shell(f"notify-send '{WARN} No internet connection!'")
