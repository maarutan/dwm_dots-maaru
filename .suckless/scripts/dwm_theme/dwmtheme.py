#!/usr/bin/env python3
import os
import argparse
import subprocess

USER = os.getenv("USER")
HOME = f"/home/{USER}"
DWM = f"{HOME}/.suckless/dwm/"

path_theme = f"{HOME}/.suckless/dwm/config/themes/"
link_path = f"{path_theme}/theme.h"


class ThemeManager:
    def __init__(self):
        self.contents = self.get_contents()

    def get_contents(self):
        try:
            themes = os.listdir(path_theme)
            return {
                theme: os.listdir(os.path.join(path_theme, theme))
                for theme in themes
                if os.path.isdir(os.path.join(path_theme, theme))
            }
        except FileNotFoundError:
            return f"Path {path_theme} not found"
        except PermissionError:
            return f"No permission to access {path_theme}"

    def list_themes(self):
        return (
            "\n".join(self.contents.keys())
            if isinstance(self.contents, dict)
            else self.contents
        )

    def list_items(self, theme_name=None):
        if theme_name is None:
            return "No theme specified. Use --list to see available themes."
        if theme_name in self.contents:
            items = self.contents[theme_name]
            return "\n".join(items)
        return f"Theme {theme_name} not found"

    def create_symlink(self, theme_name, item_name):
        theme_path = os.path.join(path_theme, theme_name)
        item_path = os.path.join(theme_path, item_name)
        if not os.path.isdir(theme_path):
            return f"Theme {theme_name} not found"
        if not os.path.exists(item_path):
            return f"Item {item_name} not found in theme {theme_name}"
        try:
            if os.path.islink(link_path) or os.path.exists(link_path):
                os.unlink(link_path)
            os.symlink(item_path, link_path)
            return f"Symlink created: {link_path} -> {item_path}"
        except Exception as e:
            return f"Error creating symlink: {str(e)}"


def execute_custom_scripts():
    try:
        custom_scripts_path = f"{HOME}/.suckless/scripts/custom/"
        if os.path.exists(custom_scripts_path) and os.path.isdir(custom_scripts_path):
            scripts = [
                os.path.join(custom_scripts_path, f)
                for f in os.listdir(custom_scripts_path)
                if f.endswith(".sh")
                and os.path.isfile(os.path.join(custom_scripts_path, f))
            ]
            for script in scripts:
                print(f"Executing custom script: {script}")
                subprocess.run(["bash", script], check=True)
        else:
            print(f"No custom scripts directory found at {custom_scripts_path}.")
    except Exception as e:
        print(f"Error executing custom scripts: {e}")


def restart_dwm():
    try:
        subprocess.run(["make", "clean", "install"], cwd=DWM, check=True)
        print("DWM has been successfully recompiled and restarted.")
    except subprocess.CalledProcessError as e:
        print(f"Error during DWM restart: {e}")


def main():
    parser = argparse.ArgumentParser(description="Theme Manager for dwm")
    parser.add_argument("-l", "--list", action="store_true", help="List all themes")
    parser.add_argument(
        "-li",
        "--listitem",
        nargs="?",
        const=None,
        help="List items in a specific theme directory",
    )
    parser.add_argument(
        "-s",
        "--set",
        nargs=2,
        metavar=("THEME", "ITEM"),
        help="Set a theme item and create symlink",
    )

    args = parser.parse_args()
    manager = ThemeManager()

    if args.list:
        print(manager.list_themes())
    elif args.listitem is not None:
        print(manager.list_items(args.listitem))
    elif args.set:
        theme_name, item_name = args.set
        print(manager.create_symlink(theme_name, item_name))
        restart_dwm()
        execute_custom_scripts()
    else:
        parser.print_help()


if __name__ == "__main__":
    main()
