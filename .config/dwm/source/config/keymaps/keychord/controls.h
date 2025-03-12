#include "../../variables/keymaps/controls.h"

#define CONTROLS                                                                  \
    &((Keychord){1, {{MODKEY | CTRL, 0x5b}}, spawn, WALLPAPER_LEFT}),             \
        &((Keychord){1, {{MODKEY | CTRL, 0x5d}}, spawn, WALLPAPER_RIGHT}),        \
        &((Keychord){1, {{MODKEY | SHIFT, 0x5b}}, spawn, BRIGHTNESS_UP}),         \
        &((Keychord){1, {{MODKEY, XK_q}}, killclient, {0}}),                      \
        &((Keychord){1, {{MODKEY | SHIFT, 0x5d}}, spawn, BRIGHTNESS_DOWN}),       \
        &((Keychord){1, {{MODKEY, 0x5b}}, spawn, VOLUME_UP}),                     \
        &((Keychord){1, {{MODKEY, 0x5d}}, spawn, VOLUME_DOWN}),                   \
        &((Keychord){1, {{MODKEY, 0x5c}}, spawn, VOLUME_MUTE}),                   \
        &((Keychord){1, {{MODKEY, XK_space}}, spawn, CHANGE_KEYBOARD}),           \
        &((Keychord){1, {{CTRL, XK_grave}}, spawn, CAPS_LOCK_TOGGLE}),            \
        &((Keychord){1, {{CTRL | SHIFT, XK_grave}}, spawn, RELOAD_KEYBOARD}),     \
        &((Keychord){1, {{MODKEY, XK_f}}, togglefullscr, {0}}),                   \
        &((Keychord){1, {{MODKEY | SHIFT, XK_h}}, viewprev, {0}}),                \
        &((Keychord){1, {{MODKEY | SHIFT, XK_l}}, viewnext, {0}}),                \
        &((Keychord){1, {{MODKEY | SHIFT | CTRL, XK_h}}, viewprevwithmove, {0}}), \
        &((Keychord){1, {{MODKEY | SHIFT | CTRL, XK_l}}, viewnextwithmove, {0}}), \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_b}}, togglebar, {0}}),            \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_p}}, toggle_padding, {0}}),       \
        &((Keychord){1, {{MODKEY, XK_Tab}}, view, {0}}),                          \
        &((Keychord){1, {{MODKEY, XK_0}}, view, {.ui = ~0}}),                     \
        &((Keychord){1, {{ALTKEY, XK_Tab}}, spawn, ALTTAB}),                      \
        &((Keychord){1, {{MODKEY, XK_o}}, winview, {0}})
