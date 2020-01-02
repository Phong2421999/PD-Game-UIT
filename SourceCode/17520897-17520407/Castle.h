#pragma once
#pragma once
#include "FrameWork/debug.h"
#include "FrameWork//GameObject.h"
#define CASTLE_ANI 8000
#define CASTLE_IDLE_ANI 80001

class Castle : public CGameObject
{
private:
	int ani;
public:
	Castle();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void RenderCurrentFrame();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};