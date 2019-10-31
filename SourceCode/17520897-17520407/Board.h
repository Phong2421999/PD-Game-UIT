#pragma once
#include "FrameWork/Sprites.h"


class Board
{
	int left, top, right, bottom;

	LPDIRECT3DTEXTURE9 tex;

public:
	Board();
	~Board();
};
