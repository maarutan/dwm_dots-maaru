#!/usr/bin/env python3

import os
import subprocess
from time import sleep

HOME = os.environ["HOME"]  # /home/user

ROFI_THEME = os.path.join(HOME, ".config/rofi/launchers/clipboard/clipboard.rasi")


HOME_PICOM_DIR = os.path.join(HOME, ".config/picom")  # /home/user/.config/picom
CURRENT_CONFIG = os.path.join(HOME_PICOM_DIR, ".current_config")
HPD = HOME_PICOM_DIR  # picom directory
LHPD = [
    i for i in os.listdir(HPD) if os.path.isdir(os.path.join(HPD, i))
]  # list picom directories


def rofi() -> str | None:
    result = subprocess.run(
        ["rofi", "-theme", ROFI_THEME, "-dmenu", "-p", "Select picom dir"],
        input="\n".join(LHPD),
        text=True,
        capture_output=True,
    )
    return result.stdout.strip() if result.stdout else print("exit")


def picom_config() -> str:
    i = rofi()
    PICKED_ROFI = os.path.join(HPD, i)  # pyright: ignore
    LISTDIR = os.listdir(PICKED_ROFI)
    result = subprocess.run(
        ["rofi", "-theme", ROFI_THEME, "-dmenu", "-p", "Select picom config"],
        input="\n".join(LISTDIR),
        text=True,
        capture_output=True,
    )
    return os.path.join(PICKED_ROFI, result.stdout.strip())


def write_current_config():
    with open(CURRENT_CONFIG, "w") as f:
        f.write(picom_config())


def read_current_config() -> str:
    with open(CURRENT_CONFIG, "r") as f:
        return f.read().strip()


def restart_picom():
    subprocess.run(["pkill", "-x", "picom"])
    sleep(0.3)
    subprocess.Popen(
        ["setsid", "picom", "--config", read_current_config()],
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )


def main():
    try:
        write_current_config()
    except:
        print("not write in your config in current config ")

    try:
        restart_picom()
    except:
        print("picom is not restart")


if __name__ == "__main__":
    main()
