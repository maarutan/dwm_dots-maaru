#!/usr/bin/env python3

# starter for dwmblocks
# https://github.com/maarutan
# Copyright (c) 2025 |  by maaru \ maarutan

import os
import subprocess
import signal

# DONE: ####   -----=== global variables ===-----   ####


MODULES = [
    "battery_power.py",
    "memory.py",
    "pacman_updates.py",
    "network_speed.py",
    "print_cava.py",
    "show_network_signal.py",
    "current_language.py",
    # --------------------------------------
    # dwmblocks only end
    "../core/dwmblocks.py",
]

# INFO: ####   -----=== logic ===-----   ####


def main():
    scripts = load_modules(*MODULES)
    for script in scripts:
        kill_processes(script)
        shell(script)


def load_modules(*modules):
    scripts = [
        os.path.abspath(os.path.join(os.path.dirname(__file__), "modules", script))
        for script in modules
    ]
    return scripts


def kill_processes(script):
    try:
        result = subprocess.run(["pgrep", "-f", script], capture_output=True, text=True)
        if result.stdout.strip():
            pids = result.stdout.strip().split("\n")
            for pid in pids:
                os.kill(int(pid), signal.SIGTERM)
            print(f"kill process: {script}")
    except Exception as e:
        print(f"error {script}: {e}")


def shell(command):
    blacklist = {"poweroff", "reboot", "rm", "shutdown"}

    cmd = command.split()[0]
    if cmd in blacklist:
        print(f"skipping: {command}")
        return

    if command.endswith(".py"):
        subprocess.Popen(["python3", command])
    else:
        subprocess.Popen(["bash", command])


if __name__ == "__main__":
    main()
