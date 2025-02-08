#define RECOMPILE_COMMAND              \
    "cd \"$HOME/.suckless/dwm\" && "   \
    "make clean install && "           \
    "pgrep -x dwm | xargs -r kill || " \
    "notify-send 'Ошибка при перекомпиляции dwm'"
