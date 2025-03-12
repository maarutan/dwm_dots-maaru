#!/usr/bin/env python3

# push dotfiles \ logic file
# https://github.com/maaru/dotfiles.git
# Copyright (c) 2025 maarutan \ Marat Arzymatov. All Rights Reserved.


# DONE: ------=== Imports ===------

import os
import subprocess
import sys
import pathlib


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


if __name__ == "__main__":
    shell("notify-send 'zinit update'")
