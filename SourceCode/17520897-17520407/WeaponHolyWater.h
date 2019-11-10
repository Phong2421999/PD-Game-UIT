#pragma once
#include "Weapon.h"
#include "Simon.h"

#define HOLY_WATER_SPEED_X 0.09
#define HOLY_WATER_SPEED_Y 0.08
#define HOLY_WATER_BBOX_WIDTH 16
#define HOLY_WATER_BBOX_HEIGHT 12

#define HOLY_WATER_GRAVITY 0.003
#define HOLY_WATER_FLY_DISTANCE_Y 25

#define HOLY_WATER_WEAPON_TIME_LIVE 2000

#define HOLY_WATER_ANI 550
#define HOLY_WATER_BURNING_ANI 551

#define HOLY_WATER_ANI_ID 0
#define HOLY_WATER_BURNING_ANI_ID 1

#define OFFSET_HOLY_WATER_X_TO_HAND_LEFT_SIMON 4.0f
#define OFFSET_HOLY_WATER_X_TO_HAND_RIGHT_SIMON 28.0f
#define OFFSET_HOLY_WATER_Y_TO_HAND_SIMON -8.0f

class WeaponHolyWater : public Weapon {

private:
	int ani;
	float sx, sy;
	bool isDeath;
	DWORD makeTime;
public:
	WeaponHolyWater(float x, float y, int nx);
	void Render();
	void SetPositionWithSimon(float x, float y, int nx);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	bool GetLastFrame()
	{
		if (animations[ani]->getLastFrame())
			return  true;
		return false;
	}
	void ResetAnimation()
	{
		animations[ani]->reset();
	}
	bool getDeath()
	{
		return isDeath;
	}
};