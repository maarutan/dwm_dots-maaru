#!/usr/bin/env python3

import os, pathlib
from subprocess import run as shell


ROFI_CONFIG = pathlib.Path(__file__).parent.parent / "assets/rofi_theme/theme.rasi"
ASSETS = pathlib.Path(__file__).parent.parent / "assets/theme"
RESULT = pathlib.Path(__file__).parent.parent / "assets/.cache/type"
CACHE_TYPE = pathlib.Path(__file__).parent.parent / "assets/.cache/type"
CACHE_THEME = pathlib.Path(__file__).parent.parent / "assets/.cache/theme"


def get_theme_cache():
    if not os.path.exists(CACHE_TYPE):
        return []
    else:
        with open(CACHE_TYPE, "r") as f:
            cache_type = f.read().strip()

        theme_path = os.path.join(ASSETS, cache_type)

        if os.path.exists(theme_path) and os.path.isdir(theme_path):
            return os.listdir(theme_path)
        return []


def get_theme():
    array = []
    files = get_theme_cache()

    cache_type = open(CACHE_TYPE).read().strip()

    for file in files:
        array.append(f"{file}\x00icon\x1f{ASSETS}/{cache_type}/{file}")

    return array


def rofi():
    result = shell(
        ["rofi", "-theme", ROFI_CONFIG, "-dmenu"],
        input="\n".join(get_theme()),
        text=True,
        capture_output=True,
    )
    return result.stdout.strip() if result.stdout else None


def pick_type():
    selection = rofi()
    if not selection:
        exit(0)

    selected_file_without_extension = os.path.splitext(selection)[0]

    type_map = {
        "live": "live",
        "static": "static",
    }

    type_value = type_map.get(selected_file_without_extension.lower())
    if type_value:
        with open(RESULT, "w") as f:
            f.write(type_value)
    else:
        print(selected_file_without_extension)

    with open(CACHE_THEME, "w") as f:
        f.write(selected_file_without_extension)


try:
    if __name__ == "__main__":
        pick_type()
except KeyboardInterrupt:
    print("\n cancel")
