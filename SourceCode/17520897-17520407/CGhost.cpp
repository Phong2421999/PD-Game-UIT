#include "CGhost.h"

CGhost::CGhost(float x, float y) {
	width = GHOST_WIDTH;
	height = GHOST_HEIGHT;
	this->AddAnimation(ANI_GHOST);
	int random = rand() % 2;
	if (random == 1)
	{
		nx = 1;
		this->x = x - GHOST_OFFSET_X;
		this->y = GHOST_SPAWN_POSITION_Y;
	}
	else
	{
		nx = -1;
		this->x = x + SCREEN_WIDTH - GHOST_OFFSET_X;
		this->y = GHOST_SPAWN_POSITION_Y;
	}
	vy = GHOST_SPAWN_GRAVITY;
	startSpawnTime = GetTickCount();
}

void CGhost::Render() {
	if (nx < 0)
		animations[0]->Render(x, y);
	else
		animations[0]->RenderFlipX(x, y, GHOST_OFFSET_FLIP_X);
	RenderBoundingBox(x, y);
}

void CGhost::RenderCurrentFrame()
{
	if (nx < 0)
		animations[0]->RenderCurrentFrame(x, y);
	else
		animations[0]->RenderCurrentFrameFlipX(x, y, GHOST_OFFSET_FLIP_X);
}

void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	DWORD now = GetTickCount();
	if (now - startSpawnTime >= GHOST_ACTIVE_TIME)
		isActive = true;
	
	if (nx > 0)
		vx = GHOST_VELOCITY_X;
	else
		vx = -GHOST_VELOCITY_X;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{

		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);// block
		x += min_tx * dx + nx * 0.4f;	// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;
		for (int i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGround*>(e->obj))
			{
				vy += GHOST_GRAVITY * dt;
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	CSimon* simon = CSimon::getInstance();
	if (this->checkAABBTouch(simon) && simon->getUntouchable() == false)
	{
		CSimon::getInstance()->TouchEnemy(this->nx);
		CSimon::getInstance()->Damage(1);
	}
}

void CGhost::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}