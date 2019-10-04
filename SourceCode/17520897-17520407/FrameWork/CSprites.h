#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Sprites.h"
#include "Game.h"
/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);
	void Flip(int id, float FlipX, float FlipY)
	{
		sprites[id]->Flip(FlipX, FlipY);
	}
	static CSprites * GetInstance();
};

