#pragma once
#include "CEnemies.h"
#include "Simon.h"
#include "Ground.h"

#define ANI_GHOST 565
#define GHOST_ACTIVE_TIME 500
#define GHOST_OFFSET_FLIP_X 8

#define GHOST_WIDTH 16
#define GHOST_HEIGHT 32

#define GHOST_GRAVITY 0.005
#define GHOST_VELOCITY_X 0.06

#define GHOST_OFFSET_X 16
#define GHOST_OFFSET_Y 8

#define GHOST_SPAWN_POSITION_Y 128
#define GHOST_SPAWN_GRAVITY 100


class CGhost : public CEnemies {
private:
	int width, height;
	DWORD startSpawnTime;
public:
	CGhost(float x, float y);
	void Render();
	void RenderCurrentFrame();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
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
	int GetNx()
	{
		return nx;
	}
};
