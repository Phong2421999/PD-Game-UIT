#include "CBat.h"

CBat::CBat(float x, float y)
{
	this->AddAnimation(ANI_BAT_IDLE);
	this->AddAnimation(ANI_BAT_FLY);
	ani = ANI_ID_BAT_FLY;
	this->width = BAT_WIDTH;
	this->height = BAT_HEIGHT;
	int random = rand() % 2;
	if (random == 1)
	{
		nx = 1;
		this->x = x + 16;
		DebugOut(L"\n x %f", x);
		this->y = y;
	}
	else
	{
		nx = -1;
		this->x = x + SCREEN_WIDTH  - 32;
		this->y = y;
	}

	
	startSpawnTime = GetTickCount();
}


void CBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	DWORD now = GetTickCount();
	if (now - startSpawnTime >= BAT_ACTIVE_TIME)
		isActive = true;
	if (nx > 0)
		vx = BAT_VELOCITY_X;
	else
		vx = -BAT_VELOCITY_X;
	
	float sx, sy;
	CSimon::getInstance()->GetPosition(sx, sy);
	if (y >= sy)
		vy = -BAT_VELOCITY_Y;
	if(y <= sy - BAT_FLY_DISTANCE_Y)
		vy = BAT_VELOCITY_Y;


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
			/*if (dynamic_cast<CSimon *>(e->obj))
			{
				e->obj->Damage(1);
			}*/
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void CBat::Render() {
	if (nx < 0)
	{
		animations[ani]->Render(x, y);
	}
	else
		animations[ani]->RenderFlipX(x, y, BAT_OFFSET_FLIP_X);
	RenderBoundingBox(x, y);
}

void CBat::RenderCurrentFrame()
{
	if (nx < 0)
	{
		animations[ani]->RenderCurrentFrame(x, y);
	}
	else
		animations[ani]->RenderCurrentFrameFlipX(x, y, BAT_OFFSET_FLIP_X);
}

void CBat::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}