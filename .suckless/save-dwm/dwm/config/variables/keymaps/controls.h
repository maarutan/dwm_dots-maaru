#define WALLPAPER_LEFT SHCMD("$HOME/.suckless/scripts/change_wallpaper.sh left")
#define WALLPAPER_RIGHT SHCMD("$HOME/.suckless/scripts/change_wallpaper.sh right")

#define BRIGHTNESS_UP SHCMD("$HOME/.suckless/scripts/brightnessControl.sh up")
#define BRIGHTNESS_DOWN SHCMD("$HOME/.suckless/scripts/brightnessControl.sh down")

#define VOLUME_UP SHCMD("$HOME/.suckless/scripts/volume.sh up")
#define VOLUME_DOWN SHCMD("$HOME/.suckless/scripts/volume.sh down")
#define VOLUME_MUTE SHCMD("$HOME/.suckless/scripts/volume.sh mute")

#define CHANGE_KEYBOARD SHCMD("pkill -RTMIN+1 dwmblocks; $HOME/.suckless/scripts/changeKeyboard.sh; setxkbmap -layout us,ru -option 'grp:ctrl_alt_toggle' -option 'ctrl:nocaps'")
#define CAPS_LOCK_TOGGLE SHCMD("$HOME/.suckless/scripts/caps.sh")
#define RELOAD_KEYBOARD SHCMD("$HOME/.suckless/scripts/realoadKB.sh")
