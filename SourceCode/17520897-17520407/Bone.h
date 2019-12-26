#pragma once
#include "WeaponEnemies.h"

#define BONE_ANI 576

#define BONE_ANI_INDEX 0

#define BONE_SPEED_X 0.09f
#define BONE_SPEED_Y 0.12f
#define BONE_BBOX_WIDTH 16
#define BONE_BBOX_HEIGHT 16

#define BONE_WEAPON_TIME_LIVE 2000

#define BONE_GRAVITY 0.0004

#define TIME_LIVE 2000

class Bone : public WeaponEnemies {

private:
	DWORD makeTime;
public:
	Bone(float x, float y, int nx);
	void Render();
	void RenderCurrentFrame();
	void SetPositionWithFish(float x, float y, int nx);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

};
