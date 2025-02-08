#!/bin/bash

# Создаем временный файл для скриншота
TEMP_SCREENSHOT="/tmp/lockscreen_screenshot.png"
TEMP_BLURRED="/tmp/lockscreen_screenshot_blurred.png"

# Проверяем наличие необходимых утилит
if ! command -v scrot &> /dev/null; then
    echo "Ошибка: 'scrot' не установлен. Установи его и попробуй снова."
    exit 1
fi

if ! command -v convert &> /dev/null; then
    echo "Ошибка: 'ImageMagick' не установлен. Установи его и попробуй снова."
    exit 1
fi

# Делаем скриншот экрана с помощью scrot
scrot "$TEMP_SCREENSHOT"

# Применяем размытие с помощью ImageMagick
convert "$TEMP_SCREENSHOT" -blur 0x5 "$TEMP_BLURRED"

# Устанавливаем размытое изображение в качестве фона для betterlockscreen
betterlockscreen -u "$TEMP_BLURRED"

# Блокируем экран
betterlockscreen -l

# Удаляем временные файлы
rm -f "$TEMP_SCREENSHOT" "$TEMP_BLURRED"
