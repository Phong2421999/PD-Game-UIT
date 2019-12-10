#pragma once
#include "FrameWork/GameObject.h"
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
	vector<LPGAMEOBJECT> get(int grid);
	int caculateGrid(float x);
};
