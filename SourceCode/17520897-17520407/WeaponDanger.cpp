#include "WeaponDanger.h"

WeaponDanger::WeaponDanger(float x, float y, int nx)
{
	this->AddAnimation(DANGER_ANI);
	if (nx > 0)
		vx = DANGER_SPEED_X;
	else
		vx = -DANGER_SPEED_X;
	this->nx = nx;
	SetTimeLive(DANGER_WEAPON_TIME_LIVE);
	SetPositionWithSimon(x, y, nx);
	SetWidthHeigth(DANGER_BBOX_WIDTH, DANGER_BBOX_HEIGHT);
	isDeath = false;
	makeTime = GetTickCount();
	health = 1;
}

void WeaponDanger::SetPositionWithSimon(float x, float y, int nx)
{
	if (nx > 0)
	{
		SetPosition(x + OFFSET_DANGER_X_TO_HAND_RIGHT_SIMON, y + OFFSET_DANGER_Y_TO_HAND_SIMON);
	}
	else
	{
		SetPosition(x - OFFSET_DANGER_X_TO_HAND_LEFT_SIMON, y + OFFSET_DANGER_Y_TO_HAND_SIMON);

	}
}

void  WeaponDanger::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;

}

void WeaponDanger::Render()
{
	if (nx > 0)
	{
		animations[DANGER_ANI_ID]->Render(x, y);
		RenderBoundingBox(x, y);
	}
	else
	{
		animations[DANGER_ANI_ID]->RenderFlipX(x, y, 8.5f);
		RenderBoundingBox(x, y);
	}

}


void WeaponDanger::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	dx = vx * dt;
	x += dx;


	DWORD now = GetTickCount();
	if (now - makeTime > DANGER_WEAPON_TIME_LIVE)
	{
		health = 0;
	}

	if (coObjects->size() >= 0)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (isTouchOtherObject(coObjects->at(i)))
			{
				if (dynamic_cast<CEnemies*>(coObjects->at(i))
					|| dynamic_cast<CStaticObject*>(coObjects->at(i)))
				{
					coObjects->at(i)->Damage(1);
					coObjects->at(i)->SetKillBySimon(true);
					health = 0;
				}
			}
		}
	}

}