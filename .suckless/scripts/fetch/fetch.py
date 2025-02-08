#!/usr/bin/env python3

import os
import subprocess


def shell(command):
    return subprocess.getoutput(command)


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


if __name__ == "__main__":
    fetch()
