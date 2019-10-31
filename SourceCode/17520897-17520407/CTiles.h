#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "GameConst.h"
#include "FrameWork/Game.h"
#include "CTile.h"
#include <fstream>
#include "FrameWork/Textures.h"
#include "FrameWork/debug.h"

using namespace std;

class CTiles
{
	int frameWidth, frameHeight;

	int ColumnTileSet, RowTileSet;
	int ColumnMap, RowMap;

	int DrawPositionX, DrawPositionY;

	int HeightBoard; // chiều cao board
	int TileMap[500][500];

	LPDIRECT3DTEXTURE9 tex;
	D3DXIMAGE_INFO info;
	vector<LPTILE> tiles;
public:

	CTiles(int texId, LPCSTR filePath);

	void ReadMapTXT(LPCSTR filePath);

	void LoadTile();

	void SetMapPosition(int offsetX, int offsetY);

	void Render();

};

typedef CTiles * LPTILES;