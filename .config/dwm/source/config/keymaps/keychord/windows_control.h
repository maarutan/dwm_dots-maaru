#include "../../variables/keymaps/windows_control.h"

#define WINCONTROL                                                                                           \
    &((Keychord){1, {{MODKEY, XK_j}}, moveresize, {.v = MOVE_WINDOW_J_VALUE}}),                              \
        &((Keychord){1, {{MODKEY, XK_k}}, moveresize, {.v = MOVE_WINDOW_K_VALUE}}),                          \
        &((Keychord){1, {{MODKEY, XK_l}}, moveresize, {.v = MOVE_WINDOW_L_VALUE}}),                          \
        &((Keychord){1, {{MODKEY, XK_h}}, moveresize, {.v = MOVE_WINDOW_H_VALUE}}),                          \
        &((Keychord){1, {{MODKEY | SHIFT | ALTKEY, XK_j}}, moveresize, {.v = MOVE_RESIZE_J_VALUE}}),         \
        &((Keychord){1, {{MODKEY | SHIFT | ALTKEY, XK_k}}, moveresize, {.v = MOVE_RESIZE_K_VALUE}}),         \
        &((Keychord){1, {{MODKEY | SHIFT | ALTKEY, XK_l}}, moveresize, {.v = MOVE_RESIZE_L_VALUE}}),         \
        &((Keychord){1, {{MODKEY | SHIFT | ALTKEY, XK_h}}, moveresize, {.v = MOVE_RESIZE_H_VALUE}}),         \
        &((Keychord){1, {{MODKEY | SHIFT, XK_j}}, focusstack, {.i = FOCUSSTACK_UP_VALUE}}),                  \
        &((Keychord){1, {{MODKEY | SHIFT, XK_k}}, focusstack, {.i = FOCUSSTACK_DOWN_VALUE}}),                \
        &((Keychord){1, {{MODKEY | CTRL, XK_l}}, setmfact, {.f = MFACT_INCREASE_VALUE}}),                    \
        &((Keychord){1, {{MODKEY | CTRL, XK_h}}, setmfact, {.f = MFACT_DECREASE_VALUE}}),                    \
        &((Keychord){1, {{MODKEY | CTRL, XK_j}}, movestack, {.i = MOVE_STACK_UP_VALUE}}),                    \
        &((Keychord){1, {{MODKEY | CTRL, XK_k}}, movestack, {.i = MOVE_STACK_DOWN_VALUE}}),                  \
        &((Keychord){1, {{MODKEY | CTRL, XK_Return}}, zoom, {ZOOM_CMD_VALUE}}),                              \
        &((Keychord){1, {{MODKEY | CTRL, XK_k}}, moveresizeedge, {.v = RESIZE_EDGE_T_VALUE}}),               \
        &((Keychord){1, {{MODKEY | CTRL, XK_j}}, moveresizeedge, {.v = RESIZE_EDGE_B_VALUE}}),               \
        &((Keychord){1, {{MODKEY | CTRL, XK_h}}, moveresizeedge, {.v = RESIZE_EDGE_L_VALUE}}),               \
        &((Keychord){1, {{MODKEY | CTRL, XK_l}}, moveresizeedge, {.v = RESIZE_EDGE_R_VALUE}}),               \
        &((Keychord){1, {{MODKEY | CTRL | SHIFT, XK_k}}, moveresizeedge, {.v = RESIZE_EDGE_T_SHIFT_VALUE}}), \
        &((Keychord){1, {{MODKEY | CTRL | SHIFT, XK_j}}, moveresizeedge, {.v = RESIZE_EDGE_B_SHIFT_VALUE}}), \
        &((Keychord){1, {{MODKEY | CTRL | SHIFT, XK_h}}, moveresizeedge, {.v = RESIZE_EDGE_L_SHIFT_VALUE}}), \
        &((Keychord){1, {{MODKEY | CTRL | SHIFT, XK_l}}, moveresizeedge, {.v = RESIZE_EDGE_R_SHIFT_VALUE}}), \
        &((Keychord){1, {{MODKEY | SHIFT, XK_0}}, tag, {.ui = ~0}}),                                         \
        &((Keychord){1, {{MODKEY | ALTKEY, XK_q}}, quit, {0}}),                                              \
        &((Keychord){1, {{MODKEY | CTRL, XK_q}}, spawn, KILL_DWM_CMD})
