#include "CEagle.h"
#include "Simon.h"
CEagle::CEagle()
{
	float cx = CGame::GetInstance()->GetCamPos_x();
	this->AddAnimation(ANI_IDLE);
	this->AddAnimation(ANI_FLY);
	vx = -FLY_SPEED;
	vy = 0;
	width = EAGLE_BB_WIDTH;
	height = EAGLE_BB_HEIGHT;
	ani = ANI_IDLE_INDEX;
	isActive = true;
	isIdle = false;
	isFly = true;
	lastInAirTime = GetTickCount();
	lastIdleTime = GetTickCount();
	x = cx + SCREEN_WIDTH - 32;
	float randomY = rand() % MAX_Y_SPAWN + MIN_Y_SPAWN;
	y = randomY;
}

void CEagle::Render() {
	RenderBoundingBox(x, y);
	if (isFly)
		ani = ANI_FLY_INDEX;
	else
		ani = ANI_IDLE_INDEX;
	animations[ani]->Render(x, y);
}
void CEagle::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;

}
void CEagle::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt);
	DWORD now = GetTickCount();
	if (now - lastIdleTime >= idleTime
		&& isIdle == false)
	{
		isIdle = true;
		lastInAirTime = GetTickCount();
		isActive = true;
	}
	if (isFly)
	{
		x += dx;
	}
	if (isIdle)
	{
		isFly = false;
		if (now - lastInAirTime >= IN_AIR_TIME)
		{
			isFly = true;
			isIdle = false;
			lastIdleTime = GetTickCount();
		}
	}
	CSimon* simon = CSimon::getInstance();
	if (checkAABBTouch(simon) && simon->getUntouchable() == false)
	{
		simon->TouchEnemy(nx);
		simon->Damage(1);
	}

}
void CEagle::RenderCurrentFrame() {
	RenderBoundingBox(x, y);
	animations[ani]->RenderCurrentFrame(x, y);
}
void CEagle::SetPosition(float x, float y) {
	this->x = x;
	this->y = y;
}
void CEagle::GetPosition(float &x, float &y) {
	x = this->x;
	y = this->y;
}