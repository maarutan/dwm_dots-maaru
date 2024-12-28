#!/bin/sh

if [[ "$1" == "default" ]]; then
    CONFIG1="$HOME/.config/picom/blur/picom_no_anims.conf"
    CONFIG2="$HOME/.config/picom/blur/picom_simple_anims.conf"
elif [[ "$1" == "glass" ]]; then
    CONFIG1="$HOME/.config/picom/glass/picom_no_anims_glass.conf"
    CONFIG2="$HOME/.config/picom/glass/picom_simple_anims_glass.conf"
elif [[ "$1" == "nOpacity" ]]; then
    CONFIG1="$HOME/.config/picom/no_opcity/picom_no_anims.conf"
    CONFIG2="$HOME/.config/picom/no_opcity/picom_simple_anims.conf"

else
    echo "Укажите режим: 'default' или 'glass' или 'nOpacity'"
    exit 1
fi

LAST_CONFIG_FILE="$HOME/.config/picom/.last_config.txt"

if [ ! -f "$LAST_CONFIG_FILE" ]; then
    echo "$CONFIG1" > "$LAST_CONFIG_FILE"
fi

LAST_CONFIG=$(cat "$LAST_CONFIG_FILE")

if [ "$LAST_CONFIG" == "$CONFIG1" ]; then
    NEW_CONFIG="$CONFIG2"
else
    NEW_CONFIG="$CONFIG1"
fi

echo "$NEW_CONFIG" > "$LAST_CONFIG_FILE"

pkill picom
sleep 0.5
picom --config "$NEW_CONFIG" &
