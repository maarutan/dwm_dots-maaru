#!/usr/bin/env python3
import os
import shutil
from glob import glob

NAME = ""
HOME = os.getenv("HOME")
WALL_DIR = os.path.join(HOME, "Pictures/wallpapers")  # pyright: ignore
CACHE_WALL = os.path.join(HOME, ".cache/wallpapers_cache")  # pyright: ignore


def clear_cache():
    if os.path.exists(CACHE_WALL):
        shutil.rmtree(CACHE_WALL)
        os.makedirs(CACHE_WALL)
        print(f"❌ Cleared cache directory: {CACHE_WALL}")
    else:
        print(f"⚠️ Cache directory does not exist: {CACHE_WALL}")


def rename_sorted_images():
    if not os.path.exists(WALL_DIR):
        print(f"Error: Directory does not exist - {WALL_DIR}")
        return

    files = sorted(
        [f for f in glob(os.path.join(WALL_DIR, "*")) if os.path.isfile(f)],
        key=lambda x: os.path.basename(x).lower(),
    )

    if not files:
        print("ℹ️ No files found to rename in the wallpaper directory.")
        return

    temp_files = []
    for idx, file_path in enumerate(files):
        try:
            ext = os.path.splitext(file_path)[1][1:]  # Get extension without dot
            temp_path = os.path.join(WALL_DIR, f"temp_{idx}.{ext}")
            os.rename(file_path, temp_path)
            temp_files.append(temp_path)
        except Exception as e:
            print(f"⚠️ Error renaming {file_path} to temporary: {str(e)}")

    renamed_count = 0
    for idx, temp_path in enumerate(temp_files, start=1):
        try:
            ext = os.path.splitext(temp_path)[1][1:]
            new_name = f"{NAME}{idx}.{ext}"
            new_path = os.path.join(WALL_DIR, new_name)
            os.rename(temp_path, new_path)
            renamed_count += 1
        except Exception as e:
            print(f"⚠️ Error renaming {temp_path} to final: {str(e)}")

    clear_cache()
    print(f"✅ Successfully renamed {renamed_count}/{len(files)} files!")


if __name__ == "__main__":
    rename_sorted_images()
