#!/usr/bin/env python3

from images.launcher import wall_start as images
from live.launcher import wall_start as live
from logic.choice_theme import CACHE_TYPE
from subprocess import run as shell


def read_cache_type() -> str:
    with open(CACHE_TYPE, "r") as f:
        file = f.read().strip()
        return file


print(read_cache_type())

try:
    if read_cache_type() == "live":
        shell(["pkill", "-f", "mpv"])
        shell(["pkill", "-f", "xwinwrap"])
        shell(["pkill", "-f", "ffmpeg"])
        live()
    elif read_cache_type() == "static":
        shell(["pkill", "-f", "mpv"])
        shell(["pkill", "-f", "xwinwrap"])
        shell(["pkill", "-f", "ffmpeg"])
        images()
except KeyboardInterrupt:
    print("\n  cancel")
