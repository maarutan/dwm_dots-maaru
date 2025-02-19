#!/usr/bin/env python3
import os
import subprocess
import re
import threading
from time import sleep

HOME = os.getenv("HOME")

CURRENT_FILE = f"{HOME}/.suckless/scripts/dwmbScripts/.currentCava"
CONFIG_FILE = "/tmp/cava_tmp_config"


def pkill_loop():
    """Функция для непрерывного выполнения pkill в фоновом потоке"""
    while True:
        os.system("kill -RTMIN+2 $(pgrep dwmblocks)")
        sleep(0.1)


def main():
    # Запускаем pkill в фоновом потоке
    pkill_thread = threading.Thread(target=pkill_loop, daemon=True)
    pkill_thread.start()

    while True:
        try:
            config_path = CONFIG_FILE
            output_file = os.path.expanduser(CURRENT_FILE)

            create_cava_config(config_path)
            process_cava_output(config_path, output_file)
        except KeyboardInterrupt:
            print("\n  cancel  ")
            break


def check_current_file():
    if not os.path.exists(CURRENT_FILE):
        with open(CURRENT_FILE, "w") as f:
            f.write("▁▁▁▁▁▁▁▁▁▁")


def create_cava_config(config_path):
    config_content = """
[general]
bars = 10

[output]
method = raw
raw_target = /dev/stdout
data_format = ascii
ascii_max_range = 7
"""
    with open(config_path, "w") as f:
        f.write(config_content)


def process_cava_output(config_path, output_file):
    bar = "▁▂▃▄▅▆▇█"

    # Создаём словарь замены
    replace_dict = {str(i): bar[i] for i in range(len(bar))}
    pattern = re.compile("|".join(replace_dict.keys()))

    while True:
        process = subprocess.Popen(
            ["cava", "-p", config_path], stdout=subprocess.PIPE, text=True
        )
        with open(output_file, "r+") as out_file:
            previous_content = out_file.read().strip()
            for line in iter(process.stdout.readline, ""):  # pyright: ignore
                line = line.strip().replace(";", "")
                transformed_line = (
                    pattern.sub(lambda m: replace_dict[m.group(0)], line)
                    if line
                    else previous_content
                )
                out_file.seek(0)
                out_file.write(transformed_line + "\n")
                out_file.truncate()
                out_file.flush()


if __name__ == "__main__":
    main()
