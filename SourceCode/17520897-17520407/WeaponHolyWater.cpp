#include "WeaponHolyWater.h"

WeaponHolyWater::WeaponHolyWater(float x, float y, int nx)
{
	this->AddAnimation(HOLY_WATER_ANI);
	this->AddAnimation(HOLY_WATER_BURNING_ANI);
	ani = HOLY_WATER_ANI_ID;
	if (nx > 0)
		vx = HOLY_WATER_SPEED_X;
	else
		vx = -HOLY_WATER_SPEED_X;
	this->nx = nx;
	vy = -HOLY_WATER_SPEED_Y;
	SetTimeLive(HOLY_WATER_WEAPON_TIME_LIVE);
	SetPositionWithSimon(x, y, nx);
	SetWidthHeigth(HOLY_WATER_BBOX_WIDTH, HOLY_WATER_BBOX_HEIGHT);
	isDeath = false;
	CSimon::getInstance()->GetPosition(sx, sy);
	makeTime = GetTickCount();
	health = 1;
}

void WeaponHolyWater::SetPositionWithSimon(float x, float y, int nx)
{
	if (nx > 0)
	{
		SetPosition(x + OFFSET_HOLY_WATER_X_TO_HAND_RIGHT_SIMON, y + OFFSET_HOLY_WATER_Y_TO_HAND_SIMON);
	}
	else
	{
		SetPosition(x - OFFSET_HOLY_WATER_X_TO_HAND_LEFT_SIMON, y + OFFSET_HOLY_WATER_Y_TO_HAND_SIMON);

	}
}

void WeaponHolyWater::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (y < sy - HOLY_WATER_FLY_DISTANCE_Y)
	{
		vy += HOLY_WATER_GRAVITY * dt;
	}

	//DWORD now = GetTickCount();
	//if (now - makeTime > HOLY_WATER_WEAPON_TIME_LIVE)
	//{
	//	health = 0;
	//}

	dx = vx * dt;
	dy = vy * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{

		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);// block
		x += min_tx * dx + nx * 0.4f;	// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;
		vx = 0;
		vy = 0;
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
				if (dynamic_cast<CGround*>(coObjects->at(i))) {
					ani = HOLY_WATER_BURNING_ANI_ID;
					if (animations[ani]->getLastFrame())
					{
						health = 0;
					}
				}
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void WeaponHolyWater::Render()
{
	if (nx > 0)
	{
		animations[ani]->Render(x, y);
		RenderBoundingBox(x, y);
	}
	else
	{
		animations[ani]->RenderFlipX(x, y, 8.5f);
		RenderBoundingBox(x, y);
	}

}

void  WeaponHolyWater::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;

}