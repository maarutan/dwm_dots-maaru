#!/usr/bin/env python3

import os
import glob
from subprocess import run as shell
from PIL import Image


HOME = os.getenv("HOME")
ROFI_THEME = f"{HOME}/.suckless/scripts/wallpapers/rofi/.wall.rasi"

WALL_DIR = f"{HOME}/Pictures/wallpapers"
CACHE_WALL = f"{HOME}/.cache/wallpapers_cache"
CURRENT_WALL = f"{HOME}/.cache/wallpaper_current"

DEFAULT_WALLS = glob.glob(f"{WALL_DIR}/.default/default.*")
DEFAULT_WALL = DEFAULT_WALLS[0] if DEFAULT_WALLS else None


def wall_start():
    shell(["feh", "--no-fehbg", "--bg-scale", rofi()])
    # and more your wall softs
    # shell(["your soft", rofi()]) # rofi() - this is path your walls


os.makedirs(CACHE_WALL, exist_ok=True)


def get_info_wall_thumbnail() -> list:
    current_wall = []
    extensions = (".jpg", ".png", ".jpeg", ".webp")

    os.makedirs(CACHE_WALL, exist_ok=True)

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

    if not selected_wall:
        if DEFAULT_WALL:
            print("you did't choose a wallpaper. load default wallpaper.")
            with open(CURRENT_WALL, "w") as f:
                f.write(DEFAULT_WALL)
            return DEFAULT_WALL
        else:
            print("Invalid selection: no wallpaper detected !!!!!")
            exit(1)

    selected_path = (
        selected_wall
        if os.path.isabs(selected_wall)
        else os.path.join(WALL_DIR, selected_wall)
    )

    with open(CURRENT_WALL, "w") as f:
        f.write(selected_path)

    return selected_path


wall_start()
