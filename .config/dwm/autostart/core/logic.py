import os
import sys
import subprocess
import psutil
from time import sleep

HOME = os.environ["HOME"]


def is_running(process_name) -> bool | None | int:
    for proc in psutil.process_iter(attrs=["name", "cmdline"]):
        try:
            if proc.info["name"] == process_name:
                return proc.pid
        except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess):
            pass
    return None


def kill_process(process_name) -> None:
    if is_running(process_name):
        print(f"🔪 killing process: {process_name}")
        subprocess.Popen(["pkill", "-x", process_name])

        sleep(1)

        if is_running(process_name):
            print(f"⚠ `pkill -x` is not enough, using `pkill -f {process_name}`")
            subprocess.Popen(["pkill", "-f", process_name])

        sleep(1)


def runner(*command, null=False, pkill=False) -> None:
    if not command:
        return

    blacklist = [
        "rm",
        "poweroff",
        "shutdown",
        "reboot",
        "dd",
        "mkfs",
    ]

    for cmd in command:
        first_word = cmd.split()[0] if cmd else ""

        if first_word in blacklist:
            print(f"Erorr: {first_word} is blacklisted!")
            continue

        if pkill:
            kill_process(first_word)

        if null:
            subprocess.Popen(cmd + " >/dev/null 2>&1", shell=True)
        else:
            subprocess.Popen(cmd, shell=True)


def while_run(*command, delay=1.0, null=False, pkill=False):
    if not command:
        return

    while True:
        runner(*command, null=null, pkill=pkill)
        sleep(delay)
