#!/usr/bin/env python3
import os
import sys
import subprocess

HOME = os.getenv("HOME")
WALLPAPER_DIR = f"{HOME}/Pictures/wallpapers"
CACHE_FILE = f"{HOME}/.cache/current_wallpaper"
NOTIFY_SEND = True


def set_wallpaper(wallpaper, cache_file):
    subprocess.run(["feh", "--bg-scale", wallpaper], check=True)
    with open(cache_file, "w") as f:
        f.write(wallpaper)
    storage_lockscreen()
    notify_send(wallpaper)


def storage_lockscreen():
    script_path = os.path.join(
        os.path.dirname(__file__), "..", "lockscreen", "betterlockscreen.py"
    )
    subprocess.run([script_path, "-g"])


def get_wallpaper_list(directory):
    return sorted(
        [
            os.path.join(directory, f)
            for f in os.listdir(directory)
            if os.path.isfile(os.path.join(directory, f))
        ]
    )


def notify_send(wallpaper):
    if NOTIFY_SEND:
        subprocess.run(
            [
                "dunstify",
                "-r",
                "9999",
                "-i",
                wallpaper,
                wallpaper,
            ]
        )


def get_current_wallpaper(cache_file, wallpaper_list):
    if os.path.exists(cache_file):
        with open(cache_file, "r") as f:
            current = f.read().strip()
        if current in wallpaper_list:
            return current
    return wallpaper_list[0] if wallpaper_list else None


if not os.path.exists(WALLPAPER_DIR) or not os.listdir(WALLPAPER_DIR):
    print("wallpapers not found!")
    sys.exit(1)

wallpaper_list = get_wallpaper_list(WALLPAPER_DIR)
current_wallpaper = get_current_wallpaper(CACHE_FILE, wallpaper_list)

if not current_wallpaper:
    print("wall not found!")
    sys.exit(1)

try:
    current_index = wallpaper_list.index(current_wallpaper)
except ValueError:
    current_index = 0

if len(sys.argv) < 2:
    print("Usage: python script.py {right|left}")
    sys.exit(1)

direction = sys.argv[1]
if direction == "right":
    new_index = (current_index + 1) % len(wallpaper_list)
elif direction == "left":
    new_index = (current_index - 1) % len(wallpaper_list)
else:
    print("Usage: python script.py {right|left}")
    sys.exit(1)

new_wallpaper = wallpaper_list[new_index]
set_wallpaper(new_wallpaper, CACHE_FILE)
print(f"wall changed: {new_wallpaper}")
