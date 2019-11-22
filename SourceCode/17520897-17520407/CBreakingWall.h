#pragma once
#include "CEffect.h"
#define ANI_BREAKING_WALL 562
#define ANI_BREAKING_WALL_ID 0


#define BREAKING_WALL_OFFSET_LEFT 8
#define BREAKING_WALL_OFFSET_RIGHT 16

#define BREAKING_WALL_VELOCITY_X 0.035
#define BREAKING_WALL_VELOCITY_y 0.03
#define BREAKING_WALL_GRAVITY 0.0003

#define BREAKING_WALL_OFFSET_X 8

#define QUANTITY_EFFECT_WALL 4

class CBreakingWall :public CEffect {

public:
	CBreakingWall(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>*coObjects);
	void reset();
};