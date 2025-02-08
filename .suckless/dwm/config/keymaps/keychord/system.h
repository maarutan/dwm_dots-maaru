#include "../../variables/keymaps/system.h"

#define SYSTEM                                                                                \
    &((Keychord){2, {{MODKEY, XK_s}, {0, XK_u}}, spawn, SHCMD(SCRIPT_UPDATE)}),               \
        &((Keychord){2, {{MODKEY, XK_s}, {0 | SHIFT, XK_p}}, spawn, SHCMD(SCRIPT_PUSHDOTS)}), \
        &((Keychord){2, {{MODKEY, XK_s}, {0, XK_r}}, recompile_and_restart, {0}}),            \
        &((Keychord){3, {{MODKEY, XK_s}, {0, XK_s}, {0, XK_t}}, toggleSystray, {0}}),         \
        &((Keychord){2, {{MODKEY, XK_s}, {0, XK_t}}, spawn, SHCMD(SCRIPT_TOGGLE_TOUCHPAD)}),  \
        &((Keychord){2, {{MODKEY, XK_s}, {0, XK_d}}, toggle_bottGaps, {0}}),                  \
        &((Keychord){2, {{MODKEY, XK_s}, {0, XK_b}}, spawn, SHCMD(SCRIPT_BLUETOOTH)}),        \
        &((Keychord){2, {{MODKEY, XK_s}, {0, XK_n}}, spawn, SHCMD(SCRIPT_NMTUI)}),            \
        &((Keychord){2, {{MODKEY, XK_s}, {0, XK_p}}, spawn, SHCMD(SCRIPT_POWERMENU)}),        \
        &((Keychord){2, {{MODKEY, XK_s}, {0, XK_l}}, spawn, SHCMD(SCRIPT_SCREEN_LOCK)}),      \
        &((Keychord){2, {{MODKEY, XK_s}, {0, XK_q}}, spawn, SHCMD(SCRIPT_QURAN)})
