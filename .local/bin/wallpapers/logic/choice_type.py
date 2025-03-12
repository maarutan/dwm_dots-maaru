#!/usr/bin/env python3

import os, pathlib
from subprocess import run as shell

ROFI_CONFIG = pathlib.Path(__file__).parent.parent / "assets/rofi_theme/types.rasi"
ASSETS = pathlib.Path(__file__).parent.parent / "assets/choice"
RESULT = pathlib.Path(__file__).parent.parent / "assets/.cache/type"


def get_img():
    array = []
    extensions = (".jpg", ".png")
    for file in os.listdir(ASSETS):
        parent_file = os.path.join(ASSETS, file)
        if os.path.isfile(parent_file) and file.endswith(extensions):
            array.append(f"{file}\x00icon\x1f{ASSETS}/{file}")
    return array


def rofi():
    result = shell(
        ["rofi", "-theme", ROFI_CONFIG, "-dmenu"],
        input="\n".join(get_img()),
        text=True,
        capture_output=True,
    )
    return result.stdout.strip() if result.stdout else None


def pick_type():
    selection = rofi()
    if not selection:
        exit(0)

    type_map = {
        "live.png": "live",
        "static.png": "static",
    }

    type_value = type_map.get(selection.lower())
    if type_value:
        with open(RESULT, "w") as f:
            f.write(type_value)
    else:
        print(f"{selection}")


if __name__ == "__main__":
    try:
        pick_type()
    except KeyboardInterrupt:
        print("\n  cancel")
