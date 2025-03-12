#!/usr/bin/env python3

# toggle_touchpad.py
# github: https://github.com/maarutan
# (c) by maaru.tan

import subprocess, os, sys

# DONE: ####   -----=== global variables ===-----   ####

TITLE_CONTENT = "touchpad"
TMP_FILE = "/tmp/touchpad_tmp_config"


# INFO: ####   -----=== logic ===-----   ####


def main(): ...


def shell(command) -> None | str:
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
        ).stdout


def notify_send(message: str = "", WARN: bool = False, INFO: bool = False):
    args = {WARN: "️⚠️", INFO: "❕"}
    title = args[INFO] if args[WARN] else args[INFO]
    shell(f'notify-send --icon="{title}""{message}"')


def find_touchpad_id() -> str | None:
    shell("xinput list | grep -i \"Touchpad\" | awk '{print $6}' | sed 's/id=//'")


def read_tmpl_file():
    with open(TMP_FILE, "r") as f:
        f.read()


def check_if_exist() -> str | None:
    read_file = read_tmpl_file()
    if read_file:
        TOUCHPAD_ID = read_file
        return TOUCHPAD_ID
    TOUCHPAD_ID = find_touchpad_id()
    if not TOUCHPAD_ID:
        sys.exit(1)


# print(check_if_exist())
notify_send("hello", WARN=True)

# if __name__ == "__main__":
#     main()
