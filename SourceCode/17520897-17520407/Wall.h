#pragma once
#include <d3d9.h>
#include "Simon.h"
#include "HiddenObjects.h"

class CWall : public HiddenObjects
{
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};
