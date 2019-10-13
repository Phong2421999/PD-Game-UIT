#include "Whip.h"

Whip::Whip(float x, float y, int nx)
{
	SetSpeed(WHIP_SPEED_X, WHIP_SPEED_Y);
	SetTimeLive(WHIP_TIME_LIVE);
	SetRenderPos(x, y);
	SetPositionWithSimon(x, y, nx);
	this->nx = nx;
	this->AddAnimation(WHIP_ANI_LEVEL_1_ID);
}

void Whip::Render()
{
	if (nx > 0)
	{
		animations[WHIP_ANI_LEVEL_1]->Render(xRender, yRender);
		RenderBoundingBox(x, y);

	}
	else
	{
		animations[WHIP_ANI_LEVEL_1]->RenderFlipX(xRender, yRender, 24);
		RenderBoundingBox(x + 15.0f, y);
	}
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	if (animations[WHIP_ANI_LEVEL_1]->getNextIsLastFrame())
	{
		SetWidthHeigth(WHIP_BBOX_LEVEL1_WIDTH, WHIP_BBOX_HEIGHT);
		Weapon::Update(dt, coObjects);
	}
}

void Whip::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (nx > 0)
	{
		left = x;
		top = y;
		right = x + width;
		bottom = y + height;
	}
	else
	{
		left = x + 15.0f;
		top = y;
		right = x + 15.0f+width;
		bottom = y + height;
	}

}

void Whip::SetPositionWithSimon(float x, float y, int nx)
{
	if (nx > 0)
	{
		SetPosition(x + WHIP_OFFSET_X_TO_HAND_LEFT_SIMON, y + WHIP_OFFSET_Y_TO_HAND_SIMON);
	}
	else
	{
		SetPosition(x - WHIP_OFFSET_X_TO_HAND_RIGHT_SIMON, y + WHIP_OFFSET_Y_TO_HAND_SIMON);
	}
}

