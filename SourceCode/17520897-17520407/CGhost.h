#pragma once
#include "CEnemies.h"
#define ANI_GHOST 565
#define GHOST_WIDTH 16
#define GHOST_HEIGHT 32

class CGhost : public CEnemies {
private:
	int width, height;
	DWORD startSpawnTime;
public:
	CGhost();
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
