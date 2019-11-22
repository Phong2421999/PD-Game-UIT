#include "CheckGround.h"
#include "Simon.h"

void CheckGround::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	CSimon* simon = CSimon::getInstance()->getInstance();
	vx = simon->vx;
	vy = simon->vy;
	this->x = this->x + 15;
	if (simon->getSit() || simon->getJump())
		this->y = this->y + SIMON_SIT_BBOX_HEIGHT - this->height;
	else
		this->y = this->y + SIMON_BBOX_HEIGHT - this->height;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	// block
	if (simon->getOnStair() == false)
	{
		simon->x += min_tx * dx + nx * 0.4f;	// nx*0.4f : need to push out a bit to avoid overlapping next frame
		simon->y += min_ty * dy + ny * 0.4f;
		x += min_tx * dx + nx * 0.4f;	// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;
	}
	if (nx != 0) vx = 0;
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (dynamic_cast<CGround *>(e->obj))// if e->obj is Goomba 
		{

			if (simon->getJump())
				simon->ResetAfterJump();
			this->ny = 0;
			if (simon->getHurt())
			{
				if (simon->health > 0)
				{
					simon->SetState(SIMON_STATE_IDLE);
					simon->setHurt(false);
				}
				else
				{
					simon->setHurt(false);
					simon->setDeath(true);
					simon->setLive(simon->getLive() - 1);
					simon->setStartDeathTime(GetTickCount());
					simon->SetState(SIMON_STATE_DIE);
				}

			}
			simon->setCanSetStair(true);
			simon->setCanOnStair(false);
			simon->setCanOutStair(false);
			simon->vy = 0;

		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CheckGround::Render()
{
	RenderBoundingBox(x, y);
}