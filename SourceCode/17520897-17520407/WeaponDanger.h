#pragma once
#include "Weapon.h"

#define DANGER_SPEED_X 0.2
#define DANGER_SPEED_Y 0
#define DANGER_BBOX_WIDTH 25
#define DANGER_BBOX_HEIGHT 6

#define DANGER_TIME_LIVE 1000

#define DANGER_ANI_ID 543

#define DANGER_ANI 0
#define OFFSET_DANGER_X_TO_HAND_LEFT_SIMON 32.0f
#define OFFSET_DANGER_X_TO_HAND_RIGHT_SIMON 0
#define OFFSET_DANGER_Y_TO_HAND_SIMON 5.0f

class WeaponDanger : public Weapon {

private:
	bool isDeath;
	DWORD makeTime;
public:
	WeaponDanger(float x, float y, int nx);
	void Render();
	void RenderFlipX();
	void SetPositionWithSimon(float x, float y, int nx);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	bool GetLastFrame()
	{
		if (animations[DANGER_ANI]->getLastFrame())
			return  true;
		return false;
	}
	void ResetAnimation()
	{
		animations[DANGER_ANI]->reset();
	}
	bool getDeath()
	{
		return isDeath;
	}
};