#include "../../variables/keymaps/windows.h"

#define WINDOWS                                                                                                 \
    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_1}}, setlayout, {.v = LAYOUT_SPIRAL}}),                             \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_2}}, setlayout, {.v = LAYOUT_DWINDLE}}),                        \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_3}}, setlayout, {.v = LAYOUT_TILE}}),                           \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_4}}, setlayout, {.v = LAYOUT_BSTACK}}),                         \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_5}}, setlayout, {.v = LAYOUT_CENTEREDMASTER}}),                 \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_6}}, setlayout, {.v = LAYOUT_NROWGRID}}),                       \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_7}}, setlayout, {.v = LAYOUT_GRID}}),                           \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_8}}, setlayout, {.v = LAYOUT_GAPLESSGRID}}),                    \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_9}}, setlayout, {.v = LAYOUT_MONOCLE}}),                        \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_0}}, setlayout, {.v = LAYOUT_DESK}}),                           \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_Tab}}, toggleAttachBelow, {0}}),                                \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_w}}, togglefloating, {0}}),                                     \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_l}}, setlayout, {0}}),                                          \
        &((Keychord){2, {{MODKEY, XK_w}, {0 | SHIFT, XK_g}}, togglesmartgaps, {0}}),                            \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_t}}, toggleTagBoxes, {0}}),                                     \
        &((Keychord){3, {{MODKEY, XK_w}, {0, XK_m}, {0 | SHIFT, XK_g}}, toggle_always_smartgaps_monocle, {0}}), \
        &((Keychord){1, {{MODKEY | SHIFT, XK_w}}, spawn, SCRIPT_WIFI}),                                         \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_c}}, spawn, SCRIPT_PICWALL}),                                   \
        &((Keychord){3, {{MODKEY, XK_w}, {0, XK_a}, {0, XK_t}}, toggleshowtitle, {0}}),                         \
        &((Keychord){3, {{MODKEY, XK_w}, {0, XK_a}, {0, XK_h}}, hidewin, {0}}),                                 \
        &((Keychord){3, {{MODKEY, XK_w}, {0, XK_a}, {0, XK_s}}, restorewin, {0}}),                              \
        &((Keychord){3, {{MODKEY, XK_w}, {0, XK_a}, {0 | SHIFT, XK_s}}, showall, {0}}),                         \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_f}}, spawn, L_CLICK}),                                          \
        &((Keychord){2, {{MODKEY, XK_w}, {0 | SHIFT, XK_f}}, spawn, R_CLICK}),                                  \
        &((Keychord){2, {{MODKEY, XK_w}, {0, XK_g}}, spawn, GRID_CLICK}),                                       \
        &((Keychord){1, {{MODKEY, XK_u}}, incnmaster, {.i = +1}}),                                              \
        &((Keychord){1, {{MODKEY, XK_d}}, incnmaster, {.i = -1}})
