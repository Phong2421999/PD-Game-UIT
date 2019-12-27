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
	isIdle = false;
	boneQuantity = 1;
	lastMakeBoneTime = 0;
	xMiddleWalking = 0;
	offsetWithSimon = 0;
	mode = WALKING_MODE;
	xJump = yJump = 0;
	isStop = false;
	isJumpBack = false;
	vxJump = 0;
	vyJump = 0;
	isActive = false;
	makeTime = GetTickCount();
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

	if (x <= lockCameraX)
	{
		x = lockCameraX;
	}
	if (x + SKELETON_BB_WIDTH >= scenceWidth)
	{
		x = scenceWidth - SKELETON_BB_WIDTH;
	}

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
	float checkJumpPos = 0;
	simon->GetPosition(sx, sy);
	if (isAttack == false
		&& isJump == false
		&& isJumpBack == false
		&& mode == JUMP_MODE
		&& now - lastJumpTime > SKELETON_DELAY_JUMP_TIME
		&& sy + SIMON_BBOX_HEIGHT < y
		&& simon->getJump() == false
		&& isActive)
	{
		isJump = true;
		xBefore = x;
		yBefore = y;
		yJump = sy - 8;
		xJump = sx;
		lastJumpTime = GetTickCount();
		vxJump = (abs(x - sx) / dt) / TIME_JUMP_TOUCH_SIMON_X;
		vyJump = (abs(y - sy) / dt) / TIME_JUMP_TOUCH_SIMON_Y;
		if (nx > 0)
			vxJump = vxJump;
		else
			vxJump = -vxJump;
		vx = vxJump;
		vy = -vyJump;
	}
	else if (isJump == false && isJumpBack == false)
	{
		if (now - lastAttackTime >= SKELETON_DELAY_ATTACK_TIME
			&& isAttack == false
			&& isActive)
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

	if (isJump || isJumpBack)
		Jump();
	if (isAttack)
		Attack();
	if (isWalking)
		Walking();
	// No collision occured, proceed normally
	vy += SKELETON_GRAVITY * dt;
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
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	if (checkAABBTouch(simon))
	{
		simon->TouchEnemy(nx);
	}
	if (now - makeTime > SKELETON_TIME_ACTIVE && isActive == false)
	{
		isActive = true;
	}
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
	float sx, sy;
	CSimon::getInstance()->GetPosition(sx, sy);
	isWalking = false;
	isAttack = false;
	if (isJump && isStop == false)
	{
		isJumpBack = false;
		isStop = false;
		vy = -0.12f;
	}
	if (isJumpBack && isStop == false)
	{
		isJump = false;
	}
	if (isJump && y <= yJump)
	{
		isJump = false;
		isJumpBack = true;
		yJump = yBefore;
		isStop = true;
	}
	if (isJumpBack && y >= yJump)
	{
		isJumpBack = false;
		isWalking = true;
	}
	if (isStop)
	{
		vy = 0;
		DWORD now = GetTickCount();
		if (now - lastJumpTime > 500)
		{
			isJumpBack = true;
			isStop = false;
			isJump = false;
			vy = -0.12f;
			if (nx > 0)
				vx = -vxJump;
			else
				vx = vxJump;
		}
	}
}

void Skeleton::Attack()
{
	if (isJump == false)
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
}

void Skeleton::Walking()
{
	if (isJump == false)
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
}