#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "FrameWork/Game.h"

class CTile {
	int left;
	int top;
	int right;
	int bottom;

	int x, y;

	LPDIRECT3DTEXTURE9      texture;
public:
	CTile(int x, int y, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	void Draw();
	~CTile();
};

typedef CTile * LPTILE;