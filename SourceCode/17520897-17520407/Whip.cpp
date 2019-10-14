#include "Whip.h"

Whip::Whip(float x, float y, int nx, int level)
{
	SetSpeed(WHIP_SPEED_X, WHIP_SPEED_Y);
	SetTimeLive(WHIP_TIME_LIVE);
	SetRenderPos(x, y);
	SetPositionWithSimon(x, y, nx);
	this->nx = nx;
	this->curLevel = level;
	this->AddAnimation(WHIP_ANI_LEVEL_1);
	this->AddAnimation(WHIP_ANI_LEVEL_2);
	this->AddAnimation(WHIP_ANI_LEVEL_3);
	curLevel = level;
	DebugOut(L"\nlevel = %d", curLevel);
}

void Whip::Render()
{
	if (nx > 0)
	{
		switch (curLevel)
		{
		case 1:
			animations[WHIP_ANI_LEVEL_1_ID]->Render(xRender, yRender);
			break;
		case 2:
			animations[WHIP_ANI_LEVEL_2_ID]->Render(xRender, yRender);
			break;
		case 3:
			animations[WHIP_ANI_LEVEL_3_ID]->Render(xRender, yRender);
			break;
		}
		RenderBoundingBox(x, y);
	}
	else
	{
		switch (curLevel)
		{
		case 1:
			animations[WHIP_ANI_LEVEL_1_ID]->RenderFlipX(xRender, yRender, 24);
			break;
		case 2:
			animations[WHIP_ANI_LEVEL_2_ID]->RenderFlipX(xRender, yRender, 24);
			break;
		case 3:
			animations[WHIP_ANI_LEVEL_3_ID]->RenderFlipX(xRender, yRender, 24);
			break;
		}
		RenderBoundingBox(x + 15.0f, y);
	}
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (isJump)
	{
		x += dx;
		y += dy;
		xRender += dx;
		yRender += dy;
	}
	int ani;
	float width;
	switch (curLevel)
	{
	case 1:
		ani = 0;
		width = WHIP_BBOX_LEVEL1_WIDTH;
		break;
	case 2:
		ani = 1;
		width = WHIP_BBOX_LEVEL2_WIDTH;
		break;
	case 3:
		ani = 2;
		width = WHIP_BBOX_LEVEL3_WIDTH;
		break;
	}
	if (animations[ani]->getNextIsLastFrame())
	{
		SetWidthHeigth(width, WHIP_BBOX_HEIGHT);
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
		right = x + 15.0f + width;
		bottom = y + height;
	}

}

void Whip::SetPositionWithSimon(float x, float y, int nx)
{
	if (nx > 0)
	{
		SetPosition(x + WHIP_OFFSET_X_TO_HAND_RIGHT_SIMON, y + WHIP_OFFSET_Y_TO_HAND_SIMON);
	}
	else
	{
		SetPosition(x - WHIP_OFFSET_X_TO_HAND_LEFT_SIMON, y + WHIP_OFFSET_Y_TO_HAND_SIMON);
	}
}

