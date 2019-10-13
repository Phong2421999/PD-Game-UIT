#pragma once
#include "Weapon.h"

#define WHIP_SPEED_X 0
#define WHIP_SPEED_Y 0
#define WHIP_BBOX_HEIGHT 6
#define WHIP_BBOX_LEVEL1_WIDTH 25
#define WHIP_BBOX_LEVEL2_WIDTH 25
#define WHIP_BBOX_LEVEL3_WIDTH 40

#define WHIP_TIME_LIVE 100

#define WHIP_ANI_LEVEL_1_ID 506

#define WHIP_ANI_LEVEL_1 0

class Whip : public Weapon {


public :
	Whip(float x, float y, int nx);
	void Render();
	void RenderFlipX();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	bool GetLastFrame()
	{
		if(animations[WHIP_ANI_LEVEL_1]->getLastFrame())
			return  true;
		return false;
	}
	void ResetAnimation()
	{
		animations[WHIP_ANI_LEVEL_1]->reset();
	}
};