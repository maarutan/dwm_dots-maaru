#!/usr/bin/env python3
import subprocess
import os

USER = os.getenv("USER")
HOME = f"/home/{USER}"
theme_script = f"{HOME}/.suckless/scripts/dwm_theme/dwmtheme.py"
compile_path = f"{HOME}/.suckless/dwm/"
rofi_config_path = f"{HOME}/.config/rofi/emoji/emoji.rasi"


# ---------------------------------------------------------------------------------
# DONE: this is the main function
def main():
    themes = get_themes()
    if not themes:
        return

    selected_theme = show_rofi_menu(themes, prompt="Select Theme:")
    if not selected_theme:
        return

    list_items = get_list_items(selected_theme)
    if not list_items:
        return

    selected_item = show_rofi_menu(list_items, prompt="Select Item:")
    if not selected_item:
        return

    set_theme(selected_theme, selected_item)


# ---------------------------------------------------------------------------------
def get_themes():
    try:
        result = subprocess.check_output([theme_script, "-l"], text=True)
        return result.strip().split("\n")
    except subprocess.CalledProcessError:
        return []


def get_list_items(theme_name):
    try:
        result = subprocess.check_output([theme_script, "-li", theme_name], text=True)
        items = result.strip().split("\n")
        return items  # Возвращаем весь список, включая первые две строки
    except subprocess.CalledProcessError:
        return []


def show_rofi_menu(options, prompt="Select:"):
    rofi_command = [
        "rofi",
        "-dmenu",
        "-p",
        prompt,
        "-theme",
        rofi_config_path,
    ]
    try:
        result = subprocess.run(
            rofi_command, input="\n".join(options), text=True, capture_output=True
        )
        return result.stdout.strip()
    except Exception:
        return None


def set_theme(theme_name, item_name):
    try:
        subprocess.run([theme_script, "-s", theme_name, item_name], check=True)
        subprocess.run(["make", "clean", "install"], cwd=compile_path, check=True)
        subprocess.run(
            "pgrep -x dwm | xargs -r kill || notify-send 'envalid dwm recompiled'",
            shell=True,
            check=True,
        )
    except subprocess.CalledProcessError:
        pass


# ---------------------------------------------------------------------------------
if __name__ == "__main__":
    main()
