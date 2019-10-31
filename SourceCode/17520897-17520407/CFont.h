#pragma once

#include <unordered_map>
#include <d3dx9.h>
#include "FrameWork/Game.h"

class CFont
{

private:
	int left, top, right, bottom;
	LPDIRECT3DTEXTURE9 tex;

public:
	CFont(int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	void Draw(float x, float y);
};

typedef CFont * LPCFONT;