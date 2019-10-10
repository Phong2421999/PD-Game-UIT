#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "FrameWork/Game.h"

class CTile {
	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9      texture;
public:
	CTile(int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	void Draw(int x, int y);
	~CTile();
};

typedef CTile * LPTILE;