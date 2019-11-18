#include <algorithm>
#include "Simon.h"

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
	if (isAutoGo)
	{
		state = SIMON_STATE_WALKING_RIGHT;
		vx = SIMON_AUTO_WALKING_SPEED;
		simonAutoGoDistance += vx * dt;
		this->x += vx * dt;
		if (simonAutoGoDistance > autoGoDistance)
		{
			isAutoGo = false;
			simonAutoGoDistance = 0;
			autoGoDistance = 0;
			if (CGame::GetInstance()->GetCamAutoGo())
			{
				CGame::GetInstance()->SetRenderCloseDoor(true);
			}
		}

	}
	else if (CGame::GetInstance()->GetCamAutoGo())
	{
		state = SIMON_STATE_IDLE;
	}
	else
	{

		if (x <= 0)
			x = 0;
		DWORD now = GetTickCount();
		if (now - startUntouchableTime >= SIMON_UNTOUCHABLE_TIME)
		{
			isUntouchable = false;
			startUntouchableTime = 0;
		}
		// Khi rơi gravity thấp hơn để rơi chậm lại

		if (vy > 0)
			vy += SIMON_FALLING_GRAVITY * dt;
		else
			vy += SIMON_GRAVITY * dt;



		// Kiểm tra để hạn chế việc nhảy và đánh liên tục;
		Attacking(dt);
		Jumping();
		UsingWeapon();
		ResetAfterSit();
		if (isUsingStopWatch)
			UpdateStopWatch();
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
			x += min_tx * dx + nx * 0.4f;	// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.4f;

			if (nx != 0) vx = 0;
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CGround *>(e->obj))// if e->obj is Goomba 
				{
					isFalling = false;
					isOnStair = false;
					if (simonWeapon)
						simonWeapon->SetIsJump(false);

					if (isJump)
					{
						ResetAfterJump();
					}
				}
				if (dynamic_cast<CEnemies *>(e->obj))
				{
					/*if (dynamic_cast<CBat *> (e->obj))
					{
						e->obj->SetKillBySimon(true);
						e->obj->Damage(1);
						health = health - 1;
					}*/
					
					//CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);	
				}
			}
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CSimon::UpdateSimonWeapon(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	if (simonWeapon)
	{
		if (dynamic_cast<Whip*>(simonWeapon))
		{
			simonWeapon->SetPosition(x, y);
			simonWeapon->SetRenderPos(x, y);
		}
		simonWeapon->Update(dt, colliable_objects);
	}
}

void CSimon::Render()
{
	int ani;
	if (simonWeapon)
	{
		simonWeapon->Render();
	}

	if (isFreeze)
	{
		ani = SIMON_ANI_FREEZE;
	}
	else if (isSit)
	{
		if (isAttack)
			ani = SIMON_ANI_SIT_ATTACK;
		else
			ani = SIMON_ANI_SIT;
	}
	else if (isJump)
	{
		if (isAttack)
			ani = SIMON_ANI_ATTACK;
		else
			ani = SIMON_ANI_SIT;
	}
	else
	{
		switch (state)
		{
		case SIMON_STATE_DIE:
			ani = SIMON_ANI_DIE;
			break;
		case SIMON_STATE_IDLE:
			ani = SIMON_ANI_IDLE;
			break;
		case SIMON_STATE_WALKING_LEFT:
			ani = SIMON_ANI_WALKING;
			break;
		case SIMON_STATE_WALKING_RIGHT:
			ani = SIMON_ANI_WALKING;
			break;
		case SIMON_STATE_ATTACK:
			ani = SIMON_ANI_ATTACK;
			break;
		}
	}

	int alpha = 255;
	if (isUntouchable) alpha = 128;
	if (nx > 0)
		animations[ani]->Render(x, y, alpha);
	else
		animations[ani]->RenderFlipX(x, y, OFFSET_FLIP_X, alpha);

	RenderBoundingBox(x + SIMON_BBOX_WIDTH, y);
}

void CSimon::AddItem(GAME_ITEM type) {
	switch (type)
	{
	case SMALL_HEART:
		heart += 1;
		break;
	case LARGE_HEART:
		heart += 5;
		break;
	case WHIP_UPGRADE:
		UpgradeWhip();
		break;
	case DANGER_ITEM:
		ChangeSubWeapon(SIMON_WEAPON::DANGER);
		break;
	case AXE_ITEM:
		ChangeSubWeapon(SIMON_WEAPON::AXE);
		break;
	case HOLY_WATER_ITEM:
		ChangeSubWeapon(SIMON_WEAPON::HOLY_WATER);
		break;
	case STOP_WATCH_ITEM:
		ChangeSubWeapon(SIMON_WEAPON::STOP_WATCH);
		break;
	case RED_MONEY_BAG:
		score = score + 100;
		break;
	case PURPLE_MONEY_BAG:
		score = score + 400;
		break;
	case WHITE_MONEY_BAG:
		score = score + 700;
		break;
	case CROSS_ITEM:
		DebugOut(L"\nClear quai\n");
		break;
	}
}

void CSimon::ChangeSubWeapon(SIMON_WEAPON type)
{
	typeSubWeapon = type;
	isHasSubWeapon = true;
}

void CSimon::UpdateFreeze(DWORD dt)
{
	int ani = SIMON_ANI_FREEZE;
	if (simonWeapon)
	{
		simonWeapon->ResetAnimation();
		isAttack = false;
		isUseSubWeapon = false;
		DELETE_POINTER(simonWeapon);
	}
	if (animations[ani]->getLastFrame())
	{
		isFreeze = false;
		animations[ani]->reset();
	}
}

void CSimon::UpgradeWhip()
{
	state = SIMON_STATE_FREEZE;
	isFreeze = true;
	if (weaponLevel == 1)
	{
		weaponLevel = 2;
	}
	else if (weaponLevel == 2)
	{
		weaponLevel = 3;
	}
}

void CSimon::UpdateStopWatch() {
	DWORD now = GetTickCount();
	if (now - timeUsingStopWatch >= 3000)
	{
		isUsingStopWatch = false;
	}
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);
	float cam_x = CGame::GetInstance()->GetCamPos_x();
	float cam_y = CGame::GetInstance()->GetCamPos_y();
	D3DXVECTOR3 p(floor(x - cam_x), floor(y - cam_y), 0);
	if (isSit)
	{
		if (state == SIMON_STATE_ATTACK)
			Attack();
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


//Xử lí khi chạm enemy
void CSimon::TouchEnemy(int nx) {
	if (isUntouchable == false)
	{
		if (nx > 0)
		{
			isUntouchable = true;
			x += PUSH_SIMON_TOUCH_ENEMIES_X;
			y -= PUSH_SIMON_TOUCH_ENEMIES_Y;
			vy = -PUSH_SIMON_TOUCH_ENEMIES_VY;
			StartUntouchable();
		}
		else
		{
			isUntouchable = true;
			x -= PUSH_SIMON_TOUCH_ENEMIES_X;
			y -= PUSH_SIMON_TOUCH_ENEMIES_Y;
			vy = -PUSH_SIMON_TOUCH_ENEMIES_VY;
			StartUntouchable();
		}
	}
}
//Xử lí khi đang tấn công
void CSimon::Attacking(DWORD dt)
{
	if (isAttack)
	{
		if (isSit)
		{
			vx = 0;
			vy = 0;
			int ani = SIMON_ANI_SIT_ATTACK;
			bool isLastFrame = animations[ani]->getLastFrame();
			if (isLastFrame)
			{
				state = SIMON_STATE_SIT;
				lastAttackTime = GetTickCount();
				timeMakeWeapon = GetTickCount();
				animations[ani]->reset();
				isAttack = false;
				isUseSubWeapon = false;
			}
		}
		else
		{
			if (isJump == false)
			{
				vx = 0;
			}
			if (vx > 0)
			{
				if (nx > 0)
					vx = SIMON_WALKING_SPEED / 2;
				else
					vx = -SIMON_WALKING_SPEED / 2;

			}
			int ani = SIMON_ANI_ATTACK;
			bool isLastFrame = animations[ani]->getLastFrame();
			bool nextIsLastFrame = animations[ani]->getNextIsLastFrame();
			if (isLastFrame)
			{
				state = SIMON_STATE_IDLE;
				lastAttackTime = GetTickCount();
				timeMakeWeapon = GetTickCount();
				animations[ani]->reset();
				MakeSubWeapon(x, y, nx);
				isAttack = false;
				isUseSubWeapon = false;
			}
			if (nextIsLastFrame == false)
				vy = 0;
		}
	}
	else
	{
		DWORD now = GetTickCount();
		if (now - lastAttackTime >= SIMON_RESET_ATTACK_TIME)
		{
			isCanAttack = true;
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

void CSimon::UsingWeapon()
{
	switch (typeSubWeapon)
	{
	case SIMON_WEAPON::DANGER:
	{
		if (heart >= SIMON_HEART_USE_WEAPON::DANGER_HEART)
			isEnoughHeart = true;
		else
			isEnoughHeart = false;
		break;
	}
	case SIMON_WEAPON::AXE:
	{
		if (heart >= SIMON_HEART_USE_WEAPON::AXE_HEART)
			isEnoughHeart = true;
		else
			isEnoughHeart = false;
		break;
	}
	case SIMON_WEAPON::HOLY_WATER:
	{
		if (heart >= SIMON_HEART_USE_WEAPON::HOLY_WATER_HEART)
			isEnoughHeart = true;
		else
			isEnoughHeart = false;
		break;
	}
	case SIMON_WEAPON::STOP_WATCH:
	{
		if (heart >= SIMON_HEART_USE_WEAPON::STOP_WATCH_HEART)
			isEnoughHeart = true;
		else
			isEnoughHeart = false;
		break;
	}
	}
	if (simonWeapon)
	{
		if (dynamic_cast<Whip*>(simonWeapon))
		{
			if (simonWeapon->GetLastFrame())
			{
				simonWeapon->ResetAnimation();
				DELETE_POINTER(simonWeapon);
			}
		}
		else
		{
			if (simonWeapon->GetHealth() <= 0)
			{
				DELETE_POINTER(simonWeapon);
			}
		}
	}
}

void CSimon::MakeSubWeapon(float x, float y, int nx)
{
	if (isUseSubWeapon)
	{
		switch (typeSubWeapon)
		{
		case SIMON_WEAPON::DANGER:
		{
			simonWeapon = new WeaponDanger(x, y, nx);
			heart -= SIMON_HEART_USE_WEAPON::DANGER_HEART;
			break;
		}
		case SIMON_WEAPON::AXE:
		{
			simonWeapon = new WeaponAxe(x, y, nx);
			heart -= SIMON_HEART_USE_WEAPON::AXE_HEART;
			break;
		}
		case SIMON_WEAPON::HOLY_WATER:
		{
			simonWeapon = new WeaponHolyWater(x, y, nx);
			heart -= SIMON_HEART_USE_WEAPON::HOLY_WATER_HEART;
			break;
		}
		case SIMON_WEAPON::STOP_WATCH:
		{
			isUsingStopWatch = true;
			timeUsingStopWatch = GetTickCount();
			heart -= SIMON_HEART_USE_WEAPON::STOP_WATCH_HEART;
			break;
		}
		}
	}
}

//Xử lí

void CSimon::Attack()
{
	if (isUseSubWeapon
		&& isAttack == false
		&& isSit == false)
	{
		isCanAttack = false;
		isAttack = true;
	}
	else
	{
		isCanAttack = false;
		isAttack = true;
		simonWeapon = new Whip(x, y, nx, weaponLevel);
	}

}

void CSimon::Sit()
{
	if (isJump)
	{
		state = SIMON_STATE_JUMP;
		return;
	}
	else if (isAttack)
	{
		state = SIMON_STATE_ATTACK;
		return;
	}
	else
	{
		vx = 0; //Khi ngồi không được di chuyển
		isSit = true;
	}
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
	if (isAttack)
	{
		state = SIMON_STATE_ATTACK;
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
	vx = -SIMON_WALKING_SPEED;

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
	if (isAttack)
	{
		isAttack = false;
		animations[SIMON_ANI_ATTACK]->reset();
	}
	isJump = false;
	y -= RESET_SIMON_AFTER_JUMP;
	this->state = SIMON_STATE_IDLE;
}

void CSimon::ResetAfterSit()
{
	if (isSit)
	{
		if (isAttack)
		{
			int ani = SIMON_ANI_SIT_ATTACK;
			if (animations[ani]->getLastFrame())
			{
				isAttack = false;
				animations[SIMON_ANI_SIT_ATTACK]->reset();
				y -= RESET_SIMON_AFTER_SIT;
			}
		}
		else if (isAttack == false && isResetSitAfterAttack == true)
		{
			isSit = false;
			isAttack = false;
			isResetSitAfterAttack = false;
			animations[SIMON_ANI_SIT_ATTACK]->reset();
			y -= RESET_SIMON_AFTER_SIT;
			state = SIMON_STATE_IDLE;
		}
	}
}


void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if ((isSit || isJump))
	{
		left = x + 15;
		top = y;
		right = x + 15 + SIMON_SIT_BBOX_WIDTH;
		bottom = y + SIMON_SIT_BBOX_HEIGHT;
	}
	else
	{
		left = x + 15;
		top = y;
		right = x + 15 + SIMON_SIT_BBOX_WIDTH;
		bottom = y + SIMON_BBOX_HEIGHT;
	}

}


