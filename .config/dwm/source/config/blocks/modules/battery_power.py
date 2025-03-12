#!/usr/bin/env python3

# battery_power.py
# https://github.com/maarutan
# Copyright (c) 2025 |  by maaru \ maarutan

import os, subprocess, sys
from time import sleep

# DONE: ####   -----=== global variables ===-----   ####

DEBUG = False  # if debug True no write in current file
DELAY_TIME = 1  # delay time in seconds to check battery
THEME_TYPE = "forward"  # lay, forward, none,
CHARGING_THEME_TYPE = "forward"  # refuel, forward, tylda
SPACE = 1  # space between icon and percent
DYNAMIC_FIND_BATTERY = (
    True  # if dynamic find battery is false you need to set the battery manually
)
BATTERY_PATH = "/sys/class/power_supply/BAT0"  # only if dynamic find battery is false


CURRENT_FILE = os.path.abspath(
    os.path.join(
        os.path.dirname(__file__),
        "..",
        "current_blocks",
        "current_battery",
    )
)

# INFO: ####   -----=== logic ===-----   ####


def main():
    while True:
        try:
            if DEBUG:
                sleep(DELAY_TIME)
                os.system("clear")
                print(
                    f"status  =   {get_battery_status()},\npercent =   {get_battery_percent()},\nicon    =   {dynamic_icon()} \n\n"
                )
            else:
                write_battery_info()
                sleep(DELAY_TIME)
        except KeyboardInterrupt:
            print("\n  cancel <3")
            sys.exit(0)


def shell(command) -> str | None:
    blacklist = [
        "poweroff",
        "reboot",
        "rm",
        "shutdown",
    ]
    if command.split()[0] in blacklist:
        return print(f"skipping: {command}")
    else:
        return subprocess.run(
            command, shell=True, text=True, capture_output=True
        ).stdout.strip()


def get_battery_path() -> str | None:
    if DYNAMIC_FIND_BATTERY:
        power_supply_path = "/sys/class/power_supply/"
        for entry in os.listdir(power_supply_path):
            if entry.startswith("BAT"):
                return os.path.join(power_supply_path, entry)
        return "Battery not found"
    else:
        return BATTERY_PATH


def get_battery_status():
    battery_path = get_battery_path()
    if battery_path:
        try:
            with open(os.path.join(battery_path, "status"), "r") as f:
                status = f.read().strip().lower()
                return status
        except FileNotFoundError:
            return "Battery not found"
    else:
        return "Battery not found"


def get_battery_percent() -> str:
    battery_path = get_battery_path()
    if battery_path:
        try:
            with open(os.path.join(battery_path, "capacity"), "r") as f:
                percent = f.read().strip()
                return percent
        except FileNotFoundError:
            return "Battery not found"
    else:
        return "Battery not found"


def formatting_word(a, length=4) -> str:
    return f"{a}%".center(length)


def dynamic_icon() -> str:
    status = get_battery_status()
    percent = int(get_battery_percent())
    THEME_TYPE.lower()

    if status == "charging" and CHARGING_THEME_TYPE == "refuel":
        icon = ""
    elif status and "not charging" and CHARGING_THEME_TYPE == "refuel":
        icon = ""
    elif (
        status == "charging" or status == "full" or status == "not charging"
    ) and CHARGING_THEME_TYPE == "forward":
        if status == "full":
            icon = "󰂅"
        elif percent >= 90 and "charging" in status:
            icon = "󰂋"
        elif percent >= 80 and "charging" in status:
            icon = "󰂊"
        elif percent >= 70 and "charging" in status:
            icon = "󰢞"
        elif percent >= 60 and "charging" in status:
            icon = "󰂉"
        elif percent >= 50 and "charging" in status:
            icon = "󰢝"
        elif percent >= 40 and "charging" in status:
            icon = "󰂈"
        elif percent >= 30 and "charging" in status:
            icon = "󰂇"
        elif percent >= 20 and "charging" in status:
            icon = "󰂆"
        elif percent >= 10 and "charging" in status:
            icon = "󰢜"
        elif percent < 10 and "charging" in status:
            icon = "󰢟"
    elif (
        status == "charging"
        and CHARGING_THEME_TYPE == "tylda"
        or status == "not charging"
    ):
        icon = "~"
    else:
        icon = "~"

    if status == "discharging" and THEME_TYPE == "lay":
        if percent > 99 and status == "discharging":
            icon = ""
        elif percent >= 80 and status == "discharging":
            icon = ""
        elif percent >= 60 and status == "discharging":
            icon = ""
        elif percent >= 40 and status == "discharging":
            icon = ""
        elif percent >= 20 and status == "discharging":
            icon = ""
        elif percent < 20 and status == "discharging":
            icon = ""
    elif status == "discharging" and THEME_TYPE == "forward":
        if percent > 99 and status == "discharging":
            icon = "󰁹"
        elif percent >= 90 and status == "discharging":
            icon = "󰂂"
        elif percent >= 80 and status == "discharging":
            icon = "󰂁"
        elif percent >= 70 and status == "discharging":
            icon = "󰂀"
        elif percent >= 60 and status == "discharging":
            icon = "󰁿"
        elif percent >= 50 and status == "discharging":
            icon = "󰁾"
        elif percent >= 40 and status == "discharging":
            icon = "󰁽"
        elif percent >= 30 and status == "discharging":
            icon = "󰁼"
        elif percent >= 20 and status == "discharging":
            icon = "󰁻"
        elif percent < 20 and status == "discharging":
            icon = "󰁺"
    elif status == "discharging" and THEME_TYPE == "none":
        icon = " "

    return icon  # pyright: ignore


def get_battery_info():
    percent = formatting_word(get_battery_percent())
    icon = dynamic_icon()
    return f"{icon}{' ' * SPACE}{percent}"


def write_battery_info() -> int | None:
    if get_battery_info() is None:
        return
    else:
        with open(CURRENT_FILE, "w") as f:
            return f.write(get_battery_info())


if __name__ == "__main__":
    main()
