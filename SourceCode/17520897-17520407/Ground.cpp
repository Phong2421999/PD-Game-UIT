#pragma once
#include "Ground.h"
#include "FrameWork/debug.h"

void CGround::Render()
{
	//animations[0]->Render(x, y);
	RenderBoundingBox(x,y);
}

void CGround::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x; //0
 	top = y; // 50
	right = x + width; //700
	bottom = y + height; // 58

	//r - l =700 b-t = 7= 8;
}