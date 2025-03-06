#!/usr/bin/env python3

import os
import re
from subprocess import run

from rounded import write_rounded_dunstrc
from opacity import write_opacity_dunstrc

ASCII = True


dunst_conf_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir))
colorscheme_path = os.path.join(dunst_conf_dir, ".colorscheme")
cache_dir = os.path.join(dunst_conf_dir, ".cache")
cache_file = os.path.join(cache_dir, "current_theme")
theme_file = os.path.join(cache_dir, "current_color")
system_theme = os.path.join(cache_dir, "system_theme")
dunstrc = os.path.join(dunst_conf_dir, "dunstrc")


def list_colorschemes() -> list[str]:
    return os.listdir(colorscheme_path)


def shell(command) -> None:
    run(command, shell=True)


def if_not_exist_cache_and_dir() -> None:
    if not os.path.exists(cache_dir):
        os.makedirs(cache_dir)

    if not os.path.isfile(cache_file):
        with open(cache_file, "w") as f:
            f.write("")

    if not os.path.isfile(system_theme):
        with open(system_theme, "w") as f:
            f.write("dark")


def read_cachefile() -> str:
    if_not_exist_cache_and_dir()
    with open(cache_file, "r") as f:
        return f.read().strip()


def path_theme_dir() -> str:
    file = read_cachefile()
    if file in os.listdir(colorscheme_path):
        return os.path.join(colorscheme_path, file)
    return ""


def read_system_theme() -> str:
    if os.path.isfile(system_theme):
        with open(system_theme, "r") as f:
            return f.read().strip()
    return "dark"


def get_system_theme() -> str:
    theme_dir = path_theme_dir()
    if not theme_dir or not os.path.isdir(theme_dir):
        print("Theme directory not found!")
        return ""

    theme_files = os.listdir(theme_dir)
    if len(theme_files) < 2:
        print("Not enough files in the theme directory!")
        return ""

    system_mode = read_system_theme()
    if system_mode == "dark":
        return os.path.join(theme_dir, theme_files[1])
    elif system_mode == "light":
        return os.path.join(theme_dir, theme_files[0])
    else:
        print("Unknown system theme:", system_mode)
        return ""


def read_theme() -> str:
    theme_path = get_system_theme()
    if theme_path and os.path.isfile(theme_path):
        with open(theme_path, "r") as f:
            return f.read()
    return ""


def write_theme() -> None:
    theme_content = read_theme()
    theme_name = read_cachefile()
    if theme_content:
        with open(theme_file, "w") as f:
            if ASCII:
                line = "─"
                line_row = "│"
                round_left = "╭"
                round_right = "╮"
                len_theme_name = len(theme_name)
                len_theme_file = len(theme_file)
                max_len_for_art = max(len_theme_name, len_theme_file)
                lines = line * max_len_for_art
                space = " "
                info_content = len("Theme successfully written:")
                max_space = " " * (max_len_for_art - info_content)
                info_content_2 = len(f"Theme content: {theme_name}")
                max_hight_space = " " * (max_len_for_art - info_content_2)

                f.write(theme_content)
                print(
                    f"{round_left}{line * 2}{lines}{round_right}\n{line_row}{space}Theme content: {theme_name}{max_hight_space}{space}{line_row}"
                )
                print(
                    f"{line_row}{space}Theme successfully written:{max_space} {line_row}"
                )
                print(f"{line_row}{space}{theme_file}{space}{line_row}")

    else:
        print("Error: could not read theme content.")


def read_dunstrc() -> list[str]:
    with open(dunstrc, "r") as f:
        return f.readlines()


def get_theme_dunstrc():
    dunst_file = read_dunstrc()
    current_word_of_theme = ["background", "highlight", "foreground", "frame_color"]
    current_new_theme = []

    for line in dunst_file:
        for word in current_word_of_theme:
            if word in line:
                current_new_theme.append(line.strip())

    return current_new_theme


def read_current_theme():
    with open(theme_file, "r") as f:
        theme_content = f.read().strip()
        theme_dict = {}
        for line in theme_content.splitlines():
            key, value = line.split("=", 1)
            theme_dict[key.strip()] = value.strip()
        return theme_dict


def write_theme_dunstrc():
    current_theme = read_current_theme()
    dunst_file = read_dunstrc()
    current_word_of_theme = ["background", "highlight", "foreground", "frame_color"]
    updated_lines = []
    for line in dunst_file:
        line = line.strip()
        for word in current_word_of_theme:
            if word in line:
                updated_line = re.sub(r"=\s*.*", f"= {current_theme[word]}", line)
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
            round_bottom_left = "╰"
            round_bottom_right = "╯"
            space = " "
            content = {
                "Theme successfully written to dunstrc!": len(
                    "Theme successfully written to dunstrc!"
                )
            }
            lenline = len(theme_file) - len("Theme successfully written to dunstrc!")
            print(
                f"{line_row}{line * 2}{line * content['Theme successfully written to dunstrc!']}{line * lenline + round_bottom_right}\n"
                f"{line_row}{space}Theme successfully written to dunstrc!{space}{line_row}\n"
                f"{round_bottom_left}{line * 2}{line * content['Theme successfully written to dunstrc!']}{round_bottom_right}"
            )
        else:
            print("Theme successfully written to dunstrc!")


def reload_dunst():
    shell("pkill -x dunst")
    shell("dunst > /dev/null 2>&1 &")


if __name__ == "__main__":
    write_theme()
    write_theme_dunstrc()
    write_rounded_dunstrc()
    write_opacity_dunstrc()

    # always end
    reload_dunst()
