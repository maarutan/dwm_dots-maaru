#!/usr/bin/env bash

dir="$HOME/.config/rofi/emoji"
theme='emoji'

## Run
rofi \
    -show emoji \
    -theme ${dir}/${theme}.rasi
