#!/usr/bin/env python3

# network_speed.py
# https://github.com/maarutan
# Copyright (c) 2025 |  by maaru \ maarutan

import os, subprocess, sys
from time import sleep


# DONE: ####   -----=== global variables ===-----   ####

SHOW = "set"  # get, set, all
ICON = False  # True, False
IF_ONLY_ONE = True  # if you choise only get or set icon will be this
DEBUG = False  # show print no write current
DELAY_TIME = 1  # for while in seconds
SPACE = 2  # space between icon and speed

# --- icons ---
IF_ONLY_ONE_ICON = ""
ICON_GET = ""
ICON_SET = ""

CURRENT_FILE = os.path.abspath(
    os.path.join(
        os.path.dirname(__file__), "..", "current_blocks", "current_inet_speed"
    )
)

# INFO: ####   -----=== logic ===-----   ####


def main():
    while True:
        try:
            speed = get_speed()
            if DEBUG:
                print(speed)
            with open(CURRENT_FILE, "w") as f:
                f.write(speed)
            sleep(DELAY_TIME)
        except KeyboardInterrupt:
            print("\n  cancel <3")
            sys.exit(0)


def shell(command) -> str:
    blacklist = {"poweroff", "reboot", "rm", "shutdown"}
    cmd = command.split()[0]

    if cmd in blacklist:
        return ""

    return subprocess.run(
        command, shell=True, text=True, capture_output=True
    ).stdout.strip()


def get_active_interface() -> str | None:
    for net in os.listdir("/sys/class/net"):
        state_path = f"/sys/class/net/{net}/operstate"
        if os.path.isfile(state_path):
            with open(state_path, "r") as f:
                if f.read().strip() == "up":
                    return net

    return shell("ip route show | awk '/^default/ {print $5}'") or None


def get_bytes() -> tuple[int, int]:
    interface = get_active_interface()
    if not interface:
        return 0, 0

    try:
        with open(f"/sys/class/net/{interface}/statistics/rx_bytes") as f:
            rx = int(f.read().strip())
        with open(f"/sys/class/net/{interface}/statistics/tx_bytes") as f:
            tx = int(f.read().strip())
        return rx, tx
    except FileNotFoundError:
        return 0, 0


def format_bytes(size: int, width: int = 9) -> str:
    units = ["B", "KB", "MB", "GB", "TB"]
    factor = 1024

    for unit in units:
        if size < factor:
            formatted = f"{size:.2f} {unit}"
            return format_word(formatted, width)
        size /= factor  # type: ignore

    return format_word(f"{size:.2f} PB", width)


def format_word(a: str, length: int = 9) -> str:
    a = str(a).strip()
    a = a[:length] if len(a) > length else a
    return f"{a:<{length}}"


def get_speed() -> str:
    rx_before, tx_before = get_bytes()
    sleep(1)
    rx_after, tx_after = get_bytes()

    rx_speed = format_bytes(rx_after - rx_before)
    tx_speed = format_bytes(tx_after - tx_before)

    if SHOW == "get":
        icon = IF_ONLY_ONE_ICON if IF_ONLY_ONE else ICON_GET
        return format_word(f"{icon}{' ' * SPACE}{rx_speed}" if ICON else rx_speed)

    elif SHOW == "set":
        icon = IF_ONLY_ONE_ICON if IF_ONLY_ONE else ICON_SET
        return format_word(f"{icon}{' ' * SPACE}{tx_speed}" if ICON else tx_speed)

    elif SHOW == "all":
        return (
            f"{ICON_GET} {rx_speed} / {ICON_SET} {tx_speed}"
            if ICON
            else f"{rx_speed} / {tx_speed}"
        )

    return "   0 B   "


if __name__ == "__main__":
    main()
