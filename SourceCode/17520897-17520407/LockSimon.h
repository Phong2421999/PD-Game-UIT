#pragma once
#include "HiddenObjects.h"
#include "Simon.h"

class LockSimon :public  HiddenObjects
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
};
