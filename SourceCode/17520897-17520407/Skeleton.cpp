#include "Skeleton.h"

Skeleton::Skeleton() {
	this->AddAnimation(ANI_WALKING);
	this->AddAnimation(ANI_IDLE);
	this->AddAnimation(ANI_ATTACK);
	ani = ANI_WALKING_INDEX;
	vy = 999;
	width = SKELETON_BB_WIDTH;
	height = SKELETON_BB_HEIGHT;
	isWalking = true;
	isJump = false;
	isAttack = false;
	xTarget = 0;
	yTarget = 0;
	boneQuantity = 1;
	lastMakeBoneTime = 0;
	xMiddleWalking = 0;
	offsetWithSimon = 0;
	mode = WALKING_MODE;
}
void Skeleton::Render() {
	for (int i = 0; i < bones.size(); i++)
	{
		bones[i]->Render();
	}
	if (isAttack)
		ani = ANI_ATTACK_INDEX;
	if (isIdle)
		ani = ANI_IDLE_INDEX;
	if (isWalking)
		ani = ANI_WALKING_INDEX;
	if (nx < 0)
		animations[ani]->Render(x, y);
	else
		animations[ani]->RenderFlipX(x, y, SKELETON_BB_WIDTH / 2);
	RenderBoundingBox(x, y);
}
void Skeleton::RenderCurrentFrame()
{
	for (int i = 0; i < bones.size(); i++)
	{
		bones[i]->RenderCurrentFrame();
	}
	if (isAttack)
		ani = ANI_ATTACK_INDEX;
	if (isIdle)
		ani = ANI_IDLE_INDEX;
	if (isWalking)
		ani = ANI_WALKING_INDEX;
	if (nx < 0)
		animations[ani]->RenderCurrentFrame(x, y);
	else
		animations[ani]->RenderCurrentFrameFlipX(x, y, SKELETON_BB_WIDTH / 2);
	RenderBoundingBox(x, y);
}
void Skeleton::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}
void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CSimon *simon = CSimon::getInstance();
	CGameObject::Update(dt);
	DWORD now = GetTickCount();

	for (int i = 0; i < bones.size(); i++)
	{
		if (bones[i]->GetHealth() > 0)
			bones[i]->Update(dt);
		else
		{
			bones.erase(bones.begin() + i);
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	float sx, sy;
	simon->GetPosition(sx, sy);
	if (y + height > sy + SIMON_BBOX_HEIGHT
		&& isAttack == false
		&& mode == JUMP_MODE)
	{
		isJump = true;
		xTarget = sx + SIMON_OFFSET_TO_BBOX_X + SIMON_BBOX_WIDTH / 2;
		yTarget = sy;
		if (sx > x)
			nx = 1;
		else
			nx = -1;
	}
	else
	{
		if (now - lastAttackTime >= SKELETON_DELAY_ATTACK_TIME
			&& isAttack == false)
		{
			isAttack = true;
			boneQuantity = rand() % MAX_WEAPON_QUANTITY + 1;
		}
		else
		{
			if (isAttack == false)
			{
				isWalking = true;
				if (sx > x)
				{
					xMiddleWalking = sx + SIMON_OFFSET_TO_BBOX_X - offsetWithSimon;
					nx = 1;
				}
				else
				{
					xMiddleWalking = sx + offsetWithSimon;
					nx = -1;
				}
			}
		}
	}
	vy += SKELETON_GRAVITY * dt;
	if (isJump)
		Jump();
	if (isAttack)
		Attack();
	if (isWalking)
		Walking();
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
				isJump = false;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Skeleton::SetPosition(float x, float y) {
	this->x = x;
	this->y = y;
}
void Skeleton::GetPosition(float &x, float &y) {
	x = this->x;
	y = this->y;
}
void Skeleton::Jump()
{
	vy = -((y - yTarget) / dt) / VY_JUMP_PART;
	if (nx > 0)
		vx = ((x - xTarget) / dt) / VX_JUMP_PART;
	else
		vx = -((x - xTarget) / dt) / VX_JUMP_PART;
	isAttack = false;
	isWalking = false;
}

void Skeleton::Attack()
{
	if (boneQuantity > 0)
	{
		DWORD now = GetTickCount();
		if (now - lastMakeBoneTime > SKELETON_MAKE_WEAPON_DELAY)
		{
			lastMakeBoneTime = GetTickCount();
			boneQuantity--;
			isIdle = false;
			Bone* bone = new Bone(x, y, nx);
			bones.push_back(bone);
		}
		else
		{
			if (now - lastMakeBoneTime > SKELETON_MAKE_WEAPON_DELAY / 2)
				isIdle = true;
		}
	}
	else
	{
		isAttack = false;
		lastAttackTime = GetTickCount();
	}
	this->makeWeapon = true;
	isWalking = false;
	isJump = false;
	vx = 0;
}

void Skeleton::Walking()
{
	if (x >= xMiddleWalking + 16)
		vx = -SKELETON_WALKIN_SPEED;
	if (x <= xMiddleWalking - 16)
		vx = SKELETON_WALKIN_SPEED;
	if (vx == 0)
		vx = SKELETON_WALKIN_SPEED;
	isJump = false;
	isAttack = false;
}