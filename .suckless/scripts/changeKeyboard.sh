#!/bin/bash

COMMON_ICON="$HOME/.icons/myIcons/language.svg"
NOTIFY_ID=9999

layout=$(xset -q | grep LED | awk '{ if (substr($10,5,1) == 1) print "Russian"; else print "English"; }')
dunstify -r $NOTIFY_ID -i "$COMMON_ICON" "       $layout"
