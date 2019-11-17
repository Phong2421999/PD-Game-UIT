#pragma once
#include "WeaponEnemies.h"

#define PROJECTILE_ANI 574
#define PROJECTILE_ANI_ID  0

#define PROJECTILE_SPEED_X 0.09
#define PROJECTILE_SPEED_Y 0
#define PROJECTILE_BBOX_WIDTH 8
#define PROJECTILE_BBOX_HEIGHT 6

#define PROJECTILE_WEAPON_TIME_LIVE 2000


#define OFFSET_DANGER_X_TO_HAND_LEFT_SIMON 4.0f
#define OFFSET_DANGER_X_TO_HAND_RIGHT_SIMON 28.0f
#define OFFSET_DANGER_Y_TO_HAND_SIMON 7.0f

class WeaponProjectile :public WeaponEnemies {

private:
	bool isDeath;
	DWORD makeTime;
public:
	WeaponProjectile(float x, float y, int nx);
	void Render();
	void RenderCurrentFrame();
	void SetPositionWithFish(float x, float y, int nx);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	bool getDeath()
	{
		return isDeath;
	}
};