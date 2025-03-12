#include "../../variables/keymaps/settings.h"

#define SETTINGS                                                                                            \
    &((Keychord){2, {{MODKEY, XK_i}, {0, XK_d}}, spawn, SHCMD(CD_DWM)}),                                    \
        &((Keychord){2, {{MODKEY, XK_i}, {0, XK_a}}, spawn, SHCMD(OPEN_AUTOSTART)}),                        \
        &((Keychord){2, {{MODKEY, XK_i}, {0, XK_l}}, spawn, SHCMD(OPEN_LOG_DWM)}),                          \
        &((Keychord){2, {{MODKEY, XK_i}, {0, XK_s}}, spawn, SHCMD(OPEN_SCRIPTS)}),                          \
        &((Keychord){3, {{MODKEY, XK_i}, {0, XK_i}, {0, XK_c}}, spawn, SHCMD(OPEN_CONFIG)}),                \
        &((Keychord){3, {{MODKEY, XK_i}, {0, XK_i}, {0, XK_d}}, spawn, SHCMD(OPEN_DWM_C)}),                 \
        &((Keychord){4, {{MODKEY, XK_i}, {0, XK_i}, {0, XK_r}, {0, XK_c}}, spawn, SHCMD(OPEN_CONFIG_REJ)}), \
        &((Keychord){4, {{MODKEY, XK_i}, {0, XK_i}, {0, XK_r}, {0, XK_d}}, spawn, SHCMD(OPEN_DWM_REJ)})
