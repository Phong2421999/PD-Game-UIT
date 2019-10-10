#pragma once
#include <d3d9.h>

//general define
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 300
#define MAX_FRAME_RATE 120
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define WINDOW_CLASS_NAME L"PDClass"
#define MAIN_WINDOW_TITLE L"PDGame"

//Map
#define ID_MAP1 100000
#define ID_MAP2 200000
#define ID_MAP3 300000

//Textures
#define ID_TEX_MAP1 100000

//debug define
#define IS_RENDER_BBOX isRenderBBox

//chieu rong cua scence
#define SCENCE_WITDH scenceWidth

#define DELETE_POINTER(pointer) if (pointer){delete pointer; pointer=NULL;}




//Chia sau

extern bool isRenderBBox;
extern int scenceWidth;
