#pragma once
#include "HiddenObjects.h"

class CheckGround :public HiddenObjects
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
};
