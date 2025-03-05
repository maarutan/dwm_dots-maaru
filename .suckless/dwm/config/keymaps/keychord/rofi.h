#include "../../variables/keymaps/rofi.h"

#define ROFI                                                                          \
    &((Keychord){1, {{MODKEY, XK_r}}, spawn, ROFI_LAUNCHER}),                         \
        &((Keychord){1, {{MODKEY, XK_v}}, spawn, ROFI_CLIPBOARD}),                    \
        &((Keychord){1, {{MODKEY | ALTKEY, XK_a}}, spawn, ROFI_EMOJI}),               \
        &((Keychord){1, {{MODKEY | SHIFT, XK_s}}, spawn, ROFI_SERF}),                 \
        &((Keychord){2, {{MODKEY, XK_p}, {0, XK_p}}, spawn, ROFI_PICOM}),             \
        &((Keychord){1, {{MODKEY | SHIFT, XK_w}}, spawn, ROFI_WALL_SELECT}),          \
        &((Keychord){2, {{MODKEY, XK_w}, {0 | SHIFT, XK_c}}, spawn, ROFI_WALL_TYPE}), \
        &((Keychord){2, {{MODKEY, XK_w}, {0 | SHIFT, XK_t}}, spawn, ROFI_THEME}),     \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_c}}, spawn, ROFI_TYPE})
