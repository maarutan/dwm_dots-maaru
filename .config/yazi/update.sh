#!/bin/sh
git pull origin main
rm -rf ~/.config/yazi/plugins/yatline-catppuccin.yazi
rm -rf ~/.config/yazi/plugins/ouch.yazi
rm -rf ~/.config/yazi/plugins/yatline.yazi
git clone https://github.com/ndtoan96/ouch.yazi.git ~/.config/yazi/plugins/ouch.yazi
git clone https://github.com/imsi32/yatline-catppuccin.yazi.git ~/.config/yazi/plugins/yatline-catppuccin.yazi
ya pack --upgrade
sleep 2
clear
echo Done

