/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "firefox"
/* appearance */
static unsigned int borderpx = 2; /* border pixel of windows */
static unsigned int snap = 0;     /* snap pixel */
static int showbar = 1;           /* 0 means no bar */
static int topbar = 1;            /* 0 means bottom bar */
static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 1;      /* 0 means no systray */
static const unsigned int gappih = 20; /* horiz inner gap between windows */
static const unsigned int gappiv = 20; /* vert inner gap between windows */
static const unsigned int gappoh =
    20; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov =
    20; /* vert outer gap between windows and screen edge */
static const int smartgaps =
    0; /* 1 means no outer gap when there is only one window */
static const Bool viewontag = True; /* Switch view on tag switch */
static const char *fonts[] = {"monospace:size=8",
                              "NotoColorEmoji:pixelsize=10:"};
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static char normbgcolor[] = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[] = "#bbbbbb";
static char selfgcolor[] = "#eeeeee";
static char selbordercolor[] = "#005577";
static char selbgcolor[] = "#005577";
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};
static const unsigned int alphas[][3] = {
    /*               fg      bg        border     */
    [SchemeNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeSel] = {OPAQUE, baralpha, borderalpha},
};

/* tagging */
static const char *tags[] = {"one", "two",   "three", "four", "five",
                             "six", "seven", "eight", "nine"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* layout(s) */
static float mfact = 0.55;  /* factor of master area size [0.05..0.95] */
static int nmaster = 1;     /* number of clients in master area */
static int resizehints = 0; /* 1 means respect size hints in tiled resizals */
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[T]", tile}, /* first entry is default */
    {"[F]", NULL}, /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", NULL};
/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    {"color0", STRING, &normbordercolor},
    {"color14", STRING, &selbordercolor},
    {"color0", STRING, &normbgcolor},
    {"color4", STRING, &normfgcolor},
    {"color0", STRING, &selfgcolor},
    {"color4", STRING, &selbgcolor},
    {"borderpx", INTEGER, &borderpx},
    {"snap", INTEGER, &snap},
    {"showbar", INTEGER, &showbar},
    {"topbar", INTEGER, &topbar},
    {"nmaster", INTEGER, &nmaster},
    {"resizehints", INTEGER, &resizehints},
    {"mfact", FLOAT, &mfact},
};

#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

static const char *termcmd[] = {TERMINAL, NULL};

static const char *wallpapercmd[] = {"/home/charles/.local/bin/dwm-colors",
                                     NULL};

static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = {"st", "-t",    scratchpadname,
                                      "-g", "90x24", NULL};

static const char *suspendcmd[] = {"/home/charles/.local/bin/sysact", NULL};

static const char *screenshotcmd[] = {"flameshot", "gui", NULL};

static Key keys[] = {
    /* modifier            key                      function        argument */
    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_w, spawn, {.v = (const char *[]){BROWSER, NULL}}},
    {MODKEY | ShiftMask, XK_w, spawn, {.v = wallpapercmd}},
    {MODKEY | ShiftMask, XK_p, spawn, {.v = suspendcmd}},
    {MODKEY | ShiftMask, XK_s, spawn, {.v = screenshotcmd}},
    {MODKEY, XK_e, spawn, {.v = (const char *[]){"dmenu-emoji", NULL}}},
    {MODKEY, XK_q, spawn, {.v = (const char *[]){"pkill", "dwm", NULL}}},
    {MODKEY | ShiftMask, XK_k, rotatestack, {.i = +1}},
    {MODKEY | ShiftMask, XK_j, rotatestack, {.i = -1}},
    {MODKEY, XK_k, focusstack, {.i = +1}},
    {MODKEY, XK_j, focusstack, {.i = -1}},
    {MODKEY, XK_n, viewtoleft, {0}},
    {MODKEY, XK_i, viewtoright, {0}},
    {MODKEY,
     XK_apostrophe,
     spawn,
     {.v = (const char *[]){TERMINAL, "-e", "pulsemixer", NULL}}},
    {MODKEY | ControlMask,
     XK_m,
     spawn,
     {.v = (const char *[]){TERMINAL, "-e", "termusic", NULL}}},
    {MODKEY, XK_y, spawn, {.v = (const char *[]){"ytfzf", "-D", NULL}}},
    {MODKEY | ControlMask,
     XK_z,
     spawn,
     {.v = (const char *[]){"Dmenu-Streaming", NULL}}},
    {MODKEY | ControlMask,
     XK_y,
     spawn,
     {.v = (const char *[]){"st", "-e", "ytccf", "--no-thumbnails", NULL}}},
    {MODKEY | ControlMask,
     XK_b,
     spawn,
     {.v = (const char *[]){"bookmarks", NULL}}},
    {MODKEY | ShiftMask,
     XK_y,
     spawn,
     {.v = (const char *[]){"youtube-dmenu", NULL}}},
    {MODKEY | ControlMask,
     XK_t,
     spawn,
     {.v = (const char *[]){"telegram-choice", NULL}}},
    {MODKEY | ShiftMask,
     XK_d,
     spawn,
     {.v = (const char *[]){"keepassxc", NULL}}},
    {MODKEY, XK_p, spawn, SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png")},
    {MODKEY | ControlMask, XK_h, tagtoleft, {0}},
    {MODKEY | ControlMask, XK_l, tagtoright, {0}},
    {MODKEY, XK_s, togglesticky, {0}},
    {MODKEY | ShiftMask, XK_h, incnmaster, {.i = +1}},
    {MODKEY | ShiftMask, XK_f, fullscreen, {0}},
    {MODKEY | ShiftMask, XK_l, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_m, hidewin, {0}},
    {MODKEY | ShiftMask, XK_m, restorewin, {0}},
    {MODKEY, XK_o, hideotherwins, {0}},
    {MODKEY | ShiftMask, XK_o, restoreotherwins, {0}},
    {MODKEY, XK_space, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_q, killclient, {0}},
    {MODKEY,
     XK_r,
     spawn,
     {.v = (const char *[]){TERMINAL, "-e", "ranger", NULL}}},
    {MODKEY | ShiftMask,
     XK_r,
     spawn,
     {.v = (const char *[]){TERMINAL, "-e", "htop", NULL}}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_Escape, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY | ShiftMask, XK_Return, togglescratch, {.v = scratchpadcmd}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ControlMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button1, togglewin, {0}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
