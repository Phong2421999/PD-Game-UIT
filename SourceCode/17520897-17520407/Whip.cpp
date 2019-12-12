#include "Whip.h"

Whip::Whip(float x, float y, int nx, int level)
{
	SetSpeed(WHIP_SPEED_X, WHIP_SPEED_Y);
	SetRenderPos(x, y);
	curLevel = level;
	SetPositionWithSimon(x, y, nx);
	this->nx = nx;
	this->curLevel = level;
	SetTimeLive(WHIP_TIME_LIVE);
	this->AddAnimation(WHIP_ANI_LEVEL_1);
	this->AddAnimation(WHIP_ANI_LEVEL_2);
	this->AddAnimation(WHIP_ANI_LEVEL_3);
	isTouchHiddenWall = false;
	isTouchEnemy = false;
}

void Whip::Render()
{
	int ani;
	switch (curLevel)
	{
	case WHIP_LEVEL_1:
		ani = WHIP_ANI_LEVEL_1_ID;
		break;
	case WHIP_LEVEL_2:
		ani = WHIP_ANI_LEVEL_2_ID;
		break;
	case WHIP_LEVEL_3:
		ani = WHIP_ANI_LEVEL_3_ID;
		break;
	}
	if (nx > 0)
	{
		animations[ani]->Render(xRender, yRender);
		RenderBoundingBox(x, y);
	}
	else
	{
		animations[ani]->RenderFlipX(xRender, yRender, 24);
		RenderBoundingBox(x + 15.0f, y);
	}
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	int ani;
	float width;
	SetPositionWithSimon(x, y, this->nx);
	switch (curLevel)
	{
	case WHIP_LEVEL_1:
		ani = WHIP_ANI_LEVEL_1_ID;
		width = WHIP_BBOX_LEVEL1_WIDTH;
		break;
	case WHIP_LEVEL_2:
		ani = WHIP_ANI_LEVEL_2_ID;
		width = WHIP_BBOX_LEVEL2_WIDTH;
		break;
	case WHIP_LEVEL_3:
		ani = WHIP_ANI_LEVEL_3_ID;
		width = WHIP_BBOX_LEVEL3_WIDTH;
		break;
	}
	if (animations[ani]->getNextIsLastFrame())
	{
		SetWidthHeigth(width, WHIP_BBOX_HEIGHT);
		if (coObjects->size() >= 0)
		{
			for (int i = 0; i < coObjects->size(); i++)
			{
				if (isTouchOtherObject(coObjects->at(i)))
				{
					if ((dynamic_cast<CEnemies*>(coObjects->at(i)))
						&& isTouchEnemy == false)
					{
						CEnemies* enemies = dynamic_cast<CEnemies*>(coObjects->at(i));
						if (enemies->GetSimonHasTouch() > 0)
							isTouchEnemy = true;
						coObjects->at(i)->Damage(1);
						coObjects->at(i)->SetKillBySimon(true);
					}
					if (dynamic_cast<CStaticObject*>(coObjects->at(i)))
					{
						coObjects->at(i)->Damage(1);
						coObjects->at(i)->SetKillBySimon(true);
					}
					if (dynamic_cast<CHiddenWall*>(coObjects->at(i))
						&& isTouchHiddenWall == false)
					{
						coObjects->at(i)->Damage(1);
						coObjects->at(i)->SetKillBySimon(true);
						isTouchHiddenWall = true;
					}
				}
			}
		}
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
	int offSetLeft, offSetRight;
	switch (curLevel)
	{
	case WHIP_LEVEL_1:
		offSetLeft = WHIP_OFFSET_X_TO_HAND_LEFT_SIMON_LEVEL_1;
		offSetRight = WHIP_OFFSET_X_TO_HAND_RIGHT_SIMON_LEVEL_1;
		break;
	case WHIP_LEVEL_2:
		offSetLeft = WHIP_OFFSET_X_TO_HAND_LEFT_SIMON_LEVEL_2;
		offSetRight = WHIP_OFFSET_X_TO_HAND_RIGHT_SIMON_LEVEL_2;
		break;
	case WHIP_LEVEL_3:
		offSetLeft = WHIP_OFFSET_X_TO_HAND_LEFT_SIMON_LEVEL_3;
		offSetRight = WHIP_OFFSET_X_TO_HAND_RIGHT_SIMON_LEVEL_3;
		break;
	}

	if (nx > 0)
	{
		SetPosition(x + offSetRight, y + WHIP_OFFSET_Y_TO_HAND_SIMON);
	}
	else
	{
		SetPosition(x - offSetLeft, y + WHIP_OFFSET_Y_TO_HAND_SIMON);
	}
}

