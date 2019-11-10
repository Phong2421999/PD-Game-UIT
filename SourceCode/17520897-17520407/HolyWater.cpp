#include"HolyWater.h"


HolyWater::HolyWater(float x, float y)
{
	this->AddAnimation(ANI_HOLY_WATER);
	this->x = x;
	this->y = y;
	this->width = HOLY_WATER_WIDTH;
	this->height = HOLY_WATER_HEIGHT;
	type = HOLY_WATER_ITEM;
	makeTime = GetTickCount();
}


void HolyWater::Render() {
	animations[ANI_HOLY_WATER_ID]->Render(x, y);
	RenderBoundingBox(x, y);
}

void HolyWater::RenderCurrentFrame() {
	animations[ANI_HOLY_WATER_ID]->RenderCurrentFrame(x, y);
}

void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItems::Update(dt, coObjects);

	DWORD now = GetTickCount();
	if (now - makeTime > HOLY_WATER_TIME_LIVE)
	{
		health = 0;
	}
}

void HolyWater::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}