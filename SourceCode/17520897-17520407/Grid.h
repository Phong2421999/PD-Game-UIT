#pragma once
#include "FrameWork/GameObject.h"
#include "FrameWork/Game.h"
#include <unordered_map>

class Grid
{
public:
	unordered_map<int, vector<LPGAMEOBJECT>> gridObjects;
public:
	void add(LPGAMEOBJECT obj, int grid);
	void clear();
	void get(int grid, vector<LPGAMEOBJECT> &objects);
	void caculateGrid(vector<int> &gridData);
	void getListObjects(vector<LPGAMEOBJECT> &objects);
};