#define WALLPAPER_LEFT SHCMD("$HOME/.suckless/scripts/wallpapers/utils/control.py left")
#define WALLPAPER_RIGHT SHCMD("$HOME/.suckless/scripts/wallpapers/utils/control.py right")

#define BRIGHTNESS_UP SHCMD("$HOME/.suckless/scripts/brightnessControl.sh up")
#define BRIGHTNESS_DOWN SHCMD("$HOME/.suckless/scripts/brightnessControl.sh down")

#define VOLUME_UP SHCMD("$HOME/.suckless/scripts/volume.sh up")
#define VOLUME_DOWN SHCMD("$HOME/.suckless/scripts/volume.sh down")
#define VOLUME_MUTE SHCMD("$HOME/.suckless/scripts/volume.sh mute")

#define CHANGE_KEYBOARD SHCMD("pkill -RTMIN+1 dwmblocks; $HOME/.suckless/scripts/changeKeyboard.sh; setxkbmap -layout us,ru -option 'grp:win_space_toggle' -option 'ctrl:nocaps'")
#define CAPS_LOCK_TOGGLE SHCMD("$HOME/.suckless/scripts/caps.sh")
#define RELOAD_KEYBOARD SHCMD("$HOME/.suckless/scripts/realoadKB.sh")
#define ALTTAB SHCMD("$HOME/.config/rofi/launchers/windows/winview.py")
