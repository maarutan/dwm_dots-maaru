#!/usr/bin/env python3

# current_language.py with help xkb-switch
# https://github.com/maarutan
# Copyright (c) 2025 |  by maaru \ maarutan

import os, subprocess, pathlib
from time import sleep

# DONE: ####   -----=== global variables ===-----   ####

DEBUG = False  # show print no write current
DELAY_TIME = 1  # while True delay time


PADDING = [0, 2]  # padding_left { icon } padding_right
WIFI_ICON = "round"  # round, square, number, triangle
NOT_CONNECTED_ICON = "󰌙"
CURRENT_FILE = (
    pathlib.Path(__file__).resolve().parent.parent
    / "current_blocks"
    / "current_signal_network"
)
CACHE_FILE = os.getenv("HOME") + "/.cache/current_signal_network_icon"  # type: ignore

# INFO: ####   -----=== logic ===-----   ####


def main():
    try:
        if DEBUG:
            print()
            print(f"ethernet_no_internet: {is_ethernet_no_connected()}")
            print(f"wifi_no_internet: {is_wifi_connected_no_internet()}")
            print()
            print(f"signal: {get_signal()}")
            print(f"icon: {icons()}")
            print(f"icon_theme: {WIFI_ICON}")
            print()
            print(f"current file: {CURRENT_FILE}")
        else:
            while read_current_file() == "":
                with open(CURRENT_FILE, "w") as f:
                    f.write(read_cache_file())
            while True:
                write_icon()
                sleep(DELAY_TIME)
    except KeyboardInterrupt:
        print("\n  cancel <3")


def write_icon():
    icon = str(padding_icons(icons()))

    with open(CURRENT_FILE, "w") as f:
        f.write(icon)

    if read_cache_file() != "":
        with open(CACHE_FILE, "w") as x:
            x.write(icon)


def padding_icons(icons):
    left_pad, right_pad = PADDING
    return " " * left_pad + icons + " " * right_pad


def read_cache_file() -> str:
    with open(CACHE_FILE, "r") as f:
        return f.read().strip()


def read_current_file() -> str:
    with open(CURRENT_FILE, "r") as f:
        return f.read().strip()


def shell(command) -> str:
    blacklist = {"poweroff", "reboot", "rm", "shutdown"}
    cmd = command.split()[0]

    if cmd in blacklist:
        return ""

    return subprocess.run(
        command, shell=True, text=True, capture_output=True
    ).stdout.strip()


def check_network_manager() -> str:
    if shell("command -v nmcli"):
        return ""
    else:
        return "nmcli not found"


def get_check_connected():
    if shell("nmcli -t -f DEVICE,TYPE,STATE dev | grep 'ethernet:connected'"):
        return "ethernet"
    if shell("nmcli -t -f DEVICE,TYPE,STATE dev | grep 'wifi:connected'"):
        return "wifi"
    return "no_connection"


def get_check_connected_no_internet():
    if is_ethernet_no_connected():
        return "ethernet_no_internet"
    if is_wifi_connected_no_internet():
        return "wifi_no_internet"
    return "no_connection"


def get_signal() -> int:
    connection_type = get_check_connected()
    if connection_type != "wifi" or connection_type == "no_connection":
        return 0  # если Wi-Fi не подключен, вернуть 0
    result = shell(
        "nmcli -t -f IN-USE,SIGNAL dev wifi | grep '*' | awk -F: '{print $2}'"
    )
    return int(result)


def is_ethernet_no_connected() -> bool:
    connection_type = get_check_connected()
    if connection_type != "ethernet":
        return True

    ip_check = shell("nmcli -t -f DEVICE,STATE,IP4 dev show | grep ethernet")

    if ip_check and "connected" in ip_check and "IP4.ADDRESS" not in ip_check:
        return True

    return False


def is_wifi_connected_no_internet() -> bool:
    connection_type = get_check_connected()
    if connection_type != "wifi":
        return False

    ip_check = shell("nmcli -t -f DEVICE,STATE,IP4 dev show | grep wifi")
    if "connected" in ip_check and "IP4.ADDRESS" not in ip_check:
        return True

    internet_check = shell("ping -c 1 8.8.8.8")
    if "1 packets transmitted, 1 received" not in internet_check:
        return True
    return False


def icons():
    signal = get_signal()
    connection_type = get_check_connected()
    connection_type_no_internet = get_check_connected_no_internet()

    rounded_wifi = {
        65: "󰤨",
        55: "󰤥",
        40: "󰤢",
        20: "󰤟",
        10: "󰤯",
        "no connection": "󰤮",
    }
    rounded_wifi_no_internet = {
        65: "󰤩",
        55: "󰤦",
        40: "󰤣",
        20: "󰤠",
        10: "󰤠",
        "no connection": "󰤮",
    }

    square_wifi = {
        65: "▁▃▅▇",
        55: "▁▃▅⎽",
        40: "▁▃⎽⎽",
        20: "▁⎽⎽⎽",
        10: "⎽⎽⎽⎽",
        "no connection": "No connection",
    }

    number_wifi = f"wifi: {signal}%"
    number_wifi_no_internet = f"wifi: {str(signal)}%!"

    square_wifi_no_internet = {
        65: "▁▃▅▇!",
        55: "▁▃▅⎽!",
        40: "▁▃⎽⎽!",
        20: "▁⎽⎽⎽!",
        10: "⎽⎽⎽⎽!",
        "no connection": "No connection",
    }

    triangle_wifi = {
        65: "󰣺",
        55: "󰣸",
        40: "󰣶",
        20: "󰣴",
        10: "󰣾",
        "no connection": "󰣽",
    }
    triangle_wifi_no_internet = {
        65: "󰣻",
        55: "󰣹",
        40: "󰣷",
        20: "󰣵",
        10: "󰣵",
        "no connection": "󰣽",
    }

    ethernet = {
        "ethernet": "󰈀",
        "no connection": "󱘖",
    }

    ethernet_no_internet = {
        "ethernet": "󰈀!",
        "no connection": "󱘖",
    }

    if connection_type == "wifi":
        if signal:
            if connection_type_no_internet != "wifi_no_internet":
                if WIFI_ICON == "round":
                    return next(
                        (
                            icon
                            for level, icon in sorted(
                                {
                                    k: v
                                    for k, v in rounded_wifi.items()
                                    if isinstance(k, int)
                                }.items(),
                                reverse=True,
                            )
                            if signal >= level
                        ),
                        rounded_wifi["no connection"],
                    )
                elif WIFI_ICON == "square":
                    return next(
                        (
                            icon
                            for level, icon in sorted(
                                {
                                    k: v
                                    for k, v in square_wifi.items()
                                    if isinstance(k, int)
                                }.items(),
                                reverse=True,
                            )
                            if signal >= level
                        ),
                        square_wifi["no connection"],
                    )
                elif WIFI_ICON == "triangle":
                    return next(
                        (
                            icon
                            for level, icon in sorted(
                                {
                                    k: v
                                    for k, v in triangle_wifi.items()
                                    if isinstance(k, int)
                                }.items(),
                                reverse=True,
                            )
                            if signal >= level
                        ),
                        triangle_wifi["no connection"],
                    )
                elif WIFI_ICON == "number":
                    return number_wifi

            elif connection_type_no_internet == "wifi_no_internet":
                if WIFI_ICON == "round":
                    return next(
                        (
                            icon
                            for level, icon in sorted(
                                {
                                    k: v
                                    for k, v in rounded_wifi_no_internet.items()
                                    if isinstance(k, int)
                                }.items(),
                                reverse=True,
                            )
                            if signal >= level
                        ),
                        rounded_wifi_no_internet["no connection"],
                    )
                elif WIFI_ICON == "square":
                    return next(
                        (
                            icon
                            for level, icon in sorted(
                                {
                                    k: v
                                    for k, v in square_wifi_no_internet.items()
                                    if isinstance(k, int)
                                }.items(),
                                reverse=True,
                            )
                            if signal >= level
                        ),
                        rounded_wifi_no_internet["no connection"],
                    )
                elif WIFI_ICON == "triangle":
                    return next(
                        (
                            icon
                            for level, icon in sorted(
                                {
                                    k: v
                                    for k, v in triangle_wifi_no_internet.items()
                                    if isinstance(k, int)
                                }.items(),
                                reverse=True,
                            )
                            if signal >= level
                        ),
                        rounded_wifi_no_internet["no connection"],
                    )
                elif WIFI_ICON == "number":
                    return number_wifi_no_internet

            elif connection_type_no_internet == "ethernet":
                return ethernet_no_internet["ethernet"]
            return NOT_CONNECTED_ICON
    elif connection_type == "ethernet":
        return ethernet["ethernet"]

    return ethernet["no connection"]


if __name__ == "__main__":
    main()
