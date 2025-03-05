// key definitions
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define SHIFT ShiftMask
#define CTRL ControlMask
#define TAGKEYS(KEY, TAG)                                                       \
    &((Keychord){1, {{MODKEY, KEY}}, view, {.ui = 1 << TAG}}),                  \
        &((Keychord){1, {{MODKEY | CTRL, KEY}}, toggleview, {.ui = 1 << TAG}}), \
        &((Keychord){1, {{MODKEY | SHIFT, KEY}}, tag, {.ui = 1 << TAG}}),       \
        &((Keychord){                                                           \
            1, {{MODKEY | CTRL | SHIFT, KEY}}, previewtag, {.ui = TAG}}),

#define SHCMD(cmd)                                           \
    {                                                        \
        .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } \
    }
