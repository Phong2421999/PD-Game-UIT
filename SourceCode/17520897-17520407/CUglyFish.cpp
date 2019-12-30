#pragma once
#include "CUglyFish.h"
#include "Simon.h"


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
	if (sx + SCREEN_WIDTH / 2 > SCENCE_WITDH)
	{
		nx = 1;
		this->x = sx - FISH_OFFSET_SPAWN_LEFT;
	}
	else
	{
		if (random == 1)
		{
			nx = 1;
			this->x = sx - FISH_OFFSET_SPAWN_LEFT;
		}
		else
		{
			nx = -1;
			this->x = sx + FISH_OFFSET_SPAWN_RIGHT;
		}

	}

	this->y = y + SCREEN_HEIGHT;
	lastAttackTime = GetTickCount();
	isJumpUp = true;
	isCanAttack = false;
	attackQuantity = 0;
	attackDistance = 0;
	weapon = nullptr;
}

void CUglyFish::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	DWORD now = GetTickCount();
	CSimon* simon = CSimon::getInstance();
	CSimon::getInstance()->GetPosition(sx, sy);
	CGameObject::Update(dt);

	if (weapon)
	{
		if (weapon->GetHealth() <= 0)
		{
			delete weapon;
			weapon = NULL;
		}
		else
			weapon->Update(dt);
	}

	if (y < 100 && isJumpUp)
	{
		isJumpUp = false;
		isActive = true;
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
				weapon = new WeaponProjectile(x, y, nx);
				if (nx > 0)
					weapon->SetPositionWithEnemey(MAKE_WEAPON_OFFSET);
				else
					weapon->SetPositionWithEnemey(MAKE_WEAPON_OFFSET_FLIP);
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
				if (abs(x - sx) > 80)
				{
					if (x < sx)
						nx = 1;
					else
						nx = -1;
				}
			}
			else
			{
				if (abs(x - sx) > 80)
				{
					if (x < sx)
						nx = 1;
					else
						nx = -1;
				}
			}

			/*if (y <= sy)
			{*/

			/*}
			else
			{
				if (nx > 0)
					nx = -1;
				else
					nx = 1;
			}*/

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
		vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGround *>(e->obj))
			{
				CGround * ground = dynamic_cast<CGround *>(e->obj);
				ground->GetPosition(xGround, yGround);
				if (y > yGround)
				{
					vy += 0.00003 * dt;
				}
			}
		}

	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	if (this->checkAABBTouch(simon) && simon->getUntouchable() == false)
	{
		if (CSimon::getInstance()->getDeath() == false)
		{
			CSimon::getInstance()->TouchEnemy(this->nx);
			CSimon::getInstance()->Damage(1);
		}
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
	if (weapon)
		weapon->Render();
	RenderBoundingBox(x, y);
}

void CUglyFish::RenderCurrentFrame()
{
	if (weapon)
		weapon->RenderCurrentFrame();
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