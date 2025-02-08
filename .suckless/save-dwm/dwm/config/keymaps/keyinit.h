#include "keychord/application.h"
#include "keychord/controls.h"
#include "keychord/define.h"
#include "keychord/explorer.h"
#include "keychord/floutpos.h"
#include "keychord/gaps.h"
#include "keychord/monitor.h"
#include "keychord/rofi.h"
#include "keychord/screen.h"
#include "keychord/settings.h"
#include "keychord/system.h"
#include "keychord/tags.h"
#include "keychord/windows.h"
#include "keychord/windows_control.h"

static Keychord *keychords[] = {
    SYSTEM,
    SETTINGS,
    APPS,
    SCREEN,
    WINDOWS,
    WINCONTROL,
    MONITOR,
    ROFI,
    EXPLORER,
    CONTROLS,
    GAPS,
    FLOATPOS,
    TAGS};
