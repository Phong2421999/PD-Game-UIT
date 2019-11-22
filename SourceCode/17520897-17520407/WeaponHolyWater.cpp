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
	SetPositionWithSimon(x, y, nx);
	SetWidthHeigth(HOLY_WATER_BBOX_WIDTH, HOLY_WATER_BBOX_HEIGHT);
	CSimon::getInstance()->GetPosition(sx, sy);
	health = 1;
	isGrounded = false;
	isFalling = false;
}

void WeaponHolyWater::SetPositionWithSimon(float x, float y, int nx)
{
	if (nx > 0)
	{
		SetPosition(x + OFFSET_HOLY_WATER_X_TO_HAND_RIGHT_SIMON, y + OFFSET_HOLY_WATER_Y_TO_HAND_SIMON);
	}
	else
	{
		SetPosition(x + OFFSET_HOLY_WATER_X_TO_HAND_LEFT_SIMON, y + OFFSET_HOLY_WATER_Y_TO_HAND_SIMON);

	}
}

void WeaponHolyWater::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	DWORD now = GetTickCount();


	if (nx > 0)
	{
		if (x > sx + 20) 
			vy += HOLY_WATER_GRAVITY * dt;
	}
	else
	{
		if (x < sx - 2)
			vy += HOLY_WATER_GRAVITY * dt;
	}

	dx = vx * dt;
	dy = vy * dt;

	if (isGrounded)
	{
		if (now - makeTime > HOLY_WATER_POND_TIME_LIVE)
		{
			health = 0;
			animations[ani]->reset();
		}
	}
	else
	{
		x += dx;
		y += dy;
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
				}
				if (dynamic_cast<CGround*>(coObjects->at(i))) {
					if (isGrounded == false)
					{
						y -= dy;
						isGrounded = true;
						width = HOLY_WATER_POND_BBOX_WIDTH;
						height = HOLY_WATER_POND_BBOX_HEIGHT;
						y -= HOLY_WATER_BBOX_HEIGHT;
						makeTime = GetTickCount();
						ani = HOLY_WATER_BURNING_ANI_ID;
					}
				}
			}

		}
	}
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
		if (isGrounded)
			animations[ani]->RenderFlipX(x, y, 10);
		else
			animations[ani]->RenderFlipX(x, y, 4);
		RenderBoundingBox(x, y);
	}

}

void  WeaponHolyWater::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;

}