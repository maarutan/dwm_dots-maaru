/* ███╗   ███╗ █████╗  ██████╗ ██████╗██╗  ██╗██╗ █████╗ ████████╗ ██████╗  */
/* ████╗ ████║██╔══██╗██╔════╝██╔════╝██║  ██║██║██╔══██╗╚══██╔══╝██╔═══██╗ */
/* ██╔████╔██║███████║██║     ██║     ███████║██║███████║   ██║   ██║   ██║ */
/* ██║╚██╔╝██║██╔══██║██║     ██║     ██╔══██║██║██╔══██║   ██║   ██║   ██║ */
/* ██║ ╚═╝ ██║██║  ██║╚██████╗╚██████╗██║  ██║██║██║  ██║   ██║   ╚██████╔╝ */
/* ╚═╝     ╚═╝╚═╝  ╚═╝ ╚═════╝ ╚═════╝╚═╝  ╚═╝╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝  */

// General colors
static const char COLOR_FG_NOACTIVE[] = "#cad3f5";
static const char COLOR_FG_ACTIVE[] = "#cad3f5";
static const char COLOR_BG_BASE[] = "#24273a";
static const char COLOR_BORDER_ACTIVE[] = "#8aadf4";
static const char COLOR_BG_NOACTIVE[] = "#494d64";
static const char COLOR_BG_SELECTED[] = "#3b4261";
static const char COLOR_FG_LOGO[] = "#8aadf4";
static const char COLOR_BG_LOGO[] = "#24273a";
static const char COLOR_BORDER_LOGO[] = "#8aadf4";
static const char COLOR_FG_POWER[] = "#24273a";
static const char COLOR_BG_POWER[] = "#ed8796";
static const char COLOR_BORDER_POWER[] = "#ed8796";
static const char COLOR_BG_TITLE[] = "#24273a";

// Tag 1 colors
static const char FG_TAG_1_ACTIVE[] = "#24273a";
static const char BG_TAG_1_ACTIVE[] = "#ed8796";
static const char FG_TAG_1_INACTIVE[] = "#f5a97f";
static const char BG_TAG_1_INACTIVE[] = "#24273a";

// Tag 2 colors
static const char FG_TAG_2_ACTIVE[] = "#24273a";
static const char BG_TAG_2_ACTIVE[] = "#f5a97f";
static const char FG_TAG_2_INACTIVE[] = "#ed8796";
static const char BG_TAG_2_INACTIVE[] = "#24273a";

// Tag 3 colors
static const char FG_TAG_3_ACTIVE[] = "#24273a";
static const char BG_TAG_3_ACTIVE[] = "#eed49f";
static const char FG_TAG_3_INACTIVE[] = "#a6da95";
static const char BG_TAG_3_INACTIVE[] = "#24273a";

// Tag 4 colors
static const char FG_TAG_4_ACTIVE[] = "#24273a";
static const char BG_TAG_4_ACTIVE[] = "#a6da95";
static const char FG_TAG_4_INACTIVE[] = "#eed49f";
static const char BG_TAG_4_INACTIVE[] = "#24273a";

// Tag 5 colors
static const char FG_TAG_5_ACTIVE[] = "#24273a";
static const char BG_TAG_5_ACTIVE[] = "#8bd5ca";
static const char FG_TAG_5_INACTIVE[] = "#8aadf4";
static const char BG_TAG_5_INACTIVE[] = "#24273a";

// Tag 6 colors
static const char FG_TAG_6_ACTIVE[] = "#24273a";
static const char BG_TAG_6_ACTIVE[] = "#8aadf4";
static const char FG_TAG_6_INACTIVE[] = "#8bd5ca";
static const char BG_TAG_6_INACTIVE[] = "#24273a";

// Tag 7 colors
static const char FG_TAG_7_ACTIVE[] = "#24273a";
static const char BG_TAG_7_ACTIVE[] = "#c6a0f6";
static const char FG_TAG_7_INACTIVE[] = "#f5a97f";
static const char BG_TAG_7_INACTIVE[] = "#24273a";

// Tag 8 colors
static const char FG_TAG_8_ACTIVE[] = "#24273a";
static const char BG_TAG_8_ACTIVE[] = "#f5a97f";
static const char FG_TAG_8_INACTIVE[] = "#8bd5ca";
static const char BG_TAG_8_INACTIVE[] = "#24273a";

// Tag 9 colors
static const char FG_TAG_9_ACTIVE[] = "#24273a";
static const char BG_TAG_9_ACTIVE[] = "#8bd5ca";
static const char FG_TAG_9_INACTIVE[] = "#c6a0f6";
static const char BG_TAG_9_INACTIVE[] = "#24273a";

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
