/*========================================================//
 ██████╗ ██████╗ ███╗   ██╗███████╗██╗ ██████╗    ██╗  ██╗
██╔════╝██╔═══██╗████╗  ██║██╔════╝██║██╔════╝    ██║  ██║
██║     ██║   ██║██╔██╗ ██║█████╗  ██║██║  ███╗   ███████║
██║     ██║   ██║██║╚██╗██║██╔══╝  ██║██║   ██║   ██╔══██║
╚██████╗╚██████╔╝██║ ╚████║██║     ██║╚██████╔╝██╗██║  ██║
 ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝     ╚═╝ ╚═════╝ ╚═╝╚═╝  ╚═╝
//==========================================================*/
//
//logo
static const char *logo = "  󰣇  "; 
static const char *logo_script = "$HOME/.config/rofi/launchers/launcher.sh";
static int logo_state = 1;  
//power 
static const char *power = "  ⏻     "; 
static const char *power_script = "$HOME/.config/rofi/powermenu/powermenu.sh"; 
static int power_state = 1; 

//========================================//
//tag preview
static const int scalepreview                 = 4;        /* preview scaling (display w and h / scalepreview) */
static const int previewbar                   = 0;        /* show the bar in the preview window */
//========================================//
// appearance  
static const unsigned int borderpx            = 4 ;       // border pixel of windows 
static const unsigned int snap                = 0 ;       // snap pixel 
//========================================//
static int floatposgrid_x                     = 5;        /* float grid columns */
static int floatposgrid_y                     = 5;        /* float grid rows */
//========================================//
//systray
static const unsigned int systraypinning     =  0 ;       // 0: sloppy systray follows selected monitor, >0: pin systray to monitor X 
static const unsigned int systrayonleft      =  0 ;       // 0: systray in the right corner, >0: systray on left of status text 
static const unsigned int systrayspacing     =  12;       // systray spacing 
static const int systraypinningfailfirst     =  1 ;       // 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor
static                int showsystray        =  1 ;
static const unsigned int systraybarspacing  = -8 ;       // Отступ между bar и systray
//========================================//
//show boxes
int                 show_tag_boxes       = 2 ;       // Установите значение для переключателя: 1, 2, или 3
//========================================//
//toggle_smartgaps_monocle
int         always_smartgaps_monocle     = 1 ;       // 0 - стандартная логика, 1 - всегда включены smartgaps
//========================================//
//gap
static const unsigned int gappiv         = 13 ;       // vert inner gap between windows 
static const unsigned int gappih         = 13 ;       // horiz inner gap between windows 
static const unsigned int gappoh         = 13 ;       // horiz outer gap between windows and screen edge 
static const unsigned int gappov         = 13 ;       // vert outer gap between windows and screen edge 
static                int smartgaps      = 1  ;       // 1 means no outer gap when there is only one window 
static const unsigned int single_gappov  = 150;       // Вертикальный внешний отступ при одном окне
static const unsigned int single_gappoh  = 40 ;       // Горизонтальный внешний отступ при одном окне
//=======================================//
static                int bottgaps       = 30 ;       // нижние отступы для dock 
#define               DOCK_NAME          "plank"      // class твоего дока
//========================================//
//awesome title
static                int showtitle      = 0  ;       // 1 — показывать заголовки, 0 — скрывать
//=======================================//
//icon title
#define                   ICONSIZE             18      // icon size
#define                   ICONSPACING          10      // space between icon and title
//=======================================//
//ascii_art title no window
const char *ascii_art = "(づ｡◕‿‿◕｡)づ";
//========================================//
//bar
static const          int showbar        = 1  ;       // 0 means no bar 
static const          int topbar         = 1  ;       // 0 means bottom bar 
//========================================//
//bar paddings
static const          int vertpad        = 10 ;       // vertical padding of bar 
static const          int sidepad        = 15 ;       // horizontal padding of bar 
//========================================//
// font
static const char *fonts[] = { 
    "FiraCode Nerd Font:size=11", 
    "Noto Sans:size=10",
    "Noto Sans CJK JP:size=10",
    "apple-color-emoji:size=10",
    "monospace:size=10", 
};
//========================================//
// Определение цветовых значений
static const char col_noActiveFG[]       = "#cdd6f4";   // Яркий светло-серый текст для неактивных элементов
static const char col_activeFG[]         = "#cdd6f4";   // Чисто белый текст для активных элементов
static const char background[]           = "#1e1e2e";   // Основной фон
static const char col_borderActive[]     = "#89b4fa";   // Цвет рамки активного элемента
static const char col_noActive[]         = "#45475a";   // Цвет фона для неактивных элементов
static const char selectedBG[]           = "#2f2f49";   // Второй цвет фона (например, для выделения)
static const char logoFG[]               = "#1e1e2e";   // Белый текст логотипа
static const char logoBG[]               = "#8aadf4";   // Фон логотипа
static const char logoBR[]               = "#8aadf4";   // Цвет рамки логотипа
static const char powerFG[]              = "#f38ba8";   // Белый текст для кнопки выключения
static const char powerBG[]              = "#1e1e2e";   // Розовый фон кнопки выключения
static const char powerBR[]              = "#f38ba8";   // Цвет рамки кнопки выключения
static const char titleBG[]              = "#c6a0f6";   // Цвет рамки кнопки выключения

// Цветовые схемы для тегов
static const char tag1ActiveFG[]         = "#ffffff"; // Белый текст (максимальный контраст)
static const char tag1InactiveFG[]       = "#d9e0ee"; // Светло-серый текст
static const char tag1ActiveBG[]         = "#f38ba8"; // Розовый акцент (Rosewater)
static const char tag1InactiveBG[]       = "#1e1e2e"; // Темный фон (Base)

static const char tag2ActiveFG[]         = "#ffffff"; // Белый текст
static const char tag2InactiveFG[]       = "#d9e0ee"; // Светло-серый текст
static const char tag2ActiveBG[]         = "#fab387"; // Оранжевый акцент (Peach)
static const char tag2InactiveBG[]       = "#1e1e2e"; // Темный фон (Base)

static const char tag3ActiveFG[]         = "#ffffff"; // Белый текст
static const char tag3InactiveFG[]       = "#d9e0ee"; // Светло-серый текст
static const char tag3ActiveBG[]         = "#f9e2af"; // Желтый акцент (Yellow)
static const char tag3InactiveBG[]       = "#1e1e2e"; // Темный фон (Base)

static const char tag4ActiveFG[]         = "#ffffff"; // Белый текст
static const char tag4InactiveFG[]       = "#d9e0ee"; // Светло-серый текст
static const char tag4ActiveBG[]         = "#a6e3a1"; // Зеленый акцент (Green)
static const char tag4InactiveBG[]       = "#1e1e2e"; // Темный фон (Base)

static const char tag5ActiveFG[]         = "#ffffff"; // Белый текст
static const char tag5InactiveFG[]       = "#d9e0ee"; // Светло-серый текст
static const char tag5ActiveBG[]         = "#89b4fa"; // Голубой акцент (Blue)
static const char tag5InactiveBG[]       = "#1e1e2e"; // Темный фон (Base)

static const char tag6ActiveFG[]         = "#ffffff"; // Белый текст
static const char tag6InactiveFG[]       = "#d9e0ee"; // Светло-серый текст
static const char tag6ActiveBG[]         = "#b4befe"; // Сиреневый акцент (Lavender)
static const char tag6InactiveBG[]       = "#1e1e2e"; // Темный фон (Base)

static const char tag7ActiveFG[]         = "#ffffff"; // Белый текст
static const char tag7InactiveFG[]       = "#d9e0ee"; // Светло-серый текст
static const char tag7ActiveBG[]         = "#cba6f7"; // Фиолетовый акцент (Mauve)
static const char tag7InactiveBG[]       = "#1e1e2e"; // Темный фон (Base)

static const char tag8ActiveFG[]         = "#ffffff"; // Белый текст
static const char tag8InactiveFG[]       = "#d9e0ee"; // Светло-серый текст
static const char tag8ActiveBG[]         = "#f5c2e7"; // Розовый акцент (Pink)
static const char tag8InactiveBG[]       = "#1e1e2e"; // Темный фон (Base)

static const char tag9ActiveFG[]         = "#ffffff"; // Белый текст
static const char tag9InactiveFG[]       = "#d9e0ee"; // Светло-серый текст
static const char tag9ActiveBG[]         = "#94e2d5"; // Аква акцент (Teal)
static const char tag9InactiveBG[]       = "#1e1e2e"; // Темный фон (Base)

// Основной массив цветов
static const char *colors[][3] = {
 //                            fg             bg            border
    [SchemeLogo]         = {   logoFG   ,    logoBG      ,    logoBR              }, // logo
    [SchemePower]        = {   powerFG  ,    powerBG     ,    powerBR             }, // power
    [SchemeNorm]         = { "#cdd6f4"  ,    "#1e1e2e"   ,    "#45475a"           }, // Нормальный режим
    [SchemeSel]          = { "#1e1e2e"  ,    "#89b4fa"   ,    "#89b4fa"           }, // Выбранный элемент
    [SchemeFg]           = { background ,    selectedBG  ,    col_borderActive    }, // title active teg color
    [SchemeTitle]        = { selectedBG,     titleBG     ,    col_borderActive    }, // title color
  // tags
    [SchemeTag1Active]   = { tag1ActiveFG, tag1ActiveBG,   "#45475a"       },
    [SchemeTag1Inactive] = { tag1InactiveFG, tag1InactiveBG, "#1e1e2e"     },
    [SchemeTag2Active]   = { tag2ActiveFG, tag2ActiveBG,   "#45475a"       },
    [SchemeTag2Inactive] = { tag2InactiveFG, tag2InactiveBG, "#1e1e2e"     },
    [SchemeTag3Active]   = { tag3ActiveFG, tag3ActiveBG,   "#45475a"       },
    [SchemeTag3Inactive] = { tag3InactiveFG, tag3InactiveBG, "#1e1e2e"     },
    [SchemeTag4Active]   = { tag4ActiveFG, tag4ActiveBG,   "#45475a"       },
    [SchemeTag4Inactive] = { tag4InactiveFG, tag4InactiveBG, "#1e1e2e"     },
    [SchemeTag5Active]   = { tag5ActiveFG, tag5ActiveBG,   "#45475a"       },
    [SchemeTag5Inactive] = { tag5InactiveFG, tag5InactiveBG, "#1e1e2e"     },
    [SchemeTag6Active]   = { tag6ActiveFG, tag6ActiveBG,   "#45475a"       },
    [SchemeTag6Inactive] = { tag6InactiveFG, tag6InactiveBG, "#1e1e2e"     },
    [SchemeTag7Active]   = { tag7ActiveFG, tag7ActiveBG,   "#45475a"       },
    [SchemeTag7Inactive] = { tag7InactiveFG, tag7InactiveBG, "#1e1e2e"     },
    [SchemeTag8Active]   = { tag8ActiveFG, tag8ActiveBG,   "#45475a"       },
    [SchemeTag8Inactive] = { tag8InactiveFG, tag8InactiveBG, "#1e1e2e"     },
    [SchemeTag9Active]   = { tag9ActiveFG, tag9ActiveBG,   "#45475a"       },
    [SchemeTag9Inactive] = { tag9InactiveFG, tag9InactiveBG, "#1e1e2e"     },
};

// Основной массив цветов
// tagging 
static const char forTags[]          = { " 󰊠 " };   
static const char *tagicons_active[] = { " 󰮯 " };
static const char *tags[]            = { forTags, forTags, forTags, forTags, forTags, forTags, forTags, forTags, forTags };

/* static const char *tags[] = { "󱍢", "", "󰈹", "", "󰣇", "", "", "", "" }; */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */

// Сохраняем состояние перед переходом в тег 0
static unsigned int prevtags         = 0   ;     // Хранение предыдущего тега
static Client *prevclient            = NULL;     // Хранение предыдущего окна
static const Layout *prevlayout      = NULL;     // Переменная для хранения предыдущего layout
static const Rule rules[] = {
    /* class            instance   title              tags mask | isfloating | floatpos | monitor */
    { "firefox"         , NULL   , NULL               , 1 << 2,       0,        NULL     , -1 },
    { "TelegramDesktop" , NULL   , NULL               , 0,            1,        "80% 50% 570W 944H"         , -1 },
    { "Blueman-manager" , NULL   , NULL               , 0,            1,        "25% 20% 800W 400H"         , -1 },
    { "WebApp-monkey5058" , NULL   , NULL             , 0,            1,        "30% 50% 570W 844H"         , -1 },
    { "kitty"           , NULL   , "neofetch_terminal", 1 << 0,       0,        NULL     , -1 },
    { "kitty"           , NULL   , "nmtui"            , 0,            1,        "75% 35% 750W 800H"         , -1 },
    { "vesktop"         , NULL   , NULL               , 0,            1,        "30% 50% 1012W 576H"        , -1 },
    { "Mechvibes"       , NULL   , NULL               , 0,            1,        NULL     , -1 },
    { "steam"           , NULL   , NULL               , 0,            1,        NULL     , -1 },
};
//============================================//
// убрать обводку 
static const char *noborder_apps[] = {
 //   "Plank",       // Пример приложения
    "polybar",
     NULL // Завершающий NULL для указания конца массива
};
//============================================//
// прикрепить ко всем тегам 
static const char *alltags_apps[] = {
   // "Plank",       // Пример: Plank
    "polybar",
    /* "TelegramDesktop", */
     NULL // Завершающий NULL
};
//============================================//
//  Игнорировать определенное окно
static const char *focusIgnore[] = {
    //"Plank",       // Пример: Plank
    "polybar",
    //NULL // Завершающий NULL
};
//============================================//
static const char *nosavetags_classes[] = {
    "TelegramDesktop", // Пример класса, который не будет сохраняться
    "vesktop",
    "steam",
    NULL
};
//============================================//
/* layout(s) */
static const float mfact             = 0.55 ;    // factor of master area size [0.05..0.95] 
static const int nmaster             = 1    ;    // number of clients in master area 
static const int resizehints         = 1    ;    // 1 means respect size hints in tiled resizals 
static const int lockfullscreen      = 1    ;    // 1 will force focus on the fullscreen window 
#define FORCE_VSPLIT                   1         // nrowgrid layout: force two clients to always split vertically
#include "vanitygaps.c"
static const Layout layouts[] = {
	// symbol     arrange function 
	{ "[@]",      spiral                 }, // first entry is default ,
	{ "[]=",      tile                   },    
	{ "[M]",      monocle                },
	{ "[\\]",     dwindle                },
	{ "H[]",      deck                   },
	{ "TTT",      bstack                 },
	{ "===",      bstackhoriz            },
	{ "HHH",      grid                   },
	{ "###",      nrowgrid               },
	{ "---",      horizgrid              },
	{ ":::",      gaplessgrid            },
	{ "|M|",      centeredmaster         },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL                   },  
	{ NULL,       NULL                   },
};
// Layout для тега 0 (все теги активны)
#define TAG0_LAYOUT &layouts             [10] // ">M>" (centeredfloatingmaster)
#define ISDOCK(c) ((c)->tags == 0 && (c)->isfloating)
//============================================//
// key definitions
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define SHIFT  ShiftMask 
#define CTRL   ControlMask 
#define TAGKEYS(KEY,TAG)                                                                          \
       &((Keychord){1, {{MODKEY, KEY}},                            view,     {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|CTRL, KEY}},                 toggleview,     {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|SHIFT, KEY}},                       tag,     {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|CTRL|SHIFT, KEY}},            previewtag,     {.ui = TAG     } }),
////======================================================================//
////======================================================================//
////======================================================================//
#define SHCMD(cmd) {.v = (const char*[]){"/bin/sh", "-c", cmd, NULL}}
static const char *termcmd[]        = { "kitty"  , NULL };
static const char *browser[]        = { "firefox", NULL };
static const char *codeEditor[]     = { "code"   , NULL };
#include "movestack.c"
void togglesmartgaps(const Arg *arg);
static Keychord *keychords[]        = {
/*
* //  _            _                      _   _    _         _ _           
* // | |_____ _  _| |__  ___  __ _ _ _ __| | | |__(_)_ _  __| (_)_ _  __ _ 
* // | / / -_) || | '_ \/ _ \/ _` | '_/ _` | | '_ \ | ' \/ _` | | ' \/ _` |
* // |_\_\___|\_, |_.__/\___/\__,_|_| \__,_| |_.__/_|_||_\__,_|_|_||_\__, |
* //          |__/                                                   |___/ 
*/
//======================================================================//
    //settings [ super + i ] 
    &((Keychord){2, {{MODKEY, XK_i}, {0, XK_d}}, spawn,  SHCMD("kitty -e $HOME/.suckless/dwm")  }),
    &((Keychord){2, {{MODKEY, XK_i}, {0, XK_a}}, spawn,  SHCMD("kitty -e $HOME/.suckless/autostart")  }),
    &((Keychord){2, {{MODKEY, XK_i}, {0, XK_s}}, spawn,  SHCMD("kitty -e $HOME/.suckless/scripts")  }),
    &((Keychord){3, {{MODKEY, XK_i}, {0, XK_i},{0,XK_c}}, spawn,  SHCMD("kitty --hold sh -c 'cd $HOME/.suckless/dwm; nvim config.h; exec $SHELL'")  }),
    &((Keychord){3, {{MODKEY, XK_i}, {0, XK_i},{0,XK_d}}, spawn,  SHCMD("kitty --hold sh -c 'cd $HOME/.suckless/dwm; nvim dwm.c; exec $SHELL'")  }),
    &((Keychord){4, {{MODKEY, XK_i}, {0, XK_i},{0,XK_r},{0,XK_c}}, spawn,  SHCMD("kitty --hold sh -c 'cd $HOME/.suckless/dwm; nvim config.def.h.rej; exec $SHELL'")  }),
    &((Keychord){4, {{MODKEY, XK_i}, {0, XK_i},{0,XK_r},{0,XK_d}}, spawn,  SHCMD("kitty --hold sh -c 'cd $HOME/.suckless/dwm; nvim dwm.c.rej; exec $SHELL'")  }),
//======================================================================//
    // system [ super + s ]
    &((Keychord){2, {{MODKEY, XK_s}, {0,XK_u}} ,          spawn,  SHCMD("kitty -e  $HOME/.suckless/scripts/update.sh")  }), //update system
    &((Keychord){2, {{MODKEY, XK_s}, {0|SHIFT,XK_p}}, spawn,  SHCMD("kitty -e  $HOME/.suckless/scripts/pushdots.sh")  }), //pushDots
    &((Keychord){2, {{MODKEY, XK_s}, {0,XK_r}} ,  recompile_and_restart,     { 0 }  }), //recompile dwm
    &((Keychord){3, {{MODKEY, XK_s}, {0, XK_s} ,  {0, XK_t}},     toggleSystray,  { 0 }  }), // toggle systray
    &((Keychord){2, {{MODKEY, XK_s}, {0, XK_t}}, spawn,           SHCMD("$HOME/.suckless/scripts/toggle_touchpad.sh")  }), // toggle systray
    &((Keychord){2, {{MODKEY, XK_s}, {0, XK_d}}, toggle_bottGaps, {0}  }), // toggle bottGaps
    &((Keychord){2, {{MODKEY, XK_s}, {0, XK_b}}, spawn,           SHCMD("pgrep blueman-manager && pkill blueman-manager || blueman-manager &")  }), // blueman-manager
    &((Keychord){2, {{MODKEY, XK_s}, {0, XK_n}}, spawn,           SHCMD("pgrep -fx 'kitty --title nmtui nmtui-connect' && pkill -fx 'kitty --title nmtui nmtui-connect' || kitty --title nmtui nmtui-connect &") }), // network-manager
    &((Keychord){2, {{MODKEY, XK_s}, {0, XK_p}}, spawn,           SHCMD("$HOME/.config/rofi/powermenu/powermenu.sh") }), //powermenu
    &((Keychord){2, {{MODKEY, XK_s}, {0, XK_l}}, spawn,           SHCMD("$HOME/.config/rofi/powermenu/.screen-lock.sh") }), //lockfullscreen
    &((Keychord){2, {{MODKEY, XK_s}, {0, XK_q}}, spawn,           SHCMD("$HOME/.suckless/scripts/quran") }), //random ayat quran
//======================================================================//
    // aplication [ super + a ] 
    &((Keychord){2, {{MODKEY, XK_a}, {0,XK_f}}, spawn,  {.v = browser } }),   //firefox
    &((Keychord){2, {{MODKEY, XK_a}, {0,XK_d}}, spawn,  SHCMD("vesktop")  }), //vesktop
    &((Keychord){2, {{MODKEY, XK_a}, {0,XK_t}}, spawn,  SHCMD("telegram-desktop")  }), //telegram-desktop
    &((Keychord){2, {{MODKEY, XK_a}, {0,XK_v}}, spawn,  {.v = codeEditor } }),//vscode
    &((Keychord){2, {{MODKEY, XK_a}, {0,XK_c}}, spawn,   SHCMD("kitty --hold sh -c 'nvim'") }), //nvim
    /* &((Keychord){2, {{MODKEY, XK_a}, {0,XK_c}}, spawn,   SHCMD("$HOME/.local/bin/neovide") }), //nvim */
    &((Keychord){2, {{MODKEY, XK_a}, {0,XK_b}}, spawn,  SHCMD("kitty -e btop")  }), //btop
//======================================================================//
    //screen [super + p ]
    &((Keychord){2, {{MODKEY, XK_p}, {0,XK_c}},  spawn,  SHCMD("$HOME/.suckless/scripts/xcolor-picker.sh")  }),//	colorpicer
    &((Keychord){2, {{MODKEY, XK_p}, {0, XK_s}}, spawn,  SHCMD("flameshot gui")  }), //screen shot
    &((Keychord){2, {{MODKEY, XK_p}, {0|SHIFT, XK_c}}, spawn, SHCMD("$HOME/.suckless/scripts/clock.sh") }), //clock
    &((Keychord){4, {{MODKEY, XK_p}, {0, XK_p},{0, XK_b},{0,XK_t}}, spawn, SHCMD("$HOME/.config/picom/toggle_config.sh default; $HOME/.config/kitty/.other/toggle_config.sh default && $HOME/.config/dunst/.picom/toggle_config.sh default") }), // picom blur
    &((Keychord){4, {{MODKEY, XK_p}, {0, XK_p},{0, XK_g},{0,XK_t}}, spawn, SHCMD("$HOME/.config/picom/toggle_config.sh glass; $HOME/.config/kitty/.other/toggle_config.sh default && $HOME/.config/dunst/.picom/toggle_config.sh default") }), // picom glass
    &((Keychord){4, {{MODKEY, XK_p}, {0, XK_p},{0, XK_o},{0,XK_t}}, spawn, SHCMD("$HOME/.config/picom/toggle_config.sh nOpacity; $HOME/.config/kitty/.other/toggle_config.sh nOpacity && $HOME/.config/dunst/.picom/toggle_config.sh nOpacity") }), // picom no opacity
    &((Keychord){3, {{MODKEY, XK_p}, {0, XK_p},{0, XK_c}}, spawn, SHCMD("kitty -e $HOME/.config/picom/") }), // picom 
//======================================================================//
    //filemanager [super + e ]
    &((Keychord){2, {{MODKEY, XK_e}, {0, XK_y}}, spawn,  SHCMD("kitty --hold sh -c 'yazi'")  }), // yazi
    &((Keychord){2, {{MODKEY, XK_e}, {0, XK_n}}, spawn,  SHCMD("nemo")  }), // nemo
//======================================================================//
    // web apps
    &((Keychord){2, {{MODKEY|SHIFT, XK_f},{0,XK_m}}, spawn,  SHCMD("firefox --class WebApp-monkey3985 --name WebApp-monkey3985 --profile $HOME/.local/share/ice/firefox/monkey3985 --no-remote 'https://monkeytype.com'")  }), //monkeytype
    &((Keychord){2, {{MODKEY|SHIFT, XK_f},{0,XK_g}}, spawn,  SHCMD("firefox --class WebApp-chatG2444 --name WebApp-chatG2444 --profile /home/maaru/.local/share/ice/firefox/chatG2444 --no-remote 'https://chatgpt.com/'")  }), //chat gpt
//======================================================================//
    //kitty 
    &((Keychord){1, {{MODKEY, XK_Return}},   spawn,          { .v = termcmd } }),
//======================================================================//
    //killActive 
    &((Keychord){1, {{MODKEY, XK_q}},       killclient,     {0} }),
//======================================================================//
    //changeKeyboard
    &((Keychord){1, {{CTRL, XK_Alt_L}}, spawn,  SHCMD("pkill -RTMIN+1 dwmblocks; $HOME/.suckless/scripts/changeKeyboard.sh; setxkbmap -layout us,ru -option 'grp:ctrl_alt_toggle' -option 'ctrl:nocaps'")  }),
    &((Keychord){1, {{CTRL, XK_grave}}, spawn,  SHCMD("$HOME/.suckless/scripts/caps.sh")  }),
    &((Keychord){1, {{CTRL|SHIFT, XK_grave}}, spawn,  SHCMD("$HOME/.suckless/scripts/realoadKB.sh")  }),
  
//======================================================================//
	//rofi
    &((Keychord){1, {{MODKEY, XK_r}}, spawn,  SHCMD("$HOME/.config/rofi/launchers/launcher.sh")  }),
    &((Keychord){1, {{MODKEY, XK_v}},           spawn,  SHCMD("$HOME/.config/rofi/clipboard/clipboard.sh") }),
    &((Keychord){1, {{MODKEY|ALTKEY, XK_a}},    spawn,  SHCMD("$HOME/.config/rofi/emoji/emoji.sh")  }),
    &((Keychord){1, {{MODKEY|SHIFT,  XK_s}},    spawn,  SHCMD("$HOME/.config/rofi/serf/serf.sh")  }),
//=================================================================k====//
    //wallpapers control
    &((Keychord){1, {{MODKEY|CTRL, 0x5b}}, spawn, SHCMD("$HOME/.suckless/scripts/change_wallpaper.sh left" ) }),
    &((Keychord){1, {{MODKEY|CTRL, 0x5d}}, spawn, SHCMD("$HOME/.suckless/scripts/change_wallpaper.sh right") }),
//======================================================================//
	// Управление Ярсотью 
    &((Keychord){1, {{MODKEY|SHIFT, 0x5b}}, spawn, SHCMD("$HOME/.suckless/scripts/brightnessControl.sh up") }),
    &((Keychord){1, {{MODKEY|SHIFT, 0x5d}}, spawn, SHCMD("$HOME/.suckless/scripts/brightnessControl.sh down") }),
//======================================================================//
    // Управление Громкостью 
    &((Keychord){1, {{MODKEY, 0x5b}}, spawn, SHCMD("$HOME/.suckless/scripts/volume.sh up"  ) }),
    &((Keychord){1, {{MODKEY, 0x5d}}, spawn, SHCMD("$HOME/.suckless/scripts/volume.sh down") }),
    &((Keychord){1, {{MODKEY, 0x5c}}, spawn, SHCMD("$HOME/.suckless/scripts/volume.sh mute") }),
//======================================================================//
    // move flouting window
	&((Keychord){1, {{MODKEY, XK_j}}, moveresize, { .v = "0x 45y 0w 0h"  } }),
    &((Keychord){1, {{MODKEY, XK_k}}, moveresize, { .v = "0x -45y 0w 0h" } }),
    &((Keychord){1, {{MODKEY, XK_l}}, moveresize, { .v = "45x 0y 0w 0h"  } }),
    &((Keychord){1, {{MODKEY, XK_h}}, moveresize, { .v = "-45x 0y 0w 0h" } }),
//======================================================================//
    //resize flouting widnow
    &((Keychord){1, {{MODKEY|SHIFT|ALTKEY, XK_j}}, moveresize, { .v = "0x 0y 0w 45h"  } }),
    &((Keychord){1, {{MODKEY|SHIFT|ALTKEY, XK_k}}, moveresize, { .v = "0x 0y 0w -45h" } }),
    &((Keychord){1, {{MODKEY|SHIFT|ALTKEY, XK_l}}, moveresize, { .v = "0x 0y 45w 0h"  } }),
    &((Keychord){1, {{MODKEY|SHIFT|ALTKEY, XK_h}}, moveresize, { .v = "0x 0y -45w 0h" } }),
//======================================================================//
    // move flouting window ALTKEY
    &((Keychord){1, {{MODKEY|CTRL, XK_k}}, moveresizeedge, { .v = "t" } }),
    &((Keychord){1, {{MODKEY|CTRL, XK_j}}, moveresizeedge, { .v = "b" } }),
    &((Keychord){1, {{MODKEY|CTRL, XK_h}}, moveresizeedge, { .v = "l" } }),
    &((Keychord){1, {{MODKEY|CTRL, XK_l}}, moveresizeedge, { .v = "r" } }),
//======================================================================//
    //move flouting wondow
    &((Keychord){1, {{MODKEY|CTRL|SHIFT, XK_k}}, moveresizeedge, { .v = "T" } }),
    &((Keychord){1, {{MODKEY|CTRL|SHIFT, XK_j}}, moveresizeedge, { .v = "B" } }),
    &((Keychord){1, {{MODKEY|CTRL|SHIFT, XK_h}}, moveresizeedge, { .v = "L" } }),
    &((Keychord){1, {{MODKEY|CTRL|SHIFT, XK_l}}, moveresizeedge, { .v = "R" } }),
//======================================================================//
	//toggleBar 
    &((Keychord){2, {{MODKEY, XK_w},{0,XK_b}}, togglebar, { 0 } }),
//======================================================================//
	//focusStack 
    &((Keychord){1, {{MODKEY|SHIFT, XK_j}}, focusstack, { .i = +1 } }),
    &((Keychord){1, {{MODKEY|SHIFT, XK_k}}, focusstack, { .i = -1 } }),
    &((Keychord){1, {{MODKEY|SHIFT, XK_h}}, focusstack, { .i = -0.05 } }),
    &((Keychord){1, {{MODKEY|SHIFT, XK_l}}, focusstack, { .i = +0.05 } }),
//======================================================================//
    //resizeStack
    &((Keychord){1, {{MODKEY|CTRL, XK_l}}, setmfact, { .f = +0.05 } }),
    &((Keychord){1, {{MODKEY|CTRL, XK_h}}, setmfact, { .f = -0.05 } }),
//======================================================================//
	// tileStack modes I, D 
    &((Keychord){1, {{MODKEY, XK_u}}, incnmaster, { .i = +1 } }),
    &((Keychord){1, {{MODKEY, XK_d}}, incnmaster, { .i = -1 } }),
//======================================================================//
	//MoveStack 
    &((Keychord){1, {{MODKEY|CTRL, XK_j}}     , movestack, { .i = +1 } }),
    &((Keychord){1, {{MODKEY|CTRL, XK_k}}     , movestack, { .i = -1 } }),
    &((Keychord){1, {{MODKEY|CTRL, XK_Return}}, zoom, { 0 } }),
//======================================================================//
	//MoveWorkSpace
    &((Keychord){1, {{MODKEY|SHIFT, XK_h}}, viewprev,  { 0 } }),
    &((Keychord){1, {{MODKEY|SHIFT, XK_l}}, viewnext,  { 0 } }),
//======================================================================//
  //MoveWorkSpaceWithMove
    &((Keychord){1, {{MODKEY|SHIFT|CTRL, XK_h}}, viewprevwithmove, { 0 } }),
    &((Keychord){1, {{MODKEY|SHIFT|CTRL, XK_l}}, viewnextwithmove, { 0 } }),
//======================================================================//
	//fullscreen
    &((Keychord){1, {{MODKEY, XK_f}}, togglefullscr, { 0 } }),
//======================================================================//
	//Gaps resize 
    &((Keychord){1, {{0, 0}}, setcfact, { .f = +0.25 } }),
    &((Keychord){1, {{0, 0}}, setcfact, { .f = -0.25 } }),
    &((Keychord){1, {{0, 0}}, setcfact, { .f =  0.00 } }),
//======================================================================//
    // view window  
    &((Keychord){1, {{MODKEY, XK_Tab}}, view, { 0 } }),
//======================================================================//
    // view all window
    &((Keychord){1, {{MODKEY, XK_0}}, view, { .ui = ~0 } }),
//======================================================================//
    &((Keychord){1, {{MODKEY, XK_o}}, winview, { 0 } }),
//======================================================================//
    // pin window
    &((Keychord){1, {{MODKEY|SHIFT   , XK_0}}, tag, { .ui = ~0 } }),
    &((Keychord){1, {{MODKEY, XK_comma}} , focusmon, { .i = -1 } }),
    &((Keychord){1, {{MODKEY, XK_period}}, focusmon, { .i = +1 } }),
    &((Keychord){1, {{MODKEY|SHIFT, XK_comma}} , tagmon, { .i = -1 } }),
    &((Keychord){1, {{MODKEY|SHIFT, XK_period}}, tagmon, { .i = +1 } }),
    //===================================================================================//
	//layouts 
	// 0 { "[@]",      spiral  /* first entry is default */    
	// 1 { "[]=",      tile     
	// 2 { "[M]",      monocle     
	// 3 { "[\\]",     dwindle 
	// 4 { "H[]",      deck 
	// 5 { "TTT",      bstack 
	// 6 { "===",      bstackhoriz 
	// 7 { "HHH",      grid 
	// 8 { "###",      nrowgrid 
	// 9 { "---",      horizgrid 
	// 10 { ":::",     gaplessgrid 
	// 11 { "|M|",     centeredmaster 
	// 12 { ">M>",     centeredfloatingmaster 
	// 13 { "><>",     NULL                 
    //===================================================================================//
    // window [ super + w ]
    //===================================================================================//
    &((Keychord){2, {{MODKEY,XK_w}, {0,XK_1}}, setlayout, { .v = &layouts[0] } }), //spiral
    &((Keychord){2, {{MODKEY,XK_w}, {0,XK_2}}, setlayout, { .v = &layouts[3] } }), //dwindle
    &((Keychord){2, {{MODKEY,XK_w}, {0,XK_3}}, setlayout, { .v = &layouts[1] } }), //tile
    &((Keychord){2, {{MODKEY,XK_w}, {0,XK_4}}, setlayout, { .v = &layouts[5] } }), //bstack
    &((Keychord){2, {{MODKEY,XK_w}, {0,XK_5}}, setlayout, { .v = &layouts[11] } }), //centeredmaster
    &((Keychord){2, {{MODKEY,XK_w}, {0,XK_6}}, setlayout, { .v = &layouts[8] } }), //nrowgrid
    &((Keychord){2, {{MODKEY,XK_w}, {0,XK_7}}, setlayout, { .v = &layouts[13] } }), //grid
    &((Keychord){2, {{MODKEY,XK_w}, {0,XK_8}}, setlayout, { .v = &layouts[10] } }), //gaplessgrid
    &((Keychord){2, {{MODKEY,XK_w}, {0,XK_9}}, setlayout, { .v = &layouts[2] } }), //monocle
    &((Keychord){2, {{MODKEY,XK_w}, {0,XK_0}}, setlayout, { .v = &layouts[4] } }), //desk
    //===================================================================================//
    &((Keychord){2, {{MODKEY, XK_w},{0,XK_Tab}}, toggleAttachBelow       ,  { 0 } }), //toggleAttachBelow
    &((Keychord){2, {{MODKEY, XK_w},{0,XK_w}},   togglefloating          ,  { 0 } }), //toggle floating
    &((Keychord){2, {{MODKEY, XK_w},{0,XK_l}},   setlayout               ,  { 0 } }),// setlayout
    &((Keychord){2, {{MODKEY, XK_w},{0|SHIFT, XK_g}}, togglesmartgaps,  { 0 } }),// togglesmartgaps
    &((Keychord){2, {{MODKEY, XK_w},{0,XK_t}},   toggleTagBoxes          ,  { 0 } }),// toggle_tag_boxes
    &((Keychord){3, {{MODKEY, XK_w},{0,XK_m},{0|SHIFT, XK_g}}, toggle_always_smartgaps_monocle, { 0 } }),// toggle_smartgaps_monocle
    &((Keychord){1, {{MODKEY|SHIFT, XK_w}}, spawn, SHCMD("$HOME/.config/rofi/wifi/wifi.sh") }),// killclient
    //awesome key
    &((Keychord){3, {{MODKEY, XK_w},{0,XK_a},{0, XK_t}}, toggleshowtitle,   { 0 } }),// toggleshowtitle 
    &((Keychord){3, {{MODKEY, XK_w},{0,XK_a},{0, XK_h}}, hidewin,   { 0 } }),        // hidewin 
    &((Keychord){3, {{MODKEY, XK_w},{0,XK_a},{0, XK_s}}, restorewin,   { 0 } }),     // restorewin 
    &((Keychord){3, {{MODKEY, XK_w},{0,XK_a},{0|SHIFT, XK_s}}, showall,   { 0 } }),     // restorewin 

    //===================================================================================//
    // click mouse
    &((Keychord){2, {{MODKEY, XK_w},{0,XK_f}}, spawn,  SHCMD("warpd --hint --click 1")  }),
    &((Keychord){2, {{MODKEY, XK_w},{0|SHIFT, XK_f}}, spawn,  SHCMD("warpd --hint --click 3")  }),
    // click mouse
    &((Keychord){2, {{MODKEY, XK_w},{0,XK_g}}, spawn,  SHCMD("warpd --grid")            }),
    //===================================================================================//
	// tags 
	TAGKEYS(            XK_1,                      0        )
	TAGKEYS(            XK_2,                      1        )
	TAGKEYS(            XK_3,                      2        )
	TAGKEYS(            XK_4,                      3        )
	TAGKEYS(            XK_5,                      4        )
	TAGKEYS(            XK_6,                      5        )
	TAGKEYS(            XK_7,                      6        )
	TAGKEYS(            XK_8,                      7        )
	TAGKEYS(            XK_9,                      8        )
//======================================================================//
    //reload && exit
    &((Keychord){1, {{MODKEY|ALTKEY, XK_q}}, quit, { 0 } }  ),
    &((Keychord){1, {{MODKEY|CTRL, XK_q}}, spawn, SHCMD("pkill -f dwm") }  ),
//======================================================================//
    //Gaps 
    &((Keychord){0, {{0, 0}}, incrgaps,   { .i = +1 } }     ),
    &((Keychord){0, {{0, 0}}, incrgaps,   { .i = -1 } }     ),
    &((Keychord){0, {{0, 0}}, incrigaps,  { .i = +1 } }     ),
    &((Keychord){0, {{0, 0}}, incrigaps,  { .i = -1 } }     ),
    &((Keychord){0, {{0, 0}}, incrogaps,  { .i = +1 } }     ),
    &((Keychord){0, {{0, 0}}, incrogaps,  { .i = -1 } }     ),
    &((Keychord){0, {{0, 0}}, incrihgaps, { .i = +1 } }     ),
    &((Keychord){0, {{0, 0}}, incrihgaps, { .i = -1 } }     ),
    &((Keychord){0, {{0, 0}}, incrivgaps, { .i = +1 } }     ),
    &((Keychord){0, {{0, 0}}, incrivgaps, { .i = -1 } }     ),
    &((Keychord){0, {{0, 0}}, incrohgaps, { .i = +1 } }     ),
    &((Keychord){0, {{0, 0}}, incrohgaps, { .i = -1 } }     ),
    &((Keychord){0, {{0, 0}}, incrovgaps, { .i = +1 } }     ),
    &((Keychord){0, {{0, 0}}, incrovgaps, { .i = -1 } }     ),
    &((Keychord){0, {{0, 0}}, togglegaps, { 0       } }     ),
    &((Keychord){0, {{0, 0}}, defaultgaps,{ 0       } }     ),
    //===================================================================================//
    /* Client position is limited to monitor window area */
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "-26x -26y" } }), // ↖
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "  0x -26y" } }), // ↑
    &((Keychord){1, {{0, 0}}, floatpos, {.v = " 26x -26y" } }), // ↗
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "-26x   0y" } }), // ←
    &((Keychord){1, {{0, 0}}, floatpos, {.v = " 26x   0y" } }), // →
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "-26x  26y" } }), // ↙
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "  0x  26y" } }), // ↓
    &((Keychord){1, {{0, 0}}, floatpos, {.v = " 26x  26y" } }), // ↘
    
    /* Absolute positioning (allows moving windows between monitors) */
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "-26a -26a" } }), // ↖
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "  0a -26a" } }), // ↑
    &((Keychord){1, {{0, 0}}, floatpos, {.v = " 26a -26a" } }), // ↗
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "-26a   0a" } }), // ←
    &((Keychord){1, {{0, 0}}, floatpos, {.v = " 26a   0a" } }), // →
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "-26a  26a" } }), // ↙
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "  0a  26a" } }), // ↓
    &((Keychord){1, {{0, 0}}, floatpos, {.v = " 26a  26a" } }), // ↘
    
    /* Resize client, client center position is fixed which means that client expands in all directions */
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "-26w -26h" } }), // ↖
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "  0w -26h" } }), // ↑
    &((Keychord){1, {{0, 0}}, floatpos, {.v = " 26w -26h" } }), // ↗
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "-26w   0h" } }), // ←
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "800W 800H" } }), // ·
    &((Keychord){1, {{0, 0}}, floatpos, {.v = " 26w   0h" } }), // →
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "-26w  26h" } }), // ↙
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "  0w  26h" } }), // ↓
    &((Keychord){1, {{0, 0}}, floatpos, {.v = " 26w  26h" } }), // ↘
    
    /* Client is positioned in a floating grid, movement is relative to client's current position */
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "-1p -1p" } }), // ↖
    &((Keychord){1, {{0, 0}}, floatpos, {.v = " 0p -1p" } }), // ↑
    &((Keychord){1, {{0, 0}}, floatpos, {.v = " 1p -1p" } }), // ↗
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "-1p  0p" } }), // ←
    &((Keychord){1, {{0, 0}}, floatpos, {.v = " 0p  0p" } }), // ·
    &((Keychord){1, {{0, 0}}, floatpos, {.v = " 1p  0p" } }), // →
    &((Keychord){1, {{0, 0}}, floatpos, {.v = "-1p  1p" } }), // ↙
    &((Keychord){1, {{0, 0}}, floatpos, {.v = " 0p  1p" } }), // ↓
    &((Keychord){1, {{0, 0}}, floatpos, {.v = " 1p  1p" } }), // ↘
    };
// button definitions 
// click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin 
//======================================================================//
static const Button buttons[]        =      {
	// click                event mask         button          function        argument 
	{ ClkLtSymbol,          0     ,            Button1,        setlayout           ,   {0} },
	{ ClkClientWin,         MODKEY,            Button1,        movemouse           ,   {0} },
	{ ClkClientWin,         MODKEY,            Button2,        togglefloating      ,   {0} },
	{ ClkClientWin,         MODKEY,            Button3,        resizemouse         ,   {0} },
	{ ClkTagBar,            0     ,            Button1,        view                ,   {0} },
	{ ClkTagBar,            0     ,            Button3,        toggleview          ,   {0} },
	{ ClkTagBar,            MODKEY,            Button1,        tag                 ,   {0} },
	{ ClkTagBar,            MODKEY,            Button3,        toggletag           ,   {0} },
	{ ClkLtSymbol,          0     ,            Button3,        setlayout           ,   {.v = &layouts[2]} },
	{ ClkStatusText,        0     ,            Button2,        spawn               ,   {.v = termcmd } },
  { ClkRootWin,            MODKEY|SHIFT,     Button4,        viewnext            ,   {0} }, // Scroll Up
  { ClkRootWin,            MODKEY|SHIFT,     Button5,        viewprev            ,   {0} }, // Scroll Down
  { ClkRootWin,            MODKEY,           Button4,        viewactivescrollnext,   {0} }, // Scroll Up (active only)
  { ClkRootWin,            MODKEY,           Button5,        viewactivescrollprev,   {0} }, // Scroll Down (active only)
};
//======================================================================//
// dwm karnel dir
#define RECOMPILE_COMMAND "cd \"$HOME/.suckless/dwm\" && " \
                          "make clean install && " \
                          "pgrep -x dwm | xargs -r kill || " \
                          "notify-send 'Ошибка при перекомпиляции dwm'"

