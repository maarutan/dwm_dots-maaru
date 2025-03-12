#include "../../variables/keymaps/screen.h"

#define SCREEN                                                            \
    &((Keychord){2, {{MODKEY, XK_p}, {0, XK_c}}, spawn, PICK_COLOR}),     \
        &((Keychord){2, {{MODKEY, XK_p}, {0, XK_s}}, spawn, SCREENSHOT}), \
        &((Keychord){1, {{MODKEY, XK_grave}}, spawn, SCREENLOCK}),        \
        &((Keychord){2, {{MODKEY, XK_p}, {0 | SHIFT, XK_c}}, spawn, CLOCK})
