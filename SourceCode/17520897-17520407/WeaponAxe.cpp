#include "WeaponAxe.h"

WeaponAxe::WeaponAxe(float x, float y, int nx)
{
	this->AddAnimation(AXE_ANI);
	if (nx > 0)
		vx = AXE_SPEED_X;
	else
		vx = -AXE_SPEED_X;
	this->nx = nx;
	vy = -AXE_SPEED_Y;
	SetTimeLive(AXE_WEAPON_TIME_LIVE);
	SetPositionWithSimon(x, y, nx);
	SetWidthHeigth(AXE_BBOX_WIDTH, AXE_BBOX_HEIGHT);
	CSimon::getInstance()->GetPosition(sx, sy);
	makeTime = GetTickCount();
	health = 1;
	isTouchEnemy = false;
}

void WeaponAxe::SetPositionWithSimon(float x, float y, int nx)
{
	if (nx > 0)
	{
		SetPosition(x + OFFSET_AXE_X_TO_HAND_RIGHT_SIMON, y + OFFSET_AXE_Y_TO_HAND_SIMON);
	}
	else
	{
		SetPosition(x - OFFSET_AXE_X_TO_HAND_LEFT_SIMON, y + OFFSET_AXE_Y_TO_HAND_SIMON);

	}
}

void WeaponAxe::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if(y < sy - AXE_FLY_DISTANCE_Y)
		vy += AXE_GRAVITY * dt;

	dx = vx * dt;
	dy = vy * dt;
	y += dy;
	x += dx;

	DWORD now = GetTickCount();
	if (now - makeTime > AXE_WEAPON_TIME_LIVE)
	{
		health = 0;
	}

	if (coObjects->size() >= 0)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (isTouchOtherObject(coObjects->at(i)))
			{
				if ((dynamic_cast<CEnemies*>(coObjects->at(i))
					|| dynamic_cast<CStaticObject*>(coObjects->at(i)))
					&& isTouchEnemy == false)
				{
					coObjects->at(i)->Damage(1);
					coObjects->at(i)->SetKillBySimon(true);
					isTouchEnemy = true;
				}
				if (dynamic_cast<CGround*>(coObjects->at(i))) {
					health = 0;
				}
			}
		}
	}

}

void WeaponAxe::Render()
{
	if (nx > 0)
	{
		animations[AXE_ANI_ID]->Render(x, y);
		RenderBoundingBox(x, y);
	}
	else
	{
		animations[AXE_ANI_ID]->RenderFlipX(x, y, 8.5f);
		RenderBoundingBox(x, y);
	}

}

void  WeaponAxe::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;

}