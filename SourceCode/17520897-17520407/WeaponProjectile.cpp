#include "Simon.h"
#include "WeaponProjectile.h"

WeaponProjectile::WeaponProjectile(float x, float y, int nx)
{
	this->AddAnimation(PROJECTILE_ANI);
	if (nx > 0)
		vx = PROJECTILE_SPEED_X;
	else
		vx = -PROJECTILE_SPEED_X;
	this->nx = nx;
	vy = 0;
	this->width = PROJECTILE_BBOX_WIDTH;
	this->height = PROJECTILE_BBOX_HEIGHT;
	makeTime = GetTickCount();
	this->x = x;
	this->y = y;
}

void WeaponProjectile::SetPositionWithEnemey(int offsetX, int offsetY)
{
	this->x = x + offsetX;
	this->y = y + offsetY;
}

void  WeaponProjectile::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;

}


void WeaponProjectile::RenderCurrentFrame()
{
	animations[PROJECTILE_ANI_ID]->RenderCurrentFrame(x, y);
	RenderBoundingBox(x, y);
}

void WeaponProjectile::Render()
{
	if (nx > 0)
		animations[PROJECTILE_ANI_ID]->Render(x, y);
	else
		animations[PROJECTILE_ANI_ID]->RenderCurrentFrameFlipX(x, y, 4);


	RenderBoundingBox(x, y);

}


void WeaponProjectile::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	dx = vx * dt;
	dy = vy * dt;
	x += dx;
	y += dy;

	DWORD now = GetTickCount();
	if (now - makeTime > PROJECTILE_WEAPON_TIME_LIVE)
	{
		health = 0;
	}


	CSimon* simon = CSimon::getInstance();
	if (isTouchOtherObject(simon) && simon->getUntouchable() == false)
	{
		simon->Damage(1);
		simon->TouchEnemy(this->nx);
		health = 0;
	}

}