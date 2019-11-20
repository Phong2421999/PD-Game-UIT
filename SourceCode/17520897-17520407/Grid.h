#pragma once
#include "FrameWork/GameObject.h"

class Grid
{
public:
	static Grid* __instance;
	static Grid * GetInstance();
	void checkGrid(vector<CGameObject*>objects, vector<CGameObject*>&returnObject);
};
