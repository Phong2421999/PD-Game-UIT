#include <algorithm>
#include "Simon.h"
#include "Ground.h"

CSimon * CSimon::__instance = NULL;

CSimon* CSimon::getInstance()
{
	if (__instance == NULL)
		__instance = new CSimon();
	return __instance;
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	if (x <= 0)
	{
		x = 0;
	}
	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	// Kiểm tra để hạn chế việc nhảy và đánh liên tục;
	Attacking();
	Jumping();


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{

		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGround *>(e->obj))// if e->obj is Goomba 
			{
				if (isJump)
				{
					ResetAfterJump();
				}	
			}
			//{
			//	CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

			//	// jump on top >> kill Goomba and deflect a bit 
			//	if (e->ny < 0)
			//	{
			//		if (goomba->GetState() != GOOMBA_STATE_DIE)
			//		{
			//			goomba->SetState(GOOMBA_STATE_DIE);
			//			vy = -MARIO_JUMP_DEFLECT_SPEED;
			//		}
			//	}
			//	else if (e->nx != 0)
			//	{
			//		if (untouchable == 0)
			//		{
			//			if (goomba->GetState() != GOOMBA_STATE_DIE)
			//			{
			//				if (level > MARIO_LEVEL_SMALL)
			//				{
			//					level = MARIO_LEVEL_SMALL;
			//					StartUntouchable();
			//				}
			//				else
			//					SetState(MARIO_STATE_DIE);
			//			}
			//		}
			//	}
			//}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::Render()
{
	int ani;
	if (isSit)
	{
		ani = nx > 0 ? SIMON_ANI_SIT_RIGHT : SIMON_ANI_SIT_LEFT;

	}
	else if (isJump)
	{
		ani = nx > 0 ? SIMON_ANI_SIT_RIGHT : SIMON_ANI_SIT_LEFT;
	}
	else
	{
		if (state == SIMON_STATE_DIE)
		{
			ani = nx > 0 ? SIMON_ANI_DIE_RIGHT : SIMON_ANI_DIE_LEFT;
		}
		else if (state == SIMON_STATE_IDLE)
		{
			ani = nx > 0 ? SIMON_ANI_IDLE_RIGHT : SIMON_ANI_IDLE_LEFT;
		}
		else if (state == SIMON_STATE_WALKING_LEFT)
		{
			ani = SIMON_ANI_WALKING_LEFT;
		}
		else if (state == SIMON_STATE_WALKING_RIGHT)
		{
			ani = SIMON_ANI_WALKING_RIGHT;
		}
		else if (state == SIMON_STATE_ATTACK)
		{
			if (weaponLevel == SIMON_WEAPON_LEVEL_1)
			{
				ani = nx > 0 ? SIMON_ANI_ATTACK_LEVEL_1_STAND_RIGHT : SIMON_ANI_ATTACK_LEVEL_1_STAND_LEFT;
			}
			
		}
	}
	int alpha = 255;
	
	animations[ani]->Render(x, y, alpha);
	
	RenderBoundingBox();
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	if (isSit)
	{
		Sitting();
		return;
	}
	else
	{
		switch (state)
		{
		case SIMON_STATE_WALKING_RIGHT:
			WalkingRight();
			break;
		case SIMON_STATE_WALKING_LEFT:
			WalkingLeft();
			break;
		case SIMON_STATE_JUMP:
			Jump();
			break;
		case SIMON_STATE_IDLE:
			vx = 0;
			break;
		case SIMON_STATE_SIT:
			Sit();
			break;
		case SIMON_STATE_ATTACK:
			Attack();
			break;
		}
	}
	
}


//Xử lí khi đang tấn công
void CSimon::Attacking()
{
	
	DWORD now = GetTickCount();
	if (now - lastAttackTime >= SIMON_RESET_ATTACK_TIME)
	{
		isCanAttack = true;
	}
	if (isAttack)
	{
		if (isSit)
		{

		}
		else
		{
			if (weaponLevel == SIMON_WEAPON_LEVEL_1)
			{
				int ani = lastAttackSide > 0 ? SIMON_ANI_ATTACK_LEVEL_1_STAND_RIGHT : SIMON_ANI_ATTACK_LEVEL_1_STAND_LEFT;
				bool isLastFrame = animations[ani]->getLastFrame();
				if (isLastFrame)
				{
					isAttack = false;
					animations[ani]->reset();
					state = SIMON_STATE_IDLE;
				}

			}
		}
	}
	
}

void CSimon::Jumping()
{
	DWORD now = GetTickCount();
	if (now - lastJumpTime >= SIMON_RESET_JUMP_TIME)
	{
		isCanJump = true;
	}
}

//Xử lí các điều khiển của nhân vật

void CSimon::Attack()
{
	lastAttackTime = GetTickCount();
	isCanAttack = false;
	isAttack = true;
	lastAttackSide = nx; // kiểm tra hướng đánh để xác định kết thúc animation;
	vx = 0;// đang đánh không được di chuyển
	vy = 0; // đang nhảy đánh thì ko rơi xuống
}
void CSimon::Sit()
{
	if (isJump)
	{
		state = SIMON_STATE_JUMP;
		return;
	}
	vx = 0; //Khi ngồi không được di chuyển
	isSit = true;
}

void CSimon::Sitting()
{
	if (isJump)
	{
		state = SIMON_STATE_JUMP;
		return;
	}
	if (isAttack)
	{
		state = SIMON_STATE_ATTACK;
		return;
	}
	if (state == SIMON_STATE_WALKING_LEFT)
		nx = -1;
	if (state == SIMON_STATE_WALKING_RIGHT)
		nx = 1;
}

void CSimon::Jump()
{
	if (isSit) // đang ngồi không được nhảy
	{
		state = SIMON_STATE_SIT;
		return;
	}
	vy = -SIMON_JUMP_SPEED_Y;
	isJump = true;
	isCanJump = false;
	lastJumpTime = GetTickCount();
}

void CSimon::WalkingLeft()
{
	if (isAttack)
	{
		state = SIMON_STATE_ATTACK;
		return;
	}
	nx = -1;
	vx =- SIMON_WALKING_SPEED;

}

void CSimon::WalkingRight()
{
	if (isAttack)
	{
		state = SIMON_STATE_ATTACK;
		return;
	}
	nx = 1;
	vx = SIMON_WALKING_SPEED;
}


void CSimon::ResetAfterJump() // đẩy nhân vật lên 1 khoảng để không bị đè bbox
{
	isJump = false;
	y -= RESET_SIMON_AFTER_JUMP;
	this->state = SIMON_STATE_IDLE;

}

void CSimon::ResetAfterSit()
{
	isSit = false;
	y -= RESET_SIMON_AFTER_SIT;
}


void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (isSit || isJump)
	{
		left = x;
		top = y;
		right = x + SIMON_SIT_BBOX_WIDTH;
		bottom = y + SIMON_SIT_BBOX_HEIGHT;
	}
	else
	{
		left = x;
		top = y;
		right = x + SIMON_BBOX_WIDTH;
		bottom = y + SIMON_BBOX_HEIGHT;
	}

}
