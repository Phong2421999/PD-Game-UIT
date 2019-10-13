#include "WeaponDanger.h"

WeaponDanger::WeaponDanger(float x, float y, int nx)
{
	if (nx > 0)
		vx = DANGER_SPEED_X;
	else
		vx = -DANGER_SPEED_X;
	this->nx = nx;
	SetTimeLive(DANGER_TIME_LIVE);
	SetRenderPos(x, y);
	SetPositionWithSimon(x, y, nx);
	SetWidthHeigth(20.0f, 8.0f);
	this->AddAnimation(DANGER_ANI_ID);
	isDeath = false;
	makeTime = GetTickCount();
	health = 1;
} 

void WeaponDanger::SetPositionWithSimon(float x, float y, int nx)
{
	if (nx > 0)
	{
		SetPosition(x + OFFSET_DANGER_X_TO_HAND_RIGHT_SIMON, y );
	}
	else
	{
		SetPosition(x  - OFFSET_DANGER_X_TO_HAND_LEFT_SIMON, y );

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
	animations[DANGER_ANI]->Render(xRender, yRender);
	RenderBoundingBox(x, y);
}

void WeaponDanger::RenderFlipX()
{

	animations[DANGER_ANI]->RenderFlipX(xRender, yRender, 8.5f);

	RenderBoundingBox(x, y);
}

void WeaponDanger::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (isDeath == false)
	{
		dx = vx * dt;
		x += dx;
		if (health <= 0)
		{
			isDeath = true;
		}
		else
		{
			DWORD now = GetTickCount();
			if (now - makeTime > DANGER_TIME_LIVE)
			{
				isDeath = true;
			}
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
						health = 0;
					}
				}
			}
		}
	}

}