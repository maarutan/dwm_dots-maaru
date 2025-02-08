/* ██╗      █████╗ ████████╗████████╗███████╗ */
/* ██║     ██╔══██╗╚══██╔══╝╚══██╔══╝██╔════╝ */
/* ██║     ███████║   ██║      ██║   █████╗   */
/* ██║     ██╔══██║   ██║      ██║   ██╔══╝   */
/* ███████╗██║  ██║   ██║      ██║   ███████╗ */
/* ╚══════╝╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝ */

// General colors
static const char COLOR_FG_NOACTIVE[] = "#4C4F69";
static const char COLOR_FG_ACTIVE[] = "#4C4F69";
static const char COLOR_BG_BASE[] = "#EFF1F5";
static const char COLOR_BORDER_ACTIVE[] = "#7287FD";
static const char COLOR_BG_NOACTIVE[] = "#CCD0DA";
static const char COLOR_BG_SELECTED[] = "#E6E9EF";
static const char COLOR_FG_LOGO[] = "#7287FD";
static const char COLOR_BG_LOGO[] = "#EFF1F5";
static const char COLOR_BORDER_LOGO[] = "#7287FD";
static const char COLOR_FG_POWER[] = "#EFF1F5";
static const char COLOR_BG_POWER[] = "#D20F39";
static const char COLOR_BORDER_POWER[] = "#D20F39";
static const char COLOR_BG_TITLE[] = "#EFF1F5";

// Tag 1 colors
static const char FG_TAG_1_ACTIVE[] = "#EFF1F5";
static const char BG_TAG_1_ACTIVE[] = "#D20F39";
static const char FG_TAG_1_INACTIVE[] = "#EA76CB";
static const char BG_TAG_1_INACTIVE[] = "#EFF1F5";

// Tag 2 colors
static const char FG_TAG_2_ACTIVE[] = "#EFF1F5";
static const char BG_TAG_2_ACTIVE[] = "#EA76CB";
static const char FG_TAG_2_INACTIVE[] = "#D20F39";
static const char BG_TAG_2_INACTIVE[] = "#EFF1F5";

// Tag 3 colors
static const char FG_TAG_3_ACTIVE[] = "#EFF1F5";
static const char BG_TAG_3_ACTIVE[] = "#E5A445";
static const char FG_TAG_3_INACTIVE[] = "#40A02B";
static const char BG_TAG_3_INACTIVE[] = "#EFF1F5";

// Tag 4 colors
static const char FG_TAG_4_ACTIVE[] = "#EFF1F5";
static const char BG_TAG_4_ACTIVE[] = "#40A02B";
static const char FG_TAG_4_INACTIVE[] = "#E5A445";
static const char BG_TAG_4_INACTIVE[] = "#EFF1F5";

// Tag 5 colors
static const char FG_TAG_5_ACTIVE[] = "#EFF1F5";
static const char BG_TAG_5_ACTIVE[] = "#209FB5";
static const char FG_TAG_5_INACTIVE[] = "#1E66F5";
static const char BG_TAG_5_INACTIVE[] = "#EFF1F5";

// Tag 6 colors
static const char FG_TAG_6_ACTIVE[] = "#EFF1F5";
static const char BG_TAG_6_ACTIVE[] = "#1E66F5";
static const char FG_TAG_6_INACTIVE[] = "#209FB5";
static const char BG_TAG_6_INACTIVE[] = "#EFF1F5";

// Tag 7 colors
static const char FG_TAG_7_ACTIVE[] = "#EFF1F5";
static const char BG_TAG_7_ACTIVE[] = "#8839EF";
static const char FG_TAG_7_INACTIVE[] = "#EA76CB";
static const char BG_TAG_7_INACTIVE[] = "#EFF1F5";

// Tag 8 colors
static const char FG_TAG_8_ACTIVE[] = "#EFF1F5";
static const char BG_TAG_8_ACTIVE[] = "#EA76CB";
static const char FG_TAG_8_INACTIVE[] = "#179299";
static const char BG_TAG_8_INACTIVE[] = "#EFF1F5";

// Tag 9 colors
static const char FG_TAG_9_ACTIVE[] = "#EFF1F5";
static const char BG_TAG_9_ACTIVE[] = "#179299";
static const char FG_TAG_9_INACTIVE[] = "#8839EF";
static const char BG_TAG_9_INACTIVE[] = "#EFF1F5";

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
