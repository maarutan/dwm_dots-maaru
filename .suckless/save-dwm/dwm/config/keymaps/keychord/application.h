#include "../../variables/keymaps/application.h"

#define APPS                                                               \
    &((Keychord){2, {{MODKEY, XK_a}, {0, XK_f}}, spawn, BROWSER}),         \
        &((Keychord){2, {{MODKEY, XK_a}, {0, XK_d}}, spawn, DISCORD}),     \
        &((Keychord){2, {{MODKEY, XK_a}, {0, XK_t}}, spawn, MASSANGER}),   \
        &((Keychord){2, {{MODKEY, XK_a}, {0, XK_v}}, spawn, CODE_EDITOR}), \
        &((Keychord){2, {{MODKEY, XK_a}, {0, XK_c}}, spawn, TERM_EDITOR}), \
        &((Keychord){1, {{MODKEY, XK_Return}}, spawn, TERM}),              \
        &((Keychord){2, {{MODKEY, XK_a}, {0, XK_b}}, spawn, MONITORING})
