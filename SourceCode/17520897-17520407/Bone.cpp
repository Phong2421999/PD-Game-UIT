#include "Bone.h"
#include "Simon.h"
Bone::Bone(float x, float y, int nx)
{
	this->AddAnimation(BONE_ANI);
	this->width = BONE_BBOX_WIDTH;
	this->height = BONE_BBOX_HEIGHT;
	if (nx > 0)
		vx = BONE_SPEED_X;
	else
		vx = -BONE_SPEED_X;
	vy = -BONE_SPEED_Y;
	makeTime = GetTickCount();
	this->x = x;
	this->y = y;
	this->nx = nx;
}

void Bone::Render()
{
	animations[BONE_ANI_INDEX]->Render(x, y);
	RenderBoundingBox(x, y);
}
void Bone::RenderCurrentFrame() {
	animations[BONE_ANI_INDEX]->RenderCurrentFrame(x, y);
	RenderBoundingBox(x, y);
}
void Bone::SetPositionWithFish(float x, float y, int nx) {

}
void Bone::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects) {
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	vy += BONE_GRAVITY * dt;
	DWORD now = GetTickCount();
	if (now - makeTime > TIME_LIVE)
	{
		this->health = -1;
	}
	CSimon* simon = CSimon::getInstance();
	if (isTouchOtherObject(simon) && simon->getUntouchable() == false)
	{
		simon->Damage(1);
		simon->TouchEnemy(this->nx);
		health = 0;
	}
}
void Bone::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x + width/4;
	top = y;
	right = x + width;
	bottom = y + height - width/4;
}