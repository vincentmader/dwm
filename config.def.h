/* See LICENSE file for copyright and license details. */

/* Constants (copied from Luke Smith) */
#define TERMINAL "st"


/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const int startwithgaps[]    = { 1 };	/* 1 means gaps are used by default, this can be customized for each tag */
static const unsigned int gappx[]   = { 45 };   /* default gap between windows in pixels, this can be customized for each tag */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 50;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
/* static const char *fonts[]          = { "monospace:size=30" }; */
/* static const char dmenufont[]       = "monospace:size=10"; */
static const char *fonts[]          = { "Font Awesome:size=25" };
static const char dmenufont[]       = "Font Awesome:size=10";
static const int attachbelow        = 1;    /* 1 means attach after the currently active window */

static const char col_bg[]          = "#666666";

static const char col_black[]       = "#AAAAAA";  /* TODO rename */
static const char col_gray1[]       = "#111111";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_blue[]       = "#268BD2";
static const char *colors[][3]      = {
	/*               fg         bg          border   */
	[SchemeNorm] = { col_gray3, col_gray1,  col_black },
	[SchemeSel]  = { col_blue,  col_gray1,  col_black  },
};

/* tagging */
static const char *tags[] = { 
    /* "", "", "", "", "", "", "", "", "" */ 
    /* "", */ 
    "",
    /* "", */ 
    "", 
    "", 
    "",
    "",
    "",
    "",
    "",
    /* "", */
    /* "", */
    /* "", */
    /* "", */ 
    "", 
    /* "", */ 
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	/* { "Gimp",     NULL,       NULL,       0,            1,           -1 }, */
	/* { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 }, */
        {  NULL,      NULL,       "emacs",       1 << 0,       False,       -1 },
        /* {  NULL,      NULL,       "spotify",       9 << 9,       False,       -1 }, */
        /* {  NULL,      NULL,       "qutebrowser", 2 << 0,       False,       -1 }, */
        /* {  NULL,      NULL,       "st",          3 << 0,       False,       -1 }, */
        /* {  NULL,      NULL,       "qutebrowser --qt-flag ignore-gpu-blacklist --qt-flag enable-gpu-rasterization --qt-flag enable-native-gpu-memory-buffers --qt-flag num-raster-threads=4",    1 << 1,       False,       -1 }, */
        /* {  NULL,      NULL,       TERMINAL " -e zsh",       1 << 2,       False,       -1 }, */
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */


#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
  	{ "[@]",      spiral },
  	{ "[\\]",     dwindle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define CMDKEY Mod4Mask  /* Mod4Mask  = cmd key */ 
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
static const char *termcmd[]  = { TERMINAL, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ CMDKEY,                       XK_e,      spawn,          SHCMD("emacs") },
	{ CMDKEY,                       XK_b,      spawn,          SHCMD("qutebrowser --qt-flag ignore-gpu-blacklist --qt-flag enable-gpu-rasterization --qt-flag enable-native-gpu-memory-buffers --qt-flag num-raster-threads=4") },
	{ CMDKEY,                       XK_r,      spawn,          SHCMD(TERMINAL " -e ranger --confdir $CONF/ranger") },  /* confdir param not really needed? */
	{ CMDKEY,                       XK_t,      spawn,          SHCMD(TERMINAL " -e zsh") },
	{ CMDKEY,                       XK_a,      spawn,          SHCMD(TERMINAL " -e gotop --color=solarized") },
	{ CMDKEY,                       XK_z,      spawn,          SHCMD("zathura") },
	{ CMDKEY,                       XK_q,      killclient,     {0} },

	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
 	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
 	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
 	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
 	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
 	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
 	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
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

