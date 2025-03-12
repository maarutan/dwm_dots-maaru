#!/usr/bin/env python3

# dwmblocks.py
# https://github.com/maarutan
# Copyright (c) 2025 |  by maaru \ maarutan

import subprocess, signal, time, sys, argparse, os, atexit


# DONE: ####   -----=== global variables ===-----   ####

DEBUG = False
HOME = os.environ["HOME"]
SIGNAL_FILE = "/tmp/block_signal"
PID_FILE = "/tmp/dwmblocks_pid"
NOW_DIR = os.path.abspath(os.path.dirname(__file__))
LOG_FILE = os.path.abspath(
    os.path.join(
        os.path.dirname(__file__), "..", "..", "..", "..", ".log", "dwmblocks.log"
    )
)
CACHE_FILE = f"{HOME}/.cache/current_xsetroot_blocks"


# INFO: ####   -----=== logic ===-----   ####

last_status_bar = ""


def setup():
    blocks = [
        Block(
            "",
            f"cat {NOW_DIR}/../current_blocks/current_language",
            0,
            1,
        ),
        Block("", f"cat {NOW_DIR}/../current_blocks/current_cava", 0.1, 0),
        Block("", f"cat {NOW_DIR}/../current_blocks/current_battery", 1, 0),
        Block(" ", f"cat {NOW_DIR}/../current_blocks/current_signal_network", 1, 0),
        Block("  ", f"cat {NOW_DIR}/../current_blocks/current_memory", 1, 0),
        Block("󰮯  ", f"cat {NOW_DIR}/../current_blocks/current_updates", 1, 0),
        Block("  ", f"cat {NOW_DIR}/../current_blocks/current_inet_speed", 1, 0),
    ]
    delim = "   "
    return blocks, delim


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-s", "--signal", type=int, help="Block number (signal) to update via SIGUSR1"
    )
    args = parser.parse_args()

    if args.signal is not None:
        if not os.path.exists(PID_FILE):
            sys.exit(1)
        try:
            with open(PID_FILE, "r") as f:
                pid = int(f.read().strip())
            os.kill(pid, 0)
        except (OSError, ValueError):
            sys.exit(1)
        with open(SIGNAL_FILE, "w") as f:
            f.write(str(args.signal))
        os.kill(pid, signal.SIGUSR1)
        sys.exit(0)

    time.sleep(0.1)
    signal.signal(signal.SIGUSR1, signal_handler)
    signal.signal(signal.SIGINT, stop_handler)
    signal.signal(signal.SIGTERM, stop_handler)

    with open(PID_FILE, "w") as f:
        f.write(str(os.getpid()))

    try:
        while True:
            for block in blocks:
                block.run()
            update_status()
            time.sleep(0.1)
    except KeyboardInterrupt:
        cleanup()
        sys.exit(0)


def shell(command) -> str:
    blacklist = ["poweroff", "reboot", "rm", "shutdown"]
    if command.split()[0] in blacklist:
        return f"skipping: {command}"
    try:
        result = subprocess.run(
            command, shell=True, text=True, capture_output=True, check=True
        )
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        return f"[ERROR] {e}"


class Block:
    def __init__(self, icon, command, interval=0.0, signal=0):
        self.icon = icon
        self.command = command
        self.interval = interval
        self.signal = signal
        self.output = ""
        self.last_run = 0

    def run(self, force=False):
        current_time = time.time()
        if (
            force
            or (self.interval > 0 and current_time - self.last_run >= self.interval)
            or (self.interval == 0 and self.output == "")
        ):
            try:
                res = subprocess.check_output(self.command, shell=True, text=True)
                self.output = f"{self.icon}{res}"
                self.last_run = current_time
            except Exception as e:
                log_message(f"Block {self.icon} error: {e}")
                self.output = f"{self.icon}[ERROR]"


blocks, delim = setup()


def cleanup():
    shell("xsetroot -name ''")
    if os.path.exists(SIGNAL_FILE):
        os.remove(SIGNAL_FILE)
    if os.path.exists(PID_FILE):
        try:
            with open(PID_FILE, "r") as f:
                pid = int(f.read().strip())
            os.kill(pid, 0)
        except (OSError, ValueError):
            os.remove(PID_FILE)


atexit.register(cleanup)


def stop_handler(signum, frame):
    cleanup()
    sys.exit(0)


def log_message(message):
    with open(LOG_FILE, "a") as log:
        log.write(f"{time.strftime('%Y-%m-%d %H:%M:%S')} - {message}\n")


def signal_handler(signum, frame):
    try:
        log_message(f"Received signal: {signum}")

        if not os.path.exists(SIGNAL_FILE):
            log_message("SIGNAL_FILE does not exist")
            return

        with open(SIGNAL_FILE, "r") as f:
            content = f.read().strip()

        if not content.isdigit():
            log_message(f"Invalid content in SIGNAL_FILE: {content}")
            return

        sig = int(content)
        log_message(f"Looking for block with signal={sig}")

        found_block = False
        for block in blocks:
            if block.signal == sig:
                block.run(force=True)
                update_status()
                found_block = True
                break

        if not found_block:
            log_message(f"No block found with signal={sig}")

    except Exception as e:
        log_message(f"Signal handler error: {e}")


def update_status():
    global last_status_bar

    status_parts = [block.output for block in blocks]
    new_status_bar = delim.join(status_parts)

    if not new_status_bar:
        if os.path.exists(CACHE_FILE):
            with open(CACHE_FILE, "r") as cf:
                cached_bar = cf.read()
            if cached_bar:
                new_status_bar = cached_bar
                log_message("[update_status] used cached status bar")

    if not new_status_bar:
        log_message("[update_status] status bar empty skipped update")
        return

    if new_status_bar != last_status_bar:
        shell(f"xsetroot -name '{new_status_bar}'")
        with open(CACHE_FILE, "w") as cf:
            cf.write(new_status_bar + "\n")

        last_status_bar = new_status_bar


if __name__ == "__main__":
    main()
