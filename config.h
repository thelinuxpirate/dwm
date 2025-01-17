/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx       = 2;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const int scalepreview            = 4;        /* Tag preview scaling */
static const unsigned int gappih         = 12;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 10;  /* vert inner gap between windows */
static const unsigned int gappoh         = 12;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 10;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 1;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const char autostartblocksh[]     = "autostart_blocking.sh";
static const char autostartsh[]          = "autostart.sh";
static const char dwmdir[]               = "dwm";
static const char localshare[]           = ".local/bin/";
static const int usealtbar = 0; /* 1 means use non-dwm status bar */
static const char *altbarclass           = "Polybar"; /* Alternate bar class name */
static const char *altbarcmd             = "$HOME/bar.sh"; /* Alternate bar launch command */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const int bar_height              = 0;   /* 0 means derive from font, >= 1 explicit height */
static const int focusonwheel            = 0;

/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = 'A';
static const char buttonbar[]            = "󰌽";
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */
static const unsigned int ulinepad       = 5;   /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke    = 2;   /* thickness / height of the underline */
static const unsigned int ulinevoffset   = 0;   /* how far above the bottom of the bar the line should appear */
static const int ulineall                = 0;   /* 1 to show underline on all tags, 0 for just the active ones */


/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static int fakefsindicatortype           = INDICATOR_PLUS;
static int floatfakefsindicatortype      = INDICATOR_PLUS_AND_LARGER_SQUARE;
static const char *fonts[]               = { "Comic Mono:size=12", "Arimo Nerd Font:size=12:antialias=true", "Font Awesome:size=12:antialias=true" };
static const char dmenufont[]            = "Comic Mono:size=12";
static const char dmenucol[]             = "10";
static const char dmenugrid[]            = "5";

static char c000000[]                    = "#000000"; // placeholder value

static char normfgcolor[]                = "#c5dde0";
static char normbgcolor[]                = "#101419";
static char normbordercolor[]            = "#202836";
static char normfloatcolor[]             = "#bf4559";

static char selfgcolor[]                 = "#c5dde0";
static char selbgcolor[]                 = "#202836";
static char selbordercolor[]             = "#6eaae6";
static char selfloatcolor[]              = "#db8fd9";

static char titlenormfgcolor[]           = "#c5dde0";
static char titlenormbgcolor[]           = "#101419";
static char titlenormbordercolor[]       = "#202836";
static char titlenormfloatcolor[]        = "#bf4559";

static char titleselfgcolor[]            = "#6eaae6";
static char titleselbgcolor[]            = "#202836";
static char titleselbordercolor[]        = "#101419";
static char titleselfloatcolor[]         = "#db8fd9";

static char tagsnormfgcolor[]            = "#5d869e";
static char tagsnormbgcolor[]            = "#101419";
static char tagsnormbordercolor[]        = "#202836";
static char tagsnormfloatcolor[]         = "#ad57a0";

static char tagsselfgcolor[]             = "#8cc5e6";
static char tagsselbgcolor[]             = "#202836";
static char tagsselbordercolor[]         = "#101419";
static char tagsselfloatcolor[]          = "#db8fd9";

static char hidnormfgcolor[]             = "#c5dde0";
static char hidselfgcolor[]              = "#c5dde0";
static char hidnormbgcolor[]             = "#151e2e";
static char hidselbgcolor[]              = "#151e2e";

static char urgfgcolor[]                 = "#8cc5e6";
static char urgbgcolor[]                 = "#151e2e";
static char urgbordercolor[]             = "#c5dde0";
static char urgfloatcolor[]              = "#bf4559";

static char *colors[][ColCount] = {
  /*                       fg                bg                border                float */
  [SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
  [SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
  [SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
  [SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
  [SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
  [SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
  [SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
  [SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
  [SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};

static const char *const autostart[] = {
  NULL
};

const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL};
static Sp scratchpads[] = {
   /* name          cmd  */
   {"spterm",      spcmd1},
};

/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
 */
static char *tagicons[][NUMTAGS] = {
    [DEFAULT_TAGS] = {"", "󰈹", "", "", "", "󰸳", "", "", "", "", "", ""},
    [ALTERNATIVE_TAGS] = {"", "󰈹", "", "", "", "󰸳", "", "", "", "", "", ""},
    [ALT_TAGS_DECORATION] = {"", "󰈹", "", "", "", "󰸳", "", "", "", "", "", ""},
};

/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   *  WM_WINDOW_ROLE(STRING) = role
   *  _NET_WM_WINDOW_TYPE(ATOM) = wintype
   */
  RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
  RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
  RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
  RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
  RULE(.instance = "spterm", .tags = SPTAG(0), .isfloating = 1)
};


/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
  /* monitor   bar    alignment         widthfunc                 drawfunc                clickfunc                hoverfunc                name */
  { -1,        0,     BAR_ALIGN_LEFT,   width_stbutton,           draw_stbutton,          click_stbutton,          NULL,                    "statusbutton" },
  { -1,        0,     BAR_ALIGN_LEFT,   width_tags,               draw_tags,              click_tags,              hover_tags,              "tags" },
  {  0,        0,     BAR_ALIGN_RIGHT,  width_systray,            draw_systray,           click_systray,           NULL,                    "systray" },
  { -1,        0,     BAR_ALIGN_LEFT,   width_ltsymbol,           draw_ltsymbol,          click_ltsymbol,          NULL,                    "layout" },
  { statusmon, 0,     BAR_ALIGN_RIGHT,  width_status2d,           draw_status2d,          click_statuscmd,         NULL,                    "status2d" },
  { -1,        0,     BAR_ALIGN_NONE,   width_awesomebar,         draw_awesomebar,        click_awesomebar,        NULL,                    "awesomebar" },
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=",      tile },    /* first entry is default */
  { "><>",      NULL },    /* no layout function means floating behavior */
  { "[M]",      monocle },
  { "TTT",      bstack },
  { "|M|",      centeredmaster },
  { ">M>",      centeredfloatingmaster },
  { "HHH",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,      comboview,      {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      combotag,       {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
  "dmenu_run",
  "-m", dmenumon,
  "-fn", dmenufont,
  "-l", dmenucol,
  "-g", dmenugrid,
  NULL
};
static const char *termcmd[] = {"alacritty", NULL};
static const char *editorcmd[] = {"emacsclient -c", NULL};
static const char *browsercmd[] = {"zen", NULL};

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
static const StatusCmd statuscmds[] = {
  { "notify-send Volume$BUTTON", 1 },
  { "notify-send CPU$BUTTON", 2 },
  { "notify-send Battery$BUTTON", 3 },
};
/* test the above with: xsetroot -name "$(printf '\x01Volume |\x02 CPU |\x03 Battery')" */
static const char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };

static const Key keys[] = {
  /* modifier                     key            function                argument */
  // Applications
  { MODKEY,                       XK_space,      spawn,                  {.v = dmenucmd } },
  { MODKEY,                       XK_Return,     spawn,                  {.v = termcmd } },
  { MODKEY,                       XK_p,          spawn,                  SHCMD("pavucontrol") },
  { MODKEY|ShiftMask,             XK_p,          spawn,                  SHCMD("pixelorama") },
  { MODKEY,                       XK_m,          spawn,                  SHCMD("prismlauncher") },
  { MODKEY|ShiftMask,             XK_b,          spawn,                  {.v = browsercmd } },
  { MODKEY|ShiftMask,             XK_e,          spawn,                  {.v = editorcmd } },
  { MODKEY|ShiftMask,             XK_t,          spawn,                  SHCMD("nemo") },
  { MODKEY|ShiftMask,             XK_d,          spawn,                  SHCMD("vesktop") },
  { MODKEY|ShiftMask,             XK_s,          spawn,                  SHCMD("spotify") },
  { MODKEY|ShiftMask,             XK_g,          spawn,                  SHCMD("godot4") },
  { MODKEY|ShiftMask,             XK_m,          spawn,                  SHCMD("./System/Applications/Slippi/Slippi-Launcher.AppImage") },

  // Base Window Manager
  { MODKEY|ShiftMask,             XK_q,          quit,                   {0} },
  { MODKEY,                       XK_w,          killclient,             {0} },
  { MODKEY,                       XK_b,          togglebar,              {0} },
  { MODKEY,                       XK_Tab,        view,                   {0} },
  { MODKEY,                       XK_q,          showhideclient,         {0} },
  // Window Management
  // Stack
  { MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
  { MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
  { MODKEY|ShiftMask,             XK_j,          pushdown,               {0} },
  { MODKEY|ShiftMask,             XK_k,          pushup,                 {0} },
  { MODKEY|Mod1Mask,              XK_j,          rotatestack,            {.i = +1 } },
  { MODKEY|Mod1Mask,              XK_k,          rotatestack,            {.i = -1 } },
  // Master
  { MODKEY,                       XK_i,          incnmaster,             {.i = +1 } },
  { MODKEY,                       XK_o,          incnmaster,             {.i = -1 } },
  {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    // Window Size
    {MODKEY, XK_h, setmfact, {.f = -0.02}},
    {MODKEY, XK_l, setmfact, {.f = +0.02}},
    {MODKEY | Mod1Mask, XK_r, togglegaps, {0}},

    // Misc
    {MODKEY | ShiftMask, XK_f, togglefakefullscreen, {0}},
    {MODKEY, XK_v, switchcol, {0}},

    // Layouts
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_e, setlayout, {.v = &layouts[3]}},
    {MODKEY, XK_y, setlayout, {.v = &layouts[6]}},
    {MODKEY, XK_c, setlayout, {.v = &layouts[4]}},
    {MODKEY, XK_f, fullscreen, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},

    // ScratchPads
    {MODKEY, XK_grave, togglescratch, {.ui = 0}},
    {MODKEY | ControlMask, XK_grave, setscratch, {.ui = 0}},
    {MODKEY | ShiftMask, XK_grave, removescratch, {.ui = 0}},

    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY | ControlMask, XK_comma, cyclelayout, {.i = -1}},
    {MODKEY | ControlMask, XK_period, cyclelayout, {.i = +1}},

    // XF86_Multi-Media
    {0, XF86XK_AudioRaiseVolume, spawn, SHCMD("pamixer -i 2")},
    {0, XF86XK_AudioLowerVolume, spawn, SHCMD("pamixer -d 2")},
    {0, XF86XK_AudioMute, spawn, SHCMD("pamixer -t")},

    {0, XF86XK_AudioPlay, spawn, SHCMD("playerctl play-pause")},
    {0, XF86XK_AudioNext, spawn, SHCMD("playerctl next")},
    {0, XF86XK_AudioPrev, spawn, SHCMD("playerctl previous")},

    {0, XF86XK_MonBrightnessUp, spawn, SHCMD("brightnessctl set +200")},
    {0, XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl set 200-")},
    {0, XF86XK_Explorer, spawn, SHCMD("flameshot gui")},

    {0, XF86XK_Search, spawn, {.v = dmenucmd}},
    {0, XF86XK_HomePage, setlayout, {.v = &layouts[0]}},

    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8) TAGKEYS(XK_0, 9) TAGKEYS(XK_minus, 10)
             TAGKEYS(XK_equal, 11) };

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
  /* click                event mask           button          function        argument */
  { ClkButton,            0,                   Button1,        spawn,          {.v = dmenucmd } },
  { ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,                   Button1,        togglewin,      {0} },
  { ClkWinTitle,          0,                   Button3,        showhideclient, {0} },
  { ClkWinTitle,          0,                   Button2,        zoom,           {0} },
  { ClkStatusText,        0,                   Button1,        spawn,          {.v = statuscmd } },
  { ClkStatusText,        0,                   Button2,        spawn,          {.v = statuscmd } },
  { ClkStatusText,        0,                   Button3,        spawn,          {.v = statuscmd } },
  /* placemouse options, choose which feels more natural:
   *    0 - tiled position is relative to mouse cursor
   *    1 - tiled postiion is relative to window center
   *    2 - mouse pointer warps to window center
   *
   * The moveorplace uses movemouse or placemouse depending on the floating state
   * of the selected client. Set up individual keybindings for the two if you want
   * to control these separately (i.e. to retain the feature to move a tiled window
   * into a floating position).
   */
  { ClkClientWin,         MODKEY,              Button1,        moveorplace,    {.i = 1} },
  { ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
  { ClkClientWin,         MODKEY|ShiftMask,    Button1,        dragmfact,      {0} },
  { ClkTagBar,            0,                   Button1,        view,           {0} },
  { ClkTagBar,            0,                   Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};
