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
#define ID_TEX_SIMON 0
#define ID_TEX_ITEMS 1
#define ID_TEX_OBJECTS 2
#define ID_TEX_ENEMIES 3
#define ID_TEX_SIMON_ATTACK 10

#define ID_TEX_MAP1 100000

//debug define
#define IS_RENDER_BBOX isRenderBBox

#define BOSS_HEALTH bossHealth

//chieu rong cua scence
#define SCENCE_WITDH scenceWidth

#define DELETE_POINTER(pointer) if (pointer){delete pointer; pointer=NULL;}

#define LOCK_CAMERA_X lockCameraX
#define LOCK_CAMERA_OFFSET_X 275


//grid
#define GRID_OFFSET 48
#define GRID_PART 5
#define ENEMIES_GRID -1
#define ITEMS_GRID -2
#define EFFECTS_GRID -3
#define WEAPONENEMIES_GRID -4


//GameItem
enum GAME_ITEM
{
	SMALL_HEART,
	LARGE_HEART,
	WHIP_UPGRADE,
	DANGER_ITEM,
	AXE_ITEM,
	HOLY_WATER_ITEM,
	STOP_WATCH_ITEM,
	CROSS_ITEM,
	RED_MONEY_BAG,
	PURPLE_MONEY_BAG,
	WHITE_MONEY_BAG,
	POT_ROAST,
	DOUBLE_SHOT,
	INVI_POTION,
	MAGIC_CRYSTAL
};

enum MAKE_OBJECTS {
	GROUND = 0,
	LARGECANDLE = 1,
	SMALLCANDLE = 2,
	WALL = 3,
	CHANGESCENE = -1,
	SPAWN = -2,
	CHECKSTAIR = -3,
	HIDDENWALL = -4,
	LOCK = -5,
	DESTROY = -99,
	INTRO_GATE = -2020
};

enum MAKE_ITEMS {
	ITEMS_LARGEHEART = 0,
	ITEMS_WHIPUPGRADE = 1,
	ITEMS_DANGER = 2,
	ITEMS_HOLYWATER = 3,
	ITEMS_CROSS = 4,
	ITEMS_INVIPOTION = 5,
	ITEMS_AXE = 6,
};



enum TYPE_DESTROY_ITEM
{
	LEFT,
	RIGHT,
	BOTTOM,
};

enum TYPE_MAKE_ITEM
{
	STATIC_OBJECT,
	ENEMY,
	BOSS
};

enum STAIR_TYPE
{
	NOSTAIR,
	UP,
	DOWN
};


//Chia sau

extern bool isRenderBBox;
extern bool isLockCamX;
extern int scenceWidth;
extern D3DCOLOR backGroundColor;
extern int bossHealth;
extern float lockCameraX;


