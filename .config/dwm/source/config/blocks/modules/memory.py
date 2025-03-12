#!/usr/bin/env python3

# memory.py
# https://github.com/maarutan
# Copyright (c) 2025 |  by maaru \ maarutan

import subprocess
import sys
from time import sleep, strftime, time
from pathlib import Path

# DONE: ####   -----=== global variables ===-----   ####

DEBUG = False  # if debug True not write in current
CURRENT_FILE = (
    Path(__file__).resolve().parent.parent / "current_blocks" / "current_memory"
)

# INFO: ####   -----=== logic ===-----   ####


def main():
    while True:
        try:
            if DEBUG:
                print(f"ram: {get_memory()} | {strftime('%H:%M:%S %d/%m/%Y')}")
            else:
                write_memory()
            sleep(1)
        except KeyboardInterrupt:
            print("\n  cancel <3")
            sys.exit(0)


def shell(command: str) -> str:
    blacklist = {"poweroff", "reboot", "rm", "shutdown"}
    cmd = command.split()[0]

    if cmd in blacklist:
        print(f"skipping: {command}")
        return ""

    return subprocess.run(
        command, shell=True, text=True, capture_output=True
    ).stdout.strip()


def get_memory() -> str:
    if shell("command -v free"):
        return shell("free -h | awk '/^Mem:/{print $3}' | sed 's/Gi/ G/'")
    return "No free"


def formatting_word(text: str, length: int = 6) -> str:
    return text.center(length)


def write_memory() -> None:
    timeout = 5
    start_time = time()

    while True:
        memory = get_memory()
        if memory:
            CURRENT_FILE.write_text(formatting_word(memory))
            return
        if time() - start_time > timeout:
            print("No free")
            return
        sleep(0.2)


if __name__ == "__main__":
    main()
