#!/usr/bin/env python3
import os

ASCII = True

rofi_conf_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir))
colorscheme_path = os.path.join(rofi_conf_dir, ".colorscheme")
cache_dir = os.path.join(rofi_conf_dir, ".cache")
cache_file = os.path.join(cache_dir, "current_theme")
theme_file = os.path.join(colorscheme_path, "theme.rasi")
system_theme = os.path.join(cache_dir, "system_theme")


def list_colorschemes() -> list[str]:
    return os.listdir(colorscheme_path)


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
        return os.path.join(theme_dir, theme_files[0])
    elif system_mode == "light":
        return os.path.join(theme_dir, theme_files[1])
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
                round_bottom_left = "╰"
                round_bottom_right = "╯"
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
                print(
                    f"{line_row}{space}{theme_file}{space}{line_row}\n{round_bottom_left}{line * 2}{lines}{round_bottom_right}"
                )

    else:
        print("Error: could not read theme content.")


if __name__ == "__main__":
    write_theme()
