/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:pixelsize=14", "JoyPixels:pixelsize=14", "Symbols Nerd Font:pixelsize=14" };
static const char dmenufont[]       = "JetBrains Mono:pixelsize=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   isterminal noswallow monitor    scratch key */
	{ "st",       NULL,       NULL,       0,            0,           1,          0,         -1,      0},
	{ "Gimp",     NULL,       NULL,       1 << 6,       0,           1,          0,         -1,      0},
	{ "Inkscape", NULL,       NULL,       1 << 6,       0,           1,          0,         -1,      0},
	{ "Brave-browser",NULL,   NULL,       1 << 1,       0,           0,          -1,        -1,      0},
	{ "ncmpcppterm",NULL,     NULL,       1 << 8,       0,           0,          -1,        -1,      0},
	{ "newsboatterm",NULL,    NULL,       1 << 7,       0,           0,          -1,        -1,      0},
	{ NULL,       NULL,       "Event Tester",0,         0,           0,          1,         -1,      0}, /* xev */
	{ "scratchpad",NULL,      NULL,       0,            1,           1,          0,         -1,      's' },
	{ "pulsemixercmd",NULL,   NULL,       0,            1,           1,          0,         -1,      'p' },
	{ "gotopcmd", NULL,       NULL,       0,            1,           1,          0,         -1,      'g' },
	{ "bccmd",    NULL,       NULL,       0,            1,           1,          0,         -1,      'c' },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "st", "-c", "scratchpad", "-t", "scratchpad", NULL}; 
static const char *pulsemixercmd[] = {"p", "st", "-c", "pulsemixercmd", "-e", "pulsemixer", NULL}; 
static const char *gotopcmd[] = {"g", "st", "-c", "gotopcmd", "-e", "gotop", NULL}; 
static const char *bccmd[] = {"c", "st", "-c", "bccmd", "-e", "bc", "-lq", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
    { MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },
	{ MODKEY,                       XK_a,      togglescratch,  {.v = pulsemixercmd } },
	{ MODKEY,                       XK_s,      togglescratch,  {.v = gotopcmd } },
	{ MODKEY,                       XK_c,      togglescratch,  {.v = bccmd } },
	{ Mod1Mask|ControlMask,         XK_m,      spawn,          SHCMD("st -c ncmpcppterm -e ncmpcpp") },
	{ Mod1Mask|ControlMask,	        XK_r,      spawn,          SHCMD("st -c newsboatterm -e newsboat") },
	{ Mod1Mask|ControlMask,	        XK_u,      spawn,          SHCMD("dmenuunicode") },
	{ Mod1Mask|ControlMask,	        XK_x,      spawn,          SHCMD("sstocb") },
	{ Mod1Mask|ControlMask,	        XK_s,      spawn,          SHCMD("sstop") },
	{ Mod1Mask|ShiftMask,	        XK_x,      spawn,          SHCMD("colorp") },
	{ Mod1Mask|ShiftMask,           XK_c,      spawn,          SHCMD("toggleprogram picom") },
	{ Mod1Mask|ControlMask,	        XK_c,      spawn,          SHCMD("clipmenu") },
	{ Mod1Mask|ControlMask,	        XK_l,      spawn,          SHCMD("lock") },
	{ MODKEY,                       XK_BackSpace,              scratchpad_show,{0} },
	{ MODKEY|ShiftMask,             XK_BackSpace,              scratchpad_hide,{0} },
	{ MODKEY,                       XK_Escape,                 scratchpad_remove,{0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_s,      swapfocus,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,                       XK_minus, scratchpad_show, {0} },
	{ MODKEY|ShiftMask,             XK_minus, scratchpad_hide, {0} },
	{ MODKEY,                       XK_equal,scratchpad_remove,{0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

