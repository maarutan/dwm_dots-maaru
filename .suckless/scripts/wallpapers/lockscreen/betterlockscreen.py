#!/usr/bin/env python3

import os
import argparse
import subprocess

HOME = os.getenv("HOME")
CURRENT_WALL = f"{HOME}/.cache/current_wallpaper"


def arguments():
    parser = argparse.ArgumentParser(description="Usage: --generate (-g), --start (-s)")

    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument(
        "-g", "--generate", action="store_true", help="Create blur image"
    )
    group.add_argument("-s", "--start", action="store_true", help="Start lockscreen")

    args = parser.parse_args()

    if args.generate:
        generate_lock_wall()
    elif args.start:
        start()


def shell(command):
    subprocess.call(command, shell=True)


def get_wall_path():
    if not os.path.exists(CURRENT_WALL):
        print("invalid: no current wallpaper")
        exit(1)
    with open(CURRENT_WALL, "r") as f:
        return f.read().strip()


def generate_lock_wall():
    shell(f"betterlockscreen -u {get_wall_path()}")


def start():
    shell("betterlockscreen -l blur")


if __name__ == "__main__":
    arguments()
