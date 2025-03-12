#!/usr/bin/env python3

from images.launcher import read_current_wall
from logic.choice_theme import CACHE_TYPE
from subprocess import run as shell


def read_cache_type() -> str:
    with open(CACHE_TYPE, "r") as f:
        file = f.read().strip()
        return file


def live() -> None:
    selected_wall = read_current_wall()

    if not selected_wall:
        return

    shell(["pkill", "-f", "mpv"])
    shell(["pkill", "-f", "xwinwrap"])
    shell(["pkill", "-f", "ffmpeg"])

    if selected_wall.endswith((".mp4", ".mkv", ".webm", ".avi", ".mov")):
        shell(
            [
                "xwinwrap",
                "-g",
                "1920x1080",
                "-ov",
                "-ni",
                "-s",
                "-nf",
                "--",
                "mpv",
                "--loop",
                "--no-audio",
                "--wid=%WID%",
                selected_wall,
            ]
        )


try:
    if read_cache_type() == "live":
        shell(["pkill", "-f", "mpv"])
        shell(["pkill", "-f", "xwinwrap"])
        shell(["pkill", "-f", "ffmpeg"])
        live()
    else:
        shell(["pkill", "-f", "mpv"])
        shell(["pkill", "-f", "xwinwrap"])
        shell(["pkill", "-f", "ffmpeg"])
        shell(["feh", "--no-fehbg", "--bg-scale", read_current_wall()])
except KeyboardInterrupt:
    print("\n  cancel")
