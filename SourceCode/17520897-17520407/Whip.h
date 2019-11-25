#pragma once
#include "Weapon.h"
#include "HiddenWall.h"

#define WHIP_SPEED_X 0
#define WHIP_SPEED_Y 0
#define WHIP_BBOX_HEIGHT 6
#define WHIP_BBOX_LEVEL1_WIDTH 26
#define WHIP_BBOX_LEVEL2_WIDTH 41
#define WHIP_BBOX_LEVEL3_WIDTH 40

#define WHIP_TIME_LIVE 100

#define WHIP_ANI_LEVEL_1 509
#define WHIP_ANI_LEVEL_2 510
#define WHIP_ANI_LEVEL_3 511

#define WHIP_ANI_LEVEL_1_ID 0
#define WHIP_ANI_LEVEL_2_ID 1
#define WHIP_ANI_LEVEL_3_ID 2

#define WHIP_LEVEL_1 1
#define WHIP_LEVEL_2 2
#define WHIP_LEVEL_3 3

#define WHIP_OFFSET_Y_TO_HAND_SIMON 8
#define WHIP_OFFSET_X_TO_HAND_LEFT_SIMON_LEVEL_1 29
#define WHIP_OFFSET_X_TO_HAND_RIGHT_SIMON_LEVEL_1 36

#define WHIP_OFFSET_X_TO_HAND_LEFT_SIMON_LEVEL_2 44
#define WHIP_OFFSET_X_TO_HAND_RIGHT_SIMON_LEVEL_2 40

#define WHIP_OFFSET_X_TO_HAND_LEFT_SIMON_LEVEL_3 45
#define WHIP_OFFSET_X_TO_HAND_RIGHT_SIMON_LEVEL_3 37

class Whip : public Weapon {

private:
	int curLevel;
	int simonX, simonY;
	bool isTouchHiddenWall;
	bool isTouchEnemy;
public :
	Whip(float x, float y, int nx, int level);
	void SetLevel(int level) {
		this->curLevel = level;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void SetRenderPos(float x, float y)
	{
		xRender = x;
		yRender = y;
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