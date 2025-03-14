/*
 * /==========================================//
 * / ██████╗ ██╗    ██╗███╗   ███╗     ██████╗
 * / ██╔══██╗██║    ██║████╗ ████║    ██╔════╝
 * / ██║  ██║██║ █╗ ██║██╔████╔██║    ██║
 * / ██║  ██║██║███╗██║██║╚██╔╝██║    ██║
 * / ██████╔╝╚███╔███╔╝██║ ╚═╝ ██║ ██╗╚ ██████╗
 * / ╚═════╝  ╚══╝╚══╝ ╚═╝     ╚═╝ ╚═╝  ╚═════╝
 * /==========================================//
 */
#include <X11/Xatom.h>
#include <X11/Xft/Xft.h>
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/keysym.h>
#ifdef XINERAMA
#include <X11/extensions/Xinerama.h>
#endif /* XINERAMA */

#include <Imlib2.h>
#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "drw.h"
#include "util.h"

/* macros */
#define BUTTONMASK (ButtonPressMask | ButtonReleaseMask)
#define CLEANMASK(mask)                                                     \
    (mask & ~(numlockmask | LockMask) &                                     \
     (ShiftMask | ControlMask | Mod1Mask | Mod2Mask | Mod3Mask | Mod4Mask | \
      Mod5Mask))
#define INTERSECT(x, y, w, h, m)                                     \
    (MAX(0, MIN((x) + (w), (m)->wx + (m)->ww) - MAX((x), (m)->wx)) * \
     MAX(0, MIN((y) + (h), (m)->wy + (m)->wh) - MAX((y), (m)->wy)))
#define ISVISIBLE(C) ((C->tags & C->mon->tagset[C->mon->seltags]))
#define EWMH_SUPPORT 1
#define MOUSEMASK (BUTTONMASK | PointerMotionMask)
#define WIDTH(X) ((X)->w + 2 * (X)->bw)
#define HEIGHT(X) ((X)->h + 2 * (X)->bw)
#define TAGMASK ((1 << LENGTH(tags)) - 1)
#define TAGSLENGTH (LENGTH(tags))
#define TEXTW(X) (drw_fontset_getwidth(drw, (X)) + lrpad)
#define SYSTEM_TRAY_REQUEST_DOCK 0
/* XEMBED messages */
#define XEMBED_EMBEDDED_NOTIFY 0
#define XEMBED_WINDOW_ACTIVATE 1
#define XEMBED_FOCUS_IN 4
#define XEMBED_MODALITY_ON 10
#define NUMTAGS 9  // Обычно количество тегов в dwm — 9
#define XEMBED_MAPPED (1 << 0)
#define XEMBED_WINDOW_ACTIVATE 1
#define XEMBED_WINDOW_DEACTIVATE 2
#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define XEMBED_EMBEDDED_VERSION (VERSION_MAJOR << 16) | VERSION_MINOR

#define STATE_FILE_PATH ".cache/smartgaps_state"
#define STATE_FILE_PATH_SYSTRAY ".cache/dwmsystray_state"
#define STATE_FILE_PATH_TITLE ".cache/dwmtitle_state"
#define STATE_FILE_TOGGLEGAPS ".cache/togglebottgaps"
#define CURRENTS_MINIBOX ".cache/dwmshowtagboxes_state"
#define STATE_FILE_PADDING ".cache/padding_state"
/* enums */
enum { CurNormal,
       CurResize,
       CurMove,
       CurLast }; /* cursor */
enum {
    NetSupported,
    NetWMName,
    NetWMIcon,
    NetWMState,
    NetWMCheck,
    NetSystemTray,
    NetWMWindowTypeNormal,
    NetSystemTrayOP,
    NetSystemTrayOrientation,
    NetSystemTrayOrientationHorz,
    NetWMFullscreen,
    NetActiveWindow,
    NetWMWindowType,
    NetWMWindowTypeDialog,
    NetWMWindowTypeDock,
    NetClientList,
    NetDesktopNames,
    NetWMWindowTypeUtility,
    NetDesktopViewport,
    NetNumberOfDesktops,
    NetCurrentDesktop,
    NetWMDesktop,
    NetWMWindowTypeMenu,
    NetWMWindowTypeToolbar,
    NetWMWindowTypePopupMenu,
    NetClientInfo,
    NetWorkarea,
    NetLast
};
/* EWMH atoms */
enum { Manager,
       Xembed,
       XembedInfo,
       XLast }; /* Xembed atoms */
enum {
    WMProtocols,
    WMDelete,
    WMState,
    WMTakeFocus,
    WMLast
}; /* default atoms */
enum {
    ClkTagBar,
    ClkLtSymbol,
    ClkStatusText,
    ClkClientWin,
    ClkRootWin,
    ClkLast
}; /* clicks */
enum {
    SchemeLogo,
    SchemeNorm,
    SchemeSel,
    SchemePower,
    SchemeTag1Active,
    SchemeFg,
    SchemeTitle,
    SchemeTag1Inactive,
    SchemeTag2Active,
    SchemeTag2Inactive,
    SchemeTag3Active,
    SchemeTag3Inactive,
    SchemeTag4Active,
    SchemeTag4Inactive,
    SchemeTag5Active,
    SchemeTag5Inactive,
    SchemeTag6Active,
    SchemeTag6Inactive,
    SchemeTag7Active,
    SchemeTag7Inactive,
    SchemeTag8Active,
    SchemeTag8Inactive,
    SchemeTag9Active,
    SchemeTag9Inactive,
    SchemeLast
};

typedef union {
    int i;
    unsigned int ui;
    float f;
    const void *v;
} Arg;

typedef struct {
    unsigned int click;
    unsigned int mask;
    unsigned int button;
    void (*func)(const Arg *arg);
    const Arg arg;
} Button;

typedef struct Monitor Monitor;
typedef struct Client Client;
struct Client {
    char name[256];
    float mina, maxa;
    float cfact;
    int x, y, w, h;
    int oldx, oldy, oldw, oldh;
    int basew, baseh, incw, inch, maxw, maxh, minw, minh, hintsvalid;
    int bw, oldbw;
    unsigned int tags;
    int isfixed, isfloating, isurgent, neverfocus, oldstate, isfullscreen;
    int hasfloatpos;  // Флаг, указывающий на наличие позиции floatpos
    int ignoresizehints;
    Client *next;
    Client *snext;
    Monitor *mon;
    Window win;
    int needsiconupdate;  // Новый флаг для проверки иконки
    unsigned int icw, ich;
    Picture icon;
};

typedef struct {
    unsigned int mod;
    KeySym keysym;
} Key;

typedef struct {
    unsigned int n;
    const Key keys[5];
    void (*func)(const Arg *);
    const Arg arg;
} Keychord;

typedef struct {
    const char *symbol;
    void (*arrange)(Monitor *);
} Layout;

typedef struct Pertag Pertag;

struct Monitor {
    int previewshow;
    Window tagwin;
    Pixmap *tagmap;
    char ltsymbol[16];
    float mfact;
    int nmaster;
    int num;
    int by;             /* bar geometry */
    int mx, my, mw, mh; /* screen size */
    int wx, wy, ww, wh; /* window area  */
    int gappih;         /* horizontal gap between windows */
    int gappiv;         /* vertical gap between windows */
    int gappoh;         /* horizontal outer gaps */
    int gappov;         /* vertical outer gaps */
    unsigned int seltags;
    unsigned int sellt;
    unsigned int tagset[2];
    int showbar;
    int showtitle; /* управление отображением заголовков */
    int topbar;
    Client *clients;
    Client *sel;
    Client *stack;
    Monitor *next;
    Window barwin;
    const Layout *lt[2];
    Pertag *pertag;
};

typedef struct {
    const char *class;
    const char *instance;
    const char *title;
    unsigned int tags;
    int isfloating;
    const char *floatpos;
    int monitor;
} Rule;

typedef struct Systray Systray;
struct Systray {
    Window win;
    Client *icons;
};

/* function declarations */
static void applyrules(Client *c);
static int applysizehints(Client *c, int *x, int *y, int *w, int *h,
                          int interact);
static void arrange(Monitor *m);
static void arrangemon(Monitor *m);
static void attach(Client *c);
static void attachBelow(Client *c);
static void toggleAttachBelow();
static void attachstack(Client *c);
static void buttonpress(XEvent *e);
static void checkotherwm(void);
static void cleanup(void);
static void cleanupmon(Monitor *mon);
static Picture geticonprop(Window w, unsigned int *icw, unsigned int *ich);
static void clientmessage(XEvent *e);
static void configure(Client *c);
static void configurenotify(XEvent *e);
static void configurerequest(XEvent *e);
static Monitor *createmon(void);
static void destroynotify(XEvent *e);
static void detach(Client *c);
static void detachstack(Client *c);
static Monitor *dirtomon(int dir);
static void drawbar(Monitor *m);
static void drawbars(void);
static void enternotify(XEvent *e);
static void expose(XEvent *e);
static void floatpos(const Arg *arg);
static void focus(Client *c);
static void focusin(XEvent *e);
static void focusmon(const Arg *arg);
static void focusstack(const Arg *arg);
static Atom getatomprop(Client *c, Atom prop);
static void getfloatpos(int pos, char pCh, int size, char sCh, int min_p,
                        int max_s, int cp, int cs, int cbw, int defgrid,
                        int *out_p, int *out_s);
static int getrootptr(int *x, int *y);
static long getstate(Window w);
static unsigned int getsystraywidth();
static Clr **scheme;
static int gettextprop(Window w, Atom atom, char *text, unsigned int size);
static void grabbuttons(Client *c, int focused);
static void grabkeys(void);
static void incnmaster(const Arg *arg);
static void keypress(XEvent *e);
static void killclient(const Arg *arg);
static void manage(Window w, XWindowAttributes *wa);
static void mappingnotify(XEvent *e);
static void maprequest(XEvent *e);
static void motionnotify(XEvent *e);
static void moveresize(const Arg *arg);
static void moveresizeedge(const Arg *arg);
static void movemouse(const Arg *arg);
static Client *nexttiled(Client *c);
static void pop(Client *c);
static void propertynotify(XEvent *e);
static void quit(const Arg *arg);
static Monitor *recttomon(int x, int y, int w, int h);
static void removesystrayicon(Client *i);
static void resize(Client *c, int x, int y, int w, int h, int interact);
static void resizebarwin(Monitor *m);
static void resizeclient(Client *c, int x, int y, int w, int h);
static void resizemouse(const Arg *arg);
static void resizerequest(XEvent *e);
static void restack(Monitor *m);
static void run(void);
static void scan(void);
static int sendevent(Window w, Atom proto, int m, long d0, long d1, long d2,
                     long d3, long d4);
static void sendmon(Client *c, Monitor *m);
static void setclientstate(Client *c, long state);
static void setcurrentdesktop(void);
static void setdesktopnames(void);
static void setnumdesktops(void);
static void setviewport(void);
static void setclienttagprop(Client *c);
static void setfocus(Client *c);
static void setfullscreen(Client *c, int fullscreen);
static void setlayout(const Arg *arg);
static void setcfact(const Arg *arg);
static void setmfact(const Arg *arg);
static void setup(void);
static void seturgent(Client *c, int urg);
static void showhide(Client *c);
static void spawn(const Arg *arg);
static Monitor *systraytomon(Monitor *m);
static void tag(const Arg *arg);
static void tagmon(const Arg *arg);
static void togglebar(const Arg *arg);
static void togglefloating(const Arg *arg);
static void togglefullscr(const Arg *arg);
static void toggletag(const Arg *arg);
static void toggleview(const Arg *arg);
static void freeicon(Client *c);
static void unfocus(Client *c, int setfocus);
static void unmanage(Client *c, int destroyed);
static void unmapnotify(XEvent *e);
static void updatecurrentdesktop(void);
static void updatebarpos(Monitor *m);
static void updatebars(void);
static void updateclientlist(void);
static int updategeom(void);
static void updatenumlockmask(void);
static void updatesizehints(Client *c);
static void updatestatus(void);
static void updatesystray(void);
static void updatesystrayicongeom(Client *i, int w, int h);
static void updatesystrayiconstate(Client *i, XPropertyEvent *ev);
static void updatetitle(Client *c);
static void updateicon(Client *c);
static void updatewindowtype(Client *c);
static void updatewmhints(Client *c);
static void view(const Arg *arg);
static Client *wintoclient(Window w);
static Monitor *wintomon(Window w);
static Client *wintosystrayicon(Window w);
static int xerror(Display *dpy, XErrorEvent *ee);
static int xerrordummy(Display *dpy, XErrorEvent *ee);
void togglesmartgaps(const Arg *arg);
static unsigned int prevtags;
static const Layout *prevlayout;
static Client *prevclient;
static int xerrorstart(Display *dpy, XErrorEvent *ee);
static void zoom(const Arg *arg);
static void winview(const Arg *arg);
void toggleSystray(const Arg *arg);
void viewnext(const Arg *arg);
void viewprev(const Arg *arg);
int is_noborder_app(const char *class);
int is_alltags_app(const char *class);
void toggleshowtitle(const Arg *arg);
void save_showtitle_state(void);
void load_showtitle_state(void);
void saveSmartgapsState(int state);
int isWindowIgnored(Client *c);        // Объявление функции
void toggle_bottGaps(const Arg *arg);  // Прототип функции
void toggleTagBoxes(const Arg *arg);
int read_saved_tag(void);     // Объявление функции для чтения сохранённого тега
void save_current_tag(void);  // Объявление функции для сохранения текущего тега
void switch_to_saved_tag(
    void);  // Объявление функции для переключения на сохранённый тег
void recompile_and_restart(const Arg *arg);
void updateworkarea(void);
void hidewin(const Arg *arg);
void restorewin(const Arg *arg);
void showall(const Arg *arg);
void saveclienttags(Client *c);
void restoreclienttags(Client *c);
void viewprevwithmove(const Arg *arg);
void viewnextwithmove(const Arg *arg);
void viewprev(const Arg *arg);
void viewnext(const Arg *arg);
void viewactivescrollnext(const Arg *arg);
void viewactivescrollprev(const Arg *arg);
static void showtagpreview(unsigned int i);
static void takepreview(void);
static void previewtag(const Arg *arg);
void loadAttachBelow(void);
void saveAttachBelow(void);
void toggle_padding(const Arg *arg);
void load_padding_settings(void);
void save_padding_settings(void);
void apply_padding_settings(void);

/* variables */
static Systray *systray = NULL;
static const char broken[] = "broken";
static char stext[256];
static Client *hidden_windows[NUMTAGS];
void setfloatpos(Client *c, const char *floatpos);
static int screen;
static int taghasclients(Monitor *m, unsigned int tag);
static int sw, sh; /* X display screen geometry width, height */
static int bh;     /* bar height */
static int lrpad;  /* sum of left and right padding for text */
static int vp;     /* vertical padding for bar */
static int sp;     /* side padding for bar */
static int (*xerrorxlib)(Display *, XErrorEvent *);
static unsigned int numlockmask = 0;
static void (*handler[LASTEvent])(XEvent *) = {
    [ButtonPress] = buttonpress,
    [ClientMessage] = clientmessage,
    [ConfigureRequest] = configurerequest,
    [ConfigureNotify] = configurenotify,
    [DestroyNotify] = destroynotify,
    [EnterNotify] = enternotify,
    [Expose] = expose,
    [FocusIn] = focusin,
    [KeyPress] = keypress,
    [MappingNotify] = mappingnotify,
    [MapRequest] = maprequest,
    [MotionNotify] = motionnotify,
    [PropertyNotify] = propertynotify,
    [ResizeRequest] = resizerequest,
    [UnmapNotify] = unmapnotify};
static Atom wmatom[WMLast], netatom[NetLast], xatom[XLast];
static int running = 1;
static int attachbelow = 0;  // Начальное значение: 0 (отключено)
static Cur *cursor[CurLast];
static Display *dpy;
static Drw *drw;
static Monitor *mons, *selmon;
static Window root, wmcheckwin;
unsigned int currentkey = 0;
extern int attachbelow;

#include "../patches/movestack.c"
/* configuration, allows nested code to access above variables */
#include "../init.h"

int read_saved_tag() {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/.cache/dwm_current_tag",
             getenv("HOME"));

    FILE *file = fopen(filepath, "r");
    if (!file) {
        return -1;  // Если файл не найден, возвращаем -1 (остаемся на дефолтном
                    // теге)
    }

    int tag;
    fscanf(file, "%d", &tag);
    fclose(file);
    return tag;
}

void save_current_tag_to_file() {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/.cache/dwm_current_tag",
             getenv("HOME"));

    FILE *file = fopen(filepath, "w");
    if (file) {
        unsigned int mask = selmon->tagset[selmon->seltags];
        int tag = 0;

        // Преобразуем битовую маску в индекс
        while (!(mask & 1)) {
            mask >>= 1;
            tag++;
        }

        fprintf(file, "%d\n", tag);  // Сохраняем индекс активного тега
        fclose(file);
        printf("Saved current tag: %d to %s\n", tag, filepath);  // Для отладки
    } else {
        fprintf(stderr, "Failed to save current tag to %s\n", filepath);
    }
}

void hidewin(const Arg *arg) {
    Client *c = selmon->sel;

    if (!c || c->isfullscreen)
        return;

    unsigned int tag = selmon->tagset[selmon->seltags];  // Текущий тег

    // Убираем окно из стека монитора
    detach(c);
    detachstack(c);

    // Добавляем окно в список скрытых для текущего тега
    c->next = hidden_windows[tag];
    hidden_windows[tag] = c;

    // Убираем окно с экрана
    XUnmapWindow(dpy, c->win);

    // Обновляем монитор
    focus(NULL);
    arrange(selmon);
}

void restorewin(const Arg *arg) {
    unsigned int tag = selmon->tagset[selmon->seltags];  // Текущий тег

    if (!hidden_windows[tag])
        return;

    // Достаем первое скрытое окно для текущего тега
    Client *c = hidden_windows[tag];
    hidden_windows[tag] = c->next;

    // Возвращаем окно в стек
    attach(c);
    attachstack(c);

    // Делаем окно видимым
    XMapWindow(dpy, c->win);

    // Обновляем монитор
    focus(c);
    arrange(selmon);
}

void showall(const Arg *arg) {
    unsigned int tag = selmon->tagset[selmon->seltags];  // Текущий тег
    Client *c;

    while (hidden_windows[tag]) {
        c = hidden_windows[tag];
        hidden_windows[tag] = c->next;

        // Возвращаем окно в стек и делаем его видимым
        attach(c);
        attachstack(c);
        XMapWindow(dpy, c->win);
    }

    // Обновляем монитор
    focus(NULL);
    arrange(selmon);
}

void switch_to_saved_tag() {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/.cache/dwm_current_tag",
             getenv("HOME"));

    FILE *file = fopen(filepath, "r");
    if (file) {
        int tag;
        fscanf(file, "%d", &tag);
        fclose(file);

        printf("Restoring tag: %d\n", tag);  // Отладочное сообщение

        if (tag >= 0 && tag < LENGTH(tags)) {
            Arg arg = {.ui = 1 << tag};  // Преобразуем индекс в битовую маску
            view(&arg);                  // Переключаемся на нужный тег
        } else {
            printf("Tag out of range: %d\n", tag);
        }
    } else {
        fprintf(stderr, "Failed to open file for restoring tag: %s\n", filepath);
    }
}

void save_bottGaps_state() {
    FILE *file = fopen(STATE_FILE_TOGGLEGAPS, "w");
    if (file) {
        fprintf(file, "%d", bottGaps);  // Сохраняем текущее значение в файл
        fclose(file);
    }
}

// Функция для чтения состояния из файла
void load_bottGaps_state() {
    FILE *file = fopen(STATE_FILE_TOGGLEGAPS, "r");
    if (file) {
        fscanf(file, "%d", &bottGaps);  // Читаем значение из файла
        fclose(file);
    }
}

void toggle_bottGaps(const Arg *arg) {
    load_bottGaps_state();
    char command[256];
    if (bottGaps == 0) {
        bottGaps = bottgaps;
        snprintf(command, sizeof(command), "%s &", DOCK_NAME);
        system(command);
    } else {
        bottGaps = 0;
        snprintf(command, sizeof(command), "pkill %s", DOCK_NAME);

        system(command);
    }
    save_bottGaps_state();
    arrange(NULL);
}
void save_showtitle_state(void) {
    FILE *file = fopen(STATE_FILE_PATH_TITLE, "w");
    if (file != NULL) {
        fprintf(file, "%d\n", showtitle);
        fclose(file);
    } else {
        fprintf(
            stderr,
            "Erorr: not able to open file for writing showtitle state.\n");
    }
}

void load_showtitle_state(void) {
    FILE *file = fopen(STATE_FILE_PATH_TITLE, "r");
    if (file != NULL) {
        if (fscanf(file, "%d", &showtitle) != 1) {
            fprintf(stderr,
                    "Erorr: not able to open file for reading showtitle state.\n"
                    "Creating new file.\n");
        }
        fclose(file);
    } else {
        fprintf(
            stderr,
            "Erorr: not able to open file for reading showtitle state.\n"
            "Creating new file.\n");
    }
}

void saveSmartgapsState(int state) {
    FILE *file = fopen(STATE_FILE_PATH, "w");
    if (file) {
        fprintf(file, "%d\n", state);
        fclose(file);
    } else {
        fprintf(
            stderr,
            "Error: not able to open file for writing smartgaps.\n");
    }
}

int loadSmartgapsState() {
    FILE *file = fopen(STATE_FILE_PATH, "r");
    int state = 1;
    if (file != NULL) {
        fscanf(file, "%d", &state);
        fclose(file);
    } else {
        fprintf(stderr,
                "Erorr: not able to open file for reading smartgaps state.\n"
                "Creating new file.\n");
    }
    return state;
}

void toggleSystray(const Arg *arg) {
    updatesystray();
    updatebars();
    showsystray = !showsystray;

    FILE *file = fopen(STATE_FILE_PATH_SYSTRAY, "w");
    if (file) {
        fprintf(file, "%d", showsystray);
        fclose(file);
    }

    if (!showsystray) {
        XUnmapWindow(dpy, systray->win);
    } else {
        XMapWindow(dpy, systray->win);
    }

    updatebarpos(selmon);
    arrange(selmon);
    drawbar(selmon);

    updatesystray();
}

void loadSystrayState() {
    FILE *file = fopen(STATE_FILE_PATH_SYSTRAY, "r");
    if (file) {
        int state;
        if (fscanf(file, "%d", &state) == 1) {
            showsystray = state;  // Восстанавливаем сохранённое состояние
        }
        fclose(file);
    } else {
        showsystray = 1;  // Если файл не найден, показываем трей по умолчанию
    }

    // Управляем видимостью трея на основе состояния
    if (!showsystray) {
        XUnmapWindow(dpy, systray->win);  // Скрываем трей, если нужно
    } else {
        XMapWindow(dpy, systray->win);  // Показываем трей, если нужно
    }
}

void viewactivescrollprev(const Arg *arg) {
    unsigned int i, curtag = selmon->tagset[selmon->seltags];
    unsigned int prevtag = 0;

    for (i = 1; i < LENGTH(tags); i++) {
        prevtag = 1 << ((ffs(curtag) - 1 + LENGTH(tags) - i) %
                        LENGTH(tags));                    // Предыдущий тег
        if (prevtag && taghasclients(selmon, prevtag)) {  // Проверяем, есть ли окна
            view(&(Arg){.ui = prevtag});
            return;
        }
    }
}

void viewactivescrollnext(const Arg *arg) {
    unsigned int i, curtag = selmon->tagset[selmon->seltags];
    unsigned int nexttag = 0;

    for (i = 1; i < LENGTH(tags); i++) {
        nexttag = 1 << ((ffs(curtag) - 1 + i) % LENGTH(tags));  // Следующий тег
        if (nexttag && taghasclients(selmon, nexttag)) {        // Проверяем, есть ли окна
            view(&(Arg){.ui = nexttag});
            return;
        }
    }
}

int taghasclients(Monitor *m, unsigned int tag) {
    Client *c;
    for (c = m->clients; c; c = c->next) {
        if (c->tags & tag)
            return 1;  // Найдено окно в указанном теге
    }
    return 0;  // В теге нет окон
}

struct Pertag {
    unsigned int curtag, prevtag;          /* current and previous tag */
    int nmasters[LENGTH(tags) + 1];        /* number of windows in master area */
    float mfacts[LENGTH(tags) + 1];        /* mfacts per tag */
    unsigned int sellts[LENGTH(tags) + 1]; /* selected layouts */
    const Layout
        *ltidxs[LENGTH(tags) + 1][2]; /* matrix of tags and layouts indexes  */
    int showbars[LENGTH(tags) + 1];   /* display bar for the current tag */
    Client *sel[LENGTH(tags) + 1];    /* selected client */
};

/* compile-time check if all tags fit into an unsigned int bit array. */
struct NumTags {
    char limitexceeded[LENGTH(tags) > 31 ? -1 : 1];
};

/* function implementations */
void applyrules(Client *c) {
    const char *class, *instance;
    unsigned int i;
    const Rule *r;
    Monitor *m;
    XClassHint ch = {NULL, NULL};

    /* rule matching */
    c->isfloating = 0;
    c->tags = 0;
    XGetClassHint(dpy, c->win, &ch);
    class = ch.res_class ? ch.res_class : broken;
    instance = ch.res_name ? ch.res_name : broken;

    for (i = 0; i < LENGTH(rules); i++) {
        r = &rules[i];
        if ((!r->title || strstr(c->name, r->title)) &&
            (!r->class || strstr(class, r->class)) &&
            (!r->instance || strstr(instance, r->instance))) {
            c->isfloating = r->isfloating;
            c->tags |= r->tags;
            for (m = mons; m && m->num != r->monitor; m = m->next);
            if (m)
                c->mon = m;
            if (c->isfloating && r->floatpos)
                setfloatpos(c, r->floatpos);
        }
    }
    if (ch.res_class)
        XFree(ch.res_class);
    if (ch.res_name)
        XFree(ch.res_name);
    c->tags =
        c->tags & TAGMASK ? c->tags & TAGMASK : c->mon->tagset[c->mon->seltags];
}

int applysizehints(Client *c, int *x, int *y, int *w, int *h, int interact) {
    int baseismin;
    Monitor *m = c->mon;

    /* set minimum possible */
    *w = MAX(1, *w);
    *h = MAX(1, *h);
    if (interact) {
        if (*x > sw)
            *x = sw - WIDTH(c);
        if (*y > sh)
            *y = sh - HEIGHT(c);
        if (*x + *w + 2 * c->bw < 0)
            *x = 0;
        if (*y + *h + 2 * c->bw < 0)
            *y = 0;
    } else {
        if (*x >= m->wx + m->ww)
            *x = m->wx + m->ww - WIDTH(c);
        if (*y >= m->wy + m->wh)
            *y = m->wy + m->wh - HEIGHT(c);
        if (*x + *w + 2 * c->bw <= m->wx)
            *x = m->wx;
        if (*y + *h + 2 * c->bw <= m->wy)
            *y = m->wy;
    }
    if (*h < bh)
        *h = bh;
    if (*w < bh)
        *w = bh;
    if (!c->ignoresizehints &&
        (resizehints || c->isfloating || !c->mon->lt[c->mon->sellt]->arrange)) {
        if (!c->hintsvalid)
            updatesizehints(c);

        /* see last two sentences in ICCCM 4.1.2.3 */
        baseismin = c->basew == c->minw && c->baseh == c->minh;
        if (!baseismin) { /* temporarily remove base dimensions */
            *w -= c->basew;
            *h -= c->baseh;
        }
        /* adjust for aspect limits */
        if (c->mina > 0 && c->maxa > 0) {
            if (c->maxa < (float)*w / *h)
                *w = *h * c->maxa + 0.5;
            else if (c->mina < (float)*h / *w)
                *h = *w * c->mina + 0.5;
        }
        if (baseismin) { /* increment calculation requires this */
            *w -= c->basew;
            *h -= c->baseh;
        }
        /* adjust for increment value */
        if (c->incw)
            *w -= *w % c->incw;
        if (c->inch)
            *h -= *h % c->inch;
        /* restore base dimensions */
        *w = MAX(*w + c->basew, c->minw);
        *h = MAX(*h + c->baseh, c->minh);
        if (c->maxw)
            *w = MIN(*w, c->maxw);
        if (c->maxh)
            *h = MIN(*h, c->maxh);
    }
    return *x != c->x || *y != c->y || *w != c->w || *h != c->h;
}

void arrange(Monitor *m) {
    if (m)
        showhide(m->stack);
    else
        for (m = mons; m; m = m->next)
            showhide(m->stack);
    if (m) {
        arrangemon(m);
        restack(m);
    } else
        for (m = mons; m; m = m->next)
            arrangemon(m);
}

void arrangemon(Monitor *m) {
    strncpy(m->ltsymbol, m->lt[m->sellt]->symbol, sizeof m->ltsymbol);
    if (m->lt[m->sellt]->arrange)
        m->lt[m->sellt]->arrange(m);
}

void attach(Client *c) {
    c->next = c->mon->clients;
    c->mon->clients = c;
}
void attachBelow(Client *c) {
    // If there is nothing on the monitor or the selected client is floating,
    // attach as normal
    if (c->mon->sel == NULL || c->mon->sel == c || c->mon->sel->isfloating) {
        attach(c);
        return;
    }

    // Set the new client's next property to the same as the currently selected
    // clients next
    c->next = c->mon->sel->next;
    // Set the currently selected clients next property to the new client
    c->mon->sel->next = c;
}

void toggleAttachBelow() {
    attachbelow = !attachbelow;
    saveAttachBelow();  // Сохраняем состояние после переключения
}

void attachstack(Client *c) {
    c->snext = c->mon->stack;
    c->mon->stack = c;
}

void buttonpress(XEvent *e) {
    unsigned int i, x, click;
    Arg arg = {0};
    Client *c;
    Monitor *m;
    XButtonPressedEvent *ev = &e->xbutton;

    click = ClkRootWin;

    /* focus monitor if necessary */
    if ((m = wintomon(ev->window)) && m != selmon) {
        unfocus(selmon->sel, 1);
        selmon = m;
        focus(NULL);
    }

    if (ev->window == selmon->barwin) {
        i = x = 0;

        /* Определяем ширину логотипа */
        int logo_width = logo_state ? TEXTW(logo) : 0;
        if (logo_state && ev->x < logo_width) {
            /* Запуск скрипта для логотипа */
            if (fork() == 0) {
                setsid();
                execl("/bin/sh", "sh", "-c", logo_script, (char *)NULL);
                exit(0);
            }
            return;
        }

        x += logo_width;  // Сдвигаем начальную позицию для тегов

        do
            x += TEXTW(tags[i]);
        while (ev->x >= x && ++i < LENGTH(tags));

        if (i < LENGTH(tags)) {
            click = ClkTagBar;
            arg.ui = 1 << i;
            /* hide preview if we click the bar */
            if (selmon->previewshow) {
                selmon->previewshow = 0;
                XUnmapWindow(dpy, selmon->tagwin);
            }
        } else if (ev->x < x + TEXTW(selmon->ltsymbol)) {
            click = ClkLtSymbol;
        } else {
            /* Проверяем область power */
            int power_width = power_state ? TEXTW(power) : 0;
            int power_x_start = selmon->ww - power_width -
                                (showsystray && !systrayonleft ? sw : 0) - borderpx;
            if (power_state && ev->x > power_x_start) {
                /* Запуск скрипта для power */
                if (fork() == 0) {
                    setsid();
                    execl("/bin/sh", "sh", "-c", power_script, (char *)NULL);
                    exit(0);
                }
                return;
            }
            click = ClkStatusText;
        }
    } else if ((c = wintoclient(ev->window))) {
        focus(c);
        restack(selmon);
        XAllowEvents(dpy, ReplayPointer, CurrentTime);
        click = ClkClientWin;
    }

    for (i = 0; i < LENGTH(buttons); i++)
        if (click == buttons[i].click && buttons[i].func &&
            buttons[i].button == ev->button &&
            CLEANMASK(buttons[i].mask) == CLEANMASK(ev->state))
            buttons[i].func(
                click == ClkTagBar && buttons[i].arg.i == 0 ? &arg : &buttons[i].arg);
}

void checkotherwm(void) {
    xerrorxlib = XSetErrorHandler(xerrorstart);
    /* this causes an error if some other window manager is running */
    XSelectInput(dpy, DefaultRootWindow(dpy), SubstructureRedirectMask);
    XSync(dpy, False);
    XSetErrorHandler(xerror);
    XSync(dpy, False);
}

void cleanup(void) {
    Arg a = {.ui = ~0};
    Layout foo = {"", NULL};
    Monitor *m;
    size_t i;

    view(&a);
    selmon->lt[selmon->sellt] = &foo;
    for (m = mons; m; m = m->next)
        while (m->stack)
            unmanage(m->stack, 0);
    XUngrabKey(dpy, AnyKey, AnyModifier, root);
    while (mons)
        cleanupmon(mons);

    if (showsystray) {
        XUnmapWindow(dpy, systray->win);
        XDestroyWindow(dpy, systray->win);
        free(systray);
    }

    for (i = 0; i < CurLast; i++)
        drw_cur_free(drw, cursor[i]);
    for (i = 0; i < LENGTH(colors); i++)
        free(scheme[i]);
    free(scheme);
    XDestroyWindow(dpy, wmcheckwin);
    drw_free(drw);
    XSync(dpy, False);
    XSetInputFocus(dpy, PointerRoot, RevertToPointerRoot, CurrentTime);
    XDeleteProperty(dpy, root, netatom[NetActiveWindow]);
}

void cleanupmon(Monitor *mon) {
    Monitor *m;
    size_t i;

    if (mon == mons)
        mons = mons->next;
    else {
        for (m = mons; m && m->next != mon; m = m->next);
        m->next = mon->next;
    }
    for (i = 0; i < LENGTH(tags); i++)
        if (mon->tagmap[i])
            XFreePixmap(dpy, mon->tagmap[i]);
    free(mon->tagmap);
    XUnmapWindow(dpy, mon->barwin);
    XDestroyWindow(dpy, mon->barwin);
    XUnmapWindow(dpy, mon->tagwin);
    XDestroyWindow(dpy, mon->tagwin);
    free(mon);
}

void clientmessage(XEvent *e) {
    XWindowAttributes wa;
    XSetWindowAttributes swa;
    XClientMessageEvent *cme = &e->xclient;
    Client *c = wintoclient(cme->window);
    unsigned int i;

    if (showsystray && cme->window == systray->win &&
        cme->message_type == netatom[NetSystemTrayOP]) {
        /* add systray icons */
        if (cme->data.l[1] == SYSTEM_TRAY_REQUEST_DOCK) {
            if (!(c = (Client *)calloc(1, sizeof(Client))))
                die("fatal: could not malloc() %u bytes\n", sizeof(Client));
            if (!(c->win = cme->data.l[2])) {
                free(c);
                return;
            }
            c->mon = selmon;
            c->next = systray->icons;
            systray->icons = c;
            if (!XGetWindowAttributes(dpy, c->win, &wa)) {
                /* use sane defaults */
                wa.width = bh;
                wa.height = bh;
                wa.border_width = 0;
            }
            c->x = c->oldx = c->y = c->oldy = 0;
            c->w = c->oldw = wa.width;
            c->h = c->oldh = wa.height;
            c->oldbw = wa.border_width;
            c->bw = 0;
            c->isfloating = True;
            /* reuse tags field as mapped status */
            c->tags = 1;
            updatesizehints(c);
            updatesystrayicongeom(c, wa.width, wa.height);
            XAddToSaveSet(dpy, c->win);
            XSelectInput(dpy, c->win,
                         StructureNotifyMask | PropertyChangeMask |
                             ResizeRedirectMask);
            XReparentWindow(dpy, c->win, systray->win, 0, 0);
            /* use parents background color */
            swa.background_pixel = scheme[SchemeNorm][ColBg].pixel;
            XChangeWindowAttributes(dpy, c->win, CWBackPixel, &swa);
            sendevent(c->win, netatom[Xembed], StructureNotifyMask, CurrentTime,
                      XEMBED_EMBEDDED_NOTIFY, 0, systray->win,
                      XEMBED_EMBEDDED_VERSION);
            /* FIXME not sure if I have to send these events, too */
            sendevent(c->win, netatom[Xembed], StructureNotifyMask, CurrentTime,
                      XEMBED_FOCUS_IN, 0, systray->win, XEMBED_EMBEDDED_VERSION);
            sendevent(c->win, netatom[Xembed], StructureNotifyMask, CurrentTime,
                      XEMBED_WINDOW_ACTIVATE, 0, systray->win,
                      XEMBED_EMBEDDED_VERSION);
            sendevent(c->win, netatom[Xembed], StructureNotifyMask, CurrentTime,
                      XEMBED_MODALITY_ON, 0, systray->win, XEMBED_EMBEDDED_VERSION);
            XSync(dpy, False);
            resizebarwin(selmon);
            updatesystray();
            setclientstate(c, NormalState);
        }
        return;
    }

    if (!c)
        return;
    if (cme->message_type == netatom[NetWMState]) {
        if (cme->data.l[1] == netatom[NetWMFullscreen] ||
            cme->data.l[2] == netatom[NetWMFullscreen])
            setfullscreen(c, (cme->data.l[0] == 1 /* _NET_WM_STATE_ADD    */
                              || (cme->data.l[0] == 2 /* _NET_WM_STATE_TOGGLE */ &&
                                  !c->isfullscreen)));
    } else if (cme->message_type == netatom[NetActiveWindow]) {
        for (i = 0; i < LENGTH(tags) && !((1 << i) & c->tags); i++);
        if (i < LENGTH(tags)) {
            const Arg a = {.ui = 1 << i};
            selmon = c->mon;
            view(&a);
            focus(c);
            restack(selmon);
        }
    }
}

void configure(Client *c) {
    XConfigureEvent ce;

    ce.type = ConfigureNotify;
    ce.display = dpy;
    ce.event = c->win;
    ce.window = c->win;
    ce.x = c->x;
    ce.y = c->y;
    ce.width = c->w;
    ce.height = c->h;
    ce.border_width = c->bw;
    ce.above = None;
    ce.override_redirect = False;
    XSendEvent(dpy, c->win, False, StructureNotifyMask, (XEvent *)&ce);
}

void configurenotify(XEvent *e) {
    Monitor *m;
    Client *c;
    XConfigureEvent *ev = &e->xconfigure;
    int dirty;

    /* TODO: updategeom handling sucks, needs to be simplified */
    if (ev->window == root) {
        dirty = (sw != ev->width || sh != ev->height);
        sw = ev->width;
        sh = ev->height;
        if (updategeom() || dirty) {
            drw_resize(drw, sw, bh);
            updatebars();
            for (m = mons; m; m = m->next) {
                for (c = m->clients; c; c = c->next)
                    if (c->isfullscreen)
                        resizeclient(c, m->mx, m->my, m->mw, m->mh);
                resizebarwin(m);
            }
            focus(NULL);
            arrange(NULL);
        }
    }
}

void configurerequest(XEvent *e) {
    Client *c;
    Monitor *m;
    XConfigureRequestEvent *ev = &e->xconfigurerequest;
    XWindowChanges wc;

    if ((c = wintoclient(ev->window))) {
        if (ev->value_mask & CWBorderWidth)
            c->bw = ev->border_width;
        else if (c->isfloating || !selmon->lt[selmon->sellt]->arrange) {
            m = c->mon;
            if (ev->value_mask & CWX) {
                c->oldx = c->x;
                c->x = m->mx + ev->x;
            }
            if (ev->value_mask & CWY) {
                c->oldy = c->y;
                c->y = m->my + ev->y;
            }
            if (ev->value_mask & CWWidth) {
                c->oldw = c->w;
                c->w = ev->width;
            }
            if (ev->value_mask & CWHeight) {
                c->oldh = c->h;
                c->h = ev->height;
            }
            if ((c->x + c->w) > m->mx + m->mw && c->isfloating)
                c->x = m->mx + (m->mw / 2 - WIDTH(c) / 2); /* center in x direction */
            if ((c->y + c->h) > m->my + m->mh && c->isfloating)
                c->y = m->my + (m->mh / 2 - HEIGHT(c) / 2); /* center in y direction */
            if ((ev->value_mask & (CWX | CWY)) &&
                !(ev->value_mask & (CWWidth | CWHeight)))
                configure(c);
            if (ISVISIBLE(c))
                XMoveResizeWindow(dpy, c->win, c->x, c->y, c->w, c->h);
        } else
            configure(c);
    } else {
        wc.x = ev->x;
        wc.y = ev->y;
        wc.width = ev->width;
        wc.height = ev->height;
        wc.border_width = ev->border_width;
        wc.sibling = ev->above;
        wc.stack_mode = ev->detail;
        XConfigureWindow(dpy, ev->window, ev->value_mask, &wc);
    }
    XSync(dpy, False);
}

Monitor *createmon(void) {
    Monitor *m;
    unsigned int i;

    m = ecalloc(1, sizeof(Monitor));
    m->tagset[0] = m->tagset[1] = 1;
    m->mfact = mfact;
    m->nmaster = nmaster;
    m->showbar = showbar;
    m->topbar = topbar;
    m->gappih = gappih;
    m->gappiv = gappiv;
    m->gappoh = gappoh;
    m->gappov = gappov;
    m->lt[0] = &layouts[0];
    m->lt[1] = &layouts[1 % LENGTH(layouts)];
    m->tagmap = ecalloc(LENGTH(tags), sizeof(Pixmap));
    strncpy(m->ltsymbol, layouts[0].symbol, sizeof m->ltsymbol);
    m->pertag = ecalloc(1, sizeof(Pertag));
    m->pertag->curtag = m->pertag->prevtag = 1;

    for (i = 0; i <= LENGTH(tags); i++) {
        m->pertag->nmasters[i] = m->nmaster;
        m->pertag->mfacts[i] = m->mfact;

        m->pertag->ltidxs[i][0] = m->lt[0];
        m->pertag->ltidxs[i][1] = m->lt[1];
        m->pertag->sellts[i] = m->sellt;

        m->pertag->showbars[i] = m->showbar;
    }

    return m;
}

void destroynotify(XEvent *e) {
    Client *c;
    XDestroyWindowEvent *ev = &e->xdestroywindow;

    if ((c = wintoclient(ev->window)))
        unmanage(c, 1);
    else if ((c = wintosystrayicon(ev->window))) {
        removesystrayicon(c);
        resizebarwin(selmon);
        updatesystray();
    }
}

void detach(Client *c) {
    Client **tc;

    for (tc = &c->mon->clients; *tc && *tc != c; tc = &(*tc)->next);
    *tc = c->next;
}

void floatpos(const Arg *arg) {
    Client *c = selmon->sel;

    if (!c || (selmon->lt[selmon->sellt]->arrange && !c->isfloating))
        return;

    setfloatpos(c, (char *)arg->v);
    resizeclient(c, c->x, c->y, c->w, c->h);

    XRaiseWindow(dpy, c->win);
    XWarpPointer(dpy, None, c->win, 0, 0, 0, 0, c->w / 2, c->h / 2);
}

void detachstack(Client *c) {
    Client **tc, *t;

    for (tc = &c->mon->stack; *tc && *tc != c; tc = &(*tc)->snext);
    *tc = c->snext;

    if (c == c->mon->sel) {
        for (t = c->mon->stack; t && !ISVISIBLE(t); t = t->snext);
        c->mon->sel = t;
    }
}

Monitor *dirtomon(int dir) {
    Monitor *m = NULL;

    if (dir > 0) {
        if (!(m = selmon->next))
            m = mons;
    } else if (selmon == mons)
        for (m = mons; m->next; m = m->next);
    else
        for (m = mons; m->next != selmon; m = m->next);
    return m;
}

void drawbars(void) {
    Monitor *m;

    for (m = mons; m; m = m->next)
        drawbar(m);
}

void enternotify(XEvent *e) {
    Client *c;
    Monitor *m;
    XCrossingEvent *ev = &e->xcrossing;

    if ((ev->mode != NotifyNormal || ev->detail == NotifyInferior) &&
        ev->window != root)
        return;
    c = wintoclient(ev->window);
    m = c ? c->mon : wintomon(ev->window);
    if (m != selmon) {
        unfocus(selmon->sel, 1);
        selmon = m;
    } else if (!c || c == selmon->sel)
        return;
    focus(c);
}

void expose(XEvent *e) {
    Monitor *m;
    XExposeEvent *ev = &e->xexpose;

    if (ev->count == 0 && (m = wintomon(ev->window))) {
        drawbar(m);
        if (m == selmon)
            updatesystray();
    }
}

int isWindowIgnored(Client *c) {
    const char **ignore = focusIgnore;  // Указатель на массив с именами окон
    XClassHint class_hint;              // Структура для хранения информации о классе окна

    // Получаем информацию о классе окна
    if (XGetClassHint(dpy, c->win,
                      &class_hint)) {  // Передаем указатель на class_hint
        while (*ignore) {
            if (strstr(class_hint.res_class,
                       *ignore)) {  // Проверяем, есть ли совпадение
                return 1;           // Окно игнорируется, возвращаем 1
            }
            ignore++;
        }
    }

    return 0;  // Фокус можно установить для этого окна
}

void updateworkarea(void) {
    long workarea[4];

    // Корректировка рабочей области для текущего монитора
    workarea[0] = selmon->wx;                               // x
    workarea[1] = selmon->wy + (selmon->showbar ? bh : 0);  // y с учётом панели
    workarea[2] = selmon->ww;                               // ширина
    workarea[3] =
        selmon->wh - (selmon->showbar ? bh : 0);  // высота с учётом панели

    XChangeProperty(dpy, root, netatom[NetWorkarea], XA_CARDINAL, 32,
                    PropModeReplace, (unsigned char *)workarea, 4);
}
void focus(Client *c) {
    // Если окно игнорируется или не видно, ищем следующее в стеке
    if (!c || !ISVISIBLE(c) || isWindowIgnored(c)) {
        for (c = selmon->stack; c && (!ISVISIBLE(c) || isWindowIgnored(c));
             c = c->snext);
    }

    // Снимаем фокус с предыдущего окна, если оно существует и отличается от
    // нового
    if (selmon->sel && selmon->sel != c) {
        unfocus(selmon->sel, 0);
    }

    if (c) {
        // Если окно на другом мониторе, переключаемся на его монитор
        if (c->mon != selmon) {
            selmon = c->mon;
        }

        // Снимаем статус "тревожного" окна
        if (c->isurgent) {
            seturgent(c, 0);
        }

        // Перемещаем окно в стек
        detachstack(c);
        attachstack(c);

        // Устанавливаем фокус на окно
        grabbuttons(c, 1);
        XSetWindowBorder(dpy, c->win, scheme[SchemeSel][ColBorder].pixel);
        setfocus(c);

        // Обновляем _NET_ACTIVE_WINDOW
        XChangeProperty(dpy, root, netatom[NetActiveWindow], XA_WINDOW, 32,
                        PropModeReplace, (unsigned char *)&(c->win), 1);
    } else {
        // Если нет активного окна, устанавливаем фокус на корневое окно
        XSetInputFocus(dpy, root, RevertToPointerRoot, CurrentTime);
        XDeleteProperty(dpy, root, netatom[NetActiveWindow]);
    }

    // Поднимаем DOCK окна наверх, чтобы они не перекрывались
    for (Client *dock = selmon->clients; dock; dock = dock->next) {
        if (ISDOCK(dock)) {
            XRaiseWindow(dpy, dock->win);
        }
    }

    // Обновляем выбранное окно
    selmon->sel = c;
    selmon->pertag->sel[selmon->pertag->curtag] = c;

    // Перерисовываем панели
    drawbars();
}

void grabbuttons(Client *c, int focused) {
    updatenumlockmask();
    {
        unsigned int i, j;
        unsigned int modifiers[] = {0, LockMask, numlockmask,
                                    numlockmask | LockMask};
        XUngrabButton(dpy, AnyButton, AnyModifier, c->win);
        if (!focused)
            XGrabButton(dpy, AnyButton, AnyModifier, c->win, False, BUTTONMASK,
                        GrabModeSync, GrabModeSync, None, None);
        for (i = 0; i < LENGTH(buttons); i++)
            if (buttons[i].click == ClkClientWin)
                for (j = 0; j < LENGTH(modifiers); j++)
                    XGrabButton(dpy, buttons[i].button, buttons[i].mask | modifiers[j],
                                c->win, False, BUTTONMASK, GrabModeAsync, GrabModeSync,
                                None, None);
    }
}

/* there are some broken focus acquiring clients needing extra handling */
void focusin(XEvent *e) {
    XFocusChangeEvent *ev = &e->xfocus;

    if (selmon->sel && ev->window != selmon->sel->win)
        setfocus(selmon->sel);
}

void focusmon(const Arg *arg) {
    Monitor *m;

    if (!mons->next)
        return;
    if ((m = dirtomon(arg->i)) == selmon)
        return;
    unfocus(selmon->sel, 0);
    selmon = m;
    focus(NULL);
}

void focusstack(const Arg *arg) {
    Client *c = NULL, *i;

    if (!selmon->sel || (selmon->sel->isfullscreen && lockfullscreen))
        return;
    if (arg->i > 0) {
        for (c = selmon->sel->next; c && !ISVISIBLE(c); c = c->next);
        if (!c)
            for (c = selmon->clients; c && !ISVISIBLE(c); c = c->next);
    } else {
        for (i = selmon->clients; i != selmon->sel; i = i->next)
            if (ISVISIBLE(i))
                c = i;
        if (!c)
            for (; i; i = i->next)
                if (ISVISIBLE(i))
                    c = i;
    }
    if (c) {
        focus(c);
        restack(selmon);
    }
}

Atom getatomprop(Client *c, Atom prop) {
    int di;
    unsigned long dl;
    unsigned char *p = NULL;
    Atom da, atom = None;

    /* FIXME getatomprop should return the number of items and a pointer to
     * the stored data instead of this workaround */
    Atom req = XA_ATOM;
    if (prop == xatom[XembedInfo])
        req = xatom[XembedInfo];

    if (XGetWindowProperty(dpy, c->win, prop, 0L, sizeof atom, False, req, &da,
                           &di, &dl, &dl, &p) == Success &&
        p) {
        atom = *(Atom *)p;
        if (da == xatom[XembedInfo] && dl == 2)
            atom = ((Atom *)p)[1];
        XFree(p);
    }
    return atom;
}

unsigned int getsystraywidth() {
    unsigned int w = 0;
    Client *i;
    if (showsystray)
        for (i = systray->icons; i; w += i->w + systrayspacing, i = i->next);
    return w ? w + systrayspacing : 1;
}

void getfloatpos(int pos, char pCh, int size, char sCh, int min_p, int max_s,
                 int cp, int cs, int cbw, int defgrid, int *out_p, int *out_s) {
    int abs_p, abs_s, i, delta, rest;

    abs_p = pCh == 'A' || pCh == 'a';
    abs_s = sCh == 'A' || sCh == 'a';

    cs += 2 * cbw;

    switch (pCh) {
        case 'A':  // absolute position
            cp = pos;
            break;
        case 'a':  // absolute relative position
            cp += pos;
            break;
        case 'y':
        case 'x':  // client relative position
            cp = MIN(cp + pos, min_p + max_s);
            break;
        case 'Y':
        case 'X':  // client position relative to monitor
            cp = min_p + MIN(pos, max_s);
            break;
        case 'S':  // fixed client position (sticky)
        case 'C':  // fixed client position (center)
        case 'Z':  // fixed client right-hand position (position + size)
            if (pos == -1)
                break;
            pos = MAX(MIN(pos, max_s), 0);
            if (pCh == 'Z')
                cs = abs((cp + cs) - (min_p + pos));
            else if (pCh == 'C')
                cs = abs((cp + cs / 2) - (min_p + pos));
            else
                cs = abs(cp - (min_p + pos));
            cp = min_p + pos;
            sCh = 0;  // size determined by position, override defined size
            break;
        case 'G':  // grid
            if (pos <= 0)
                pos = defgrid;  // default configurable
            if (size == 0 || pos < 2 || (sCh != 'p' && sCh != 'P'))
                break;
            delta = (max_s - cs) / (pos - 1);
            rest = max_s - cs - delta * (pos - 1);
            if (sCh == 'P') {
                if (size < 1 || size > pos)
                    break;
                cp = min_p + delta * (size - 1);
            } else {
                for (i = 0;
                     i < pos &&
                     cp >= min_p + delta * i + (i > pos - rest ? i + rest - pos + 1 : 0);
                     i++);
                cp = min_p + delta * (MAX(MIN(i + size, pos), 1) - 1) +
                     (i > pos - rest ? i + rest - pos + 1 : 0);
            }
            break;
    }

    switch (sCh) {
        case 'A':  // absolute size
            cs = size;
            break;
        case 'a':  // absolute relative size
            cs = MAX(1, cs + size);
            break;
        case '%':  // client size percentage in relation to monitor window area size
            if (size <= 0)
                break;
            size = max_s * MIN(size, 100) / 100;
            /* falls through */
        case 'h':
        case 'w':  // size relative to client
            if (sCh == 'w' || sCh == 'h') {
                if (size == 0)
                    break;
                size += cs;
            }
            /* falls through */
        case 'H':
        case 'W':  // normal size, position takes precedence
            if (pCh == 'S' && cp + size > min_p + max_s)
                size = min_p + max_s - cp;
            else if (size > max_s)
                size = max_s;

            if (pCh == 'C') {  // fixed client center, expand or contract client
                delta = size - cs;
                if (delta < 0 || (cp - delta / 2 + size <= min_p + max_s))
                    cp -= delta / 2;
                else if (cp - delta / 2 < min_p)
                    cp = min_p;
                else if (delta)
                    cp = min_p + max_s;
            } else if (pCh == 'Z')
                cp -= size - cs;

            cs = size;
            break;
    }

    if (pCh ==
        '%')  // client mid-point position in relation to monitor window area size
        cp = min_p + max_s * MAX(MIN(pos, 100), 0) / 100 - (cs) / 2;
    if (pCh == 'm' || pCh == 'M')
        cp = pos - cs / 2;

    if (!abs_p && cp < min_p)
        cp = min_p;
    if (cp + cs > min_p + max_s && !(abs_p && abs_s)) {
        if (abs_p || cp == min_p)
            cs = min_p + max_s - cp;
        else
            cp = min_p + max_s - cs;
    }

    *out_p = cp;
    *out_s = MAX(cs - 2 * cbw, 1);
}

static uint32_t prealpha(uint32_t p) {
    uint8_t a = p >> 24u;
    uint32_t rb = (a * (p & 0xFF00FFu)) >> 8u;
    uint32_t g = (a * (p & 0x00FF00u)) >> 8u;
    return (rb & 0xFF00FFu) | (g & 0x00FF00u) | (a << 24u);
}

Picture geticonprop(Window win, unsigned int *picw, unsigned int *pich) {
    int format;
    unsigned long n, extra, *p = NULL;
    Atom real;

    if (XGetWindowProperty(dpy, win, netatom[NetWMIcon], 0L, LONG_MAX, False,
                           AnyPropertyType, &real, &format, &n, &extra,
                           (unsigned char **)&p) != Success)
        return None;
    if (n == 0 || format != 32) {
        XFree(p);
        return None;
    }

    unsigned long *bstp = NULL;
    uint32_t w, h, sz;
    {
        unsigned long *i;
        const unsigned long *end = p + n;
        uint32_t bstd = UINT32_MAX, d, m;
        for (i = p; i < end - 1; i += sz) {
            if ((w = *i++) >= 16384 || (h = *i++) >= 16384) {
                XFree(p);
                return None;
            }
            if ((sz = w * h) > end - i)
                break;
            if ((m = w > h ? w : h) >= ICONSIZE && (d = m - ICONSIZE) < bstd) {
                bstd = d;
                bstp = i;
            }
        }
        if (!bstp) {
            for (i = p; i < end - 1; i += sz) {
                if ((w = *i++) >= 16384 || (h = *i++) >= 16384) {
                    XFree(p);
                    return None;
                }
                if ((sz = w * h) > end - i)
                    break;
                if ((d = ICONSIZE - (w > h ? w : h)) < bstd) {
                    bstd = d;
                    bstp = i;
                }
            }
        }
        if (!bstp) {
            XFree(p);
            return None;
        }
    }

    if ((w = *(bstp - 2)) == 0 || (h = *(bstp - 1)) == 0) {
        XFree(p);
        return None;
    }

    uint32_t icw, ich;
    if (w <= h) {
        ich = ICONSIZE;
        icw = w * ICONSIZE / h;
        if (icw == 0)
            icw = 1;
    } else {
        icw = ICONSIZE;
        ich = h * ICONSIZE / w;
        if (ich == 0)
            ich = 1;
    }
    *picw = icw;
    *pich = ich;

    uint32_t i, *bstp32 = (uint32_t *)bstp;
    for (sz = w * h, i = 0; i < sz; ++i)
        bstp32[i] = prealpha(bstp[i]);

    Picture ret = drw_picture_create_resized(drw, (char *)bstp, w, h, icw, ich);
    XFree(p);

    return ret;
}

int getrootptr(int *x, int *y) {
    int di;
    unsigned int dui;
    Window dummy;

    return XQueryPointer(dpy, root, &dummy, &dummy, x, y, &di, &di, &dui);
}

long getstate(Window w) {
    int format;
    long result = -1;
    unsigned char *p = NULL;
    unsigned long n, extra;
    Atom real;

    if (XGetWindowProperty(dpy, w, wmatom[WMState], 0L, 2L, False,
                           wmatom[WMState], &real, &format, &n, &extra,
                           (unsigned char **)&p) != Success)
        return -1;
    if (n != 0)
        result = *p;
    XFree(p);
    return result;
}

int gettextprop(Window w, Atom atom, char *text, unsigned int size) {
    char **list = NULL;
    int n;
    XTextProperty name;

    if (!text || size == 0)
        return 0;
    text[0] = '\0';
    if (!XGetTextProperty(dpy, w, &name, atom) || !name.nitems)
        return 0;
    if (name.encoding == XA_STRING) {
        strncpy(text, (char *)name.value, size - 1);
    } else if (XmbTextPropertyToTextList(dpy, &name, &list, &n) >= Success &&
               n > 0 && *list) {
        strncpy(text, *list, size - 1);
        XFreeStringList(list);
    }
    text[size - 1] = '\0';
    XFree(name.value);
    return 1;
}

void drawbar(Monitor *m) {
    int x, y = 0, w, tw = 0, stw = 0;
    int th = bh;
    int mw = m->ww;
    int title_start, title_width;
    unsigned int i, occ = 0, urg = 0;
    Client *c;

    int logo_width = logo_state ? TEXTW(logo) : 0;
    int power_width = power_state ? TEXTW(power) : 0;

    static const int tag_colors_active[] = {
        SchemeTag1Active, SchemeTag2Active, SchemeTag3Active,
        SchemeTag4Active, SchemeTag5Active, SchemeTag6Active,
        SchemeTag7Active, SchemeTag8Active, SchemeTag9Active};

    static const int tag_colors_inactive[] = {
        SchemeTag1Inactive, SchemeTag2Inactive, SchemeTag3Inactive,
        SchemeTag4Inactive, SchemeTag5Inactive, SchemeTag6Inactive,
        SchemeTag7Inactive, SchemeTag8Inactive, SchemeTag9Inactive};

    if (!m->showbar)
        return;

    XFillRectangle(drw->dpy, drw->drawable, drw->gc, 0, 0, m->ww, bh);

    if (showsystray && m == systraytomon(m)) {
        stw = getsystraywidth();
        if (!systrayonleft) {
            stw += systraybarspacing;
        }
    }

    x = 0;

    if (logo_state) {
        drw_setscheme(drw, scheme[SchemeLogo]);
        drw_rect(drw, x, y, logo_width, th, 1, 1);
        drw_text(drw, x, y, logo_width, th, lrpad / 2, logo, 0);
        x += logo_width;
    }

    if (m == selmon) {
        drw_setscheme(drw, scheme[SchemeNorm]);
        tw = TEXTW(stext) - lrpad / 2 + 2;
        drw_text(drw, mw - tw - stw - power_width, y, tw, th, lrpad / 2 - 2, stext,
                 0);
    }

    resizebarwin(m);

    for (c = m->clients; c; c = c->next) {
        if (c->tags != ~0)
            occ |= c->tags;

        if (c->isurgent)
            urg |= c->tags;
    }

    for (i = 0; i < LENGTH(tags); i++) {
        const char *icon;
        int is_active = m->tagset[m->seltags] & (1 << i);

        icon = is_active ? tagicons_active[i] : tags[i];

        w = TEXTW(icon);

        drw_setscheme(
            drw,
            scheme[is_active
                       ? tag_colors_active[i % LENGTH(tag_colors_active)]
                       : tag_colors_inactive[i % LENGTH(tag_colors_inactive)]]);

        drw_text(drw, x, y, w, th, lrpad / 2, icon, urg & (1 << i));

        if (occ & (1 << i)) {
            int line_width = w - 8;

            if (show_tag_boxes == 1) {
                int line_height = MAX(1, bh / 12);
                int line_y_position = 2;

                int line_offset = (w - line_width) / 2;
                drw_setscheme(drw, scheme[is_active ? SchemeFg : SchemeNorm]);
                drw_rect(drw, x + line_offset, line_y_position, line_width, line_height,
                         1, 0);
            } else if (show_tag_boxes == 2) {
                int line_height = MAX(1, bh / 12);
                int line_y_position = bh - line_height - 2;

                int line_offset = (w - line_width) / 2;
                drw_setscheme(drw, scheme[is_active ? SchemeFg : SchemeNorm]);
                drw_rect(drw, x + line_offset, line_y_position, line_width, line_height,
                         1, 0);
            } else if (show_tag_boxes == 3) {
                int box_size = MIN(bh / 3, 5);
                int box_y_position = (bh - box_size) / 2.5;
                int offset = 5;
                drw_setscheme(drw, scheme[is_active ? SchemeFg : SchemeNorm]);
                drw_rect(drw, x + offset, box_y_position, box_size, box_size, 1, 0);
            }
        }
        x += w;
    }

    w = TEXTW(m->ltsymbol);
    drw_setscheme(drw, scheme[SchemeNorm]);
    x = drw_text(drw, x, y, w, th, lrpad / 2, m->ltsymbol, 0);

    if ((title_width = mw - tw - stw - x - power_width + 10) > th) {
        title_start = x;

        switch (showtitle) {
            case 0: {
                if (m->sel) {
                    char app_name[256] = "Unknown";
                    XClassHint ch = {NULL, NULL};
                    if (XGetClassHint(dpy, m->sel->win, &ch)) {
                        if (ch.res_class) {
                            strncpy(app_name, ch.res_class, sizeof(app_name) - 1);
                            app_name[sizeof(app_name) - 1] = '\0';
                            XFree(ch.res_class);
                        }
                        if (ch.res_name)
                            XFree(ch.res_name);
                    }

                    int total_width = TEXTW(app_name);
                    int icon_offset = 0;

                    if (m->sel->icon) {
                        total_width += m->sel->icw + ICONSPACING;
                    }

                    int center_offset = MAX((title_width - total_width) / 2, 0);

                    // Рисуем фон
                    drw_setscheme(drw, scheme[SchemeTitle]);
                    drw_rect(drw, title_start, y, title_width, th, 1, 1);

                    // Рисуем иконку, если есть
                    if (m->sel->icon) {
                        drw_pic(drw, title_start + center_offset, y + (th - m->sel->ich) / 2,
                                m->sel->icw, m->sel->ich, m->sel->icon);
                        icon_offset = m->sel->icw + ICONSPACING;
                    }

                    // Рисуем текст
                    drw_text(drw, title_start + center_offset + icon_offset, y,
                             title_width - center_offset - icon_offset, th, lrpad / 2,
                             app_name, 0);
                } else {
                    int art_width = TEXTW(ascii_art);

                    // Рисуем фон
                    drw_setscheme(drw, scheme[SchemeTitle]);
                    drw_rect(drw, title_start, y, title_width, th, 1, 1);

                    // Рисуем ASCII-арт, если текст отсутствует
                    drw_text(drw, title_start + MAX((title_width - art_width) / 2, 0), y,
                             art_width, th, lrpad / 2, ascii_art, 0);
                }
                break;
            }

            case 1: {
                int art_width = TEXTW(ascii_art);

                // Рисуем фон
                drw_setscheme(drw, scheme[SchemeTitle]);
                drw_rect(drw, title_start, y, title_width, th, 1, 1);

                // Рисуем ASCII-арт
                drw_text(drw, title_start + MAX((title_width - art_width) / 2, 0), y,
                         art_width, th, lrpad / 2, ascii_art, 0);
                break;
            }

            case 2: {
                // Рисуем полный фон
                drw_rect(drw, title_start, y, title_width, th, 1, 1);
                break;
            }
            case 3: {  // Часы HH:MM:SS
                time_t now = time(NULL);
                struct tm *tm_info = localtime(&now);
                char time_str[9];  // "HH:MM:SS"
                strftime(time_str, sizeof(time_str), "%H:%M:%S", tm_info);

                int time_width = TEXTW(time_str);
                int time_x = title_start + MAX((title_width - time_width) / 2, 0);

                drw_setscheme(drw, scheme[SchemeTitle]);
                drw_rect(drw, time_x, y, time_width, th, 1, 1);  // Фон только под текст
                drw_text(drw, time_x, y, time_width, th, lrpad / 2, time_str, 0);
                break;
            }

            case 4: {  // Часы AM/PM
                time_t now = time(NULL);
                struct tm *tm_info = localtime(&now);
                char time_str[9];  // "HH:MM AM/PM"
                strftime(time_str, sizeof(time_str), "%I:%M %p", tm_info);

                int time_width = TEXTW(time_str);
                int time_x = title_start + MAX((title_width - time_width) / 2, 0);

                drw_setscheme(drw, scheme[SchemeTitle]);
                drw_rect(drw, time_x, y, time_width, th, 1, 1);
                drw_text(drw, time_x, y, time_width, th, lrpad / 2, time_str, 0);
                break;
            }
        }
    }

    if (power_state) {
        drw_setscheme(drw, scheme[SchemePower]);
        int power_x = mw - power_width - stw - borderpx;
        drw_rect(drw, power_x, y, power_width, th, 1, 1);
        drw_text(drw, power_x, y, power_width, th, lrpad / 2, power, 0);
    }

    drw_map(drw, m->barwin, 0, 0, m->ww - stw, bh);
}

void MINIBOXloadState() {
    FILE *inputFile = fopen(CURRENTS_MINIBOX, "r");
    if (inputFile != NULL) {
        fscanf(inputFile, "%d", &show_tag_boxes);  // Считываем значение из файла
        fclose(inputFile);
    }
}

void MINIBOXsaveState() {
    FILE *outputFile = fopen(CURRENTS_MINIBOX, "w");
    if (outputFile != NULL) {
        fprintf(outputFile, "%d", show_tag_boxes);  // Записываем значение в файл
        fclose(outputFile);
    }
}
// Изменение функции toggleTagBoxes
void toggleTagBoxes(const Arg *arg) {
    if (show_tag_boxes == 1) {
        show_tag_boxes = 2;
    } else if (show_tag_boxes == 2) {
        show_tag_boxes = 3;
    } else if (show_tag_boxes == 3) {
        show_tag_boxes = 1;
    } else if (show_tag_boxes == 4) {
        show_tag_boxes = 4;
    }

    // Сохраняем новое состояние
    MINIBOXsaveState();  // Функция сохранения
}

void toggleshowtitle(const Arg *arg) {
    // Переключаем между 5 состояниями (0-4)
    showtitle = (showtitle + 1) % 5;

    save_showtitle_state();  // Сохраняем состояние
    drawbars();              // Обновляем панели
}

void grabkeys(void) {
    updatenumlockmask();
    {
        /* unsigned int i, j, k; */
        unsigned int i, c, k;
        unsigned int modifiers[] = {0, LockMask, numlockmask,
                                    numlockmask | LockMask};
        int start, end, skip;
        KeySym *syms;

        XUngrabKey(dpy, AnyKey, AnyModifier, root);
        XDisplayKeycodes(dpy, &start, &end);
        syms = XGetKeyboardMapping(dpy, start, end - start + 1, &skip);
        if (!syms)
            return;

        for (k = start; k <= end; k++)
            for (i = 0; i < LENGTH(keychords); i++)
                /* skip modifier codes, we do that ourselves */
                if (keychords[i]->keys[currentkey].keysym == syms[(k - start) * skip])
                    for (c = 0; c < LENGTH(modifiers); c++)
                        XGrabKey(dpy, k, keychords[i]->keys[currentkey].mod | modifiers[c],
                                 root, True, GrabModeAsync, GrabModeAsync);
        if (currentkey > 0)
            XGrabKey(dpy, XKeysymToKeycode(dpy, XK_Escape), AnyModifier, root, True,
                     GrabModeAsync, GrabModeAsync);
        XFree(syms);
    }
}

void incnmaster(const Arg *arg) {
    selmon->nmaster = selmon->pertag->nmasters[selmon->pertag->curtag] =
        MAX(selmon->nmaster + arg->i, 0);
    arrange(selmon);
}

#ifdef XINERAMA
static int isuniquegeom(XineramaScreenInfo *unique, size_t n,
                        XineramaScreenInfo *info) {
    while (n--)
        if (unique[n].x_org == info->x_org && unique[n].y_org == info->y_org &&
            unique[n].width == info->width && unique[n].height == info->height)
            return 0;
    return 1;
}
#endif /* XINERAMA */

void keypress(XEvent *e) {
    /* unsigned int i; */
    XEvent event = *e;
    unsigned int ran = 0;
    KeySym keysym;
    XKeyEvent *ev;

    Keychord *arr1[sizeof(keychords) / sizeof(Keychord *)];
    Keychord *arr2[sizeof(keychords) / sizeof(Keychord *)];
    memcpy(arr1, keychords, sizeof(keychords));
    Keychord **rpointer = arr1;
    Keychord **wpointer = arr2;

    size_t r = sizeof(keychords) / sizeof(Keychord *);

    while (1) {
        ev = &event.xkey;
        keysym = XKeycodeToKeysym(dpy, (KeyCode)ev->keycode, 0);
        size_t w = 0;
        for (int i = 0; i < r; i++) {
            if (keysym == (*(rpointer + i))->keys[currentkey].keysym &&
                CLEANMASK((*(rpointer + i))->keys[currentkey].mod) ==
                    CLEANMASK(ev->state) &&
                (*(rpointer + i))->func) {
                if ((*(rpointer + i))->n == currentkey + 1) {
                    (*(rpointer + i))->func(&((*(rpointer + i))->arg));
                    ran = 1;
                } else {
                    *(wpointer + w) = *(rpointer + i);
                    w++;
                }
            }
        }
        currentkey++;
        if (w == 0 || ran == 1)
            break;
        grabkeys();
        while (running && !XNextEvent(dpy, &event) && !ran)
            if (event.type == KeyPress)
                break;
        r = w;
        Keychord **holder = rpointer;
        rpointer = wpointer;
        wpointer = holder;
    }
    currentkey = 0;
    grabkeys();
}

void killclient(const Arg *arg) {
    if (!selmon->sel)
        return;

    if (!sendevent(selmon->sel->win, wmatom[WMDelete], NoEventMask,
                   wmatom[WMDelete], CurrentTime, 0, 0, 0)) {
        XGrabServer(dpy);
        XSetErrorHandler(xerrordummy);
        XSetCloseDownMode(dpy, DestroyAll);
        XKillClient(dpy, selmon->sel->win);
        XSync(dpy, False);
        XSetErrorHandler(xerror);
        XUngrabServer(dpy);
    }
}

void manage(Window w, XWindowAttributes *wa) {
    Client *c, *t = NULL;
    Window trans = None;
    XWindowChanges wc;

    c = ecalloc(1, sizeof(Client));
    c->hasfloatpos = 0;
    c->win = w;

    c->x = c->oldx = wa->x;
    c->y = c->oldy = wa->y;
    c->w = c->oldw = wa->width;
    c->h = c->oldh = wa->height;
    c->oldbw = wa->border_width;
    c->cfact = 1.0;
    c->ignoresizehints = 0;
    c->needsiconupdate = 1;

    updateicon(c);
    updatetitle(c);

    Atom type = None;
    unsigned char *data = NULL;
    int format;
    unsigned long nitems, bytes_after;

    Atom wtype = getatomprop(c, netatom[NetWMWindowType]);

    // Проверка на типы окон
    if (wtype == netatom[NetWMWindowTypeDialog] ||
        wtype == netatom[NetWMWindowTypeNormal]) {
        c->isfloating = 1;
    }

    if (wtype == netatom[NetWMWindowTypeUtility]) {
        c->isfloating = 1;
        c->bw = 0;
        XSetWindowBorderWidth(dpy, w, 0);
    }

    // Проверка на тип PopUp меню
    if (wtype == netatom[NetWMWindowTypePopupMenu]) {
        c->isfloating = 1;  // Окно будет плавающим
        c->bw = 0;          // Убираем границу
        XSetWindowBorderWidth(dpy, w, 0);
        // Если вы хотите, чтобы PopUp меню всегда было поверх других окон:
        XRaiseWindow(dpy, w);
    }

    // Проверка на тип Menu (для контекстных меню или меню приложений)
    if (wtype == netatom[NetWMWindowTypeMenu]) {
        c->isfloating = 1;  // Окно будет плавающим
        c->bw = 0;          // Убираем границу
        XSetWindowBorderWidth(dpy, w, 0);
        // Если вы хотите, чтобы меню всегда было поверх других окон:
        XRaiseWindow(dpy, w);
    }

    // Проверка на тип Toolbar
    if (wtype == netatom[NetWMWindowTypeToolbar]) {
        c->isfloating = 1;                 // Окно будет плавающим
        c->bw = 0;                         // Убираем границу, если нужно
        XSetWindowBorderWidth(dpy, w, 0);  // Установить 0 границу для панели инструментов

        // Дополнительные действия для Toolbar, если нужно:
        XRaiseWindow(dpy, w);  // Повышаем окно (сделать его на переднем плане)
    }

    // Обработка других типов окон, если нужно...
    if (XGetWindowProperty(dpy, w, netatom[NetWMWindowType], 0L, 1L, False,
                           XA_ATOM, &type, &format, &nitems, &bytes_after,
                           &data) == Success &&
        data) {
        if (*(Atom *)data == netatom[NetWMWindowTypeDock]) {
            XFree(data);

            long struts[4] = {0};
            if (XGetWindowProperty(
                    dpy, w, XInternAtom(dpy, "_NET_WM_STRUT_PARTIAL", False), 0L, 4L,
                    False, XA_CARDINAL, &type, &format, &nitems, &bytes_after,
                    (unsigned char **)&data) == Success &&
                data) {
                memcpy(struts, data, sizeof(long) * 4);
                XFree(data);

                if (struts[0] > 0)
                    selmon->wx += struts[0];
                if (struts[1] > 0)
                    selmon->ww -= struts[1];
                if (struts[2] > 0)
                    selmon->wy += struts[2];
                if (struts[3] > 0)
                    selmon->wh -= struts[3];
            }

            XRaiseWindow(dpy, w);
            XMapWindow(dpy, w);

            XChangeProperty(dpy, root, netatom[NetClientList], XA_WINDOW, 32,
                            PropModeAppend, (unsigned char *)&w, 1);

            free(c);
            return;
        }
        XFree(data);
    }
    Atom protocols __attribute__((unused));

    c->bw = borderpx;

    if (XGetTransientForHint(dpy, w, &trans) && (t = wintoclient(trans))) {
        c->mon = t->mon;
        c->tags = t->tags;
    } else {
        c->mon = selmon;
        applyrules(c);
    }

    restoreclienttags(c);

    if (c->x + WIDTH(c) > c->mon->mx + c->mon->mw)
        c->x = c->mon->mx + c->mon->mw - WIDTH(c);
    if (c->y + HEIGHT(c) > c->mon->my + c->mon->mh)
        c->y = c->mon->my + c->mon->mh - HEIGHT(c);
    c->x = MAX(c->x, c->mon->wx);
    c->y = MAX(c->y, c->mon->wy);

    char class[256] = "";
    XClassHint ch = {NULL, NULL};

    if (XGetClassHint(dpy, c->win, &ch)) {
        if (ch.res_class)
            strncpy(class, ch.res_class, sizeof(class) - 1);

        if (is_alltags_app(class)) {
            c->tags = ~0;
        }

        if (is_noborder_app(class)) {
            c->bw = 0;
        } else {
            c->bw = borderpx;
        }

        if (ch.res_class)
            XFree(ch.res_class);
        if (ch.res_name)
            XFree(ch.res_name);
    } else {
        c->bw = borderpx;
    }

    wc.border_width = c->bw;
    XConfigureWindow(dpy, w, CWBorderWidth, &wc);
    XSetWindowBorder(dpy, w, scheme[SchemeNorm][ColBorder].pixel);

    configure(c);
    updatewindowtype(c);
    updatesizehints(c);
    updatewmhints(c);
    if (c->isfloating) {
        if (c->hasfloatpos == 0) {
            c->x = c->mon->wx + (c->mon->ww - WIDTH(c)) / 2;
            c->y = c->mon->wy + (c->mon->wh - HEIGHT(c)) / 2;
        }
    } else {
        c->x = c->mon->wx + (c->mon->ww - WIDTH(c)) / 2;
        c->y = c->mon->wy + (c->mon->wh - HEIGHT(c)) / 2;
    }

    XMoveResizeWindow(dpy, c->win, c->x, c->y, c->w, c->h);

    if (attachbelow)
        attachBelow(c);
    else
        attach(c);

    attachstack(c);

    XChangeProperty(dpy, root, netatom[NetClientList], XA_WINDOW, 32,
                    PropModeAppend, (unsigned char *)&(c->win), 1);
    setclientstate(c, NormalState);

    if (c->mon == selmon)
        unfocus(selmon->sel, 0);

    c->mon->sel = c;
    arrange(c->mon);
    XMapWindow(dpy, c->win);

    saveclienttags(c);

    updateclientlist();

    focus(NULL);
}

int is_nosavetags_class(const char *class) {
    for (int i = 0; nosavetags_classes[i]; i++) {
        if (strcmp(class, nosavetags_classes[i]) == 0)
            return 1;
    }
    return 0;
}

void saveclienttags(Client *c) {
    char class[256] = "";
    XClassHint ch = {NULL, NULL};

    if (XGetClassHint(dpy, c->win, &ch)) {
        if (ch.res_class) {
            strncpy(class, ch.res_class, sizeof(class) - 1);
            if (is_nosavetags_class(class)) {
                // Если класс в списке исключений, выходим
                XFree(ch.res_class);
                if (ch.res_name)
                    XFree(ch.res_name);
                return;
            }
        }
        if (ch.res_class)
            XFree(ch.res_class);
        if (ch.res_name)
            XFree(ch.res_name);
    }

    // Сохраняем теги и монитор
    long data[2] = {c->tags, c->mon->num};
    XChangeProperty(dpy, c->win, netatom[NetClientInfo], XA_CARDINAL, 32,
                    PropModeReplace, (unsigned char *)data, 2);
}

void restoreclienttags(Client *c) {
    char class[256] = "";
    XClassHint ch = {NULL, NULL};

    if (XGetClassHint(dpy, c->win, &ch)) {
        if (ch.res_class) {
            strncpy(class, ch.res_class, sizeof(class) - 1);
            if (is_nosavetags_class(class)) {
                // Если класс в списке исключений, выходим
                XFree(ch.res_class);
                if (ch.res_name)
                    XFree(ch.res_name);
                return;
            }
        }
        if (ch.res_class)
            XFree(ch.res_class);
        if (ch.res_name)
            XFree(ch.res_name);
    }

    // Восстанавливаем теги и монитор
    Atom actual_type;
    int actual_format;
    unsigned long nitems, bytes_after;
    unsigned long *data = NULL;

    if (XGetWindowProperty(dpy, c->win, netatom[NetClientInfo], 0L, 2L, False,
                           XA_CARDINAL, &actual_type, &actual_format, &nitems,
                           &bytes_after, (unsigned char **)&data) == Success &&
        nitems == 2) {
        c->tags = data[0];
        for (Monitor *m = mons; m; m = m->next) {
            if (m->num == data[1]) {
                c->mon = m;
                break;
            }
        }
    }
    if (data)
        XFree(data);
}

int is_noborder_app(const char *class) {
    for (int i = 0; noborder_apps[i]; i++) {
        if (strstr(class, noborder_apps[i]))
            return 1;
    }
    return 0;
}

int is_alltags_app(const char *class) {
    for (int i = 0; alltags_apps[i]; i++) {
        if (strstr(class, alltags_apps[i]))
            return 1;
    }
    return 0;
}

void mappingnotify(XEvent *e) {
    XMappingEvent *ev = &e->xmapping;

    XRefreshKeyboardMapping(ev);
    if (ev->request == MappingKeyboard)
        grabkeys();
}

void maprequest(XEvent *e) {
    static XWindowAttributes wa;
    XMapRequestEvent *ev = &e->xmaprequest;

    Client *i;
    if ((i = wintosystrayicon(ev->window))) {
        sendevent(i->win, netatom[Xembed], StructureNotifyMask, CurrentTime,
                  XEMBED_WINDOW_ACTIVATE, 0, systray->win, XEMBED_EMBEDDED_VERSION);
        resizebarwin(selmon);
        updatesystray();
    }

    if (!XGetWindowAttributes(dpy, ev->window, &wa) || wa.override_redirect)
        return;
    if (!wintoclient(ev->window))
        manage(ev->window, &wa);
}

void motionnotify(XEvent *e) {
    static Monitor *mon = NULL;
    Monitor *m;
    XMotionEvent *ev = &e->xmotion;
    unsigned int i, x;

    if (ev->window == selmon->barwin) {
        i = x = 0;

        /* Учитываем область логотипа */
        int logo_width = TEXTW(logo);
        if (ev->x < logo_width) {
            if (selmon->previewshow) {
                selmon->previewshow = 0;
                XUnmapWindow(dpy, selmon->tagwin);
            }
            return;  // Наведение на логотип, ничего не делаем
        }

        x += logo_width;  // Начинаем проверку тегов после логотипа

        do
            x += TEXTW(tags[i]);
        while (ev->x >= x && ++i < LENGTH(tags));

        if (i < LENGTH(tags)) {
            if (selmon->previewshow != (i + 1) &&
                !(selmon->tagset[selmon->seltags] & 1 << i)) {
                selmon->previewshow = i + 1;
                showtagpreview(i);
            } else if (selmon->tagset[selmon->seltags] & 1 << i) {
                selmon->previewshow = 0;
                XUnmapWindow(dpy, selmon->tagwin);
            }
        } else if (selmon->previewshow) {
            selmon->previewshow = 0;
            XUnmapWindow(dpy, selmon->tagwin);
        }
    } else if (ev->window == selmon->tagwin) {
        selmon->previewshow = 0;
        XUnmapWindow(dpy, selmon->tagwin);
    } else if (selmon->previewshow) {
        selmon->previewshow = 0;
        XUnmapWindow(dpy, selmon->tagwin);
    }

    if (ev->window != root)
        return;
    if ((m = recttomon(ev->x_root, ev->y_root, 1, 1)) != mon && mon) {
        unfocus(selmon->sel, 1);
        selmon = m;
        focus(NULL);
    }
    mon = m;
}

void setfloatpos(Client *c, const char *floatpos) {
    char xCh, yCh, wCh, hCh;
    int x, y, w, h, wx, ww, wy, wh;

    if (!c || !floatpos)
        return;

    c->hasfloatpos = 1;  // Устанавливаем флаг floatpos

    // Проверка на плавающее окно
    if (selmon->lt[selmon->sellt]->arrange && !c->isfloating)
        return;

    // Разбор строки позиции
    switch (sscanf(floatpos, "%d%c %d%c %d%c %d%c", &x, &xCh, &y, &yCh, &w, &wCh,
                   &h, &hCh)) {
        case 4:
            if (xCh == 'w' || xCh == 'W') {  // Относительные размеры окна
                w = x;
                wCh = xCh;
                h = y;
                hCh = yCh;
                x = -1;
                xCh = 'C';
                y = -1;
                yCh = 'C';
            } else if (xCh == 'p' || xCh == 'P') {  // Процентные размеры
                w = x;
                wCh = xCh;
                h = y;
                hCh = yCh;
                x = 0;
                xCh = 'G';
                y = 0;
                yCh = 'G';
            } else if (xCh == 'm' || xCh == 'M') {  // Абсолютное положение мыши
                getrootptr(&x, &y);
            } else {  // Если ничего не совпало
                w = 0;
                wCh = 0;
                h = 0;
                hCh = 0;
            }
            break;
        case 8:
            if (xCh == 'm' || xCh == 'M')  // Мышь для абсолютных координат
                getrootptr(&x, &y);
            break;
        default:
            return;  // Если ничего не подходит
    }

    // Область монитора
    wx = c->mon->wx;
    wy = c->mon->wy;
    ww = c->mon->ww;
    wh = c->mon->wh;

    // Игнорировать подсказки по размеру
    c->ignoresizehints = 1;

    // Установка позиции и размера окна
    getfloatpos(x, xCh, w, wCh, wx, ww, c->x, c->w, c->bw, floatposgrid_x, &c->x,
                &c->w);
    getfloatpos(y, yCh, h, hCh, wy, wh, c->y, c->h, c->bw, floatposgrid_y, &c->y,
                &c->h);
}

void movemouse(const Arg *arg) {
    int x, y, ocx, ocy, nx, ny;
    Client *c;
    Monitor *m;
    XEvent ev;
    Time lasttime = 0;

    if (!(c = selmon->sel))
        return;
    if (c->isfullscreen) /* no support moving fullscreen windows by mouse */
        return;
    restack(selmon);
    ocx = c->x;
    ocy = c->y;
    if (XGrabPointer(dpy, root, False, MOUSEMASK, GrabModeAsync, GrabModeAsync,
                     None, cursor[CurMove]->cursor, CurrentTime) != GrabSuccess)
        return;
    if (!getrootptr(&x, &y))
        return;
    do {
        XMaskEvent(dpy, MOUSEMASK | ExposureMask | SubstructureRedirectMask, &ev);
        switch (ev.type) {
            case ConfigureRequest:
            case Expose:
            case MapRequest:
                handler[ev.type](&ev);
                break;
            case MotionNotify:
                if ((ev.xmotion.time - lasttime) <= (1000 / 60))
                    continue;
                lasttime = ev.xmotion.time;

                nx = ocx + (ev.xmotion.x - x);
                ny = ocy + (ev.xmotion.y - y);
                if (abs(selmon->wx - nx) < snap)
                    nx = selmon->wx;
                else if (abs((selmon->wx + selmon->ww) - (nx + WIDTH(c))) < snap)
                    nx = selmon->wx + selmon->ww - WIDTH(c);
                if (abs(selmon->wy - ny) < snap)
                    ny = selmon->wy;
                else if (abs((selmon->wy + selmon->wh) - (ny + HEIGHT(c))) < snap)
                    ny = selmon->wy + selmon->wh - HEIGHT(c);
                if (!selmon->lt[selmon->sellt]->arrange || c->isfloating)
                    resize(c, nx, ny, c->w, c->h, 1);
                else if (selmon->lt[selmon->sellt]->arrange || !c->isfloating) {
                    if ((m = recttomon(ev.xmotion.x_root, ev.xmotion.y_root, 1, 1)) !=
                        selmon) {
                        sendmon(c, m);
                        selmon = m;
                        focus(NULL);
                    }

                    Client *cc = c->mon->clients;
                    while (1) {
                        if (cc == 0)
                            break;
                        if (cc != c && !cc->isfloating && ISVISIBLE(cc) &&
                            ev.xmotion.x_root > cc->x && ev.xmotion.x_root < cc->x + cc->w &&
                            ev.xmotion.y_root > cc->y && ev.xmotion.y_root < cc->y + cc->h) {
                            break;
                        }

                        cc = cc->next;
                    }

                    if (cc) {
                        Client *cl1, *cl2, ocl1;

                        if (!selmon->lt[selmon->sellt]->arrange)
                            return;

                        cl1 = c;
                        cl2 = cc;
                        ocl1 = *cl1;
                        strcpy(cl1->name, cl2->name);
                        cl1->win = cl2->win;
                        cl1->x = cl2->x;
                        cl1->y = cl2->y;
                        cl1->w = cl2->w;
                        cl1->h = cl2->h;

                        cl2->win = ocl1.win;
                        strcpy(cl2->name, ocl1.name);
                        cl2->x = ocl1.x;
                        cl2->y = ocl1.y;
                        cl2->w = ocl1.w;
                        cl2->h = ocl1.h;

                        selmon->sel = cl2;

                        c = cc;
                        focus(c);

                        arrange(cl1->mon);
                    }
                }
                break;
        }
    } while (ev.type != ButtonRelease);
    XUngrabPointer(dpy, CurrentTime);
    if ((m = recttomon(c->x, c->y, c->w, c->h)) != selmon) {
        sendmon(c, m);
        selmon = m;
        focus(NULL);
    }
}

void moveresize(const Arg *arg) {
    /* only floating windows can be moved */
    Client *c;
    c = selmon->sel;
    int x, y, w, h, nx, ny, nw, nh, ox, oy, ow, oh;
    char xAbs, yAbs, wAbs, hAbs;
    int msx, msy, dx, dy, nmx, nmy;
    unsigned int dui;
    Window dummy;

    if (!c || !arg)
        return;
    if (selmon->lt[selmon->sellt]->arrange && !c->isfloating)
        return;
    if (sscanf((char *)arg->v, "%d%c %d%c %d%c %d%c", &x, &xAbs, &y, &yAbs, &w,
               &wAbs, &h, &hAbs) != 8)
        return;

    /* compute new window position; prevent window from be positioned outside the
     * current monitor */
    nw = c->w + w;
    if (wAbs == 'W')
        nw = w < selmon->mw - 2 * c->bw ? w : selmon->mw - 2 * c->bw;

    nh = c->h + h;
    if (hAbs == 'H')
        nh = h < selmon->mh - 2 * c->bw ? h : selmon->mh - 2 * c->bw;

    nx = c->x + x;
    if (xAbs == 'X') {
        if (x < selmon->mx)
            nx = selmon->mx;
        else if (x > selmon->mx + selmon->mw)
            nx = selmon->mx + selmon->mw - nw - 2 * c->bw;
        else
            nx = x;
    }

    ny = c->y + y;
    if (yAbs == 'Y') {
        if (y < selmon->my)
            ny = selmon->my;
        else if (y > selmon->my + selmon->mh)
            ny = selmon->my + selmon->mh - nh - 2 * c->bw;
        else
            ny = y;
    }

    ox = c->x;
    oy = c->y;
    ow = c->w;
    oh = c->h;

    XRaiseWindow(dpy, c->win);
    Bool xqp =
        XQueryPointer(dpy, root, &dummy, &dummy, &msx, &msy, &dx, &dy, &dui);
    resize(c, nx, ny, nw, nh, True);

    /* move cursor along with the window to avoid problems caused by the sloppy
     * focus */
    if (xqp && ox <= msx && (ox + ow) >= msx && oy <= msy && (oy + oh) >= msy) {
        nmx = c->x - ox + c->w - ow;
        nmy = c->y - oy + c->h - oh;
        /* make sure the cursor stays inside the window */
        if ((msx + nmx) > c->x && (msy + nmy) > c->y)
            XWarpPointer(dpy, None, None, 0, 0, 0, 0, nmx, nmy);
    }
}

void moveresizeedge(const Arg *arg) {
    /* move or resize floating window to edge of screen */
    Client *c;
    c = selmon->sel;
    char e;
    int nx, ny, nw, nh, ox, oy, ow, oh, bp;
    int msx, msy, dx, dy, nmx, nmy;
    int starty;
    unsigned int dui;
    Window dummy;

    nx = c->x;
    ny = c->y;
    nw = c->w;
    nh = c->h;

    starty = selmon->showbar && topbar ? bh : 0;
    bp = selmon->showbar && !topbar ? bh : 0;

    if (!c || !arg)
        return;
    if (selmon->lt[selmon->sellt]->arrange && !c->isfloating)
        return;
    if (sscanf((char *)arg->v, "%c", &e) != 1)
        return;

    if (e == 't')
        ny = starty;

    if (e == 'b')
        ny = c->h > selmon->mh - 2 * c->bw ? c->h - bp
                                           : selmon->mh - c->h - 2 * c->bw - bp;

    if (e == 'l')
        nx = selmon->mx;

    if (e == 'r')
        nx = c->w > selmon->mw - 2 * c->bw
                 ? selmon->mx + c->w
                 : selmon->mx + selmon->mw - c->w - 2 * c->bw;

    if (e == 'T') {
        /* if you click to resize again, it will return to old size/position */
        if (c->h + starty == c->oldh + c->oldy) {
            nh = c->oldh;
            ny = c->oldy;
        } else {
            nh = c->h + c->y - starty;
            ny = starty;
        }
    }

    if (e == 'B')
        nh = c->h + c->y + 2 * c->bw + bp == selmon->mh
                 ? c->oldh
                 : selmon->mh - c->y - 2 * c->bw - bp;

    if (e == 'L') {
        if (selmon->mx + c->w == c->oldw + c->oldx) {
            nw = c->oldw;
            nx = c->oldx;
        } else {
            nw = c->w + c->x - selmon->mx;
            nx = selmon->mx;
        }
    }

    if (e == 'R')
        nw = c->w + c->x + 2 * c->bw == selmon->mx + selmon->mw
                 ? c->oldw
                 : selmon->mx + selmon->mw - c->x - 2 * c->bw;

    ox = c->x;
    oy = c->y;
    ow = c->w;
    oh = c->h;

    XRaiseWindow(dpy, c->win);
    Bool xqp =
        XQueryPointer(dpy, root, &dummy, &dummy, &msx, &msy, &dx, &dy, &dui);
    resizeclient(c, nx, ny, nw, nh);

    /* move cursor along with the window to avoid problems caused by the sloppy
     * focus */
    if (xqp && ox <= msx && (ox + ow) >= msx && oy <= msy && (oy + oh) >= msy) {
        nmx = c->x - ox + c->w - ow;
        nmy = c->y - oy + c->h - oh;
        /* make sure the cursor stays inside the window */
        if ((msx + nmx) > c->x && (msy + nmy) > c->y)
            XWarpPointer(dpy, None, None, 0, 0, 0, 0, nmx, nmy);
    }
}

Client *nexttiled(Client *c) {
    for (; c && (c->isfloating || !ISVISIBLE(c)); c = c->next);
    return c;
}

void pop(Client *c) {
    detach(c);
    attach(c);
    focus(c);
    arrange(c->mon);
}

void propertynotify(XEvent *e) {
    Client *c;
    Window trans;
    XPropertyEvent *ev = &e->xproperty;

    if ((c = wintosystrayicon(ev->window))) {
        if (ev->atom == XA_WM_NORMAL_HINTS) {
            updatesizehints(c);
            updatesystrayicongeom(c, c->w, c->h);
        } else {
            updatesystrayiconstate(c, ev);
        }
        resizebarwin(selmon);
        updatesystray();
    }

    if ((ev->window == root) && (ev->atom == XA_WM_NAME)) {
        updatestatus();
    } else if (ev->state == PropertyDelete) {
        return; /* ignore */
    } else if ((c = wintoclient(ev->window))) {
        if (ev->atom == netatom[NetWMIcon]) {
            updateicon(c);
            if (c == c->mon->sel)
                drawbar(c->mon);
        } else {
            switch (ev->atom) {
                default:
                    break;
                case XA_WM_TRANSIENT_FOR:
                    if (!c->isfloating && (XGetTransientForHint(dpy, c->win, &trans)) &&
                        (c->isfloating = (wintoclient(trans)) != NULL))
                        arrange(c->mon);
                    break;
                case XA_WM_NORMAL_HINTS:
                    c->hintsvalid = 0;
                    break;
                case XA_WM_HINTS:
                    updatewmhints(c);
                    if (c == c->mon->sel)
                        drawbar(c->mon);
                    break;
            }
        }

        if (ev->atom == XA_WM_NAME || ev->atom == netatom[NetWMName]) {
            updatetitle(c);
            drawbar(c->mon);
        }
        if (ev->atom == netatom[NetWMWindowType]) {
            updatewindowtype(c);
            drawbar(c->mon);
        }
    }
}

void quit(const Arg *arg) { running = 0; }

Monitor *recttomon(int x, int y, int w, int h) {
    Monitor *m, *r = selmon;
    int a, area = 0;

    for (m = mons; m; m = m->next)
        if ((a = INTERSECT(x, y, w, h, m)) > area) {
            area = a;
            r = m;
        }
    return r;
}

void removesystrayicon(Client *i) {
    Client **ii;

    if (!showsystray || !i)
        return;
    for (ii = &systray->icons; *ii && *ii != i; ii = &(*ii)->next);
    if (ii)
        *ii = i->next;
    free(i);
}

void resize(Client *c, int x, int y, int w, int h, int interact) {
    if (applysizehints(c, &x, &y, &w, &h, interact))
        resizeclient(c, x, y, w, h);
}

void resizebarwin(Monitor *m) {
    unsigned int w = m->ww - 2 * sp; /* Учитываем боковые отступы */
    if (showsystray && m == systraytomon(m) && !systrayonleft)
        w -= getsystraywidth(); /* Учитываем ширину системного трея */
    XMoveResizeWindow(dpy, m->barwin, m->wx + sp, m->by + vp, w, bh);
}

void resizeclient(Client *c, int x, int y, int w, int h) {
    XWindowChanges wc;

    c->oldx = c->x;
    c->x = wc.x = x;
    c->oldy = c->y;
    c->y = wc.y = y;
    c->oldw = c->w;
    c->w = wc.width = w;
    c->oldh = c->h;
    c->h = wc.height = h;
    wc.border_width = c->bw;
    XConfigureWindow(dpy, c->win, CWX | CWY | CWWidth | CWHeight | CWBorderWidth,
                     &wc);
    configure(c);
    XSync(dpy, False);
}

void resizerequest(XEvent *e) {
    XResizeRequestEvent *ev = &e->xresizerequest;
    Client *i;

    if ((i = wintosystrayicon(ev->window))) {
        updatesystrayicongeom(i, ev->width, ev->height);
        resizebarwin(selmon);
        updatesystray();
    }
}

void resizemouse(const Arg *arg) {
    int x, y, ocw, och, nw, nh;
    Client *c;
    Monitor *m;
    XEvent ev;
    Time lasttime = 0;

    if (!(c = selmon->sel))
        return;
    if (c->isfullscreen) /* no support resizing fullscreen windows by mouse */
        return;
    restack(selmon);
    ocw = c->w;
    och = c->h;
    if (XGrabPointer(dpy, root, False, MOUSEMASK, GrabModeAsync, GrabModeAsync,
                     None, cursor[CurResize]->cursor, CurrentTime) != GrabSuccess)
        return;
    if (!getrootptr(&x, &y))
        return;
    do {
        XMaskEvent(dpy, MOUSEMASK | ExposureMask | SubstructureRedirectMask, &ev);
        switch (ev.type) {
            case ConfigureRequest:
            case Expose:
            case MapRequest:
                handler[ev.type](&ev);
                break;
            case MotionNotify:
                if ((ev.xmotion.time - lasttime) <= (1000 / 60))
                    continue;
                lasttime = ev.xmotion.time;

                nw = MAX(ocw + (ev.xmotion.x - x), 1);
                nh = MAX(och + (ev.xmotion.y - y), 1);
                if (c->mon->wx + nw >= selmon->wx &&
                    c->mon->wx + nw <= selmon->wx + selmon->ww &&
                    c->mon->wy + nh >= selmon->wy &&
                    c->mon->wy + nh <= selmon->wy + selmon->wh) {
                    if (!c->isfloating && selmon->lt[selmon->sellt]->arrange &&
                        (abs(nw - c->w) > snap || abs(nh - c->h) > snap))
                        togglefloating(NULL);
                }
                if (!selmon->lt[selmon->sellt]->arrange || c->isfloating)
                    resize(c, c->x, c->y, nw, nh, 1);
                break;
        }
    } while (ev.type != ButtonRelease);
    XUngrabPointer(dpy, CurrentTime);
    while (XCheckMaskEvent(dpy, EnterWindowMask, &ev));
    if ((m = recttomon(c->x, c->y, c->w, c->h)) != selmon) {
        sendmon(c, m);
        selmon = m;
        focus(NULL);
    }
}

void restack(Monitor *m) {
    Client *c;
    XEvent ev;
    XWindowChanges wc;

    drawbar(m);
    if (!m->sel)
        return;
    if (m->sel->isfloating || !m->lt[m->sellt]->arrange)
        XRaiseWindow(dpy, m->sel->win);
    if (m->lt[m->sellt]->arrange) {
        wc.stack_mode = Below;
        wc.sibling = m->barwin;
        for (c = m->stack; c; c = c->snext)
            if (!c->isfloating && ISVISIBLE(c)) {
                XConfigureWindow(dpy, c->win, CWSibling | CWStackMode, &wc);
                wc.sibling = c->win;
            }
    }
    XSync(dpy, False);
    while (XCheckMaskEvent(dpy, EnterWindowMask, &ev));
}

void run(void) {
    XEvent ev;
    /* main event loop */
    XSync(dpy, False);

    while (running) {
        /* Обработка всех событий из очереди */
        while (XPending(dpy)) {
            XNextEvent(dpy, &ev);
            if (handler[ev.type])
                handler[ev.type](&ev); /* call handler */
        }

        /* Регулярная проверка состояния клиентов */
        Client *c;
        for (Monitor *m = mons; m; m = m->next) {
            for (c = m->clients; c; c = c->next) {
                if (c->needsiconupdate) {
                    updateicon(c);
                    if (c->icon) {
                        c->needsiconupdate = 0; /* Сбрасываем флаг, если иконка загружена */
                        drawbar(m);             /* Перерисовываем панель */
                    }
                }
            }
        }

        /* Другие задачи */
    }
}

void scan(void) {
    unsigned int i, num;
    Window d1, d2, *wins = NULL;
    XWindowAttributes wa;

    if (XQueryTree(dpy, root, &d1, &d2, &wins, &num)) {
        for (i = 0; i < num; i++) {
            if (!XGetWindowAttributes(dpy, wins[i], &wa) || wa.override_redirect ||
                XGetTransientForHint(dpy, wins[i], &d1))
                continue;
            if (wa.map_state == IsViewable || getstate(wins[i]) == IconicState)
                manage(wins[i], &wa);
        }
        for (i = 0; i < num; i++) { /* now the transients */
            if (!XGetWindowAttributes(dpy, wins[i], &wa))
                continue;
            if (XGetTransientForHint(dpy, wins[i], &d1) &&
                (wa.map_state == IsViewable || getstate(wins[i]) == IconicState))
                manage(wins[i], &wa);
        }
        if (wins)
            XFree(wins);
    }
}

void sendmon(Client *c, Monitor *m) {
    if (c->mon == m)
        return;
    unfocus(c, 1);
    detach(c);
    detachstack(c);
    c->mon = m;
    c->tags = m->tagset[m->seltags]; /* assign tags of target monitor */
    if (attachbelow)
        attachBelow(c);
    else
        attach(c);
    attachstack(c);
    setclienttagprop(c);
    focus(NULL);
    arrange(NULL);
}

void setclientstate(Client *c, long state) {
    long data[] = {state, None};

    XChangeProperty(dpy, c->win, wmatom[WMState], wmatom[WMState], 32,
                    PropModeReplace, (unsigned char *)data, 2);
}
void setcurrentdesktop(void) {
    long data[] = {0};
    XChangeProperty(dpy, root, netatom[NetCurrentDesktop], XA_CARDINAL, 32,
                    PropModeReplace, (unsigned char *)data, 1);
}
void setdesktopnames(void) {
    XTextProperty text;
    Xutf8TextListToTextProperty(dpy, (char **)tags, TAGSLENGTH, XUTF8StringStyle,
                                &text);

    XSetTextProperty(dpy, root, &text, netatom[NetDesktopNames]);
}

int sendevent(Window w, Atom proto, int mask, long d0, long d1, long d2,
              long d3, long d4) {
    int n;
    Atom *protocols, mt;
    int exists = 0;
    XEvent ev;

    if (proto == wmatom[WMTakeFocus] || proto == wmatom[WMDelete]) {
        mt = wmatom[WMProtocols];
        if (XGetWMProtocols(dpy, w, &protocols, &n)) {
            while (!exists && n--)
                exists = protocols[n] == proto;
            XFree(protocols);
        }
    } else {
        exists = True;
        mt = proto;
    }

    if (exists) {
        ev.type = ClientMessage;
        ev.xclient.window = w;
        ev.xclient.message_type = mt;
        ev.xclient.format = 32;
        ev.xclient.data.l[0] = d0;
        ev.xclient.data.l[1] = d1;
        ev.xclient.data.l[2] = d2;
        ev.xclient.data.l[3] = d3;
        ev.xclient.data.l[4] = d4;
        XSendEvent(dpy, w, False, mask, &ev);
    }
    return exists;
}

void setnumdesktops(void) {
    long data[] = {TAGSLENGTH};
    XChangeProperty(dpy, root, netatom[NetNumberOfDesktops], XA_CARDINAL, 32,
                    PropModeReplace, (unsigned char *)data, 1);
}
void setfocus(Client *c) {
    if (!c->neverfocus) {
        XSetInputFocus(dpy, c->win, RevertToPointerRoot, CurrentTime);
        XChangeProperty(dpy, root, netatom[NetActiveWindow], XA_WINDOW, 32,
                        PropModeReplace, (unsigned char *)&(c->win), 1);
    }

    /* Проверка на поддержку WM_TAKE_FOCUS */
    if (sendevent(c->win, wmatom[WMTakeFocus], NoEventMask, CurrentTime, 0, 0, 0,
                  0) == 0) {
        printf("Window does not support WM_TAKE_FOCUS: %ld\n", c->win);
    }
}

void setfullscreen(Client *c, int fullscreen) {
    if (fullscreen && !c->isfullscreen) {
        XChangeProperty(dpy, c->win, netatom[NetWMState], XA_ATOM, 32,
                        PropModeReplace, (unsigned char *)&netatom[NetWMFullscreen],
                        1);
        c->isfullscreen = 1;
        c->oldstate = c->isfloating;
        c->oldbw = c->bw;
        c->bw = 0;
        c->isfloating = 1;
        resizeclient(c, c->mon->mx, c->mon->my, c->mon->mw, c->mon->mh);
        XRaiseWindow(dpy, c->win);
    } else if (!fullscreen && c->isfullscreen) {
        XChangeProperty(dpy, c->win, netatom[NetWMState], XA_ATOM, 32,
                        PropModeReplace, (unsigned char *)0, 0);
        c->isfullscreen = 0;
        c->isfloating = c->oldstate;
        c->bw = c->oldbw;
        c->x = c->oldx;
        c->y = c->oldy;
        c->w = c->oldw;
        c->h = c->oldh;
        resizeclient(c, c->x, c->y, c->w, c->h);
        arrange(c->mon);
    }
}

void setlayout(const Arg *arg) {
    if (!arg || !arg->v || arg->v != selmon->lt[selmon->sellt])
        selmon->sellt = selmon->pertag->sellts[selmon->pertag->curtag] ^= 1;
    if (arg && arg->v)
        selmon->lt[selmon->sellt] =
            selmon->pertag->ltidxs[selmon->pertag->curtag][selmon->sellt] =
                (Layout *)arg->v;
    strncpy(selmon->ltsymbol, selmon->lt[selmon->sellt]->symbol,
            sizeof selmon->ltsymbol);
    if (selmon->sel)
        arrange(selmon);
    else
        drawbar(selmon);
}

void setcfact(const Arg *arg) {
    float f;
    Client *c;

    c = selmon->sel;

    if (!arg || !c || !selmon->lt[selmon->sellt]->arrange)
        return;
    f = arg->f + c->cfact;
    if (arg->f == 0.0)
        f = 1.0;
    else if (f < 0.25 || f > 4.0)
        return;
    c->cfact = f;
    arrange(selmon);
}

/* arg > 1.0 will set mfact absolutely */
void setmfact(const Arg *arg) {
    float f;

    if (!arg || !selmon->lt[selmon->sellt]->arrange)
        return;
    f = arg->f < 1.0 ? arg->f + selmon->mfact : arg->f - 1.0;
    if (f < 0.05 || f > 0.95)
        return;
    selmon->mfact = selmon->pertag->mfacts[selmon->pertag->curtag] = f;
    arrange(selmon);
}

void showtagpreview(unsigned int i) {
    if (!selmon->previewshow || !selmon->tagmap[i]) {
        XUnmapWindow(dpy, selmon->tagwin);
        return;
    }

    XSetWindowBackgroundPixmap(dpy, selmon->tagwin, selmon->tagmap[i]);
    XCopyArea(dpy, selmon->tagmap[i], selmon->tagwin, drw->gc, 0, 0,
              selmon->mw / scalepreview, selmon->mh / scalepreview, 0, 0);
    XSync(dpy, False);
    XMapRaised(dpy, selmon->tagwin);
}

void takepreview(void) {
    Client *c;
    Imlib_Image image;
    unsigned int occ = 0, i;

    for (c = selmon->clients; c; c = c->next)
        occ |= c->tags;
    // occ |= c->tags == 255 ? 0 : c->tags; /* hide vacants */

    for (i = 0; i < LENGTH(tags); i++) {
        /* searching for tags that are occupied && selected */
        if (!(occ & 1 << i) || !(selmon->tagset[selmon->seltags] & 1 << i))
            continue;

        if (selmon->tagmap[i]) { /* tagmap exist, clean it */
            XFreePixmap(dpy, selmon->tagmap[i]);
            selmon->tagmap[i] = 0;
        }

        /* try to unmap the window so it doesn't show the preview on the preview */
        selmon->previewshow = 0;
        XUnmapWindow(dpy, selmon->tagwin);
        XSync(dpy, False);

        if (!(image = imlib_create_image(sw, sh))) {
            fprintf(stderr, "dwm: imlib: failed to create image, skipping.");
            continue;
        }
        imlib_context_set_image(image);
        imlib_context_set_display(dpy);
        /* uncomment if using alpha patch */
        // imlib_image_set_has_alpha(1);
        // imlib_context_set_blend(0);
        // imlib_context_set_visual(visual);
        imlib_context_set_visual(DefaultVisual(dpy, screen));
        imlib_context_set_drawable(root);

        if (previewbar)
            imlib_copy_drawable_to_image(0, selmon->wx, selmon->wy, selmon->ww,
                                         selmon->wh, 0, 0, 1);
        else
            imlib_copy_drawable_to_image(0, selmon->mx, selmon->my, selmon->mw,
                                         selmon->mh, 0, 0, 1);
        selmon->tagmap[i] =
            XCreatePixmap(dpy, selmon->tagwin, selmon->mw / scalepreview,
                          selmon->mh / scalepreview, DefaultDepth(dpy, screen));
        imlib_context_set_drawable(selmon->tagmap[i]);
        imlib_render_image_part_on_drawable_at_size(0, 0, selmon->mw, selmon->mh, 0,
                                                    0, selmon->mw / scalepreview,
                                                    selmon->mh / scalepreview);
        imlib_free_image();
    }
}

void previewtag(const Arg *arg) {
    if (selmon->previewshow != (arg->ui + 1))
        selmon->previewshow = arg->ui + 1;
    else
        selmon->previewshow = 0;
    showtagpreview(arg->ui);
}

void loadAttachBelow() {
    FILE *file = fopen(".cache/attachbelow_state",
                       "r");  // Файл состояния в текущей директории
    if (file) {
        fscanf(file, "%d", &attachbelow);
        fclose(file);
    }
}

void saveAttachBelow() {
    FILE *file = fopen(".cache/attachbelow_state",
                       "w");  // Файл состояния в текущей директории
    if (file) {
        fprintf(file, "%d", attachbelow);
        fclose(file);
    }
}

void setup(void) {
    load_showtitle_state();
    int i;
    XSetWindowAttributes wa;
    Atom utf8string;
    struct sigaction sa;

    /* do not transform children into zombies when they terminate */
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_NOCLDSTOP | SA_NOCLDWAIT | SA_RESTART;
    sa.sa_handler = SIG_IGN;
    sigaction(SIGCHLD, &sa, NULL);

    /* clean up any zombies (inherited from .xinitrc etc) immediately */
    while (waitpid(-1, NULL, WNOHANG) > 0);

    /* init screen */
    screen = DefaultScreen(dpy);
    sw = DisplayWidth(dpy, screen);
    sh = DisplayHeight(dpy, screen);
    root = RootWindow(dpy, screen);
    drw = drw_create(dpy, screen, root, sw, sh);
    if (!drw_fontset_create(drw, fonts, LENGTH(fonts)))
        die("no fonts could be loaded.");
    lrpad = drw->fonts->h;
    bh = drw->fonts->h + 2 + borderpx * 2; /* Учитываем толщину рамки */
    updategeom();
    sp = sidepad;
    vp = (topbar == 1) ? vertpad : -vertpad;

    /* init atoms */
    utf8string = XInternAtom(dpy, "UTF8_STRING", False);

    wmatom[WMProtocols] = XInternAtom(dpy, "WM_PROTOCOLS", False);
    wmatom[WMDelete] = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
    wmatom[WMState] = XInternAtom(dpy, "WM_STATE", False);
    wmatom[WMTakeFocus] = XInternAtom(dpy, "WM_TAKE_FOCUS", False);
    netatom[NetWMWindowTypeMenu] = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_MENU", False);
    netatom[NetWMWindowTypeToolbar] = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_TOOLBAR", False);
    netatom[NetActiveWindow] = XInternAtom(dpy, "_NET_ACTIVE_WINDOW", False);
    netatom[NetSupported] = XInternAtom(dpy, "_NET_SUPPORTED", False);
    netatom[NetDesktopViewport] =
        XInternAtom(dpy, "_NET_DESKTOP_VIEWPORT", False);
    netatom[NetActiveWindow] = XInternAtom(dpy, "_NET_ACTIVE_WINDOW", False);
    netatom[NetNumberOfDesktops] =
        XInternAtom(dpy, "_NET_NUMBER_OF_DESKTOPS", False);
    netatom[NetWMWindowTypePopupMenu] =
        XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_POPUP_MENU", False);
    netatom[NetCurrentDesktop] = XInternAtom(dpy, "_NET_CURRENT_DESKTOP", False);
    netatom[NetWorkarea] = XInternAtom(dpy, "_NET_WORKAREA", False);
    netatom[NetDesktopNames] = XInternAtom(dpy, "_NET_DESKTOP_NAMES", False);
    netatom[NetWMWindowTypeDock] =
        XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DOCK", False);
    netatom[NetWMDesktop] = XInternAtom(dpy, "_NET_WM_DESKTOP", False);
    netatom[NetSystemTray] = XInternAtom(dpy, "_NET_SYSTEM_TRAY_S0", False);
    netatom[NetSystemTrayOP] = XInternAtom(dpy, "_NET_SYSTEM_TRAY_OPCODE", False);
    netatom[NetSystemTrayOrientation] =
        XInternAtom(dpy, "_NET_SYSTEM_TRAY_ORIENTATION", False);
    netatom[NetSystemTrayOrientationHorz] =
        XInternAtom(dpy, "_NET_SYSTEM_TRAY_ORIENTATION_HORZ", False);
    netatom[NetWMName] = XInternAtom(dpy, "_NET_WM_NAME", False);
    netatom[NetWMState] = XInternAtom(dpy, "_NET_WM_STATE", False);
    netatom[NetWMCheck] = XInternAtom(dpy, "_NET_SUPPORTING_WM_CHECK", False);
    netatom[NetWMFullscreen] =
        XInternAtom(dpy, "_NET_WM_STATE_FULLSCREEN", False);
    netatom[NetWMWindowType] = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE", False);
    netatom[NetWMWindowTypeDialog] =
        XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DIALOG", False);
    netatom[NetClientList] = XInternAtom(dpy, "_NET_CLIENT_LIST", False);
    netatom[NetWMIcon] = XInternAtom(dpy, "_NET_WM_ICON", False);
    netatom[NetClientInfo] = XInternAtom(dpy, "_NET_CLIENT_INFO", False);

    netatom[NetWMWindowTypeUtility] =
        XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_UTILITY", False);

    netatom[NetWMWindowTypeNormal] =
        XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_NORMAL", False);

    xatom[Manager] = XInternAtom(dpy, "MANAGER", False);
    xatom[Xembed] = XInternAtom(dpy, "_XEMBED", False);
    xatom[XembedInfo] = XInternAtom(dpy, "_XEMBED_INFO", False);

    /* init cursors */
    cursor[CurNormal] = drw_cur_create(drw, XC_left_ptr);
    cursor[CurResize] = drw_cur_create(drw, XC_sizing);
    cursor[CurMove] = drw_cur_create(drw, XC_fleur);

    /* init appearance */
    scheme = ecalloc(LENGTH(colors), sizeof(Clr *));
    for (i = 0; i < LENGTH(colors); i++)
        scheme[i] = drw_scm_create(drw, colors[i], 3);

    /* init system tray */
    updatesystray();
    /* init bars */
    updatebars();
    updatestatus();
    updatebarpos(selmon);

    /* supporting window for NetWMCheck */
    wmcheckwin = XCreateSimpleWindow(dpy, root, 0, 0, 1, 1, 0, 0, 0);
    XChangeProperty(dpy, wmcheckwin, netatom[NetWMCheck], XA_WINDOW, 32,
                    PropModeReplace, (unsigned char *)&wmcheckwin, 1);
    XChangeProperty(dpy, wmcheckwin, netatom[NetWMName], utf8string, 8,
                    PropModeReplace, (unsigned char *)"dwm", 3);
    XChangeProperty(dpy, root, netatom[NetWMCheck], XA_WINDOW, 32,
                    PropModeReplace, (unsigned char *)&wmcheckwin, 1);

    /* EWMH support per view */
    XChangeProperty(dpy, root, netatom[NetSupported], XA_ATOM, 32,
                    PropModeReplace, (unsigned char *)netatom, NetLast);
    setnumdesktops();
    setcurrentdesktop();
    setdesktopnames();
    setviewport();
    XDeleteProperty(dpy, root, netatom[NetClientList]);
    XDeleteProperty(dpy, root, netatom[NetClientInfo]);

    /* select events */
    wa.cursor = cursor[CurNormal]->cursor;
    wa.event_mask = SubstructureRedirectMask | SubstructureNotifyMask |
                    ButtonPressMask | PointerMotionMask | EnterWindowMask |
                    LeaveWindowMask | StructureNotifyMask | PropertyChangeMask;
    XChangeWindowAttributes(dpy, root, CWEventMask | CWCursor, &wa);
    XSelectInput(dpy, root, wa.event_mask);

    /* Глобальная обработка скролла мыши */
    XGrabButton(dpy, Button4, MODKEY, root, True, ButtonPressMask, GrabModeAsync,
                GrabModeAsync, None, None);
    XGrabButton(dpy, Button5, MODKEY, root, True, ButtonPressMask, GrabModeAsync,
                GrabModeAsync, None, None);

    XGrabButton(dpy, Button4, MODKEY | ShiftMask, root, True, ButtonPressMask,
                GrabModeAsync, GrabModeAsync, None, None);
    XGrabButton(dpy, Button5, MODKEY | ShiftMask, root, True, ButtonPressMask,
                GrabModeAsync, GrabModeAsync, None, None);

    grabkeys();
    focus(NULL);
    loadSystrayState();
}
void setviewport(void) {
    long data[] = {0, 0};
    XChangeProperty(dpy, root, netatom[NetDesktopViewport], XA_CARDINAL, 32,
                    PropModeReplace, (unsigned char *)data, 2);
}

void seturgent(Client *c, int urg) {
    XWMHints *wmh;

    c->isurgent = urg;
    if (!(wmh = XGetWMHints(dpy, c->win)))
        return;
    wmh->flags = urg ? (wmh->flags | XUrgencyHint) : (wmh->flags & ~XUrgencyHint);
    XSetWMHints(dpy, c->win, wmh);
    XFree(wmh);
}

void showhide(Client *c) {
    if (!c)
        return;
    if (ISVISIBLE(c)) {
        /* show clients top down */
        XMoveWindow(dpy, c->win, c->x, c->y);
        if ((!c->mon->lt[c->mon->sellt]->arrange || c->isfloating) &&
            !c->isfullscreen)
            resize(c, c->x, c->y, c->w, c->h, 0);
        showhide(c->snext);
    } else {
        /* hide clients bottom up */
        showhide(c->snext);
        XMoveWindow(dpy, c->win, WIDTH(c) * -2, c->y);
    }
}

void spawn(const Arg *arg) {
    struct sigaction sa;

    if (fork() == 0) {
        if (dpy)
            close(ConnectionNumber(dpy));
        setsid();

        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sa.sa_handler = SIG_DFL;
        sigaction(SIGCHLD, &sa, NULL);

        execvp(((char **)arg->v)[0], (char **)arg->v);
        die("dwm: execvp '%s' failed:", ((char **)arg->v)[0]);
    }
}

void setclienttagprop(Client *c) {
    long data[] = {(long)c->tags, (long)c->mon->num};
    XChangeProperty(dpy, c->win, netatom[NetClientInfo], XA_CARDINAL, 32,
                    PropModeReplace, (unsigned char *)data, 2);
}

void tag(const Arg *arg) {
    Client *c;
    if (selmon->sel && arg->ui & TAGMASK) {
        c = selmon->sel;
        selmon->sel->tags = arg->ui & TAGMASK;
        setclienttagprop(c);
        focus(NULL);
        arrange(selmon);
        updatecurrentdesktop();
    }
}

void tagmon(const Arg *arg) {
    if (!selmon->sel || !mons->next)
        return;
    sendmon(selmon->sel, dirtomon(arg->i));
}

void togglebar(const Arg *arg) {
    selmon->showbar = selmon->pertag->showbars[selmon->pertag->curtag] =
        !selmon->showbar;
    updatebarpos(selmon);
    resizebarwin(selmon);

    if (showsystray) {
        XWindowChanges wc;
        if (!selmon->showbar)
            wc.y = -bh - vp; /* Учёт вертикального отступа */
        else {
            wc.y = vp; /* Учёт верхнего отступа */
            if (!selmon->topbar)
                wc.y = selmon->mh - bh - vp; /* Учёт нижнего отступа */
        }
        XConfigureWindow(dpy, systray->win, CWY, &wc);
    }

    arrange(selmon);
}
void togglefloating(const Arg *arg) {
    if (!selmon->sel)
        return;
    if (selmon->sel->isfullscreen) /* no support for fullscreen windows */
        return;
    selmon->sel->isfloating = !selmon->sel->isfloating || selmon->sel->isfixed;
    if (selmon->sel->isfloating)
        resize(selmon->sel, selmon->sel->x, selmon->sel->y, selmon->sel->w,
               selmon->sel->h, 0);
    arrange(selmon);
}

void togglefullscr(const Arg *arg) {
    if (selmon->sel)
        setfullscreen(selmon->sel, !selmon->sel->isfullscreen);
}

void toggletag(const Arg *arg) {
    unsigned int newtags;

    if (!selmon->sel)
        return;
    newtags = selmon->sel->tags ^ (arg->ui & TAGMASK);
    if (newtags) {
        selmon->sel->tags = newtags;
        setclienttagprop(selmon->sel);
        focus(NULL);
        arrange(selmon);
    }
    updatecurrentdesktop();
}

void toggleview(const Arg *arg) {
    unsigned int newtagset =
        selmon->tagset[selmon->seltags] ^ (arg->ui & TAGMASK);
    int i;

    if (newtagset) {
        takepreview();
        selmon->tagset[selmon->seltags] = newtagset;

        if (newtagset == ~0) {
            selmon->pertag->prevtag = selmon->pertag->curtag;
            selmon->pertag->curtag = 0;
        }

        /* test if the user did not select the same tag */
        if (!(newtagset & 1 << (selmon->pertag->curtag - 1))) {
            selmon->pertag->prevtag = selmon->pertag->curtag;
            for (i = 0; !(newtagset & 1 << i); i++);
            selmon->pertag->curtag = i + 1;
        }

        /* apply settings for this view */
        selmon->nmaster = selmon->pertag->nmasters[selmon->pertag->curtag];
        selmon->mfact = selmon->pertag->mfacts[selmon->pertag->curtag];
        selmon->sellt = selmon->pertag->sellts[selmon->pertag->curtag];
        selmon->lt[selmon->sellt] =
            selmon->pertag->ltidxs[selmon->pertag->curtag][selmon->sellt];
        selmon->lt[selmon->sellt ^ 1] =
            selmon->pertag->ltidxs[selmon->pertag->curtag][selmon->sellt ^ 1];

        if (selmon->showbar != selmon->pertag->showbars[selmon->pertag->curtag])
            togglebar(NULL);

        focus(NULL);
        arrange(selmon);
    }
    updatecurrentdesktop();
}

void freeicon(Client *c) {
    if (c->icon) {
        XRenderFreePicture(dpy, c->icon);
        c->icon = None;
    }
}

void unfocus(Client *c, int setfocus) {
    if (!c)
        return;
    grabbuttons(c, 0);
    XSetWindowBorder(dpy, c->win, scheme[SchemeNorm][ColBorder].pixel);
    if (setfocus) {
        XSetInputFocus(dpy, root, RevertToPointerRoot, CurrentTime);
        XDeleteProperty(dpy, root, netatom[NetActiveWindow]);
    }
}

void unmanage(Client *c, int destroyed) {
    int i;
    Monitor *m = c->mon;
    XWindowChanges wc;

    // Удаляем клиента из перетагов
    for (i = 0; i < LENGTH(tags) + 1; i++)
        if (c->mon->pertag->sel[i] == c)
            c->mon->pertag->sel[i] = NULL;

    detach(c);
    detachstack(c);
    freeicon(c);

    if (!destroyed) {
        wc.border_width = c->oldbw;
        XGrabServer(dpy); /* avoid race conditions */
        XSetErrorHandler(xerrordummy);
        XSelectInput(dpy, c->win, NoEventMask);
        XConfigureWindow(dpy, c->win, CWBorderWidth, &wc); /* restore border */
        XUngrabButton(dpy, AnyButton, AnyModifier, c->win);
        setclientstate(c, WithdrawnState);
        XSync(dpy, False);
        XSetErrorHandler(xerror);
        XUngrabServer(dpy);
    }

    // Удаляем окно из _NET_CLIENT_LIST
    int count = 0;
    for (Client *t = selmon->clients; t; t = t->next) {
        count++;
    }
    Window *windows =
        calloc(count, sizeof(Window));  // Динамическое выделение памяти
    count = 0;                          // Сброс счётчика
    for (Client *t = selmon->clients; t; t = t->next) {
        if (t != c) {
            windows[count++] = t->win;
        }
    }
    XChangeProperty(dpy, root, netatom[NetClientList], XA_WINDOW, 32,
                    PropModeReplace, (unsigned char *)windows, count);
    free(windows);

    free(c);
    focus(NULL);
    updateclientlist();
    arrange(m);
}

void unmapnotify(XEvent *e) {
    Client *c;
    XUnmapEvent *ev = &e->xunmap;

    if ((c = wintoclient(ev->window))) {
        if (ev->send_event)
            setclientstate(c, WithdrawnState);
        else
            unmanage(c, 0);
    } else if ((c = wintosystrayicon(ev->window))) {
        /* KLUDGE! sometimes icons occasionally unmap their windows, but do
         * _not_ destroy them. We map those windows back */
        XMapRaised(dpy, c->win);
        updatesystray();
    }
}

void updatebars(void) {
    unsigned int w;
    Monitor *m;
    XSetWindowAttributes wa = {.override_redirect = True,
                               .background_pixmap = ParentRelative,
                               .event_mask = ButtonPressMask | ExposureMask |
                                             PointerMotionMask};

    XClassHint ch = {"dwm", "dwm"};
    for (m = mons; m; m = m->next) {
        if (!m->tagwin) {
            m->tagwin =
                XCreateWindow(dpy, root, m->wx, m->by + bh, m->mw / scalepreview,
                              m->mh / scalepreview, 0, DefaultDepth(dpy, screen),
                              CopyFromParent, DefaultVisual(dpy, screen),
                              CWOverrideRedirect | CWBackPixmap | CWEventMask, &wa);
            XDefineCursor(dpy, m->tagwin, cursor[CurNormal]->cursor);
            XUnmapWindow(dpy, m->tagwin);
        }
        if (m->barwin)
            continue;
        w = m->ww;
        if (showsystray && m == systraytomon(m))
            w -= getsystraywidth();
        m->barwin = XCreateWindow(
            dpy, root, m->wx, m->by, w, bh, 0, DefaultDepth(dpy, screen),
            CopyFromParent, DefaultVisual(dpy, screen),
            CWOverrideRedirect | CWBackPixmap | CWEventMask, &wa);
        XDefineCursor(dpy, m->barwin, XCreateFontCursor(dpy, XC_hand2));
        if (showsystray && m == systraytomon(m))
            XMapRaised(dpy, systray->win);
        XMapRaised(dpy, m->barwin);
        XSetClassHint(dpy, m->barwin, &ch);
    }
}

void updatebarpos(Monitor *m) {
    m->wy = m->my;
    m->wh = m->mh;
    if (m->showbar) {
        m->wh -=
            bh +
            2 * vp; /* Уменьшаем высоту на высоту панели и вертикальные отступы */
        m->by = m->topbar ? m->wy : m->wy + m->wh + vp;
        m->wy = m->topbar ? m->wy + bh + vp : m->wy;
    } else {
        m->by = -bh - vp; /* Если панель скрыта */
    }
}

void updateclientlist(void) {
    Client *c;
    Monitor *m;

    // Удаляем старый список
    XDeleteProperty(dpy, root, netatom[NetClientList]);

    // Добавляем все окна
    for (m = mons; m; m = m->next) {
        for (c = m->clients; c; c = c->next) {
            XChangeProperty(dpy, root, netatom[NetClientList], XA_WINDOW, 32,
                            PropModeAppend, (unsigned char *)&(c->win), 1);
        }
    }
}

void setactivewindow(Client *c) {
    if (c) {
        XChangeProperty(dpy, root, netatom[NetActiveWindow], XA_WINDOW, 32,
                        PropModeReplace, (unsigned char *)&(c->win), 1);
    } else {
        XDeleteProperty(dpy, root, netatom[NetActiveWindow]);
    }
}

void updatecurrentdesktop(void) {
    unsigned long rawdata =
        selmon->tagset[selmon->seltags];  // Битовая маска текущих тегов
    int i = 0;

    // Поиск активного тега по битовой маске
    while (rawdata > 1) {
        rawdata >>= 1;  // Сдвигаем битовую маску вправо
        i++;
    }

    long data[] = {i};  // Индекс активного тега
    XChangeProperty(dpy, root, netatom[NetCurrentDesktop], XA_CARDINAL, 32,
                    PropModeReplace, (unsigned char *)data, 1);
}

int updategeom(void) {
    int dirty = 0;

#ifdef XINERAMA
    if (XineramaIsActive(dpy)) {
        int i, j, n, nn;
        Client *c;
        Monitor *m;
        XineramaScreenInfo *info = XineramaQueryScreens(dpy, &nn);
        XineramaScreenInfo *unique = NULL;

        for (n = 0, m = mons; m; m = m->next, n++);
        /* only consider unique geometries as separate screens */
        unique = ecalloc(nn, sizeof(XineramaScreenInfo));
        for (i = 0, j = 0; i < nn; i++)
            if (isuniquegeom(unique, j, &info[i]))
                memcpy(&unique[j++], &info[i], sizeof(XineramaScreenInfo));
        XFree(info);
        nn = j;

        /* new monitors if nn > n */
        for (i = n; i < nn; i++) {
            for (m = mons; m && m->next; m = m->next);
            if (m)
                m->next = createmon();
            else
                mons = createmon();
        }
        for (i = 0, m = mons; i < nn && m; m = m->next, i++) {
            if (i >= n || unique[i].x_org != m->mx || unique[i].y_org != m->my ||
                unique[i].width != m->mw || unique[i].height != m->mh) {
                dirty = 1;
                m->num = i;
                m->mx = m->wx = unique[i].x_org;
                m->my = m->wy = unique[i].y_org;
                m->mw = m->ww = unique[i].width;
                m->mh = m->wh = unique[i].height;

                /* Обработка окон типа dock */
                updatebarpos(m);
                long struts[4] = {0};
                Atom type;
                int format;
                unsigned long nitems, bytes_after;
                unsigned char *data = NULL;
                Window root_return, parent_return, *children = NULL;
                unsigned int nchildren;

                // Получаем список всех окон
                if (XQueryTree(dpy, root, &root_return, &parent_return, &children,
                               &nchildren)) {
                    for (unsigned int k = 0; k < nchildren; k++) {
                        if (XGetWindowProperty(
                                dpy, children[k],
                                XInternAtom(dpy, "_NET_WM_STRUT_PARTIAL", False), 0L, 4L,
                                False, XA_CARDINAL, &type, &format, &nitems, &bytes_after,
                                &data) == Success &&
                            data) {
                            memcpy(struts, data, sizeof(long) * 4);
                            XFree(data);

                            /* Корректируем размеры монитора */
                            if (struts[0] > 0)
                                m->wx += struts[0];  // Левый отступ
                            if (struts[1] > 0)
                                m->ww -= struts[1];  // Правый отступ
                            if (struts[2] > 0)
                                m->wy += struts[2];  // Верхний отступ
                            if (struts[3] > 0)
                                m->wh -= struts[3];  // Нижний отступ
                        }
                    }
                    if (children) {
                        XFree(children);
                    }
                }
            }
        }
        /* removed monitors if n > nn */
        for (i = nn; i < n; i++) {
            for (m = mons; m && m->next; m = m->next);
            while ((c = m->clients)) {
                dirty = 1;
                m->clients = c->next;
                detachstack(c);
                c->mon = mons;
                if (attachbelow)
                    attachBelow(c);
                else
                    attach(c);

                attachstack(c);
            }
            if (m == selmon)
                selmon = mons;
            cleanupmon(m);
        }
        free(unique);
    } else
#endif /* XINERAMA */
    {  /* default monitor setup */
        if (!mons)
            mons = createmon();
        if (mons->mw != sw || mons->mh != sh) {
            dirty = 1;
            mons->mw = mons->ww = sw;
            mons->mh = mons->wh = sh;

            /* Корректируем размеры для окон dock */
            long struts[4] = {0};
            Atom type;
            int format;
            unsigned long nitems, bytes_after;
            unsigned char *data = NULL;
            Window root_return, parent_return, *children = NULL;
            unsigned int nchildren;

            if (XQueryTree(dpy, root, &root_return, &parent_return, &children,
                           &nchildren)) {
                for (unsigned int k = 0; k < nchildren; k++) {
                    if (XGetWindowProperty(
                            dpy, children[k],
                            XInternAtom(dpy, "_NET_WM_STRUT_PARTIAL", False), 0L, 4L,
                            False, XA_CARDINAL, &type, &format, &nitems, &bytes_after,
                            &data) == Success &&
                        data) {
                        memcpy(struts, data, sizeof(long) * 4);
                        XFree(data);

                        if (struts[0] > 0)
                            mons->wx += struts[0];  // Левый отступ
                        if (struts[1] > 0)
                            mons->ww -= struts[1];  // Правый отступ
                        if (struts[2] > 0)
                            mons->wy += struts[2];  // Верхний отступ
                        if (struts[3] > 0)
                            mons->wh -= struts[3];  // Нижний отступ
                    }
                }
                if (children) {
                    XFree(children);
                }
            }
            updatebarpos(mons);
        }
    }
    if (dirty) {
        selmon = mons;
        selmon = wintomon(root);
    }
    // updateworkarea();
    return dirty;
}

void updatenumlockmask(void) {
    unsigned int i, j;
    XModifierKeymap *modmap;

    numlockmask = 0;
    modmap = XGetModifierMapping(dpy);
    for (i = 0; i < 8; i++)
        for (j = 0; j < modmap->max_keypermod; j++)
            if (modmap->modifiermap[i * modmap->max_keypermod + j] ==
                XKeysymToKeycode(dpy, XK_Num_Lock))
                numlockmask = (1 << i);
    XFreeModifiermap(modmap);
}

void updatesizehints(Client *c) {
    long msize;
    XSizeHints size;

    if (!XGetWMNormalHints(dpy, c->win, &size, &msize))
        /* size is uninitialized, ensure that size.flags aren't used */
        size.flags = PSize;
    if (size.flags & PBaseSize) {
        c->basew = size.base_width;
        c->baseh = size.base_height;
    } else if (size.flags & PMinSize) {
        c->basew = size.min_width;
        c->baseh = size.min_height;
    } else
        c->basew = c->baseh = 0;
    if (size.flags & PResizeInc) {
        c->incw = size.width_inc;
        c->inch = size.height_inc;
    } else
        c->incw = c->inch = 0;
    if (size.flags & PMaxSize) {
        c->maxw = size.max_width;
        c->maxh = size.max_height;
    } else
        c->maxw = c->maxh = 0;
    if (size.flags & PMinSize) {
        c->minw = size.min_width;
        c->minh = size.min_height;
    } else if (size.flags & PBaseSize) {
        c->minw = size.base_width;
        c->minh = size.base_height;
    } else
        c->minw = c->minh = 0;
    if (size.flags & PAspect) {
        c->mina = (float)size.min_aspect.y / size.min_aspect.x;
        c->maxa = (float)size.max_aspect.x / size.max_aspect.y;
    } else
        c->maxa = c->mina = 0.0;
    c->isfixed = (c->maxw && c->maxh && c->maxw == c->minw && c->maxh == c->minh);
    c->hintsvalid = 1;
}

void updatestatus(void) {
    if (!gettextprop(root, XA_WM_NAME, stext, sizeof(stext)))
        strcpy(stext, "dwm-" VERSION);
    drawbar(selmon);
    updatesystray();
}

void updatesystrayicongeom(Client *i, int w, int h) {
    if (i) {
        i->h = bh;
        if (w == h)
            i->w = bh;
        else if (h == bh)
            i->w = w;
        else
            i->w = (int)((float)bh * ((float)w / (float)h));
        applysizehints(i, &(i->x), &(i->y), &(i->w), &(i->h), False);
        /* force icons into the systray dimensions if they don't want to */
        if (i->h > bh) {
            if (i->w == i->h)
                i->w = bh;
            else
                i->w = (int)((float)bh * ((float)i->w / (float)i->h));
            i->h = bh;
        }
    }
}

void updatesystrayiconstate(Client *i, XPropertyEvent *ev) {
    long flags;
    int code = 0;

    if (!showsystray || !i || ev->atom != xatom[XembedInfo] ||
        !(flags = getatomprop(i, xatom[XembedInfo])))
        return;

    if (flags & XEMBED_MAPPED && !i->tags) {
        i->tags = 1;
        code = XEMBED_WINDOW_ACTIVATE;
        XMapRaised(dpy, i->win);
        setclientstate(i, NormalState);
    } else if (!(flags & XEMBED_MAPPED) && i->tags) {
        i->tags = 0;
        code = XEMBED_WINDOW_DEACTIVATE;
        XUnmapWindow(dpy, i->win);
        setclientstate(i, WithdrawnState);
    } else
        return;
    sendevent(i->win, xatom[Xembed], StructureNotifyMask, CurrentTime, code, 0,
              systray->win, XEMBED_EMBEDDED_VERSION);
}

void updatesystray(void) {
    XSetWindowAttributes wa;
    XWindowChanges wc;
    Client *i;
    Monitor *m = systraytomon(NULL);
    unsigned int x = m->mx + m->mw;
    unsigned int sw = TEXTW(stext) - lrpad + systrayspacing;
    unsigned int w = 1;

    if (!showsystray)
        return;

    if (systrayonleft) {
        /* Если systray слева, отступ между systray и bar не добавляется */
        x -= sw + lrpad / 2;
    }

    if (!systray) {
        /* init systray */
        if (!(systray = (Systray *)calloc(1, sizeof(Systray))))
            die("fatal: could not malloc() %u bytes\n", sizeof(Systray));
        systray->win = XCreateSimpleWindow(dpy, root, x, m->by, w, bh, 0, 0,
                                           scheme[SchemeSel][ColBg].pixel);
        wa.event_mask = ButtonPressMask | ExposureMask;
        wa.override_redirect = True;
        wa.background_pixel = scheme[SchemeNorm][ColBg].pixel;
        XSelectInput(dpy, systray->win, SubstructureNotifyMask);
        XChangeProperty(dpy, systray->win, netatom[NetSystemTrayOrientation],
                        XA_CARDINAL, 32, PropModeReplace,
                        (unsigned char *)&netatom[NetSystemTrayOrientationHorz], 1);
        XChangeWindowAttributes(
            dpy, systray->win, CWEventMask | CWOverrideRedirect | CWBackPixel, &wa);
        XMapRaised(dpy, systray->win);
        XSetSelectionOwner(dpy, netatom[NetSystemTray], systray->win, CurrentTime);
        if (XGetSelectionOwner(dpy, netatom[NetSystemTray]) == systray->win) {
            sendevent(root, xatom[Manager], StructureNotifyMask, CurrentTime,
                      netatom[NetSystemTray], systray->win, 0, 0);
            XSync(dpy, False);
        } else {
            fprintf(stderr, "dwm: unable to obtain system tray.\n");
            free(systray);
            systray = NULL;
            return;
        }
    }

    /* Обработка иконок systray */
    for (w = 0, i = systray->icons; i; i = i->next) {
        /* make sure the background color stays the same */
        wa.background_pixel = scheme[SchemeNorm][ColBg].pixel;
        XChangeWindowAttributes(dpy, i->win, CWBackPixel, &wa);
        XMapRaised(dpy, i->win);
        w += systrayspacing;
        i->x = w;
        XMoveResizeWindow(dpy, i->win, i->x, 0, i->w, i->h);
        w += i->w;
        if (i->mon != m)
            i->mon = m;
    }

    /* Учитываем отступ между bar и systray */
    if (!systrayonleft) {
        x -= systraybarspacing;  // Добавляем отступ только если systray справа
    }

    w = w ? w + systrayspacing : 1;
    x -= w;

    XMoveResizeWindow(dpy, systray->win, x - sp, m->by + vp, w, bh);
    wc.x = x - sp;
    wc.y = m->by + vp;
    wc.width = w;
    wc.height = bh;
    wc.stack_mode = Above;
    wc.sibling = m->barwin;
    XConfigureWindow(dpy, systray->win,
                     CWX | CWY | CWWidth | CWHeight | CWSibling | CWStackMode,
                     &wc);
    XMapWindow(dpy, systray->win);
    XMapSubwindows(dpy, systray->win);

    /* redraw background */
    XSetForeground(dpy, drw->gc, scheme[SchemeNorm][ColBg].pixel);
    XFillRectangle(dpy, systray->win, drw->gc, 0, 0, w, bh);
    XSync(dpy, False);
}

void updatetitle(Client *c) {
    if (!gettextprop(c->win, netatom[NetWMName], c->name, sizeof c->name))
        gettextprop(c->win, XA_WM_NAME, c->name, sizeof c->name);
    if (c->name[0] == '\0') /* no name */
        strcpy(c->name, broken);
}

void updateicon(Client *c) {
    freeicon(c);
    c->icon = geticonprop(c->win, &c->icw, &c->ich);
}

void updatewindowtype(Client *c) {
    Atom state = getatomprop(c, netatom[NetWMState]);
    Atom wtype = getatomprop(c, netatom[NetWMWindowType]);

    if (state == netatom[NetWMFullscreen])
        setfullscreen(c, 1);
    if (wtype == netatom[NetWMWindowTypeDialog])
        c->isfloating = 1;
}

void updatewmhints(Client *c) {
    XWMHints *wmh;

    if ((wmh = XGetWMHints(dpy, c->win))) {
        if (c == selmon->sel && wmh->flags & XUrgencyHint) {
            wmh->flags &= ~XUrgencyHint;
            XSetWMHints(dpy, c->win, wmh);
        } else
            c->isurgent = (wmh->flags & XUrgencyHint) ? 1 : 0;
        if (wmh->flags & InputHint)
            c->neverfocus = !wmh->input;
        else
            c->neverfocus = 0;
        XFree(wmh);
    }
}

void viewnext(const Arg *arg) {
    unsigned int i;
    for (i = 0; i < LENGTH(tags); i++) {
        if (selmon->tagset[selmon->seltags] & (1 << i)) {
            view(&(Arg){.ui = 1 << ((i + 1) % LENGTH(tags))});
            return;
        }
    }
}

void viewprev(const Arg *arg) {
    unsigned int i;
    for (i = 0; i < LENGTH(tags); i++) {
        if (selmon->tagset[selmon->seltags] & (1 << i)) {
            view(&(Arg){.ui = 1 << ((i + LENGTH(tags) - 1) % LENGTH(tags))});
            return;
        }
    }
}

void recompile_and_restart(const Arg *arg) {
    int status = system(RECOMPILE_COMMAND);
    if (status != 0) {
        fprintf(stderr, "ERORR RECOMPILE: %s\n", RECOMPILE_COMMAND);
        return;
    }
    system("make clean install");
}

void viewnextwithmove(const Arg *arg) {
    unsigned int i;
    Client *c = selmon->sel;
    unsigned int prevtags =
        selmon->tagset[selmon->seltags];  // Сохраняем текущие теги

    if (!c)  // Если нет активного окна, просто переключаем тег
        goto switch_tag;

    for (i = 0; i < LENGTH(tags); i++) {
        if (selmon->tagset[selmon->seltags] & (1 << i)) {
            // Перемещаем активное окно в следующий тег
            c->tags = 1 << ((i + 1) % LENGTH(tags));
            setclienttagprop(c);  // Обновляем свойства окна (если используется EWMH)
            break;
        }
    }

switch_tag:
    for (i = 0; i < LENGTH(tags); i++) {
        if (selmon->tagset[selmon->seltags] & (1 << i)) {
            // Переключаем на следующий тег
            view(&(Arg){.ui = 1 << ((i + 1) % LENGTH(tags))});

            // Устанавливаем фокус на перемещённое окно
            selmon->sel = c;
            focus(c);
            arrange(selmon);

            // Обновляем текущий рабочий стол
            updatecurrentdesktop();

            // Сохраняем предыдущие теги для возможного возврата
            selmon->pertag->prevtag = prevtags;
            return;
        }
    }
}

void viewprevwithmove(const Arg *arg) {
    unsigned int i;
    Client *c = selmon->sel;
    unsigned int prevtags =
        selmon->tagset[selmon->seltags];  // Сохраняем текущие теги

    if (!c)  // Если нет активного окна, просто переключаем тег
        goto switch_tag;

    for (i = 0; i < LENGTH(tags); i++) {
        if (selmon->tagset[selmon->seltags] & (1 << i)) {
            // Перемещаем активное окно в предыдущий тег
            c->tags = 1 << ((i + LENGTH(tags) - 1) % LENGTH(tags));
            setclienttagprop(c);  // Обновляем свойства окна (если используется EWMH)
            break;
        }
    }

switch_tag:
    for (i = 0; i < LENGTH(tags); i++) {
        if (selmon->tagset[selmon->seltags] & (1 << i)) {
            // Переключаем на предыдущий тег
            view(&(Arg){.ui = 1 << ((i + LENGTH(tags) - 1) % LENGTH(tags))});

            // Устанавливаем фокус на перемещённое окно
            selmon->sel = c;
            focus(c);
            arrange(selmon);

            // Обновляем текущий рабочий стол
            updatecurrentdesktop();

            // Сохраняем предыдущие теги для возможного возврата
            selmon->pertag->prevtag = prevtags;
            return;
        }
    }
}

void view(const Arg *arg) {
    int i;
    unsigned int tmptag;

    // Если тег уже активен, не делаем ничего
    if ((arg->ui & TAGMASK) == selmon->tagset[selmon->seltags]) {
        updatecurrentdesktop();
        save_current_tag_to_file();
        return;
    }

    // Скрываем превью перед переключением тегов
    takepreview();

    // Если мы переключаемся на тег 0
    if (arg->ui == ~0) {
        if (selmon->pertag->curtag == 0) {
            // Если мы уже находимся на теге 0, восстанавливаем прежнее состояние
            if (prevtags != 0) {
                selmon->tagset[selmon->seltags] = prevtags;
                setlayout(&((Arg){.v = prevlayout}));
                focus(prevclient);
                arrange(selmon);
            }
            updatecurrentdesktop();      // Обновляем _NET_CURRENT_DESKTOP
            save_current_tag_to_file();  // Сохраняем текущий тег
            return;
        } else {
            prevtags = selmon->tagset[selmon->seltags];
            prevclient = selmon->sel;
            prevlayout = selmon->lt[selmon->sellt];
            selmon->pertag->curtag = 0;
            setlayout(&((Arg){.v = TAG0_LAYOUT}));
        }
    }

    selmon->seltags ^= 1; /* toggle sel tagset */
    if (arg->ui & TAGMASK) {
        selmon->tagset[selmon->seltags] = arg->ui & TAGMASK;
        selmon->pertag->prevtag = selmon->pertag->curtag;

        if (arg->ui != ~0) {
            for (i = 0; !(arg->ui & 1 << i); i++);
            selmon->pertag->curtag = i + 1;
        }
    } else {
        tmptag = selmon->pertag->prevtag;
        selmon->pertag->prevtag = selmon->pertag->curtag;
        selmon->pertag->curtag = tmptag;
    }

    selmon->nmaster = selmon->pertag->nmasters[selmon->pertag->curtag];
    selmon->mfact = selmon->pertag->mfacts[selmon->pertag->curtag];
    selmon->sellt = selmon->pertag->sellts[selmon->pertag->curtag];
    selmon->lt[selmon->sellt] =
        selmon->pertag->ltidxs[selmon->pertag->curtag][selmon->sellt];
    selmon->lt[selmon->sellt ^ 1] =
        selmon->pertag->ltidxs[selmon->pertag->curtag][selmon->sellt ^ 1];

    if (selmon->showbar != selmon->pertag->showbars[selmon->pertag->curtag])
        togglebar(NULL);

    // Поднимаем DOCK окна при переключении тегов
    for (Client *dock = selmon->clients; dock; dock = dock->next) {
        if (ISDOCK(dock)) {
            XRaiseWindow(dpy, dock->win);
        }
    }

    focus(selmon->pertag->sel[selmon->pertag->curtag]);
    arrange(selmon);
    updatecurrentdesktop();      // Обновляем _NET_CURRENT_DESKTOP
    save_current_tag_to_file();  // Сохраняем текущий тег
}

Client *wintoclient(Window w) {
    Client *c;
    Monitor *m;

    for (m = mons; m; m = m->next)
        for (c = m->clients; c; c = c->next)
            if (c->win == w)
                return c;
    return NULL;
}

Client *wintosystrayicon(Window w) {
    Client *i = NULL;

    if (!showsystray || !w)
        return i;
    for (i = systray->icons; i && i->win != w; i = i->next);
    return i;
}

Monitor *wintomon(Window w) {
    int x, y;
    Client *c;
    Monitor *m;

    if (w == root && getrootptr(&x, &y))
        return recttomon(x, y, 1, 1);
    for (m = mons; m; m = m->next)
        if (w == m->barwin)
            return m;
    if ((c = wintoclient(w)))
        return c->mon;
    return selmon;
}

/* Selects for the view of the focused window. The list of tags */
/* to be displayed is matched to the focused window tag list. */
void winview(const Arg *arg) {
    Window win, win_r, win_p, *win_c;
    unsigned nc;
    int unused;
    Client *c;
    Arg a;

    if (!XGetInputFocus(dpy, &win, &unused))
        return;
    while (XQueryTree(dpy, win, &win_r, &win_p, &win_c, &nc) && win_p != win_r)
        win = win_p;

    if (!(c = wintoclient(win)))
        return;

    a.ui = c->tags;
    view(&a);
}

/* There's no way to check accesses to destroyed windows, thus those cases are
 * ignored (especially on UnmapNotify's). Other types of errors call Xlibs
 * default error handler, which may call exit. */
int xerror(Display *dpy, XErrorEvent *ee) {
    if (ee->error_code == BadWindow ||
        (ee->request_code == X_SetInputFocus && ee->error_code == BadMatch) ||
        (ee->request_code == X_PolyText8 && ee->error_code == BadDrawable) ||
        (ee->request_code == X_PolyFillRectangle &&
         ee->error_code == BadDrawable) ||
        (ee->request_code == X_PolySegment && ee->error_code == BadDrawable) ||
        (ee->request_code == X_ConfigureWindow && ee->error_code == BadMatch) ||
        (ee->request_code == X_GrabButton && ee->error_code == BadAccess) ||
        (ee->request_code == X_GrabKey && ee->error_code == BadAccess) ||
        (ee->request_code == X_CopyArea && ee->error_code == BadDrawable))
        return 0;
    fprintf(stderr, "dwm: fatal error: request code=%d, error code=%d\n",
            ee->request_code, ee->error_code);
    return xerrorxlib(dpy, ee); /* may call exit */
}

int xerrordummy(Display *dpy, XErrorEvent *ee) { return 0; }

/* Startup Error handler to check if another window manager
 * is already running. */
int xerrorstart(Display *dpy, XErrorEvent *ee) {
    die("dwm: another window manager is already running");
    return -1;
}

Monitor *systraytomon(Monitor *m) {
    Monitor *t;
    int i, n;
    if (!systraypinning) {
        if (!m)
            return selmon;
        return m == selmon ? m : NULL;
    }
    for (n = 1, t = mons; t && t->next; n++, t = t->next);
    for (i = 1, t = mons; t && t->next && i < systraypinning; i++, t = t->next);
    if (systraypinningfailfirst && n < systraypinning)
        return mons;
    return t;
}

void zoom(const Arg *arg) {
    Client *c = selmon->sel;

    if (!selmon->lt[selmon->sellt]->arrange || !c || c->isfloating)
        return;
    if (c == nexttiled(selmon->clients) && !(c = nexttiled(c->next)))
        return;
    pop(c);
}

void apply_padding_settings(void) {
    if (padding_enabled == 1) {
        sp = sidepad;                             // Устанавливаем отступы для боковой панели
        vp = (topbar == 1) ? vertpad : -vertpad;  // Устанавливаем отступы для вертикальной панели
    } else {
        sp = 0;  // Если отступы отключены, устанавливаем их в 0
        vp = 0;
    }

    arrange(selmon);    // Применяем изменения (перерисовываем окно)
    drawbar(selmon);    // Перерисовываем бар
    XSync(dpy, False);  // Обновляем экран
}

void load_padding_settings(void) {
    FILE *file = fopen(STATE_FILE_PADDING, "r");
    if (file) {
        fscanf(file, "%d", &padding_enabled);  // Загружаем состояние
        fclose(file);
    } else {
        padding_enabled = 0;  // Значение по умолчанию
    }
}

void save_padding_settings(void) {
    FILE *file = fopen(STATE_FILE_PADDING, "w");
    if (file) {
        fprintf(file, "%d", padding_enabled);  // Сохраняем состояние
        fclose(file);
    }
}

void toggle_padding(const Arg *arg) {
    padding_enabled = !padding_enabled;  // Переключаем между 1 и 0
    save_padding_settings();             // Сохраняем новое состояние

    // Перерисовываем с учётом новых отступов
    apply_padding_settings();

    // Принудительная перезагрузка баров
    arrange(selmon);
    drawbar(selmon);
    XSync(dpy, False);
}
int main(int argc, char *argv[]) {
    load_padding_settings();
    loadAttachBelow();
    load_bottGaps_state();
    MINIBOXloadState();
    smartgaps = loadSmartgapsState();
    if (argc == 2 && !strcmp("-v", argv[1]))
        die("dwm-" VERSION);
    else if (argc != 1)
        die("usage: dwm [-v]");
    if (!setlocale(LC_CTYPE, "") || !XSupportsLocale())
        fputs("warning: no locale support\n", stderr);
    if (!(dpy = XOpenDisplay(NULL)))
        die("dwm: cannot open display");
    checkotherwm();
    setup();
#ifdef __OpenBSD__
    if (pledge("stdio rpath proc exec", NULL) == -1)
        die("pledge");
#endif /* __OpenBSD__ */
    scan();
    switch_to_saved_tag();  // Восстанавливаем сохранённый тег
    run();
    cleanup();
    XCloseDisplay(dpy);
    return EXIT_SUCCESS;
    switch_to_saved_tag();
}
void togglesmartgaps(const Arg *arg) {
    smartgaps = !smartgaps;         // Переключение значения smartgaps
    saveSmartgapsState(smartgaps);  // Сохранение текущего состояния
    arrange(NULL);                  // Обновление расположения окон
}
