#!/bin/bash

# Массив со списком скриптов
SCRIPTS=(
    "$HOME/.suckless/scripts/dwmbScripts/batteryInfo.sh"
    "$HOME/.suckless/scripts/dwmbScripts/internet.sh"
    "$HOME/.suckless/scripts/dwmbScripts/showInternet.sh"
    "$HOME/.suckless/scripts/dwmbScripts/updateInfo.py"
    # "$HOME/.suckless/scripts/dwmbScripts/printCava.py"
    "$HOME/.suckless/scripts/dwmbScripts/memory.sh"
    # "$HOME/.suckless/scripts/dwmbScripts/weather.sh"
)

# Перезапуск всех скриптов из списка
for script in "${SCRIPTS[@]}"; do
    # Убиваем старый процесс скрипта
    pkill -f "$script" && echo "Остановлен: $script"

    # Запускаем новый процесс скрипта
    if [[ "$script" == *.py ]]; then
        # Для Python-скриптов используем python3
        python3 "$script" &
    else
        "$script" &
    fi
    echo "Запущен: $script"
done

