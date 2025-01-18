/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int gappx     = 7;        /* gaps between windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:size=11:antialias=true:autohint=true", "Symbols Nerd Font Mono:style=Regular:size=11:antialias=true:autohint=true", "Noto Color Emoji:style=Regular:pixelsize=12:antialias=true:autohint=true" };
static char dmenufont[]       = "JetBrains Mono:size=11";
static char normbgcolor[]           = "#02021B";
static char normbordercolor[]       = "#8e9ea5";
static char normfgcolor[]           = "#cce2ec";
static char selfgcolor[]            = "#cce2ec";
static char selbordercolor[]        = "#cce2ec";
static char selbgcolor[]            = "#3B5986";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;

/* #include "/home/adi/.cache/wal/colors-wal-dwm.h" */
#include <X11/XF86keysym.h>

static const unsigned int alphas[][3]	={
	/*		 fg	 bg	   border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha},
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha},
};

/* tagging */
static const char *tags[] = { "󰍳", "","", "󰎈", "󰗚", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ "TelegramDesktop", NULL, NULL,      1 << 2,	      0,            1,		       -1 },
	{ "Firefox",  NULL,       NULL,       1 << 1,       0,            0,           -1 },
  { "obs",      NULL,       NULL,       1 << 5,       0,            0,           -1 },
  { "sioyek",   NULL,       NULL,       1 << 4,       0,            0,           -1 },
  { "com.github.johnfactotum.Foliate",   NULL,       NULL,       1 << 4,       0,         0,           -1 },
	{ "Sxiv",     NULL,       NULL,       0,            1,            1,           -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, };
static const char *termcmd[]  = { "st", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		/* { "font",               STRING,  &font }, */
		/* { "dmenufont",          STRING,  &dmenufont }, */
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		/* { "borderpx",          	INTEGER, &borderpx }, */
		/* { "snap",          		INTEGER, &snap }, */
		/* { "showbar",          	INTEGER, &showbar }, */
		/* { "topbar",          	INTEGER, &topbar }, */
		/* { "nmaster",          	INTEGER, &nmaster }, */
		/* { "resizehints",       	INTEGER, &resizehints }, */
		/* { "mfact",      	 	FLOAT,   &mfact }, */
};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_slash,      spawn,          {.v = dmenucmd } },
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
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
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
	{ 0,                       XF86XK_AudioLowerVolume, spawn, SHCMD("wpctl set-volume @DEFAULT_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },
	{ 0,                       XF86XK_AudioMute, spawn, 	   SHCMD("wpctl set-mute @DEFAULT_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, SHCMD("wpctl set-volume @DEFAULT_SINK@ 5%+; kill -44 $(pidof dwmblocks)") },
	{ 0,			   XF86XK_MonBrightnessUp, spawn,  SHCMD("brightnessctl s +5%; kill -44 $(pidof dwmblocks)") },
	{ 0,			   XF86XK_MonBrightnessDown, spawn,SHCMD("brightnessctl s 5%-; kill -44 $(pidof dwmblocks)") },
  { 0, XF86XK_AudioPlay, spawn, SHCMD("mpc toggle; mpdstatus") },
  { 0, XF86XK_AudioNext, spawn, SHCMD("mpc next; mpdstatus") },
  { 0, XF86XK_AudioPrev, spawn, SHCMD("mpc prev; mpdstatus") },
  { MODKEY, XK_o, spawn, SHCMD("sleep 0.5;xtrlock") },
  { 0, XK_Print, spawn, SHCMD("shot -p") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

