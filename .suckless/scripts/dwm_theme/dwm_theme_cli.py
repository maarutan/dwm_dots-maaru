#!/usr/bin/env python3

import os
import subprocess
import argparse

HOME = os.getenv("HOME")
dwm_path = f"{HOME}/.suckless/dwm"
dwm_theme_path = os.path.join(dwm_path, "config", "themes")
dwm_theme_file = os.path.join(dwm_theme_path, "theme.h")


def list_theme_dir():
    return os.listdir(dwm_theme_path)


print(list_theme_dir())


def read_theme_file():
    with open(dwm_theme_file, "r") as f:
        return f.read()
