#include "../../variables/mouse/initmouse.h"

static Button buttons[] = {
    {ClkLtSymbol, 0, BUTTON1, ACTION_SETLAYOUT, {0}},
    {ClkClientWin, MODKEY, BUTTON1, ACTION_MOVEMOUSE, {0}},
    {ClkClientWin, MODKEY, BUTTON2, ACTION_TOGGLEFLOATING, {0}},
    {ClkClientWin, MODKEY, BUTTON3, ACTION_RESIZEMOUSE, {0}},
    {ClkTagBar, 0, BUTTON1, ACTION_VIEW, {0}},
    {ClkTagBar, 0, BUTTON3, ACTION_TOGGLEVIEW, {0}},
    {ClkTagBar, MODKEY, BUTTON1, ACTION_TAG, {0}},
    {ClkTagBar, MODKEY, BUTTON3, ACTION_TOGGLETAG, {0}},
    {ClkLtSymbol, 0, BUTTON3, ACTION_SETLAYOUT, {.v = &layouts[2]}},
    {ClkStatusText, 0, BUTTON2, ACTION_SPAWN, TERM},
    {ClkRootWin, MODKEY | SHIFT, BUTTON4, ACTION_VIEWNEXT, {0}},
    {ClkRootWin, MODKEY | SHIFT, BUTTON5, ACTION_VIEWPREV, {0}},
    {ClkRootWin, MODKEY, BUTTON4, ACTION_VIEWACTIVESCROLLNEXT, {0}},
    {ClkRootWin, MODKEY, BUTTON5, ACTION_VIEWACTIVESCROLLPREV, {0}}};
