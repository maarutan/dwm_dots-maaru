#!/bin/bash

KITTY_CONFIG_DIR="$HOME/.config/kitty"
KITTY_OPAQUE_CONF="$KITTY_CONFIG_DIR/.other/kitty_picom_1.conf"
KITTY_TRANSPARENT_CONF="$KITTY_CONFIG_DIR/.other/kitty_picom_2.conf"
KITTY_ACTIVE_CONF="$KITTY_CONFIG_DIR/kitty.conf"

case "$1" in
    nOpacity) cat "$KITTY_OPAQUE_CONF" > "$KITTY_ACTIVE_CONF" ;;
    default) cat "$KITTY_TRANSPARENT_CONF" > "$KITTY_ACTIVE_CONF" ;;
    *) exit 1 ;;
esac

