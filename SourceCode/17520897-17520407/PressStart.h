#pragma once
#include "FrameWork/debug.h"
#include "FrameWork//GameObject.h"

#define PRESSSTART_IDLE_ANI 80002
#define PRESSSTART_ANI 80003

class PressStart : public CGameObject
{
private:
	int ani;
public:
	PressStart();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void RenderCurrentFrame();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};
