#!/usr/bin/env python3

# current_language.py with help xkb-switch
# https://github.com/maarutan
# Copyright (c) 2025 |  by maaru \ maarutan

import subprocess, os, sys
from time import sleep


# DONE: ####   -----=== global variables ===-----   ####


DEBUG = False  # show print no write current
theme = "small"  # small, upper
wrapper = "[]"  # [], (), {}, ""

lang_change_view = {
    "us": "en",
}

CURRENT_FILE = os.path.abspath(
    os.path.join(
        os.path.dirname(__file__),
        "..",
        "current_blocks",
        "current_language",
    )
)


# INFO: ####   -----=== logic ===-----   ####


def shell(command: str) -> str:
    blacklist = {"poweroff", "reboot", "rm", "shutdown"}
    cmd = command.split()[0]

    if cmd in blacklist:
        return ""

    return subprocess.run(
        command,
        shell=True,
        text=True,
        capture_output=True,
        env={"DISPLAY": os.getenv("DISPLAY", ":0")},
    ).stdout.strip()


def get_language() -> str:
    lang = shell("xkb-switch -p")
    if not lang:
        return "No xkb-switch"

    # Подмена языка, если есть в `lang_change_view`
    lang = lang_change_view.get(lang, lang)

    if theme == "upper":
        lang = lang.upper()

    wrappers = {
        "[]": f"[{lang}]",
        "()": f"({lang})",
        "{}": f"{{{lang}}}",
        '""': f'"{lang}"',
        "''": f"'{lang}'",
        "": lang,
    }

    return wrappers.get(wrapper, lang)


if __name__ == "__main__":
    if DEBUG:
        print(get_language())
    else:
        while True:
            try:
                sleep(0.1)
                with open(CURRENT_FILE, "w") as f:
                    f.write(get_language())
            except KeyboardInterrupt:
                print("\n  cancel <3")
                sys.exit(0)
