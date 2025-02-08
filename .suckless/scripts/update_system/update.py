#!/usr/bin/env python3
# =====================#
#  .--.
# / _.-' .-.   .-.  .-.
# \  '-. '-'   '-'  '-'
#  '--'
# =====================#
# by: https://github.com/maarutan/
# 2025-02-05 (c)
# =====================#

# ui
NOTIFY = True
FETCH = True


# packages
PACMAN = True
YAY = True
PARU = False
FLATPAK = False


# ======#
# logic #
# ======#


import os
import subprocess
from fetch import fetch

RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
CYAN = "\033[36m"
RESET = "\033[0m"
PURPLE = "\033[35m"


def main():
    if FETCH:
        fetch()


def shell(command):
    return subprocess.getoutput(command)


def check_font():
    font_list = [
        "Nerd",
        "NerdFont",
        "Nerd Font",
        "nerd font",
        "nerdfont",
        "nerd",
    ]

    font_info = shell("fc-list :family")

    if any(font in font_info for font in font_list):
        # print("\n".join(f for f in font_list if f in font_info))
        return True
    else:
        print("\n\nNerd Font not found")
        print("Install it from https://www.nerdfonts.com")
        print("-" * 30)
        print(f"{GREEN}sudo pacman -S ttf-nerd-fonts-symbols{GREEN}\n\n")


if __name__ == "__main__":
    if check_font():
        main()
