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
		this->x = x + SCREEN_WIDTH - 32;
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
	if (y <= sy - BAT_FLY_DISTANCE_Y)
		vy = BAT_VELOCITY_Y;

	x += dx;
	y += dy;

	CSimon* simon = CSimon::getInstance();
	if (this->checkAABBTouch(simon) && simon->getUntouchable() == false)
	{
		if (CSimon::getInstance()->getDeath() == false)
		{
			CSimon::getInstance()->TouchEnemy(this->nx);
			CSimon::getInstance()->Damage(1);
			this->health = 0;
		}

	}
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
