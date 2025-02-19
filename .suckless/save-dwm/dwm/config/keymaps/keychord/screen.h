#include "../../variables/keymaps/screen.h"

#define SCREEN                                                            \
    &((Keychord){2, {{MODKEY, XK_p}, {0, XK_c}}, spawn, PICK_COLOR}),     \
        &((Keychord){2, {{MODKEY, XK_p}, {0, XK_s}}, spawn, SCREENSHOT}), \
        &((Keychord){1, {{MODKEY, XK_l}}, spawn, SCREENLOCK}),            \
        &((Keychord){2, {{MODKEY, XK_p}, {0 | SHIFT, XK_c}}, spawn, CLOCK})
/* &((Keychord){4, {{MODKEY, XK_p}, {0, XK_p}, {0, XK_b}, {0, XK_t}}, spawn, PICOM_BLUR}),       \ */
/* &((Keychord){4, {{MODKEY, XK_p}, {0, XK_p}, {0, XK_g}, {0, XK_t}}, spawn, PICOM_GLASS}),      \ */
/* &((Keychord){4, {{MODKEY, XK_p}, {0, XK_p}, {0, XK_o}, {0, XK_t}}, spawn, PICOM_NO_OPACITY}), \ */
/* &((Keychord){3, {{MODKEY, XK_p}, {0, XK_p}, {0, XK_c}}, spawn, PICOM_CONFIG}) */
