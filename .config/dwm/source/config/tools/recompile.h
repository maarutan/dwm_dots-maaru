#define RECOMPILE_COMMAND                 \
    "cd \"$HOME/.config/dwm/source\" && " \
    "make clean install && "              \
    "pgrep -x dwm | xargs -r kill || "    \
    "notify-send 'Failed to recompile dwm'"
