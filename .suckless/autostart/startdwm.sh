#!/bin/bash

export QT_QPA_PLATFORMTHEME=qt5ct

APPLICATIONS=(
    "xsettingsd"
    "picom --config \"$(cat $HOME/.config/picom/.current_config)\""
    "libinput-gestures-setup start"
    "dunst"
    "greenclip daemon"
    "setsid feh --no-fehbg --bg-scale \"$(echo $(cat $HOME/.cache/current_wallpaper))\""
    "$HOME/.local/bin/dwmblocks || dwmblocks"
    "$HOME/.suckless/scripts/dwmbScripts/blocks.sh"
    "$HOME/.suckless/scripts/battery-alert.sh"
    "blueman-applet"
    # "plank"
)

kill_existing_instances() {
    local app_name="$1"
    echo "Завершаю старые экземпляры $app_name..."
    pkill -f "$app_name" 2>/dev/null || echo "$app_name не запущен."
}

run_application() {
    local app_command="$1"

    local app_name=$(echo "$app_command" | awk '{print $1}')

    if pgrep -x "$app_name" > /dev/null; then
        echo "$app_name уже запущен. Завершаю его."
        kill_existing_instances "$app_name"
    fi

    if [[ "$app_name" == "feh" ]]; then
        if [[ ! -f ~/.current_wallpaper ]]; then
            echo "Файл ~/.current_wallpaper не найден. Пропускаю feh."
            return
        fi
    fi

    echo "Запуск $app_name..."
    eval "$app_command" &
}

echo "Настройка раскладки клавиатуры..."
setxkbmap -layout us,ru -option 'grp:ctrl_alt_toggle' -option 'ctrl:nocaps'

for app_command in "${APPLICATIONS[@]}"; do
    run_application "$app_command"
done

export PATH=$PATH:$HOME/.local/bin
#
echo "Запуск оконного менеджера dwm..."
while true; do
    setxkbmap -layout us,ru -option 'grp:ctrl_alt_toggle' -option 'ctrl:nocaps'
    dwmblocks 2>~/.dwmblocks.log &
    dwm 2>~/.dwm.log

done

