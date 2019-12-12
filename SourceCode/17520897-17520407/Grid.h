#pragma once
#include "FrameWork/GameObject.h"
#include "FrameWork/Game.h"
#include <unordered_map>

class Grid
{
private:
	unordered_map<int, vector<LPGAMEOBJECT>> gridObjects;
public:
	static Grid* __instance;
	static Grid * GetInstance();
	void add(LPGAMEOBJECT obj, int grid);
	void clear();
	void get(int grid, vector<LPGAMEOBJECT> &objects);
	void caculateGrid(vector<int> &gridData);
	void eraseObject(int gridId, int index);
};