#include "CBoardGame.h"

CBoardGame * CBoardGame::__instance = NULL;

CBoardGame *CBoardGame::GetInstance() {
	if (__instance == NULL)
	{
		__instance = new CBoardGame();
	}
	return __instance;
}


void CBoardGame::GetBoardInfo(int rowLetter, int columnLetter, int letterWidth, int letterHeight, int subWeapon_posX, int subWeapon_posY, int simonHealthBar_posX, int simonHealthBar_posY, int enemyHealthBar_posX, int enemyHealthBar_posY)
{
	this->RowLetterBoard = rowLetter;
	this->ColumLetterBoard = columnLetter;
	this->letterWidth = letterWidth;
	this->letterHeight = letterHeight;
	this->subWeapon_posX = subWeapon_posX;
	this->subWeapon_posY = subWeapon_posY;
	this->simonHealthBar_posX = simonHealthBar_posX;
	this->simonHealthBar_posY = simonHealthBar_posY;
	this->enemyHealthBar_posX = enemyHealthBar_posX;
	this->enemyHealthBar_posY = enemyHealthBar_posY;
}

void CBoardGame::LoadBackBoard(int texId, LPCSTR filePath) {

	tex = CTextures::GetInstance()->Get(texId);

	HRESULT result = D3DXGetImageInfoFromFileA(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}
	int left = 0.0f;
	int top = 0.0f;
	int right = left + info.Width;
	int bottom = top + info.Height;
	CSprites::GetInstance()->Add(BLACK_BOARD_ID, left, top, right, bottom, tex);
}

void CBoardGame::LoadFont(int texId) {

	tex = CTextures::GetInstance()->Get(texId);

	for (int i = 0; i < RowLetterBoard; i++)
	{
		for (int j = 0; j < ColumLetterBoard; j++)
		{
			int left = j * letterWidth;
			int top = i * letterHeight;
			int right = left + letterWidth;
			int bottom = top + letterHeight;
			LPCFONT font = new CFont(left, top, right, bottom, tex);
			letters.push_back(font);
		}
	}
}

LPCFONT CBoardGame::Get(int fontId) {
	if(fontId != -1)
		return letters[fontId];
}

int CBoardGame::GetSubWeapon(SIMON_WEAPON type) {
	switch (type)
	{
	case NONE:
		return -1;
		break;
	case AXE:
		return SPRITE_AXE_ID;
		break;
	case DANGER:
		return SPRITE_DANGER_ID;
	case HOLY_WATER:
		return SPRITE_HOLY_WATER_ID;
		break;
	case STOP_WATCH:
		return SPRITE_STOP_WATCH_ID;
		break;
	}
}

int CBoardGame::GetWithNumber(int number) {
	switch (number)
	{
	case 0:
		return 26;
		break;
	case 1:
		return 27;
		break;
	case 2:
		return 28;
		break;
	case 3:
		return 29;
		break;
	case 4:
		return 30;
		break;
	case 5:
		return 31;
		break;
	case 6:
		return 32;
		break;
	case 7:
		return 33;
		break;
	case 8:
		return 34;
		break;
	case 9:
		return 35;
		break;
	default:
		return 26;
		break;
	}
}