#!/usr/bin/env python3

# =====================#
#  .--.
# / _.-' .-.   .-.  .-.
# \  '-. '-'   '-'  '-'
#  '--'
# =====================#
# by: https://github.com/maarutan/
# 2025-02-05 (c)
# =====================#

# ui
NOTIFY = False
WARN_ICON = "⚠️"
INFO_ICON = "❕"

FETCH = True


# packages
PACMAN = True
YAY = True
PARU = False
FLATPAK = False
END_DELAY = 5


# nerd font check
FONT_CHECK = False

# ======#
# logic #
# ======#


def main():
    try:
        if FETCH:
            fetch()
        check_font()
        ui()
        start_update()

    except KeyboardInterrupt:
        print(f"\n {PURPLE}cancel{PURPLE}")


import os
import subprocess
from time import sleep

RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
PURPLE = "\033[35m"
CYAN = "\033[36m"
RESET = "\033[0m"


def shell(command) -> str:
    return subprocess.getoutput(command)


def ending():
    print(
        f"{RESET}▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁{RESET}\n\n",
        YELLOW,
        "\n === Done ===",
        YELLOW,
        PURPLE,
        f"\n === bye bye {os.environ['USER']} ^^ ===",
        PURPLE,
        f"{RESET}\n\n▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁{RESET}\n\n",
    )
    sleep(END_DELAY)


def start_update() -> None:
    if NOTIFY:
        shell(f"notify-send '{WARN_ICON} Updating !!! \nSudo password needed'")
    if PACMAN:
        os.system("sudo pacman -Syu --noconfirm")
    if YAY:
        yay_update()
    if PARU:
        paru_update()
    if FLATPAK:
        flatpak_update()
    ending()


def yay_update() -> int | None:
    if not shell("command -v yay"):
        return print("yay not found")
    return os.system("yay -Syu --noconfirm")


def paru_update() -> int | None:
    if not shell("command -v paru"):
        return print("paru not found")
    return os.system("paru -Syu --noconfirm")


def flatpak_update() -> int | None:
    if not shell("command -v flatpak"):
        return print("flatpak not found")
    return os.system("flatpak update")


def ui():
    output = []
    if PACMAN:
        output.append(f"{YELLOW}~~>   󰮯  :  Pacman   ===     {check_pacman()}{YELLOW}")
    if YAY:
        output.append(f"{BLUE}~~>     :  yay      ===     {check_yay()}{BLUE}")
    if FLATPAK:
        output.append(f"{CYAN}~~>     :  Flatpak  ===     {check_flatpak()}{CYAN}")
    if PARU:
        output.append(f"{PURPLE}~~>     :  Paru     ===     {check_paru()}{PURPLE}")

    output.append(
        f"{RESET}▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁{RESET}\n\n {GREEN}=== {GREEN}Updates : {sum_updates()}{GREEN} ===\n"
    )
    print("\n".join(output))


def get_check_pacman() -> int:
    if not shell("command -v checkupdates"):
        return 0

    attempt = 0

    while True:
        result = shell("checkupdates | wc -l")

        if "ERROR: Cannot fetch updates" in result or result == "":
            attempt += 1
            if attempt == 5:
                print(YELLOW, f"{WARN_ICON} Pacman could not update", YELLOW)
        else:
            return int(result) if result.isdigit() else 0


def check_pacman() -> int:
    return get_check_pacman()


def check_yay() -> int:
    if not shell("command -v yay"):
        return 0
    updates = shell("yay -Qua | wc -l")
    return int(updates) if updates.isdigit() else 0


def check_paru() -> int:
    if not shell("command -v paru"):
        return 0
    updates = shell("paru -Qua | wc -l")
    return int(updates) if updates.isdigit() else 0


def check_flatpak() -> int:
    if not shell("command -v flatpak"):
        return 0
    updates = shell("flatpak remote-ls --updates | wc -l")
    return int(updates) if updates.isdigit() else 0


def sum_updates():
    sum_update = 0

    if PACMAN:
        sum_update += int(check_pacman())
    if YAY:
        sum_update += int(check_yay())
    if PARU:
        sum_update += int(check_paru())
    if FLATPAK:
        sum_update += int(check_flatpak())

    if NOTIFY:
        shell(f"notify-send '{INFO_ICON} Updates : {sum_update}'")

    return sum_update


def fetch():
    os_icon = ""
    kernel_icon = ""
    wm_icon = ""
    shell_icon = ""
    uptime_icon = ""
    memory_icon = ""
    pacman_icon = "󰮯"

    # ANSI colors
    c0 = "\033[38;5;243m"
    c1 = "\033[31m"
    c2 = "\033[32m"
    c3 = "\033[33m"
    c4 = "\033[34m"
    c7 = "\033[37m"
    PURPLE = "\033[35m"
    CYAN = "\033[36m"
    YELLOW = "\033[33m"
    GREEN = "\033[32m"
    RESET = "\033[0m"
    BLUE = "\033[34m"
    RED = "\033[31m"
    user = shell("whoami")
    host = shell("uname -n")
    os_info = shell("source /etc/os-release && echo $PRETTY_NAME")
    kernel = shell("uname -sr")
    wm = shell(
        "xprop -root _NET_SUPPORTING_WM_CHECK 2>/dev/null | awk '{print $5}' | xargs -I {} xprop -id {} _NET_WM_NAME 2>/dev/null | cut -d '\"' -f 2"
    )
    shell_info = os.path.basename(os.environ.get("SHELL", "unknown"))
    mem_info = shell("free -m | awk '/^Mem:/ {print $3, $2}'").split()
    mem_used, mem_total = mem_info if len(mem_info) == 2 else ("0", "0")
    pacman_count = shell("pacman -Q 2>/dev/null | wc -l")
    colors = shell('for i in {0..7}; do echo -en "\\e[38;5;$((30 + i))m▁▁▁"; done')

    # Uptime function
    def get_uptime():
        seconds = int(float(open("/proc/uptime").read().split()[0]))
        days, seconds = divmod(seconds, 86400)
        hours, seconds = divmod(seconds, 3600)
        minutes, _ = divmod(seconds, 60)
        uptime = ""
        if days:
            uptime += f"{days}d "
        if hours:
            uptime += f"{hours}h "
        if minutes or not uptime:
            uptime += f"{minutes}m"
        return uptime

    uptime = get_uptime()

    # Output the system info
    print(f"""
{c0} ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁
{c0} ▎▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▎ {c2} {c0} {c3} {c0}{c1}  {c0}▎ {c1}{c4}{c1} {c4}{user}@{c1}{host} {PURPLE}<3 ^^{PURPLE}
{c0} ▎                            ▎ {c4}
{c0} ▎        {c4}█▀▀▀▀▀▀▀▀▀█{c0}         ▎  {CYAN}{os_icon} {CYAN}  ▎ {c4}os      {c7} {os_info}
{c0} ▎        {c4}█         █{c0}         ▎  {GREEN}{kernel_icon} {GREEN}  ▎ {c4}kr      {c7} {kernel}
{c0} ▎        {c4}█  █   █  █{c0}         ▎  {PURPLE}{wm_icon} {PURPLE}  ▎ {c4}wm      {c7} {wm}
{c0} ▎        {c0}█         █{c0}         ▎  {RESET}{shell_icon} {RESET}  ▎ {c4}sh      {c7} {shell_info}
{c0} ▎        {c0}▀█▄▄▄▄▄▄▄█▀{c0}         ▎  {YELLOW}{pacman_icon} {YELLOW}  ▎ {c4}pkgs    {c7} {pacman_count}
{c0} ▎                            ▎  {BLUE}{uptime_icon} {BLUE}  ▎{c4} uptime  {c7} {uptime}
{c0} ▎ {c4}{os_info}   {user} ^^  {c0} ▎  {RED}{memory_icon} {RED}  ▎{c4} ram     {c7} {mem_used} / {mem_total} MiB
{c0} ▎▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▎ {colors}
{RESET} 
""")


def check_font():
    font_list = [
        "Nerd",
        "NerdFont",
        "Nerd Font",
        "nerd font",
        "nerdfont",
        "nerd",
    ]

    font_info = shell("fc-list :family")

    if any(font in font_info for font in font_list):
        if FONT_CHECK:
            print("Nerd Font found")
            print("\n▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n")
            print("\n".join(f for f in font_list if f in font_info))
            print("▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n")

        return True
    else:
        print("\n\nNerd Font not found")
        print("Install it from https://www.nerdfonts.com")
        print("-" * 30)
        print(f"{GREEN}sudo pacman -S ttf-nerd-fonts-symbols{GREEN}\n\n")


if __name__ == "__main__":
    main()
