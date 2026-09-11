// platform/pc/pc_widescreen.h — PC-only widescreen plumbing.
//
// The GBA renders 240x160. On the PC port we can widen the view: BG2/BG3 (the
// dungeon terrain/overlay and ground maps) are drawn by game code into
// gPc_WideTilemaps (stride 64 columns) instead of the 32-column gBgTilemaps,
// and the compositor samples them at the configured width. BG0/BG1 (HUD, text
// windows, menus) keep the 240-wide 32-column layout.
//
// All symbols are no-ops for the GBA build: game code only touches them under
// PLATFORM_PC, so the ROM build stays byte-identical.
#ifndef PMDRED_PC_WIDESCREEN_H
#define PMDRED_PC_WIDESCREEN_H

// Camera-centering offset and screen-edge constants for the wide view. On the
// GBA they are the fixed 240-wide values; on PC they follow Pc_ViewW() so the
// game logic re-centers automatically when widescreen toggles.
#ifdef PLATFORM_PC
#define PC_CAM_CENTER_X (Pc_ViewW() / 2)
#define PC_CAM_EDGE (Pc_ViewW())
// Ground-mode camera centering constant (code_809D148.c): places the leader
// Pc_ViewW()/2 + 1 px from the left. GBA = 30976 (121*256).
#define PC_GROUND_CAM_X ((Pc_ViewW() / 2 + 1) * 256 - 0x80)
// Ground camera clamp margin (sub_80A579C): keeps the view inside the map.
// GBA = 0x7800 (120*256) for the 240px view.
#define PC_GROUND_CAM_MIN ((Pc_ViewW() / 2 + 1) * 256)
// Visible width for on-screen culling (240 classic / 384 widescreen).
#define PC_VIEW_W() (Pc_ViewW())
// Trap/stairs scan half-extent in map cells (24px): 6 = classic view.
#define PC_TRAP_HALF (Pc_WidescreenOn() ? (Pc_ViewW() / 24) : 6)
// Dungeon "near camera" reveal half-extent in map cells (sub_803F428): items
// closer than this are shown. 6 = classic half-view (5) + 1 margin.
#define PC_CAM_TILES_HALF (Pc_WidescreenOn() ? (Pc_ViewW() / 48 + 1) : 6)
#else
#define PC_CAM_CENTER_X 120
#define PC_CAM_EDGE 240
#define PC_GROUND_CAM_X 30976
#define PC_GROUND_CAM_MIN 0x7800
#define PC_VIEW_W() 240
#define PC_TRAP_HALF 6
#define PC_CAM_TILES_HALF 6
#endif

#ifdef PLATFORM_PC

#include <stddef.h>

// Max horizontal tilemap columns for the wide BGs (power-of-two row stride so
// the renderer can mask; 64 columns = 512px, more than enough for 384px wide).
#define PC_TILEMAP_COLS 64

#define PC_WIDE_W  384
#define PC_WIDE_W8 48 // PC_WIDE_W / 8

#define PC_CLASSIC_W  240
#define PC_CLASSIC_W8 32

#ifdef __cplusplus
extern "C" {
#endif

// Wide BG tilemaps (BG2/BG3). Defined in src/text_1.c (PLATFORM_PC only).
// Rows are PC_TILEMAP_COLS wide so a strided flat index (row*64+col) works;
// only the first Pc_ViewW8() columns of each row carry valid data.
extern unsigned short gPc_WideTilemaps[4][32][PC_TILEMAP_COLS];

// Current render width (240 classic / 384 widescreen) and its 8px-tile count.
int Pc_ViewW(void);
int Pc_ViewW8(void);
// 1 while the widescreen mode is active.
int Pc_WidescreenOn(void);
// Enable/disable widescreen live (toggles the video backend width too).
void Pc_SetWidescreen(int on);

// The dungeon/ground tilemap writers call Pc_WideBgsMark() whenever they paint
// BG2/BG3 into gPc_WideTilemaps; the compositor consumes the flag once per
// frame and clears it, so menu scenes (which write 32-col data into gBgTilemaps
// and the VRAM screenbases) keep rendering from the classic path.
void Pc_WideBgsMark(void);
int Pc_WideBgsActive(void);
void Pc_WideBgsClear(void);

#ifdef __cplusplus
}
#endif

#endif // PLATFORM_PC
#endif // PMDRED_PC_WIDESCREEN_H