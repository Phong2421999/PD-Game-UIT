#include "WeaponProjectile.h"

WeaponProjectile::WeaponProjectile(float x, float y, int nx)
{
	this->AddAnimation(PROJECTILE_ANI);
	if (nx > 0)
		vx = PROJECTILE_SPEED_X;
	else
		vx = -PROJECTILE_SPEED_X;
	this->nx = nx;
	SetPositionWithFish(x, y, nx);
	this->width = PROJECTILE_BBOX_WIDTH;
	this->height = PROJECTILE_BBOX_HEIGHT;
	makeTime = GetTickCount();
}

void WeaponProjectile::SetPositionWithFish(float x, float y, int nx)
{
	this->y = y;
	if (nx > 0)
	{
		this->x = x + 16;
	}
	else
	{
		this->x = x - 4;
	}
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
	x += dx;

	DWORD now = GetTickCount();
	if (now - makeTime > PROJECTILE_WEAPON_TIME_LIVE)
	{
		health = 0;
	}

	WeaponEnemies::Update(dt, coObjects);

}