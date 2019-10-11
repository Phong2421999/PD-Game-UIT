#include "CEnemies.h"

#include "FrameWork/debug.h"

void CEnemies::Render()
{
	//animations[0]->Render(x, y);
	RenderBoundingBox();
}

void CEnemies::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x; 
	top = y; 
	right = x + width; 
	bottom = y + height;

}

void CEnemies::Damage()
{
	this->health--;
}