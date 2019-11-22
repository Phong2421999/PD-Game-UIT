#pragma once
#include "CBreakingWall.h"

CBreakingWall::CBreakingWall(float x, float y)
{
	this->AddAnimation(ANI_BREAKING_WALL);
	this->x = x;
	this->y = y;
}

void CBreakingWall::Render() {
	animations[ANI_BREAKING_WALL_ID]->Render(x, y);
}