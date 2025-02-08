#include "../../variables/keymaps/rofi.h"

#define ROFI                                                            \
    &((Keychord){1, {{MODKEY, XK_r}}, spawn, ROFI_LAUNCHER}),           \
        &((Keychord){1, {{MODKEY, XK_v}}, spawn, ROFI_CLIPBOARD}),      \
        &((Keychord){1, {{MODKEY | ALTKEY, XK_a}}, spawn, ROFI_EMOJI}), \
        &((Keychord){1, {{MODKEY | SHIFT, XK_s}}, spawn, ROFI_SERF})
