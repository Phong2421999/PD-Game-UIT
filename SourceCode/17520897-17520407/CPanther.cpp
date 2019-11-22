#include "CPanther.h"

CPanther::CPanther(float x, float y) {
	this->AddAnimation(ANI_PANTHER_IDLE);
	this->AddAnimation(ANI_PANTHER_RUN);
	this->AddAnimation(ANI_PANTHER_JUMP);
	width = PANTHER_WIDTH;
	height = PANTHER_HEIGHT;
	ani = ANI_ID_PANTHER_IDLE;
	this->x = x;
	this->xBefore = x;
	this->y = y;
	CSimon::getInstance()->GetPosition(sx, sy);
	if ((this->x - sx) < 0)
		nx = 1;
	else
		nx = -1;
	isAttacking = false;
	isJumping = false;
	xGround = 0;
	yGround = 0;
	timeSpawn = GetTickCount();
	isActive = true;
}


void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	if (CSimon::getInstance()->getJump() == false)
	{
		CSimon::getInstance()->GetPosition(sx, sy);
	}
	vy += PANTHER_GRAVITY * dt;
	if (abs(x - sx) < 92)
	{
		isAttacking = true;
	}
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
		CheckJump();
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);// block
		x += min_tx * dx + nx * 0.4f;	// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;
		vx = 0;
		vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGround *>(e->obj))
			{

				CGround * ground = dynamic_cast<CGround *>(e->obj);
				ground->GetPosition(xGround, yGround);
				ground->GetWidthHeight(widthGround, heightGround);
				isJumping = false;

				if (this->isAttacking)
				{
					ani = ANI_ID_PANTHER_RUN;
					isRunning = true;
					if (isJumping)
					{

						if (y < sy)
						{
							if (x > sx)
							{
								this->nx = -1;
							}
						}
					}

				}
			}
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (isAttacking)
	{
		Run();
		Jump();
		CSimon* simon = CSimon::getInstance();
		if (this->checkAABBTouch(simon) && simon->getUntouchable() == false)
		{
			CSimon::getInstance()->TouchEnemy(this->nx);
			CSimon::getInstance()->Damage(1);
		}
	}

}


void CPanther::Run() {
	if (isRunning)
	{
		ani = ANI_ID_PANTHER_RUN;
		vx = PANTHER_VELOCITY_X * nx;
	}
}

void CPanther::Jump()
{
	if (isJumping)
	{
		isRunning = false;
		ani = ANI_ID_PANTHER_JUMP;
		vy = 0.007 *dt;
		vx = 0.12 * nx;
	}
}

void CPanther::CheckJump()
{
	if (this->nx > 0)
	{
		if (abs(xBefore - x + PANTHER_WIDTH) >= abs(xBefore - xGround + widthGround - 16))
		{
			if (y < sy)
			{
				isJumping = true;
				vy -= 0.0001*dt;
			}
			else
			{
				if (x > sx)
				{
					nx = -1;
				}
				else
				{
					nx = 1;
				}
			}
		}
		else
		{
			isJumping = false;
			isRunning = true;
		}
	}
	else
	{
		if (x + PANTHER_WIDTH < xGround + 2)
		{
			if (y < sy)
			{
				isJumping = true;
			}
			else
			{
				if (x > sx)
				{
					nx = -1;
				}
				else
				{
					nx = 1;
				}
			}
		}
		else
		{
			isJumping = false;
			isRunning = true;
		}
	}
}


void CPanther::Render() {
	if (nx < 0)
	{
		animations[ani]->Render(x, y);
	}
	else
		animations[ani]->RenderFlipX(x, y, PANTHER_OFFSET_FLIP_X);
	RenderBoundingBox(x, y);
}

void CPanther::RenderCurrentFrame()
{
	if (nx < 0)
	{
		animations[ani]->RenderCurrentFrame(x, y);
	}
	else
		animations[ani]->RenderCurrentFrameFlipX(x, y, PANTHER_OFFSET_FLIP_X);
}

void CPanther::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}