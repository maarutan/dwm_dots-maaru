#!/usr/bin/env python
from core.logic import *


def main():
    runner(
        'picom --config "$(cat $HOME/.config/picom/.current_config)"',
        "$HOME/.suckless/scripts/wallpapers/autostart.py",
        "dunst",
        "$HOME/.suckless/scripts/battery-alert.sh",
        "setsid $HOME/.config/dwm/source/config/blocks/core/dwmblocks.py",
        "$HOME/.config/dwm/source/config/blocks/start.py",
        "greenclip daemon",
        "xsettingsd",
        "setxkbmap -layout us,ru -option 'grp:ctrl_alt_toggle' -option 'ctrl:nocaps'",
    )

    while_run(
        "$HOME/.local/bin/dwm >> $HOME/.config/dwm/.log/dwm.log || dwm ",
    )


if __name__ == "__main__":
    try:
        main()
        sys.exit()

    except KeyboardInterrupt:
        print("\n   cancel <3")
        sys.exit()
