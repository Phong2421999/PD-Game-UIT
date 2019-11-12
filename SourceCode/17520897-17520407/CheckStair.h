#pragma once
#include "HiddenObjects.h"
#include "Simon.h"
#include "GameConst.h"

class CheckStair:public HiddenObjects
{
private:
	STAIR_TYPE type;
public:
	CheckStair()
	{
		type = STAIR_TYPE::NOSTAIR;
	}
	void SetStairType(STAIR_TYPE type)
	{
		this->type = type;
	}
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
};
