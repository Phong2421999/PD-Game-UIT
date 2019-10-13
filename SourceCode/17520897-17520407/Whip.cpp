#include "Whip.h"

Whip::Whip(float x, float y, int nx)
{
	SetSpeed(WHIP_SPEED_X, WHIP_SPEED_Y);
	SetTimeLive(WHIP_TIME_LIVE);
	SetPositionWithSimon(x, y, nx);
	this->AddAnimation(WHIP_ANI_LEVEL_1_ID);
}

void Whip::Render()
{
	animations[WHIP_ANI_LEVEL_1]->Render(xRender,yRender);
	RenderBoundingBox(x, y);
}

void Whip::RenderFlipX()
{
	animations[WHIP_ANI_LEVEL_1]->RenderFlipX(xRender, yRender);
	RenderBoundingBox(x, y);
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	if (animations[WHIP_ANI_LEVEL_1]->getLastFrame())
	{
		SetWidthHeigth(WHIP_BBOX_LEVEL1_WIDTH, WHIP_BBOX_HEIGHT);
		Weapon::Update(dt, coObjects);
	}
}

