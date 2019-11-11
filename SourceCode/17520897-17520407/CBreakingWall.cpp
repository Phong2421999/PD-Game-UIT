#pragma once
#include "CBreakingWall.h"

CBreakingWall::CBreakingWall()
{
	this->AddAnimation(ANI_BREAKING_WALL);
}

void CBreakingWall::Render() {
	animations[ANI_BREAKING_WALL_ID]->Render(x, y);
}