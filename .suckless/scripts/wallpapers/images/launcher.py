#!/usr/bin/env python3

LOAD_RANDOM_WALL = 0
LOAD_DEFAULT_WALL = 0
NOTIFY = 1
SCREEN_LOCK = 1

import os
import glob
from subprocess import run as shell
from PIL import Image
import random

HOME = os.getenv("HOME")
ROFI_THEME = f"{HOME}/.suckless/scripts/wallpapers/images/.wall.rasi"

WALL_DIR = f"{HOME}/Pictures/wallpapers"
CACHE_WALL = f"{HOME}/.cache/wallpapers_cache"
CURRENT_WALL = f"{HOME}/.cache/current_wallpaper"

DEFAULT_WALLS = glob.glob(f"{WALL_DIR}/.default/default.*")
DEFAULT_WALL = DEFAULT_WALLS[0] if DEFAULT_WALLS else ""
DEFAULT_RANDOM_DIR = f"{HOME}/Pictures/wallpapers/"
TEMPLATE_STORAGE = "/tmp/wallpaper_storage"

os.makedirs(CACHE_WALL, exist_ok=True)


def template_storage(write):
    if write:
        with open(TEMPLATE_STORAGE, "w") as f:
            f.write(write)


def read_template():
    if os.path.exists(TEMPLATE_STORAGE):
        with open(TEMPLATE_STORAGE, "r") as f:
            return f.read().strip()
    return ""


def read_current_wall():
    if os.path.exists(CURRENT_WALL):
        with open(CURRENT_WALL, "r") as f:
            content = f.read().strip()
            template_storage(content)
            return content
    return ""


def storage_lockscreen():
    script_path = os.path.join(
        os.path.dirname(__file__), "..", "lockscreen", "betterlockscreen.py"
    )
    shell([script_path, "-g"])

    if NOTIFY:
        current_wall = read_current_wall()
        if current_wall and os.path.exists(current_wall):
            shell(
                [
                    "dunstify",
                    "-r",
                    "9999",
                    "-i",
                    current_wall,
                    "Lockscreen Updated",
                    f"Wallpaper: {os.path.basename(current_wall)}",
                ]
            )


def get_random_wall() -> str:
    walls = glob.glob(f"{DEFAULT_RANDOM_DIR}/*")
    return random.choice(walls) if walls else ""


def get_theme_type():
    current_theme = []
    if_dir_current = ["live", "static"]
    for dirlists in os.listdir(WALL_DIR):
        if os.path.isdir(os.path.join(WALL_DIR, dirlists)):
            if dirlists in if_dir_current:
                current_theme.append(os.path.join(WALL_DIR, dirlists))

    return current_theme


def get_info_wall_thumbnail() -> list:
    current_wall = []
    extensions = (".jpg", ".png", ".jpeg", ".webp")

    for file in os.listdir(WALL_DIR):
        source_path = os.path.join(WALL_DIR, file)
        cache_path = os.path.join(CACHE_WALL, file)

        if os.path.isfile(source_path) and file.endswith(extensions):
            if not os.path.exists(cache_path):
                with Image.open(source_path) as img:
                    img = img.convert("RGB")
                    width, height = img.size
                    aspect = 500 / min(width, height)
                    new_size = (int(width * aspect), int(height * aspect))
                    img = img.resize(new_size, Image.LANCZOS)  # pyright: ignore

                    left = (img.width - 500) / 2
                    top = (img.height - 500) / 2
                    right = left + 500
                    bottom = top + 500

                    img = img.crop((left, top, right, bottom))
                    img.save(cache_path, "JPEG", quality=90)

            current_wall.append(f"{file}\x00icon\x1f{cache_path}")
    return current_wall


def rofi() -> str:
    result = shell(
        ["rofi", "-theme", ROFI_THEME, "-dmenu"],
        input="\n".join(get_info_wall_thumbnail()),
        text=True,
        capture_output=True,
    )

    selected_wall = result.stdout.strip()

    if not selected_wall and LOAD_DEFAULT_WALL:
        if not DEFAULT_WALL:
            print("Error: No default wallpaper found.")
            return ""
        print("you didn't choose a wallpaper. Loading default wallpaper.")
        with open(CURRENT_WALL, "w") as f:
            f.write(DEFAULT_WALL)
        return DEFAULT_WALL

    if not selected_wall and LOAD_RANDOM_WALL:
        random_wall = get_random_wall()
        if not random_wall:
            print("Error: No random wallpaper found.")
            return ""
        print("you didn't choose a wallpaper. Loading random wallpaper.")
        with open(CURRENT_WALL, "w") as f:
            f.write(random_wall)
        return random_wall

    if not selected_wall:
        print("you didn't choose a wallpaper.")
        return ""

    selected_path = (
        selected_wall
        if os.path.isabs(selected_wall)
        else os.path.join(WALL_DIR, selected_wall)
    )

    with open(CURRENT_WALL, "w") as f:
        f.write(selected_path)

    return selected_path


def wall_start() -> None:
    selected_wall = rofi()
    if not selected_wall:
        print("Error: No wallpaper selected.")
        return
    shell(["feh", "--no-fehbg", "--bg-scale", selected_wall])

    if SCREEN_LOCK and read_template() == read_current_wall():
        return
    storage_lockscreen()


# wall_start()
