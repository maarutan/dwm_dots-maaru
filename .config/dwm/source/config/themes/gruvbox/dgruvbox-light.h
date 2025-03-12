/* ██╗     ██╗ ██████╗ ██╗  ██╗████████╗ */
/* ██║     ██║██╔════╝ ██║  ██║╚══██╔══╝ */
/* ██║     ██║██║  ███╗███████║   ██║ */
/* ██║     ██║██║   ██║██╔══██║   ██║ */
/* ███████╗██║╚██████╔╝██║  ██║   ██║ */
// General colors
static const char COLOR_FG_NOACTIVE[] = "#928374"; // Gray (inactive text)
static const char COLOR_FG_ACTIVE[] = "#3c3836";   // Dark brown (active text)
static const char COLOR_BG_BASE[] = "#fbf1c7";     // Light yellow (background)
static const char COLOR_BORDER_ACTIVE[] = "#ebdbb2"; // Orange (active border)
static const char COLOR_BG_NOACTIVE[] = "#928374";   // Beige (inactive bg)
static const char COLOR_BG_SELECTED[] = "#d5c4a1";  // Light gray (selection bg)
static const char COLOR_FG_LOGO[] = "#b57614";      // Yellow-orange
static const char COLOR_BG_LOGO[] = "#fbf1c7";      // Background
static const char COLOR_BORDER_LOGO[] = "#b57614";  // Yellow-orange
static const char COLOR_FG_POWER[] = "#fbf1c7";     // Background
static const char COLOR_BG_POWER[] = "#cc241d";     // Red
static const char COLOR_BORDER_POWER[] = "#cc241d"; // Red
static const char COLOR_BG_TITLE[] = "#fbf1c7";     // Background

// Tag 1 colors
static const char FG_TAG_1_ACTIVE[] = "#fbf1c7";   // Background
static const char BG_TAG_1_ACTIVE[] = "#d65d0e";   // Orange
static const char FG_TAG_1_INACTIVE[] = "#b57614"; // Yellow-orange
static const char BG_TAG_1_INACTIVE[] = "#fbf1c7"; // Background

// Tag 2 colors
static const char FG_TAG_2_ACTIVE[] = "#fbf1c7";
static const char BG_TAG_2_ACTIVE[] = "#b57614";   // Yellow-orange
static const char FG_TAG_2_INACTIVE[] = "#d65d0e"; // Orange
static const char BG_TAG_2_INACTIVE[] = "#fbf1c7";

// Tag 3 colors
static const char FG_TAG_3_ACTIVE[] = "#fbf1c7";
static const char BG_TAG_3_ACTIVE[] = "#98971a";   // Green
static const char FG_TAG_3_INACTIVE[] = "#b57614"; // Yellow-orange
static const char BG_TAG_3_INACTIVE[] = "#fbf1c7";

// Tag 4 colors
static const char FG_TAG_4_ACTIVE[] = "#fbf1c7";
static const char BG_TAG_4_ACTIVE[] = "#458588";   // Cyan
static const char FG_TAG_4_INACTIVE[] = "#98971a"; // Green
static const char BG_TAG_4_INACTIVE[] = "#fbf1c7";

// Tag 5 colors
static const char FG_TAG_5_ACTIVE[] = "#fbf1c7";
static const char BG_TAG_5_ACTIVE[] = "#b16286";   // Pink
static const char FG_TAG_5_INACTIVE[] = "#458588"; // Cyan
static const char BG_TAG_5_INACTIVE[] = "#fbf1c7";

// Tag 6 colors
static const char FG_TAG_6_ACTIVE[] = "#fbf1c7";
static const char BG_TAG_6_ACTIVE[] = "#d79921";   // Orange-yellow
static const char FG_TAG_6_INACTIVE[] = "#b16286"; // Pink
static const char BG_TAG_6_INACTIVE[] = "#fbf1c7";

// Tag 7 colors
static const char FG_TAG_7_ACTIVE[] = "#fbf1c7";
static const char BG_TAG_7_ACTIVE[] = "#98971a";   // Green
static const char FG_TAG_7_INACTIVE[] = "#d79921"; // Orange-yellow
static const char BG_TAG_7_INACTIVE[] = "#fbf1c7";

// Tag 8 colors
static const char FG_TAG_8_ACTIVE[] = "#fbf1c7";
static const char BG_TAG_8_ACTIVE[] = "#458588";   // Cyan
static const char FG_TAG_8_INACTIVE[] = "#d79921"; // Orange-yellow
static const char BG_TAG_8_INACTIVE[] = "#fbf1c7";

// Tag 9 colors
static const char FG_TAG_9_ACTIVE[] = "#fbf1c7";
static const char BG_TAG_9_ACTIVE[] = "#d65d0e";   // Orange
static const char FG_TAG_9_INACTIVE[] = "#458588"; // Cyan
static const char BG_TAG_9_INACTIVE[] = "#fbf1c7";

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
}; /* ╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝ */
