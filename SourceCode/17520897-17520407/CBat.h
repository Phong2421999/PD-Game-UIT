#pragma once
#include "CEnemies.h"
#include "Simon.h"
#define ANI_BAT_IDLE 569
#define ANI_BAT_FLY 570

#define ANI_ID_BAT_IDLE 0
#define ANI_ID_BAT_FLY 1

#define BAT_ACTIVE_TIME 2000

#define BAT_OFFSET_FLIP_X 8
#define BAT_FLY_DISTANCE_Y 8

#define BAT_VELOCITY_X 0.03
#define BAT_VELOCITY_Y 0.03

#define BAT_WIDTH 16
#define BAT_HEIGHT 16

class CBat :public CEnemies
{
private:
	int width, height, ani;
	DWORD startSpawnTime;

public:
	CBat(float x, float y);
	void Render();
	void RenderCurrentFrame();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	bool IsTouchSimon(LPGAMEOBJECT gameObject);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetPosition(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	void GetPosition(float &x, float &y)
	{
		x = this->x;
		y = this->y;
	}
};
