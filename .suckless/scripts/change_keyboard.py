#!/usr/bin/env python3

# changeKeyboard.py
# github: https://github.com/maarutan
# (c) by maaru.tan

import os, subprocess
import time

# DONE: ####   -----=== global variables ===-----   ####

HOME = os.getenv("HOME")
ICON_PATH = f"{HOME}/.icons/myIcons/language.svg"
COMMAND = lambda lang: f"dunstify -r 9999 -i {ICON_PATH} '{lang}'"
DWMBLCOKS_PREVIEW = lambda: shell(
    "$HOME/.config/dwm/source/config/blocks/core/dwmblocks.py -s 1"
)
PADDING = [7, 0]  # padding_left { content } padding_right
NOTIFY = True

# change view content
# if us change in English and more
change_layout_output = {
    "us": "English",
    "ru": "Russian",
}


# INFO: ####   -----=== logic ===-----   ####


def main():
    changeKeyboard()


def padding_word(icons):
    left_pad, right_pad = PADDING
    return " " * left_pad + icons + " " * right_pad


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


def check_xkb_switch() -> bool:
    return bool(shell("command -v xkb-switch"))


def changeKeyboard() -> None:
    if not check_xkb_switch():
        print("xkb-switch not found")
        return

    shell("xkb-switch -n")

    lang = shell("xkb-switch -p")
    if not lang:
        print("Failed to detect keyboard layout")
        return

    lang = change_layout_output.get(lang, lang)

    if NOTIFY:
        shell(COMMAND(padding_word(lang)))
    else:
        print(COMMAND(padding_word(lang)))

    time.sleep(0.1)
    DWMBLCOKS_PREVIEW()


if __name__ == "__main__":
    main()
