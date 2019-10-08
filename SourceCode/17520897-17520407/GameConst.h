#pragma once
#include <d3d9.h>

//general define
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define MAX_FRAME_RATE 120
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define WINDOW_CLASS_NAME L"PDClass"
#define MAIN_WINDOW_TITLE L"PDGame"


//debug define
#define IS_RENDER_BBOX isRenderBBox

//chieu rong cua scence
#define SCENCE_WITDH scenceWidth


//Chia sau

extern bool isRenderBBox;
extern int scenceWidth;
