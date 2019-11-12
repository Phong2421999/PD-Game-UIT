#pragma once
#include "HiddenObjects.h"
#include "Simon.h"

class CWall:public HiddenObjects
{
public:
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};
