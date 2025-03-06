/* ███████╗██████╗  █████╗ ██████╗ ██████╗ ███████╗ */
/* ██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔════╝ */
/* █████╗  ██████╔╝███████║██████╔╝██████╔╝█████╗   */
/* ██╔══╝  ██╔══██╗██╔══██║██╔═══╝ ██╔═══╝ ██╔══╝   */
/* ██║     ██║  ██║██║  ██║██║     ██║     ███████╗ */
/* ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝     ╚══════╝ */

// General colors
static const char COLOR_FG_NOACTIVE[] = "#c6d0f5";
static const char COLOR_FG_ACTIVE[] = "#c6d0f5";
static const char COLOR_BG_BASE[] = "#303446";
static const char COLOR_BORDER_ACTIVE[] = "#8caaee";
static const char COLOR_BG_NOACTIVE[] = "#414559";
static const char COLOR_BG_SELECTED[] = "#51576d";
static const char COLOR_FG_LOGO[] = "#8caaee";
static const char COLOR_BG_LOGO[] = "#303446";
static const char COLOR_BORDER_LOGO[] = "#8caaee";
static const char COLOR_FG_POWER[] = "#303446";
static const char COLOR_BG_POWER[] = "#e78284";
static const char COLOR_BORDER_POWER[] = "#e78284";
static const char COLOR_BG_TITLE[] = "#303446";

// Tag 1 colors
static const char FG_TAG_1_ACTIVE[] = "#303446";
static const char BG_TAG_1_ACTIVE[] = "#e78284";
static const char FG_TAG_1_INACTIVE[] = "#ca9ee6";
static const char BG_TAG_1_INACTIVE[] = "#303446";

// Tag 2 colors
static const char FG_TAG_2_ACTIVE[] = "#303446";
static const char BG_TAG_2_ACTIVE[] = "#ca9ee6";
static const char FG_TAG_2_INACTIVE[] = "#e78284";
static const char BG_TAG_2_INACTIVE[] = "#303446";

// Tag 3 colors
static const char FG_TAG_3_ACTIVE[] = "#303446";
static const char BG_TAG_3_ACTIVE[] = "#e5c890";
static const char FG_TAG_3_INACTIVE[] = "#a6d189";
static const char BG_TAG_3_INACTIVE[] = "#303446";

// Tag 4 colors
static const char FG_TAG_4_ACTIVE[] = "#303446";
static const char BG_TAG_4_ACTIVE[] = "#a6d189";
static const char FG_TAG_4_INACTIVE[] = "#e5c890";
static const char BG_TAG_4_INACTIVE[] = "#303446";

// Tag 5 colors
static const char FG_TAG_5_ACTIVE[] = "#303446";
static const char BG_TAG_5_ACTIVE[] = "#81c8be";
static const char FG_TAG_5_INACTIVE[] = "#8caaee";
static const char BG_TAG_5_INACTIVE[] = "#303446";

// Tag 6 colors
static const char FG_TAG_6_ACTIVE[] = "#303446";
static const char BG_TAG_6_ACTIVE[] = "#8caaee";
static const char FG_TAG_6_INACTIVE[] = "#81c8be";
static const char BG_TAG_6_INACTIVE[] = "#303446";

// Tag 7 colors
static const char FG_TAG_7_ACTIVE[] = "#303446";
static const char BG_TAG_7_ACTIVE[] = "#f4b8e4";
static const char FG_TAG_7_INACTIVE[] = "#ca9ee6";
static const char BG_TAG_7_INACTIVE[] = "#303446";

// Tag 8 colors
static const char FG_TAG_8_ACTIVE[] = "#303446";
static const char BG_TAG_8_ACTIVE[] = "#ca9ee6";
static const char FG_TAG_8_INACTIVE[] = "#99d1db";
static const char BG_TAG_8_INACTIVE[] = "#303446";

// Tag 9 colors
static const char FG_TAG_9_ACTIVE[] = "#303446";
static const char BG_TAG_9_ACTIVE[] = "#99d1db";
static const char FG_TAG_9_INACTIVE[] = "#f4b8e4";
static const char BG_TAG_9_INACTIVE[] = "#303446";

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
