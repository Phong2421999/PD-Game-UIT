#pragma once
#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <fstream>
#include "CFont.h"
#include "GameConst.h"
#include "FrameWork/Game.h"
#include "FrameWork/Textures.h"
#include "FrameWork/debug.h"
#include "FrameWork/CSprites.h"
#include "SimonConst.h"
#include "Simon.h"

#define BLACK_BOARD_ID 999999

#define SCORE_LENGTH 6
#define TIME_LENGTH 4
#define STAGE_LENGTH 2
#define HEART_LENGTH 2
#define LIVE_LENGTH 2

#define TEX_FONT_ID 4
#define TEX_BLACK_BOARD_ID 5

#define SIMON_MAX_HEALTH 16
#define ENEMY_MAX_HEALTH 16

#define CELL_MARGIN 6

#define DAGGER_ITEM_PADDING_LEFT 3

#define AXE_ITEM_PADDING_LEFT 2
#define AXE_ITEM_PADDING_TOP -2

#define HOLY_WATER_ITEM_PADDING_LEFT 5
#define HOLY_WATER_ITEM_PADDING_TOP -5

#define STOP_WATCH_ITEM_PADDING_LEFT 5
#define STOP_WATCH_ITEM_PADDING_TOP -5

#define DOUBLE_SHOT_ICON_POS_X 270
#define DOUBLE_SHOT_ICON_POS_Y 24

#define SPRITE_SIMON_HEALTH_CELL_ID 60165 
#define SPRITE_ENEMY_HEALTH_CELL_ID 60167

#define SPRITE_LOST_HEALTH_ID 60166

#define SPRITE_DANGER_ID 10111 
#define SPRITE_AXE_ID 10112
#define SPRITE_STOP_WATCH_ID 10122
#define SPRITE_HOLY_WATER_ID 10123
#define SPRITE_DOUBLE_SHOT_ID 10134


using namespace std;

class CBoardGame
{
	static CBoardGame * __instance;

	int letterWidth, letterHeight;

	int ColumLetterBoard, RowLetterBoard;

	float subWeapon_posX, subWeapon_posY;

	float simonHealthBar_posX, simonHealthBar_posY;
	float enemyHealthBar_posX, enemyHealthBar_posY;

	int limitTime;

	LPDIRECT3DTEXTURE9 tex;

	D3DXIMAGE_INFO info;

	vector<LPCFONT> letters;

public:

	static CBoardGame* GetInstance();

	CBoardGame()
	{
		limitTime = 300;
	}

	void setLimitTime(int time) {
		limitTime = time;
	}

	int getLimitTime()
	{
		return limitTime;
	}

	void GetPositionSubWeapon(float &x, float &y)
	{
		x = subWeapon_posX;
		y = subWeapon_posY;
	}

	void GetPositionSimonHealthBar(float &x, float &y)
	{
		x = simonHealthBar_posX;
		y = simonHealthBar_posY;
	}

	void GetPositionEnemyHealthBar(float &x, float &y)
	{
		x = enemyHealthBar_posX;
		y = enemyHealthBar_posY;
	}

	void GetBoardInfo(int rowLetter, int columnLetter, int letterWidth, int letterHeight, int subWeapon_posX, int subWeapon_posY, int simonHealthBar_posX, int simonHealthBar_posY, int enemyHealthBar_posX, int enemyHealthBar_posY);

	void LoadBackBoard(int texId, LPCSTR filePath);

	void LoadFont(int texId);


	LPCFONT Get(int fontId);

	int GetSubWeapon(SIMON_WEAPON type);

	int GetWithNumber(int number);

};

typedef CBoardGame * LPBOARDGAME;