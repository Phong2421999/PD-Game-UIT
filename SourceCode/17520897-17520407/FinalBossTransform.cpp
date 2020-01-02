#include "FinalBossTranform.h"

FinalBossTransform::FinalBossTransform()
{
	this->AddAnimation(FINAL_BOSS_ANI_TRANSFROM_ID);
	vx = vy = 0;
	effectType = 0;
}

void FinalBossTransform::Render()
{
	animations[0]->Render(x, y);
}

void FinalBossTransform::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	this->vx += vxPlus;
	this->vy += vyPlus;
}

