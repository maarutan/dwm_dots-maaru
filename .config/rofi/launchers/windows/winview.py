#!/usr/bin/env python3
# ██████╗  ██████╗ ███████╗██╗
# ██╔══██╗██╔═══██╗██╔════╝██║
# ██████╔╝██║   ██║█████╗  ██║
# ██╔══██╗██║   ██║██╔══╝  ██║
# ██║  ██║╚██████╔╝██║     ██║
# ╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚═╝
# ============================
#
#
config = "windows_view"
mode = "-show window"
#
#
#
# =====================
from subprocess import run
import os

dir = os.path.dirname(os.path.realpath(__file__))


def main():
    shell(f"""rofi \
                 {mode} \
                 -theme {dir}/{config}.rasi 
                 """)


def shell(command):
    return run(command, shell=True, capture_output=True, text=True)


if __name__ == "__main__":
    main()
