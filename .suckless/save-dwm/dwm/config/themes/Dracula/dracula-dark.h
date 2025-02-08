/* ██████╗  █████╗ ██████╗ ██╗  ██╗ */
/* ██╔══██╗██╔══██╗██╔══██╗██║ ██╔╝ */
/* ██║  ██║███████║██████╔╝█████╔╝ */
/* ██║  ██║██╔══██║██╔══██╗██╔═██╗ */
/* ██████╔╝██║  ██║██║  ██║██║  ██╗ */
/* ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝ */
// General colors
static const char COLOR_FG_NOACTIVE[] = "#ff79c6";   //  Pink
static const char COLOR_FG_ACTIVE[] = "#ff79c6";     //  Pink
static const char COLOR_BG_BASE[] = "#282a36";       // Background
static const char COLOR_BORDER_ACTIVE[] = "#bd93f9"; // Purple (active border)
static const char COLOR_BG_NOACTIVE[] = "#44475a";  // Darker gray (inactive bg)
static const char COLOR_BG_SELECTED[] = "#6272a4";  // Gray-blue (selection bg)
static const char COLOR_FG_LOGO[] = "#bd93f9";      // Green
static const char COLOR_BG_LOGO[] = "#282a36";      // Background
static const char COLOR_BORDER_LOGO[] = "#50fa7b";  // Green
static const char COLOR_FG_POWER[] = "#282a36";     // Background
static const char COLOR_BG_POWER[] = "#bd93f9";     // Purple (active border)
static const char COLOR_BORDER_POWER[] = "#ff5555"; // Red
static const char COLOR_BG_TITLE[] = "#282a36";     // Background

// Tag 1 colors
static const char FG_TAG_1_ACTIVE[] = "#282a36";   // Background
static const char BG_TAG_1_ACTIVE[] = "#bd93f9";   // Red
static const char FG_TAG_1_INACTIVE[] = "#ff79c6"; // Pink
static const char BG_TAG_1_INACTIVE[] = "#282a36"; // Background

// Tag 2 colors
static const char FG_TAG_2_ACTIVE[] = "#282a36";
static const char BG_TAG_2_ACTIVE[] = "#ffb86c"; // Orange
static const char FG_TAG_2_INACTIVE[] = "#ff5555";
static const char BG_TAG_2_INACTIVE[] = "#282a36";

// Tag 3 colors
static const char FG_TAG_3_ACTIVE[] = "#282a36";
static const char BG_TAG_3_ACTIVE[] = "#f1fa8c";   // Yellow
static const char FG_TAG_3_INACTIVE[] = "#50fa7b"; // Green
static const char BG_TAG_3_INACTIVE[] = "#282a36";

// Tag 4 colors
static const char FG_TAG_4_ACTIVE[] = "#282a36";
static const char BG_TAG_4_ACTIVE[] = "#50fa7b";   // Green
static const char FG_TAG_4_INACTIVE[] = "#f1fa8c"; // Yellow
static const char BG_TAG_4_INACTIVE[] = "#282a36";

// Tag 5 colors
static const char FG_TAG_5_ACTIVE[] = "#282a36";
static const char BG_TAG_5_ACTIVE[] = "#bd93f9";   // Purple
static const char FG_TAG_5_INACTIVE[] = "#8be9fd"; // Cyan
static const char BG_TAG_5_INACTIVE[] = "#282a36";

// Tag 6 colors
static const char FG_TAG_6_ACTIVE[] = "#282a36";
static const char BG_TAG_6_ACTIVE[] = "#8be9fd";   // Cyan
static const char FG_TAG_6_INACTIVE[] = "#bd93f9"; // Purple
static const char BG_TAG_6_INACTIVE[] = "#282a36";

// Tag 7 colors
static const char FG_TAG_7_ACTIVE[] = "#282a36";
static const char BG_TAG_7_ACTIVE[] = "#ff79c6";   // Pink
static const char FG_TAG_7_INACTIVE[] = "#FFB86C"; // Orange
static const char BG_TAG_7_INACTIVE[] = "#282a36";

// Tag 8 colors
static const char FG_TAG_8_ACTIVE[] = "#282a36";
static const char BG_TAG_8_ACTIVE[] = "#ff79c6";   // Pink
static const char FG_TAG_8_INACTIVE[] = "#8be9fd"; // Cyan
static const char BG_TAG_8_INACTIVE[] = "#282a36";

// Tag 9 colors
static const char FG_TAG_9_ACTIVE[] = "#282a36";
static const char BG_TAG_9_ACTIVE[] = "#8be9fd";   // Cyan
static const char FG_TAG_9_INACTIVE[] = "#ff79c6"; // Pink
static const char BG_TAG_9_INACTIVE[] = "#282a36";

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
