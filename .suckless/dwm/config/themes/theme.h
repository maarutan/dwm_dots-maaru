/* ███╗   ███╗ ██████╗  ██████╗██╗  ██╗ █████╗  */
/* ████╗ ████║██╔═══██╗██╔════╝██║  ██║██╔══██╗ */
/* ██╔████╔██║██║   ██║██║     ███████║███████║ */
/* ██║╚██╔╝██║██║   ██║██║     ██╔══██║██╔══██║ */
/* ██║ ╚═╝ ██║╚██████╔╝╚██████╗██║  ██║██║  ██║ */
/* ╚═╝     ╚═╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ */

// General colors
static const char COLOR_FG_NOACTIVE[] = "#cdd6f4";
static const char COLOR_FG_ACTIVE[] = "#cdd6f4";
static const char COLOR_BG_BASE[] = "#1e1e2e";
static const char COLOR_BORDER_ACTIVE[] = "#89b4fa";
static const char COLOR_BG_NOACTIVE[] = "#45475a";
static const char COLOR_BG_SELECTED[] = "#2f2f49";
static const char COLOR_FG_LOGO[] = "#8aadf4";
static const char COLOR_BG_LOGO[] = "#1e1e2e";
static const char COLOR_BORDER_LOGO[] = "#8aadf4";
static const char COLOR_FG_POWER[] = "#1e1e2e";
static const char COLOR_BG_POWER[] = "#f38ba8";
static const char COLOR_BORDER_POWER[] = "#f38ba8";
static const char COLOR_BG_TITLE[] = "#1E1E2E";

// Tag 1 colors
static const char FG_TAG_1_ACTIVE[] = "#1e1e2e";
static const char BG_TAG_1_ACTIVE[] = "#f38ba8";
static const char FG_TAG_1_INACTIVE[] = "#FAB387";
static const char BG_TAG_1_INACTIVE[] = "#1e1e2e";

// Tag 2 colors
static const char FG_TAG_2_ACTIVE[] = "#1e1e2e";
static const char BG_TAG_2_ACTIVE[] = "#fab387";
static const char FG_TAG_2_INACTIVE[] = "#F38BA8";
static const char BG_TAG_2_INACTIVE[] = "#1e1e2e";

// Tag 3 colors
static const char FG_TAG_3_ACTIVE[] = "#1e1e2e";
static const char BG_TAG_3_ACTIVE[] = "#f9e2af";
static const char FG_TAG_3_INACTIVE[] = "#A6E3A1";
static const char BG_TAG_3_INACTIVE[] = "#1e1e2e";

// Tag 4 colors
static const char FG_TAG_4_ACTIVE[] = "#1e1e2e";
static const char BG_TAG_4_ACTIVE[] = "#a6e3a1";
static const char FG_TAG_4_INACTIVE[] = "#f9e2af";
static const char BG_TAG_4_INACTIVE[] = "#1e1e2e";

// Tag 5 colors
static const char FG_TAG_5_ACTIVE[] = "#1e1e2e";
static const char BG_TAG_5_ACTIVE[] = "#89b4fa";
static const char FG_TAG_5_INACTIVE[] = "#b4befe";
static const char BG_TAG_5_INACTIVE[] = "#1e1e2e";

// Tag 6 colors
static const char FG_TAG_6_ACTIVE[] = "#1e1e2e";
static const char BG_TAG_6_ACTIVE[] = "#b4befe";
static const char FG_TAG_6_INACTIVE[] = "#89b4fa";
static const char BG_TAG_6_INACTIVE[] = "#1e1e2e";

// Tag 7 colors
static const char FG_TAG_7_ACTIVE[] = "#1e1e2e";
static const char BG_TAG_7_ACTIVE[] = "#cba6f7";
static const char FG_TAG_7_INACTIVE[] = "#f5c2e7";
static const char BG_TAG_7_INACTIVE[] = "#1e1e2e";

// Tag 8 colors
static const char FG_TAG_8_ACTIVE[] = "#1e1e2e";
static const char BG_TAG_8_ACTIVE[] = "#f5c2e7";
static const char FG_TAG_8_INACTIVE[] = "#94e2d5";
static const char BG_TAG_8_INACTIVE[] = "#1e1e2e";

// Tag 9 colors
static const char FG_TAG_9_ACTIVE[] = "#1e1e2e";
static const char BG_TAG_9_ACTIVE[] = "#94e2d5";
static const char FG_TAG_9_INACTIVE[] = "#cba6f7";
static const char BG_TAG_9_INACTIVE[] = "#1e1e2e";

// Colors array for scheme
static const char *colors[][3] = {
    [SchemeLogo] = {COLOR_FG_LOGO, COLOR_BG_LOGO, COLOR_BORDER_LOGO},
    [SchemePower] = {COLOR_BG_POWER, COLOR_FG_POWER, COLOR_BORDER_POWER},
    [SchemeNorm] = {COLOR_FG_NOACTIVE, COLOR_BG_BASE, COLOR_BG_NOACTIVE},
    [SchemeSel] = {COLOR_FG_ACTIVE, COLOR_BORDER_ACTIVE, COLOR_BORDER_ACTIVE},
    [SchemeFg] = {COLOR_BG_BASE, COLOR_BG_SELECTED, COLOR_BORDER_ACTIVE},
    [SchemeTitle] = {COLOR_FG_ACTIVE, COLOR_BG_TITLE, COLOR_BORDER_ACTIVE},
    [SchemeTag1Active] = {FG_TAG_1_ACTIVE, BG_TAG_1_ACTIVE,
                          COLOR_BORDER_ACTIVE},
    [SchemeTag1Inactive] = {FG_TAG_1_INACTIVE, BG_TAG_1_INACTIVE,
                            COLOR_BG_NOACTIVE},
    [SchemeTag2Active] = {FG_TAG_2_ACTIVE, BG_TAG_2_ACTIVE,
                          COLOR_BORDER_ACTIVE},
    [SchemeTag2Inactive] = {FG_TAG_2_INACTIVE, BG_TAG_2_INACTIVE,
                            COLOR_BG_NOACTIVE},
    [SchemeTag3Active] = {FG_TAG_3_ACTIVE, BG_TAG_3_ACTIVE,
                          COLOR_BORDER_ACTIVE},
    [SchemeTag3Inactive] = {FG_TAG_3_INACTIVE, BG_TAG_3_INACTIVE,
                            COLOR_BG_NOACTIVE},
    [SchemeTag4Active] = {FG_TAG_4_ACTIVE, BG_TAG_4_ACTIVE,
                          COLOR_BORDER_ACTIVE},
    [SchemeTag4Inactive] = {FG_TAG_4_INACTIVE, BG_TAG_4_INACTIVE,
                            COLOR_BG_NOACTIVE},
    [SchemeTag5Active] = {FG_TAG_5_ACTIVE, BG_TAG_5_ACTIVE,
                          COLOR_BORDER_ACTIVE},
    [SchemeTag5Inactive] = {FG_TAG_5_INACTIVE, BG_TAG_5_INACTIVE,
                            COLOR_BG_NOACTIVE},
    [SchemeTag6Active] = {FG_TAG_6_ACTIVE, BG_TAG_6_ACTIVE,
                          COLOR_BORDER_ACTIVE},
    [SchemeTag6Inactive] = {FG_TAG_6_INACTIVE, BG_TAG_6_INACTIVE,
                            COLOR_BG_NOACTIVE},
    [SchemeTag7Active] = {FG_TAG_7_ACTIVE, BG_TAG_7_ACTIVE,
                          COLOR_BORDER_ACTIVE},
    [SchemeTag7Inactive] = {FG_TAG_7_INACTIVE, BG_TAG_7_INACTIVE,
                            COLOR_BG_NOACTIVE},
    [SchemeTag8Active] = {FG_TAG_8_ACTIVE, BG_TAG_8_ACTIVE,
                          COLOR_BORDER_ACTIVE},
    [SchemeTag8Inactive] = {FG_TAG_8_INACTIVE, BG_TAG_8_INACTIVE,
                            COLOR_BG_NOACTIVE},
    [SchemeTag9Active] = {FG_TAG_9_ACTIVE, BG_TAG_9_ACTIVE,
                          COLOR_BORDER_ACTIVE},
    [SchemeTag9Inactive] = {FG_TAG_9_INACTIVE, BG_TAG_9_INACTIVE,
                            COLOR_BG_NOACTIVE},
};
