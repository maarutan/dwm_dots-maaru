#include "../../variables/keymaps/monitor.h"

#define MONITOR                                                                           \
    &((Keychord){1, {{MODKEY, XK_comma}}, focusmon, {.i = FOCUSMON_PREV_VALUE}}),         \
        &((Keychord){1, {{MODKEY, XK_period}}, focusmon, {.i = FOCUSMON_NEXT_VALUE}}),    \
        &((Keychord){1, {{MODKEY | SHIFT, XK_comma}}, tagmon, {.i = TAGMON_PREV_VALUE}}), \
        &((Keychord){1, {{MODKEY | SHIFT, XK_period}}, tagmon, {.i = TAGMON_NEXT_VALUE}})
