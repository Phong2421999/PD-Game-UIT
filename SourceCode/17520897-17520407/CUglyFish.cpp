#pragma once
#include "CUglyFish.h"

CUglyFish::CUglyFish(float x, float y)
{
	this->AddAnimation(ANI_FISH_IDLE);
	this->AddAnimation(ANI_FISH_MOVING);
	this->AddAnimation(ANI_FISH_ATTACK);
	ani = ANI_ID_FISH_IDLE;
	this->width = FISH_WIDTH;
	this->height = FISH_HEIGHT;
	vy = -FISH_VELOCITY_Y;
	CSimon::getInstance()->GetPosition(sx, sy);

	int random = rand() % 2;
	if (random == 1)
	{
		nx = 1;
		this->x = sx - 32;
	}
	else
	{
		nx = -1;
		this->x = sx + 96;
	}
	this->y = y + SCREEN_HEIGHT;
	startSpawnTime = GetTickCount();
	lastAttackTime = GetTickCount();
	isJumpUp = true;
	isCanAttack = false;
	attackQuantity = 0;
	attackDistance = 0;
}

void CUglyFish::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	DWORD now = GetTickCount();
	CSimon* simon = CSimon::getInstance();
	CSimon::getInstance()->GetPosition(sx, sy);

	CGameObject::Update(dt);
	if (now - startSpawnTime >= FISH_TIME_ACTIVE)
		isActive = true;

	if (y < 100 && isJumpUp)
	{
		isJumpUp = false;
	}

	if (nx > 0)
	{
		attackDistance = sx - this->x;
	}
	else
		attackDistance = this->x - sx;

	if (isJumpUp == false)
	{
		vy += FISH_GRAVITY * dt;

		if (now - lastAttackTime >= 2000 && isCanAttack == false)
		{
			isCanAttack = true;
			resetAttackTime = GetTickCount();
		}

		if (isCanAttack)
		{
			if (now - resetAttackTime >= 500)
			{
				isCanAttack = false;
				this->makeWeapon = true;
				lastAttackTime = GetTickCount();
				attackQuantity++;
			}
			ani = ANI_ID_FISH_ATTACK;
			vx = 0;
		}
		else
		{
			ani = ANI_ID_FISH_MOVING;
			this->makeWeapon = false;

			if (attackQuantity > 2)
			{
				attackQuantity = 0;

				if (y <= sy)
				{
					if (x - sx >= 0)
						nx = -1;
					else
						nx = 1;
				}
				else
				{
					if (nx > 0)
						nx = -1;
					else
						nx = 1;
				}

			}

			if (nx > 0)
			{
				vx = FISH_VELOCITY_X;
			}
			else
				vx = -FISH_VELOCITY_X;

		}
	}


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
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	if (this->checkAABBTouch(simon) && simon->getUntouchable() == false)
	{
		CSimon::getInstance()->TouchEnemy(this->nx);
		CSimon::getInstance()->Damage(1);
	}
}


void CUglyFish::Render() {
	if (nx < 0)
	{
		animations[ani]->Render(x, y);
	}
	else
	{
		animations[ani]->RenderFlipX(x, y, 8);
	}
	RenderBoundingBox(x, y);
}

void CUglyFish::RenderCurrentFrame()
{
	if (nx < 0)
	{
		animations[ani]->RenderCurrentFrame(x, y);
	}
	else
		animations[ani]->RenderCurrentFrameFlipX(x, y, 8);
}


void CUglyFish::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	if (isJumpUp)
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
	else
	{
		left = x;
		top = y;
		right = x + width;
		bottom = y + height;
	}
}