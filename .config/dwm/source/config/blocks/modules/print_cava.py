#!/usr/bin/env python3

# print_cava.py
# https://github.com/maarutan
# Copyright (c) 2025 |  by maaru \ maarutan

import os
import subprocess
import re
import shutil
from time import sleep

# DONE: ####   -----=== global variables ===-----   ####

DELAY_TIME = 0.2
CAVA_NOT_FOUND = "cava not found"
CURRENT_FILE = os.path.abspath(
    os.path.join(
        os.path.dirname(__file__),
        "..",
        "current_blocks",
        "current_cava",
    )
)
CONFIG_FILE = "/tmp/cava_tmp_config"

# INFO: ####   -----=== logic ===-----   ####


def check_cava() -> bool:
    return shutil.which("cava") is not None


def main():
    while True:
        try:
            check_current_file()
            if not check_cava():
                with open(CURRENT_FILE, "w") as f:
                    f.write(CAVA_NOT_FOUND)

            config_path = CONFIG_FILE
            output_file = os.path.expanduser(CURRENT_FILE)

            create_cava_config(config_path)
            process_cava_output(config_path, output_file)
            sleep(DELAY_TIME)
        except KeyboardInterrupt:
            print("\n  cancel  ")
            break


def check_current_file():
    if not os.path.exists(CURRENT_FILE):
        with open(CURRENT_FILE, "w") as f:
            f.write("▁▁▁▁▁▁▁▁▁▁" if check_cava() else CAVA_NOT_FOUND)


def create_cava_config(config_path):
    config_content = """
[general]
bars = 10

[output]
method = raw
raw_target = /dev/stdout
data_format = ascii
ascii_max_range = 7
"""
    with open(config_path, "w") as f:
        f.write(config_content.strip())


def process_cava_output(config_path, output_file):
    if not check_cava():
        with open(output_file, "w") as out_file:
            out_file.write(CAVA_NOT_FOUND)
        return

    bar = "▁▂▃▄▅▆▇█"
    replace_dict = {str(i): bar[i] for i in range(len(bar))}
    pattern = re.compile("|".join(replace_dict.keys()))

    process = subprocess.Popen(
        ["cava", "-p", config_path], stdout=subprocess.PIPE, text=True
    )

    with open(output_file, "r+") as out_file:
        previous_content = out_file.read().strip()
        for line in iter(process.stdout.readline, ""):  # pyright: ignore
            line = line.strip().replace(";", "")
            transformed_line = (
                pattern.sub(lambda m: replace_dict[m.group(0)], line)
                if line
                else previous_content
            )

            if transformed_line != previous_content:
                out_file.seek(0)
                out_file.write(transformed_line)
                out_file.truncate()
                out_file.flush()
                previous_content = transformed_line


if __name__ == "__main__":
    main()
