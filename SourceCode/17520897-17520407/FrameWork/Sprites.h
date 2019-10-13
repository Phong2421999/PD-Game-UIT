#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Game.h"

using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;			// Toạ độ
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9      texture;
	LPD3DXSPRITE spriteHandler;

public: 
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y, int alpha = 255);
	void DrawFlipX(float x, float y, float offsetX, int alpha = 255);
};

typedef CSprite * LPSPRITE;





