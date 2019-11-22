#pragma once
#include "CBreakingWall.h"

CBreakingWall::CBreakingWall(float x, float y)
{
	this->AddAnimation(ANI_BREAKING_WALL);
	int random = rand() % 4;
	if (random == 1)
	{
		this->vx = -BREAKING_WALL_VELOCITY_X;
		this->vy = -BREAKING_WALL_VELOCITY_y - 0.002;
	}
	else if (random == 2)
	{
		this->vx = BREAKING_WALL_VELOCITY_X + 0.01;
		this->vy = -BREAKING_WALL_VELOCITY_y + 0.01;
	}
	else if (random == 3)
	{
		this->vx = -BREAKING_WALL_VELOCITY_X + 0.003;
		this->vy = -BREAKING_WALL_VELOCITY_y + 0.003;
	}
	else
	{
		this->vx = 0;
		this->vy = -BREAKING_WALL_VELOCITY_y;
	}
	this->x = x;
	this->y = y;
}

void CBreakingWall::Update(DWORD dt, vector<LPGAMEOBJECT>*coObjects) {
	vy += BREAKING_WALL_GRAVITY * dt;
	dx = vx * dt;
	dy = vy * dt;
	x += dx;
	y += dy;
}

void CBreakingWall::Render() {
	animations[ANI_BREAKING_WALL_ID]->Render(x, y);
}

void CBreakingWall::reset() {
	animations[0]->reset();
}