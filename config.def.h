/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Source Code Pro:pixelsize=14", "JoyPixels:pixelsize=14", "Symbols Nerd Font:pixelsize=14" };
static const char dmenufont[]       = "Source Code Pro:pixelsize=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_selborder[]   = "#45b6fe";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_selborder  },
};

/* tagging */
#define MAX_TAGLEN 16
static char tags[][MAX_TAGLEN] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   isterminal noswallow monitor    scratch key */
	{ "st",       NULL,       NULL,       0,            0,           1,          0,         -1,      0},
	{ "Viber",  NULL,       NULL,       1 << 5,       0,           0,          -1,        -1,      0},
	{ "Gimp",     NULL,       NULL,       1 << 6,       0,           1,          0,         -1,      0},
	{ "Inkscape", NULL,       NULL,       1 << 6,       0,           1,          0,         -1,      0},
	{ "newsboatterm",NULL,    NULL,       1 << 7,       0,           0,          -1,        -1,      0},
	{ "ncmpcppterm",NULL,     NULL,       1 << 8,       0,           0,          -1,        -1,      0},
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
	{ "TTT",      bstack },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "[M]",      monocle },
	{ "[D]",      deck },
	{ "><>",      NULL },    /* no layout function means floating behavior */
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
static const char *bccmd[] = {"c", "st", "-c", "bccmd", "-g", "40x20", "-e", "bc", "-lq", NULL};

#include "movestack.c"
#include "shiftview.c"
#include <X11/XF86keysym.h>
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
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ Mod1Mask,                     XK_Tab,    swapfocus,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ControlMask,           XK_space,  setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscreen, {0} },
	{ MODKEY|ShiftMask,             XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,      nametag,        {0} },
	{ MODKEY,                       XK_minus,  shiftviewclients,{ .i = -1 } },
	{ MODKEY,                       XK_equal,  shiftviewclients,{ .i = +1 } },
	{ MODKEY|ControlMask,           XK_minus,  shiftview,      { .i = -1 } },
	{ MODKEY|ControlMask,           XK_equal,  shiftview,      { .i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 

/* External programs */
	{ Mod1Mask|ControlMask,		XK_p,		spawn,          SHCMD("mpc toggle") },
	{ Mod1Mask|ShiftMask,		XK_p,		spawn,          SHCMD("mpc stop") },
	{ Mod1Mask|ControlMask,		XK_comma,	spawn,          SHCMD("mpc prev") },
	{ Mod1Mask|ControlMask,		XK_period,	spawn,          SHCMD("mpc next") },
	{ Mod1Mask|ShiftMask,		XK_comma,	spawn,          SHCMD("mpc seek -10") },
	{ Mod1Mask|ShiftMask,		XK_period,	spawn,          SHCMD("mpc seek +10") },
	{ Mod1Mask|ControlMask,		XK_minus,	spawn,          SHCMD("pamixer --allow-boost -d 5; dunstify -r 2 \"VOL: $(pamixer --get-volume-human)\"") },
	{ Mod1Mask|ControlMask,		XK_equal,	spawn,          SHCMD("pamixer --allow-boost -i 5; dunstify -r 2 \"VOL: $(pamixer --get-volume-human)\"") },
	{ Mod1Mask|ControlMask,		XK_BackSpace,	spawn,          SHCMD("pamixer -t; dunstify -r 2 \"$(pamixer --get-volume-human)\"") },
	{ Mod1Mask|ShiftMask,		XK_minus,	spawn,          SHCMD("xbacklight -dec 10; dunstify -r 3 \"BRIGHT: $(xbacklight -get | awk '{print int($1)}')\"") },
	{ Mod1Mask|ShiftMask,		XK_equal,	spawn,          SHCMD("xbacklight -inc 10; dunstify -r 3 \"BRIGHT: $(xbacklight -get | awk '{print int($1)}')\"") },

/* Extra keyboard keys */
	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("pamixer -t") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 5") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 5") },
	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("mpc next") },
	{ 0, XF86XK_AudioPause,		spawn,		SHCMD("mpc pause") },
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("mpc play") },
	{ 0, XF86XK_AudioStop,		spawn,		SHCMD("mpc stop") },
	{ 0, XF86XK_AudioRewind,	spawn,		SHCMD("mpc seek -10") },
	{ 0, XF86XK_AudioForward,	spawn,		SHCMD("mpc seek +10") },
	{ 0, XF86XK_AudioMedia,		spawn,		SHCMD("st -e ncmpcpp") },
	/* { 0, XF86XK_PowerOff,		spawn,		SHCMD("sysact") }, */
	{ 0, XF86XK_Calculator,		spawn,		SHCMD("st -e bc -l") },
	{ 0, XF86XK_Sleep,		spawn,		SHCMD("sudo -A zzz") },
	{ 0, XF86XK_WWW,		spawn,		SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,		spawn,		SHCMD("st") },
	{ 0, XF86XK_ScreenSaver,	spawn,		SHCMD("lock") },
	{ 0, XF86XK_TaskPane,		spawn,		SHCMD("st -e gotop") },
	{ 0, XF86XK_Mail,		spawn,		SHCMD("st -e neomutt") },
	{ 0, XF86XK_MyComputer,		spawn,		SHCMD("st -e lf /") },
	/* { 0, XF86XK_Battery,		spawn,		SHCMD("") }, */
	{ 0, XF86XK_Launch1,		spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("toggletouchpad") },
	{ 0, XF86XK_TouchpadOff,	spawn,		SHCMD("toggletouchpad on") },
	{ 0, XF86XK_TouchpadOn,		spawn,		SHCMD("toggletouchpad off") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 10") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 10") },
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

