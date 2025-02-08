#!/usr/bin/env python3
import os
from glob import glob

NAME = ""

HOME = os.getenv("HOME")
WALL_DIR = f"{HOME}/Pictures/wallpapers"
CACHE_WALL = f"{HOME}/.cache/wallpapers_cache"


def delete(dir):
    for file in os.listdir(dir):
        os.remove(os.path.join(dir, file))


def rename_sorted_images():
    if not os.path.exists(WALL_DIR):
        print(f"invalid path:  {WALL_DIR} not exists!")
        return

    files = sorted(
        glob(f"{WALL_DIR}/*"),
        key=lambda x: os.path.basename(x).lower(),
    )

    renamed_files = []
    base_name = NAME
    for i, file in enumerate(files, start=1):
        ext = file.split(".")[-1]
        new_name = f"{base_name}{i}.{ext}"
        new_path = os.path.join(WALL_DIR, new_name)

        if new_path != file:
            os.rename(file, new_path)
            renamed_files.append(new_name)

    delete(CACHE_WALL)
    print(f"❌ deleted {CACHE_WALL} folder!")
    print(f"✅ renamed {len(renamed_files)} images!")


rename_sorted_images()
