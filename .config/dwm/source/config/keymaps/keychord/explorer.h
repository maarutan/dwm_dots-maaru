#include "../../variables/keymaps/explorer.h"

#define EXPLORER                                                             \
    &((Keychord){2, {{MODKEY, XK_e}, {0, XK_y}}, spawn, FILE_MANAGER_YAZI}), \
        &((Keychord){2, {{MODKEY, XK_e}, {0, XK_n}}, spawn, FILE_MANAGER_NEMO})
