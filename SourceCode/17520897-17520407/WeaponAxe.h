#pragma once
#include "Weapon.h"
#include "Simon.h"

#define AXE_SPEED_X 0.1
#define AXE_SPEED_Y 0.1
#define AXE_BBOX_WIDTH 15
#define AXE_BBOX_HEIGHT 15

#define AXE_GRAVITY 0.0004
#define AXE_FLY_DISTANCE_Y 25

#define AXE_WEAPON_TIME_LIVE 2000

#define AXE_ANI 644

#define AXE_ANI_ID 0
#define OFFSET_AXE_X_TO_HAND_LEFT_SIMON 4.0f
#define OFFSET_AXE_X_TO_HAND_RIGHT_SIMON 28.0f
#define OFFSET_AXE_Y_TO_HAND_SIMON -8.0f

class WeaponAxe : public Weapon {

private:
	float sx, sy;
	bool isDeath;
	DWORD makeTime;
public:
	WeaponAxe(float x, float y, int nx);
	void Render();
	void SetPositionWithSimon(float x, float y, int nx);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	bool GetLastFrame()
	{
		if (animations[AXE_ANI_ID]->getLastFrame())
			return  true;
		return false;
	}
	void ResetAnimation()
	{
		animations[AXE_ANI_ID]->reset();
	}
	bool getDeath()
	{
		return isDeath;
	}
};