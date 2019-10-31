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

#define BLACK_BOARD_ID 999999

#define SCORE_LENGTH 6
#define TIME_LENGTH 4
#define STAGE_LENGTH 2
#define HEART_LENGTH 2
#define LIVE_LENGTH 2


#define TEX_FONT_ID 4
#define TEX_BLACK_BOARD_ID 5


using namespace std;

class CBoardGame
{
	static CBoardGame * __instance;

	int letterWidth, letterHeight;

	int ColumLetterBoard, RowLetterBoard;

	int limitTime;

	LPDIRECT3DTEXTURE9 tex;

	D3DXIMAGE_INFO info;

	vector<LPCFONT> letters;
public:
	static CBoardGame* GetInstance();

	CBoardGame()
	{
		limitTime=300;
	}

	void setLimitTime(int time) {
		limitTime = time;
	}

	int getLimitTime()
	{
		return limitTime;
	}
	void ReadFontTXT(LPCSTR filePath);

	void LoadBackBoard(int texId, LPCSTR filePath);

	void LoadFont(int texId);

	LPCFONT Get(int fontId);

	int GetWithNumber(int number);


};

typedef CBoardGame * LPBOARDGAME;