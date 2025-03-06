#!/usr/bin/env python3

import os
import re
from subprocess import run

ASCII = True

dunst_conf_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir))
cache_dir = os.path.join(dunst_conf_dir, ".cache")
cache_opacity_file = os.path.join(cache_dir, "opacity")
settings_opacity = os.path.join(dunst_conf_dir, ".settings", "opacity")
settings_no_opacity_file = os.path.join(settings_opacity, "no_opacity")
settings_opacity_file = os.path.join(settings_opacity, "with_opacity")
dunstrc = os.path.join(dunst_conf_dir, "dunstrc")


def shell(command) -> None:
    run(command, shell=True)


def read_opacity_file() -> str:
    if os.path.isfile(cache_opacity_file):
        with open(cache_opacity_file, "r") as f:
            return f.read().strip()
    return "transparency  = 0"


def read_settings_no_opacity_file() -> str:
    if os.path.isfile(settings_no_opacity_file):
        with open(settings_no_opacity_file, "r") as f:
            return f.read().strip()
    return "transparency  = 0"


def read_settings_opacity_file() -> str:
    if os.path.isfile(settings_opacity_file):
        with open(settings_opacity_file, "r") as f:
            return f.read().strip()
    return "transparency  = 0"


def read_dunstrc() -> list[str]:
    with open(dunstrc, "r") as f:
        return f.readlines()


def read_cachefile() -> str:
    with open(cache_opacity_file, "r") as f:
        return f.read().strip()


def logic_choice() -> str:
    cache_value = read_cachefile()
    if cache_value.isdigit():
        cache_value = int(cache_value)
        if cache_value > 0:
            return read_settings_opacity_file()
        elif cache_value == 0:
            return read_settings_no_opacity_file()
    elif cache_value.lower() == "true":
        return read_settings_opacity_file()
    elif cache_value.lower() == "false":
        return read_settings_no_opacity_file()

    return str(cache_value)


def write_opacity_dunstrc():
    current_theme = logic_choice()
    dunst_file = read_dunstrc()
    current_word_of_theme = ["transparency"]
    updated_lines = []

    for line in dunst_file:
        line = line.strip()
        for word in current_word_of_theme:
            if word in line:
                updated_line = re.sub(
                    r"=\s*.*", f"= {current_theme.split('=')[-1].strip()}", line
                )
                updated_lines.append(updated_line)
                break
        else:
            updated_lines.append(line)

    with open(dunstrc, "w") as f:
        for line in updated_lines:
            f.write(line + "\n")

    if ASCII:
        line = "─"
        line_row = "│"
        round_left = "╭"
        round_right = "╮"
        round_bottom_left = "╰"
        round_bottom_right = "╯"

        print(
            f"{round_left}{line * 5}{round_right}\n"
            f"{line_row} successfull !!!\n"
            f"{line_row} opacity is {current_theme}\n"
            f"{round_bottom_left}{line * 5}{round_bottom_right}"
        )
    else:
        print(f"opacity is {current_theme}")


if __name__ == "__main__":
    write_opacity_dunstrc()
