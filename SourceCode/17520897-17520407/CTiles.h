#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "CTile.h"
#include <vector>
#include "FrameWork/Textures.h"
#include "FrameWork/debug.h"

using namespace std;

class CTiles 
{
	int offsetX, offsetY;
	LPDIRECT3DTEXTURE9 tex;
	vector<LPTILE> tiles;
	D3DXIMAGE_INFO info;
public:

	CTiles(LPCSTR filePath, int texId);
	
	void SetMapPosition(int offsetX, int offsetY);

	void LoadMap();

	void Draw();

};

typedef CTiles * LPTILES;