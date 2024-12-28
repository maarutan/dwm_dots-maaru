#!/bin/bash

DUNST_CONFIG_DIR="$HOME/.config/dunst"
DUNST_OPAQUE_CONF="$DUNST_CONFIG_DIR/.picom/dunst_picom_2"       
DUNST_TRANSPARENT_CONF="$DUNST_CONFIG_DIR/.picom/dunst_picom_1"  
DUNST_ACTIVE_CONF="$DUNST_CONFIG_DIR/dunstrc"                
CONFIG_NAME="$1"

case "$CONFIG_NAME" in
    nOpacity)
        cat "$DUNST_OPAQUE_CONF" > "$DUNST_ACTIVE_CONF"
        ;;
    default)
        cat "$DUNST_TRANSPARENT_CONF" > "$DUNST_ACTIVE_CONF"
        ;;
    *)
        echo "Usage: $0 {nOpacity|default}"
        exit 1
        ;;
esac

pkill dunst
dunst &
