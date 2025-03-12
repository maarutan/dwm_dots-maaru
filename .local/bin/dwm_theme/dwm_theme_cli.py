#!/usr/bin/env python3

import os
import sys
import subprocess
import argparse


ASCII = True
KILL_DWM = True


def AFTER_START():
    shell("notify-send hello maaru")


HOME = os.getenv("HOME")
dwm_path = f"{HOME}/.suckless/dwm"
dwm_theme_path = os.path.join(dwm_path, "config", "themes")
dwm_theme_file = os.path.join(dwm_theme_path, "theme.h")

# DONE: ---------=== logic ===---------


def shell(command) -> None:
    subprocess.run(command, shell=True)


def list_theme_dir() -> list:
    current_dir = []
    if os.path.isdir(dwm_theme_path):
        for dir in os.listdir(dwm_theme_path):
            if os.path.isdir(os.path.join(dwm_theme_path, dir)):
                current_dir.append(dir)
        return current_dir
    else:
        return []


def check_exist_file(file):
    check = os.path.exists(file)
    if check:
        return None
    else:
        with open(file, "+a"):
            ...
    return None


def read_theme_file() -> str:
    check_exist_file(dwm_theme_file)
    with open(dwm_theme_file, "r") as f:
        return f.read()


# DONE: ---------=== arguments ===---------

parset = argparse.ArgumentParser(
    description="Change dwm theme",
    add_help=False,
)

parset.add_argument(
    "theme",
    nargs="?",
    type=str,
    help="Theme name",
)

parset.add_argument(
    "-l",
    "--list",
    action="store_true",
    help="List all available themes",
)

parset.add_argument(
    "-s",
    "--set",
    type=str,
    help="Set a theme",
)

parset.add_argument(
    "-h",
    "--help",
    "-help",
    action="store_true",
    help="Show this help message and exit",
)

args = parset.parse_args()

if args.help:
    help_content = """
    dwm_theme - Change dwm theme

    list themes: dwm_theme_cli.py -l  
         ╭──────────────╮ 
         │  catppuccin  │ 
         │  dracula     │ 
         │  gruvbox     │ 
         ╰──────────────╯ 


    list colorsheme: dwm_theme_cli.py [theme]
         ╭───────────────╮ 
         │  latte.h      │ 
         │  frappe.h     │ 
         │  mocha.h      │ 
         │  macchiato.h  │ 
         ╰───────────────╯ 
    
    set theme: dwm_theme_cli.py [theme] -s [colorsheme]

        example: dwm_theme_cli.py catppuccin -s mocha 
        

    Options:
             -h,      --help      show this help message and exit
             -l,      --list      List all available themes
             -s,      --set       Set a theme
    """
    print(help_content)
    sys.exit(0)


# DONE: ---------=== logic with arguments ===---------


def main():
    if ASCII:
        line = "─"
        line_row = "│"
        round_left = "╭"
        round_right = "╮"
        round_bottom_left = "╰"
        round_bottom_right = "╯"

        if args.list:
            list_dir_theme = list_theme_dir()
            max_len_theme = max(len(i) for i in list_dir_theme)
            space = " "
            space_plus_one = space * 2
            line_plus_one = line * 2

            print(
                f"{space}{round_left}{line_plus_one}{line * max_len_theme}{line_plus_one}{round_right}{space}"
            )
            for theme in list_dir_theme:
                print(
                    f"{space}{line_row}{space_plus_one}{theme:<{max_len_theme}}{space_plus_one}{line_row}{space}"
                )
            print(
                f"{space}{round_bottom_left}{line_plus_one}{line * max_len_theme}{
                    line_plus_one
                }{round_bottom_right}{space}"
            )
            sys.exit(0)
    else:
        if args.list:
            list_dir_theme = list_theme_dir()
            print("\n".join(i for i in list_dir_theme))
            sys.exit(0)

    if args.theme:
        theme_list = list_theme_dir()

        def list_current_theme_dir(theme_name) -> list:
            theme_path = os.path.join(dwm_theme_path, theme_name)

            if os.path.isdir(theme_path):
                return [
                    file
                    for file in os.listdir(theme_path)
                    if os.path.isfile(os.path.join(theme_path, file))
                ]

            return []

        if ASCII:
            line = "─"
            line_row = "│"
            round_left = "╭"
            round_right = "╮"
            round_bottom_left = "╰"
            round_bottom_right = "╯"

            if args.theme in theme_list:
                list_dir_theme = list_current_theme_dir(args.theme)
                max_len_theme = max(len(i) for i in list_dir_theme)
                space = " "
                space_plus_one = space * 2
                line_plus_one = line * 2
                print(
                    f"{space}{round_left}{line_plus_one}{line * max_len_theme}{line_plus_one}{round_right}{space}"
                )
                for theme in list_dir_theme:
                    print(
                        f"{space}{line_row}{space_plus_one}{theme:<{max_len_theme}}{space_plus_one}{line_row}{space}"
                    )
                print(
                    f"{space}{round_bottom_left}{line_plus_one}{line * max_len_theme}{
                        line_plus_one
                    }{round_bottom_right}{space}"
                )
    if args.set:
        if not args.theme:
            print("Error: You must specify a theme when using -s")
            sys.exit(1)

        theme_list = list_theme_dir()

        if args.theme not in theme_list:
            print(f"Error: Theme '{args.theme}' does not exist.")
            sys.exit(1)

        theme_path = os.path.join(dwm_theme_path, args.theme)
        file_name = args.set if args.set.endswith(".h") else f"{args.set}.h"
        file_path = os.path.join(theme_path, file_name)

        if not os.path.isfile(file_path):
            print(f"Error: File '{file_name}' does not exist in theme '{args.theme}'.")
            sys.exit(1)

        with open(file_path, "r") as src, open(dwm_theme_file, "w") as dest:
            dest.write(src.read())

        if not os.path.exists(os.path.join(dwm_path, "Makefile")):
            print("Error: Makefile not found in", dwm_path)
            sys.exit(1)

        print("Rebuilding dwm...")
        result = subprocess.run(
            ["make", "clean", "install"],
            cwd=dwm_path,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
        if KILL_DWM:
            subprocess.run("pgrep -x dwm | xargs -r kill", shell=True)

        if result.returncode == 0:
            print("DWM successfully recompiled and installed!")
        else:
            print("Error during compilation:", result.stderr.decode())

        print(f"Theme '{args.theme}' applied with '{file_name}'.")

        AFTER_START()

    sys.exit(0)


# DONE: ---------=== start ===---------

if __name__ == "__main__":
    main()
