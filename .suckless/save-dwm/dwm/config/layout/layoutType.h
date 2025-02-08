#include "../../patches/vanitygaps.c"

static const Layout layouts[] = {
    // first entry is default ,
    {"[@]", spiral},
    {"[]=", tile},
    {"[M]", monocle},
    {"[\\]", dwindle},
    {"H[]", deck},
    {"TTT", bstack},
    {"===", bstackhoriz},
    {"HHH", grid},
    {"###", nrowgrid},
    {"---", horizgrid},
    {":::", gaplessgrid},
    {"|M|", centeredmaster},
    {">M>", centeredfloatingmaster},
    {"><>", NULL},
    {NULL, NULL},
};
// Layout for tag 0 (if all tags are active)
#define TAG0_LAYOUT &layouts[10] // ">M>" (centeredfloatingmaster)
#define ISDOCK(c) ((c)->tags == 0 && (c)->isfloating)
