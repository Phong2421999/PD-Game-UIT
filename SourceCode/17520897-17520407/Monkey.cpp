#include "Monkey.h"

Monkey::Monkey()
{
	this->AddAnimation(ANI_IDLE);
	this->AddAnimation(ANI_JUMP);
	ani = ANI_IDLE_INDEX;
	nx = -1;
	width = MONKEY_BB_WIDTH;
	height = MONKEY_BB_HEIGHT;
	isJump = true;
	isClamping = false;
	lastMoveTime = 0;
	lastClampTime = 0;
	xWallTarget = 0;
	yWallTarget = 999999;
	isIdle = true;
	isActive = false;
	spawnTime = GetTickCount();
	numberOfCheckSide = 0;
	lastCheckNxTime = 0;
}

void Monkey::Render()
{
	if (isIdle)
		ani = ANI_IDLE_INDEX;
	else
		ani = ANI_JUMP_INDEX;
	if (nx < 0)
		animations[ani]->Render(x, y);
	else
		animations[ani]->RenderFlipX(x, y, 8);
	RenderBoundingBox(x, y);
}
void Monkey::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}
void Monkey::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	if (isActive)
	{
		DWORD now = GetTickCount();
		vector<LPGAMEOBJECT> checkGround;
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CWall*>(coObjects->at(i)))
			{
				CWall* wall = dynamic_cast<CWall*>(coObjects->at(i));
				float wallWidth, wallHeight;
				float wallX, wallY;
				wall->GetPosition(wallX, wallY);
				wall->GetWidthHeight(wallWidth, wallHeight);
				if (this->checkAABBTouch(coObjects->at(i)))
				{
					xWallTarget = wallX;
					yWallTarget = wallY;
					vx = 0;
					isClamping = true;
				}
			}
			else
			{
				checkGround.push_back(coObjects->at(i));
			}
		}
		if (isClamping)
		{
			if (y <= yWallTarget)
			{
				isClamping = false;
				Jump();
			}
		}

		CSimon* simon = CSimon::getInstance();
		int simonNx = simon->nx;
		float simonX, simonY;
		simon->GetPosition(simonX, simonY);
		if (isClamping == false
			&& isJump == true)
		{
			if (now - lastCheckNxTime > CHECK_NX_TIME_DELAY)
			{
				if (simonX < x - SIMON_OFFSET_TO_BBOX_X)
					nx = -1;
				else
					nx = 1;
				lastCheckNxTime = GetTickCount();
			}
		}
		if (isJump == false
			&& isClamping == false)
		{
			if (now - lastMoveTime > JUMP_TIME_DELAY)
			{
				if (abs(simonX - x) > OFFSET_WALKING)
					Walking();
				else
					Jump();
			}
		}
		if (isClamping)
		{

			if (now - lastClampTime > CLAMP_TIME_DELAY)
			{
				Clamping();
			}
			else
			{
				vx = 0;
				isIdle = true;
			}
		}

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		if (isClamping == false)
			vy += GRAVITY * dt;
		CalcPotentialCollisions(&checkGround, coEvents);

		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
			isJump = true;
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
					isIdle = true;
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		if (checkAABBTouch(simon) && simon->getUntouchable() == false)
		{
			simon->TouchEnemy(nx);
			simon->Damage(1);
		}
	}
	else
	{
		vx = -NOT_ACTIVE_SPEED_X;
		isIdle = true;
		x += vx * dt;
		DWORD now = GetTickCount();
		if (now - spawnTime >= timeActive)
		{
			isActive = true;
			Jump();
		}
	}
}
void Monkey::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}
void Monkey::GetPosition(float &x, float &y)
{
	x = this->x;
	y = this->y;
}

void Monkey::Jump()
{
	isJump = true;
	isClamping = false;
	isIdle = false;
	lastMoveTime = GetTickCount();
	if (nx > 0)
		vx = JUMP_SPEED_X;
	else
		vx = -JUMP_SPEED_X;
	vy = -JUMP_SPEED_Y;
	isIdle = false;
}

void Monkey::Walking()
{
	isJump = true;
	isClamping = false;
	lastMoveTime = GetTickCount();
	if (nx > 0)
		vx = JUMP_SPEED_X;
	else
		vx = -JUMP_SPEED_X;
	vy = -WALKING_SPEED_Y;
	isIdle = false;
}

void Monkey::Clamping()
{

	y -= CLAMPING_POSITION_Y;
	vy = 0;
	if (x > xWallTarget)
	{
		vx = -((x - xWallTarget) / dt) / VX_PART_CLAMPING;
	}
	else if (x < xWallTarget)
	{
		vx = ((xWallTarget - x) / dt) / VX_PART_CLAMPING;
	}
	else
		vx = 0;
	lastClampTime = GetTickCount();
	isIdle = false;
}