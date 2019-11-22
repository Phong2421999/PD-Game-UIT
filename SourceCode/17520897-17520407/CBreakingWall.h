#pragma once
#include "CEffect.h"
#define ANI_BREAKING_WALL 562
#define ANI_BREAKING_WALL_ID 0

class CBreakingWall :public CEffect {

public:
	CBreakingWall(float x, float y);
	void Render();
};