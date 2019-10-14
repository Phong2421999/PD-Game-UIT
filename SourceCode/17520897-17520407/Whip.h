#pragma once
#include "Weapon.h"

#define WHIP_SPEED_X 0
#define WHIP_SPEED_Y 0
#define WHIP_BBOX_HEIGHT 6
#define WHIP_BBOX_LEVEL1_WIDTH 26
#define WHIP_BBOX_LEVEL2_WIDTH 26
#define WHIP_BBOX_LEVEL3_WIDTH 40

#define WHIP_TIME_LIVE 100

#define WHIP_ANI_LEVEL_1 509
#define WHIP_ANI_LEVEL_2 510
#define WHIP_ANI_LEVEL_3 511

#define WHIP_ANI_LEVEL_1_ID 0
#define WHIP_ANI_LEVEL_2_ID 1
#define WHIP_ANI_LEVEL_3_ID 2

#define WHIP_OFFSET_Y_TO_HAND_SIMON 8
#define WHIP_OFFSET_X_TO_HAND_LEFT_SIMON 35
#define WHIP_OFFSET_X_TO_HAND_RIGHT_SIMON 31

class Whip : public Weapon {

private:
	int curLevel;
public :
	Whip(float x, float y, int nx, int level);
	void SetLevel(int level) {
		this->curLevel = level;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void SetDxDy(float dx, float dy)
	{
		this->dx = dx;
		this->dy = dy;
	}
	bool GetLastFrame()
	{
		int ani;
		switch (curLevel)
		{
		case 1:
			ani = 0;
			break;
		case 2:
			ani = 1;
			break;
		case 3:
			ani = 2;
			break;
		}
		if(animations[ani]->getLastFrame())
			return  true;
		return false;
	}
	void ResetAnimation()
	{
		int ani;
		switch (curLevel)
		{
		case 1:
			ani = 0;
			break;
		case 2:
			ani = 1;
			break;
		case 3:
			ani = 2;
			break;
		}
		animations[ani]->reset();
	}
	void SetPositionWithSimon(float x, float y, int nx);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

};