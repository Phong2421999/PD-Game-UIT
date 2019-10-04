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

	LPDIRECT3DTEXTURE9 texture;
public: 
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	void Draw(float x, float y, int alpha = 255);
	void Flip(float FlipX, float FlipY) {
		CGame::GetInstance()->Flip(FlipX, FlipY);
	}
};

typedef CSprite * LPSPRITE;





