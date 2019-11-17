#include "CPanther.h"

CPanther::CPanther(float x,float y) {
	this->AddAnimation(ANI_PANTHER_IDLE);
	this->AddAnimation(ANI_PANTHER_RUN);
	this->AddAnimation(ANI_PANTHER_JUMP);
	width = PANTHER_WIDTH;
	height = PANTHER_HEIGHT;
	ani = ANI_ID_PANTHER_IDLE;
	attackDistance = 9999;
	isAttack = false;
	this->x = 710;
	this->y = 100;
	this->yBefore = 100;

	CSimon::getInstance()->GetPosition(sx, sy);
	float posX = this->x - sx;
	if (posX < 0)
		nx = 1;
	else
		nx = -1;
	isJump = false;
}


void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	CSimon::getInstance()->GetPosition(sx, sy);

	vy += PANTHER_GRAVITY * dt;
	
	if (abs(x - sx) < 100)
	{
		isActive = true;
		Run();
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
		vx = 0;
		vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGround *>(e->obj))
			{
				isJump = false;
				if (this->isActive)
					ani = ANI_ID_PANTHER_RUN;
				else
					ani = ANI_ID_PANTHER_IDLE;
			}
		}

	}
	
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void CPanther::Run() {
	ani = ANI_ID_PANTHER_RUN;
	vx = PANTHER_VELOCITY_X * nx;
}


void CPanther::Render() {
	if (nx < 0)
	{
		animations[ani]->Render(x, y);
	}
	else
		animations[ani]->RenderFlipX(x, y, PANTHER_OFFSET_FLIP_X);
	RenderBoundingBox(x, y);
}

void CPanther::RenderCurrentFrame()
{
	if (nx < 0)
	{
		animations[ani]->RenderCurrentFrame(x, y);
	}
	else
		animations[ani]->RenderCurrentFrameFlipX(x, y, PANTHER_OFFSET_FLIP_X);
}

void CPanther::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}