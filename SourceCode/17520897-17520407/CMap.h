#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include "CTiles.h"
#include <unordered_map>
#include "FrameWork/debug.h"

#define ID_MAP_LEVEL1 100000

class CMap
{
	static CMap * __instance;
	unordered_map<int, LPTILES> maps;

public:
	void Add(int id, LPCSTR filePath, int texId);
	
	LPTILES Get(int id);

	static CMap* GetInstance();
	
};
