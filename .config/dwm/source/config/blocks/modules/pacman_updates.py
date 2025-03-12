#!/usr/bin/env python3

# paccman_updates.py
# https://github.com/maarutan
# Copyright (c) 2025 |  by maaru \ maarutan

import subprocess, os
from time import sleep

# DONE: ####   -----=== global variables ===-----   ####

WARN_ICON = "⚠️"
INFO_ICON = "❕"

DELAY_TIME = 5
NOTIFY = 1
START = 1
DEBUG = 0

YELLOW = "\033[33m"
RESET = "\033[0m"
PURPLE = "\033[35m"

CURRENT_FILE = os.path.abspath(
    os.path.join(
        os.path.dirname(__file__),
        "..",
        "current_blocks",
        "current_updates",
    )
)

# INFO: ####   -----=== logic ===-----   ####


def main():
    try:
        validate_start()
        while True:
            update = str(get_check_pacman())
            if DEBUG:
                print(f"Total updates: {YELLOW}{update}{RESET}")

            if START and os.path.exists(CURRENT_FILE) and check_inside(int(update)):
                with open(CURRENT_FILE, "w") as f:
                    f.write(format_string(update))
                    print("\n", YELLOW, f"Total updates: {update}", RESET)
                    print("write to current file")
            sleep(DELAY_TIME)
    except KeyboardInterrupt:
        print(f"\n {PURPLE}cancel{PURPLE}")


def validate_start():
    if not os.path.exists(CURRENT_FILE):
        with open(CURRENT_FILE, "w") as f:
            f.write("0")


def current_inside_info() -> str:
    try:
        with open(CURRENT_FILE, "r") as f:
            content = f.read().strip()
            return content if content else "0"
    except FileNotFoundError:
        return "0"


def check_inside(paccman: int) -> bool:
    carr_ins = current_inside_info()
    try:
        return paccman != int(carr_ins)
    except ValueError:
        return True


def shell(command) -> str:
    return subprocess.getoutput(command).strip()


def format_string(a, length=3) -> str:
    return a.center(length)


def get_check_pacman() -> int:
    if not shell("command -v checkupdates"):
        if DEBUG:
            print("checkupdates not found")
            print("▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁")
            print("yay -S checkupdates-systemd-git")
            print("\n or other AUR Helper")
            return 0
        elif NOTIFY:
            shell(
                f'notify-send -u critical  "{WARN_ICON} checkupdates not found";'
                f'notify-send -u critical  "{INFO_ICON} yay -S checkupdates-systemd-git";'
                f'notify-send -u critical  "{INFO_ICON} or other AUR Helper";'
            )
            return 0
        else:
            return 0

    attempt = 0
    while attempt < 5:
        result = shell("checkupdates | wc -l")
        if "ERROR: Cannot fetch updates" in result:
            attempt += 1
            if attempt == 5:
                print(YELLOW, f"{WARN_ICON} Pacman could not update", YELLOW)
        else:
            return int(result) if result.isdigit() else 0
    exit(1)


if __name__ == "__main__":
    main()
