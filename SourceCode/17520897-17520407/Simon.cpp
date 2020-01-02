#include <algorithm>
#include "Simon.h"
#include "Scenes.h"
#include "SoundController.h"
CSimon * CSimon::__instance = NULL;
CSimon::CSimon()
{
	subWeaponQuantity = 1;
	isOnGround = true;
	isDeath = false;
	isFightingBoss = false;
	onStairDistance = 0;
	isCanOutStair = false;
	isCanSetStair = false;
	isJump = false;
	isSit = false;
	isAttack = false;
	isOnStair = false;
	isFreeze = false;
	isCanAttack = true;
	isCanAttackSubWeapon = true;
	isCanJump = true;
	isCanOnStair = false;
	isUsingStopWatch = false;
	isUsingDoubleShot = false;
	isUsingCross = false;
	isInvisible = false;
	lastAttackTime = -1;
	lastAttackSide = 1;
	isUseSubWeapon = false;
	isEnoughHeart = false;
	isJumpAttack = false;
	isResetSitAfterAttack = false;
	lastAttackTime = -1;
	lastAttackSide = 1;
	isHasSubWeapon = false;
	typeSubWeapon = SIMON_WEAPON::NONE;
	stairType = STAIR_TYPE::NOSTAIR;
	weaponLevel = SIMON_WEAPON_LEVEL_1;
	heart = SIMON_DEFAULT_HEART;
	health = SIMON_MAX_HEALTH;
	live = SIMON_LIVE;
	currentScene = -1;
	nx = -1;
	score = 0;
	isAutoGo = false;
	autoGoDistance = 0;
	simonAutoGoDistance = 0;
	endWalkOnStairTime = GetTickCount();
	stairNx = 0;
	stairNy = 0;
	stairActiveNy = 0;
	ny = 0;
	isAutoGoOutStair = false;
	isHurt = false;
	isLock = false;
	isTouchWall = false;
	health = 8;
}
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
		isSit = false;
		state = SIMON_STATE_WALKING_RIGHT;
		if (nx > 0)
			vx = SIMON_AUTO_WALKING_SPEED;
		else
			vx = -SIMON_AUTO_WALKING_SPEED;
		this->x += vx * dt;
		simonAutoGoDistance += abs(vx * dt);
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
	else if (isAutoGoToStair && isOnStair)
	{
		if (nx > 0)
		{
			vx = SIMON_AUTO_WALKING_SPEED;
			state = SIMON_STATE_WALKING_RIGHT;
		}
		else
		{
			vx = -SIMON_AUTO_WALKING_SPEED;
			state = SIMON_STATE_WALKING_LEFT;

		}
		this->x += vx * dt;
		vy = 0;
		simonAutoGoDistance += abs(vx * dt);
		if (simonAutoGoDistance > autoGoDistance)
		{
			isAutoGoToStair = false;
			simonAutoGoDistance = 0;
			autoGoDistance = 0;
			isCanOutStair = false;
			onStairDistance = 0;
		}
	}
	else if (isAutoGoOutStair)
	{
		if (nx > 0)
		{
			vx = SIMON_AUTO_WALKING_SPEED;
			state = SIMON_STATE_WALKING_RIGHT;
		}
		else
		{
			vx = -SIMON_AUTO_WALKING_SPEED;
			state = SIMON_STATE_WALKING_LEFT;
		}
		this->x += vx * dt;
		vy = 0;
		simonAutoGoDistance += abs(vx * dt);
		isCanOutStair = false;
		isOnStair = false;
		isCanOnStair = false;
		if (simonAutoGoDistance > autoGoDistance)
		{
			isAutoGoOutStair = false;
			simonAutoGoDistance = 0;
			autoGoDistance = 0;
			onStairDistance = 0;
			isCanOutStair = false;
			isCanSetStair = true;
			ny = 0;
		}

	}
	else if (CGame::GetInstance()->GetCamAutoGo())
	{
		state = SIMON_STATE_IDLE;
	}
	else
	{
		simonAutoGoDistance = 0;
		if (x <= LOCK_CAMERA_X - SIMON_OFFSET_TO_BBOX_X)
			x = LOCK_CAMERA_X - SIMON_OFFSET_TO_BBOX_X;
		if (x >= CGame::GetInstance()->GetCamPos_x() + LOCK_CAMERA_OFFSET_X)
		{
			x = CGame::GetInstance()->GetCamPos_x() + LOCK_CAMERA_OFFSET_X;
		}
		DWORD now = GetTickCount();
		if (now - startUntouchableTime >= SIMON_UNTOUCHABLE_TIME)
		{
			isUntouchable = false;
			startUntouchableTime = 0;
		}
		if (isOnStair == false)
		{
			if (isHurt)
			{
				if (now - startHurtTime < 250)
				{

					if (isTouchWall == false)
					{
						vy = -PUSH_SIMON_TOUCH_ENEMIES_VY;
						if (nx > 0)
						{
							vx = -PUSH_SIMON_TOUCH_ENEMIES_VX;
						}
						else
						{
							vx = +PUSH_SIMON_TOUCH_ENEMIES_VX;
						}
					}
					else if (isJump == false)
					{
						vy = -PUSH_SIMON_TOUCH_ENEMIES_VY;
						vx = 0;
					}
				}
				else
				{
					vx = 0;
					if (isJump)
						vy = PUSH_SIMON_TOUCH_ENEMIES_VY * 2;
					else
						vy = PUSH_SIMON_TOUCH_ENEMIES_VY;
				}
				x += vx * dt;
				y += vy * dt;
			}
			else
			{
				if (isLock)
				{
					vy = 0;
					if (health <= 0)
					{
						isDeath = true;
						live--;
						isLock = false;
						startDeathTime = GetTickCount();
						state = SIMON_STATE_DIE;
					}
				}
				else
				{
					if (vy > 0)
					{
						vy += SIMON_FALLING_GRAVITY * dt;
					}
					else
						vy += SIMON_GRAVITY * dt;
				}

			}

		}
		else if (isOnStair && isAttack == false)
		{

			if (nx > 0)
				vx = SIMON_ON_STAIR_SPEED_X;
			else
				vx = -SIMON_ON_STAIR_SPEED_X;
			if (ny > 0)
				vy = -SIMON_ON_STAIR_SPEED_Y;
			else
				vy = SIMON_ON_STAIR_SPEED_X;
			if (onStairDistance < SIMON_ON_STAIR_DISTANCE)
			{
				isCanAttack = false;
				x += vx * dt;
				y += vy * dt;
				onStairDistance += abs(vx * dt);
				if (onStairDistance > 8.0f)
				{
					if (nx > 0)
						x -= onStairDistance - 8.0f;
					else
						x += onStairDistance - 8.0f;
				}
				if (ny > 0)
					state = SIMON_STATE_ON_STAIR_UP;
				else
					state = SIMON_STATE_ON_STAIR_DOWN;
				endWalkOnStairTime = GetTickCount();

			}
			else
			{
				if (ny > 0)
					state = SIMON_STATE_ON_STAIR_IDLE_UP;
				else
					state = SIMON_STATE_ON_STAIR_IDLE_DOWN;

			}
		}
		// Kiểm tra để hạn chế việc nhảy và đánh liên tục;
		Attacking(dt);
		Jumping();
		UsingWeapon();
		ResetAfterSit();
		UpdateStopWatch();
		UpdateCross();
		UpdateInvisible();



		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			if (isOnStair == false
				&& isHurt == false)
			{
				x += dx;
				y += dy;
			}
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			// block
			if (isOnStair == false)
			{
				x += min_tx * dx + nx * 0.4f;	// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty * dy + ny * 0.4f;
			}
			if (nx != 0) vx = 0;
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CGround *>(e->obj))// if e->obj is Goomba 
				{
					isTouchWall = false;
					if (isHurt)
					{
						if (health > 0)
						{
							state = SIMON_STATE_IDLE;
							isHurt = false;
						}
						else
						{
							isHurt = false;
							isDeath = true;
							live--;
							startDeathTime = GetTickCount();
							state = SIMON_STATE_DIE;
							SoundController::Play(SIMON_SOUND::LIVE_LOST);
						}

					}
					if (isJump)
						ResetAfterJump();
					this->ny = 0;
					isFalling = false;
					isCanSetStair = true;
					if (isAutoGoOutStair == false)
						isCanOnStair = false;
					isCanOutStair = false;
					isOnGround = true;
					vy = 0;
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}

}


void CSimon::UpdateCheckStair(vector<LPGAMEOBJECT> * coCheckStair)
{
	for (int i = 0; i < coCheckStair->size(); i++)
	{
		if (dynamic_cast<CheckStair*> (coCheckStair->at(i)))
		{
			CheckStair* checkStair = dynamic_cast<CheckStair*> (coCheckStair->at(i));
			if (this->checkAABBTouch(checkStair))
			{
				isCanOnStair = true;
				float width, height;
				checkStair->GetWidthHeight(width, height);
				if (isOnStair
					&& this->ny != checkStair->ny
					&& this->ny != 0
					)
				{
					if (this->ny > 0 && this->y + SIMON_BBOX_HEIGHT - height - 2 <= checkStair->y + height) // -2 để đẩy 1 ít ko để bị chạm với ground
						isCanOutStair = true;
					if (this->ny < 0 && this->y + SIMON_BBOX_HEIGHT - height + 2 >= checkStair->y) // +2 để đẩy 1 ít ko để bị chạm với ground
					{
						isAutoGoOutStair = true;
						autoGoDistance = SIMON_AUTO_GO_STAIR_DISTANCE;
					}
				}
			}
		}
	}
}

void CSimon::UpdateSimonWeapon(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	for (int i = 0; i < simonWeapon.size(); i++)
	{
		if (simonWeapon[i] != NULL)
		{
			if (dynamic_cast<Whip*>(simonWeapon[i]))
			{
				simonWeapon[i]->SetPosition(x, y);
				simonWeapon[i]->SetRenderPos(x, y);
			}
			simonWeapon[i]->Update(dt, coObjects);
		}
	}
}

void CSimon::Render()
{
	int ani;

	for (int i = 0; i < simonWeapon.size(); i++)
	{
		if (simonWeapon[i])
		{
			simonWeapon[i]->Render();
		}
	}

	if (isFreeze)
	{
		ani = SIMON_ANI_FREEZE;
	}
	else if (isHurt)
	{
		ani = SIMON_ANI_HURT;
	}
	else if (isSit)
	{
		if (isInvisible)
		{
			if (isAttack)
				ani = SIMON_ANI_SIT_ATTACK__INVISIBLE;
			else
				ani = SIMON_ANI_SIT__INVISIBLE;
		}
		else
		{
			if (isAttack)
				ani = SIMON_ANI_SIT_ATTACK;
			else
				ani = SIMON_ANI_SIT;
		}

	}
	else if (isJump)
	{
		if (isInvisible)
		{
			if (isAttack)
				ani = SIMON_ANI_SIT_ATTACK__INVISIBLE;
			else
				ani = SIMON_ANI_SIT__INVISIBLE;
		}
		else
		{
			if (isAttack)
				ani = SIMON_ANI_ATTACK;
			else
				ani = SIMON_ANI_SIT;
		}
	}
	else
	{
		if (isInvisible)
		{
			switch (state)
			{
			case SIMON_STATE_DIE:
				ani = SIMON_ANI_DIE;
				break;
			case SIMON_STATE_IDLE:
				ani = SIMON_ANI_IDLE__INVISIBLE;
				break;
			case SIMON_STATE_WALKING_LEFT:
				ani = SIMON_ANI_WALKING__INVISIBLE;
				break;
			case SIMON_STATE_WALKING_RIGHT:
				ani = SIMON_ANI_WALKING__INVISIBLE;
				break;
			case SIMON_STATE_ATTACK:
				if (isOnStair)
				{
					if (ny > 0)
						ani = SIMON_ANI_ON_STAIR__UP_ATTACK__INVISIBLE;
					else
						ani = SIMON_ANI_ON_STAIR__DOWN_ATTACK__INVISIBLE;
				}
				else
				{
					ani = SIMON_ANI_ATTACK__INVISIBLE;
				}
				break;
			case SIMON_STATE_ON_STAIR_DOWN:
				ani = SIMON_ANI_ON_STAIR_DOWN__INVISIBLE;
				break;
			case SIMON_STATE_ON_STAIR_UP:
				ani = SIMON_ANI_ON_STAIR_UP__INVISIBLE;
				break;
			case SIMON_STATE_ON_STAIR_IDLE_UP:
				ani = SIMON_ANI_ON_STAIR_IDLE_UP__INVISIBLE;
				break;
			case SIMON_STATE_ON_STAIR_IDLE_DOWN:
				ani = SIMON_ANI_ON_STAIR_IDLE_DOWN__INVISIBLE;
				break;
			}
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
				if (isOnStair)
				{
					if (ny > 0)
						ani = SIMON_ANI_ON_STAIR__UP_ATTACK;
					else
						ani = SIMON_ANI_ON_STAIR__DOWN_ATTACK;
				}
				else
				{
					ani = SIMON_ANI_ATTACK;
				}
				break;
			case SIMON_STATE_ON_STAIR_DOWN:
				ani = SIMON_ANI_ON_STAIR_DOWN;
				break;
			case SIMON_STATE_ON_STAIR_UP:
				ani = SIMON_ANI_ON_STAIR_UP;
				break;
			case SIMON_STATE_ON_STAIR_IDLE_UP:
				ani = SIMON_ANI_ON_STAIR_IDLE_UP;
				break;
			case SIMON_STATE_ON_STAIR_IDLE_DOWN:
				ani = SIMON_ANI_ON_STAIR_IDLE_DOWN;
				break;
			case SIMON_STATE_INTO_GATE:
				ani = 33;
			}
		}
	}

	int alpha = 255;
	if (isUntouchable
		&& isHurt == false
		&& isDeath == false) alpha = 128;
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
	case LARGE_HEART:
	case DOUBLE_SHOT:
	case POT_ROAST:
	case MAGIC_CRYSTAL:
		SoundController::Play(SIMON_SOUND::COLLECT_ITEM);
		break;
	case WHIP_UPGRADE:
	case DANGER_ITEM:
	case AXE_ITEM:
	case HOLY_WATER_ITEM:
	case STOP_WATCH_ITEM:
		SoundController::Play(SIMON_SOUND::COLLECT_WEAPON);
	case RED_MONEY_BAG:
	case PURPLE_MONEY_BAG:
	case WHITE_MONEY_BAG:
		SoundController::Play(SIMON_SOUND::COLLECT_MONEY);
		break;
	case INVI_POTION:
		SoundController::Play(SIMON_SOUND::COLLECT_INVISIABLE);
		break;
	case CROSS_ITEM:
		SoundController::Play(SIMON_SOUND::USING_CROSS);
		break;
	}
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
		if (typeSubWeapon != SIMON_WEAPON::DANGER)
		{
			subWeaponQuantity = 1;
			isUsingDoubleShot = false;
		}
		ChangeSubWeapon(SIMON_WEAPON::DANGER);
		break;
	case AXE_ITEM:
		if (typeSubWeapon != SIMON_WEAPON::AXE)
		{
			subWeaponQuantity = 1;
			isUsingDoubleShot = false;
		}
		ChangeSubWeapon(SIMON_WEAPON::AXE);
		break;
	case HOLY_WATER_ITEM:
		if (typeSubWeapon != SIMON_WEAPON::HOLY_WATER)
		{
			subWeaponQuantity = 1;
			isUsingDoubleShot = false;
		}
		ChangeSubWeapon(SIMON_WEAPON::HOLY_WATER);
		break;
	case STOP_WATCH_ITEM:
		ChangeSubWeapon(SIMON_WEAPON::STOP_WATCH);
		break;
	case CROSS_ITEM:
		isUsingCross = true;
		timeUsingCross = GetTickCount();
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
	case POT_ROAST:
		health = SIMON_MAX_HEALTH;
		break;
	case INVI_POTION:
		isInvisible = true;
		timeUsingInvisible = GetTickCount();
		break;
	case DOUBLE_SHOT:
		isUsingDoubleShot = true;
		subWeaponQuantity = 2;
		break;
	case MAGIC_CRYSTAL:
		Scenes::GetInstance()->NextScenes();
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
	for (int i = 0; i < simonWeapon.size(); i++)
	{
		if (simonWeapon[i])
		{
			simonWeapon[i]->ResetAnimation();
			isAttack = false;
			isUseSubWeapon = false;
			DELETE_POINTER(simonWeapon[i]);
		}
		if (animations[ani]->getLastFrame())
		{
			isFreeze = false;
			animations[ani]->reset();
		}
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
	if (isUsingStopWatch)
	{
		DWORD now = GetTickCount();
		if (now - timeUsingStopWatch >= USING_STOP_WATCH_TIME)
		{
			isUsingStopWatch = false;
			SoundController::Play(SIMON_SOUND::DISABLE_STOPWATCH);
			SoundController::Stop(SIMON_SOUND::ENABLE_STOPWATCH);
		}
	}
}

void CSimon::UpdateCross()
{
	if (isUsingCross)
	{
		DWORD now = GetTickCount();
		if (now - timeUsingCross >= USING_CROSS_TIME)
		{
			isUsingCross = false;
			CSpawner::GetInstance()->resetAfterUsingCross();
		}
	}
}

void CSimon::UpdateInvisible()
{
	if (isInvisible)
	{
		isUntouchable = true;
	}
	if (isInvisible
		&& isAttack == false)
	{
		DWORD now = GetTickCount();
		if (now - timeUsingInvisible >= 3000)
		{
			isUntouchable = false;
			isInvisible = false;
			SoundController::Play(SIMON_SOUND::COLLECT_INVISIABLE);
		}
	}
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);
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
		case SIMON_STATE_DIE:
			vx = 0;
			break;
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
		case SIMON_STATE_ON_STAIR_UP:
			OnStairUp();
			break;
		case SIMON_STATE_ON_STAIR_DOWN:
			OnStairDown();
			break;
		case SIMON_STATE_ON_STAIR_IDLE_UP:
		case SIMON_STATE_ON_STAIR_IDLE_DOWN:
		case SIMON_STATE_INTO_GATE:
			vx = 0;
			vy = 0;
			break;
		}
	}

}


//Xử lí khi chạm enemy
void CSimon::TouchEnemy(int nx) {
	if (isDeath == false)
	{
		if (isOnStair == false && isLock == false)
		{
			if (isUntouchable == false)
			{
				this->nx = -nx;
				isHurt = true;
				isUntouchable = true;
				StartUntouchable();
				startHurtTime = GetTickCount();
				isSit = false;
			}
		}
		else
		{
			isUntouchable = true;
			StartUntouchable();
		}
	}
	SoundController::Play(SIMON_SOUND::HURT);
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
			int ani;
			if (isInvisible)
				ani = SIMON_ANI_ATTACK__INVISIBLE;
			else
				ani = SIMON_ANI_SIT_ATTACK;
			bool isLastFrame = animations[ani]->getLastFrame();
			if (isHurt)
			{
				isAttack = false;
				lastAttackTime = GetTickCount();
				timeMakeWeapon = GetTickCount();
				animations[ani]->reset();
				isAttack = false;
				isUseSubWeapon = false;
			}
			else if (isLastFrame)
			{
				state = SIMON_STATE_SIT;
				lastAttackTime = GetTickCount();
				timeMakeWeapon = GetTickCount();
				animations[ani]->reset();
				isAttack = false;
				isUseSubWeapon = false;
			}
		}
		else if (isOnStair)
		{
			vx = 0;
			vy = 0;
			int ani = 0;
			if (isInvisible)
			{
				if (ny > 0)
					ani = SIMON_ANI_ON_STAIR__UP_ATTACK__INVISIBLE;
				else
					ani = SIMON_ANI_ON_STAIR__DOWN_ATTACK__INVISIBLE;
			}
			else
			{
				if (ny > 0)
					ani = SIMON_ANI_ON_STAIR__UP_ATTACK;
				else
					ani = SIMON_ANI_ON_STAIR__DOWN_ATTACK;
			}
			bool isLastFrame = animations[ani]->getLastFrame();
			if (isHurt)
			{
				isAttack = false;
				lastAttackTime = GetTickCount();
				timeMakeWeapon = GetTickCount();
				animations[ani]->reset();
				isAttack = false;
				isUseSubWeapon = false;
			}
			else if (isLastFrame)
			{
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
			else
				isOnGround = false;
			if (vx > 0)
			{
				if (nx > 0)
					vx = SIMON_WALKING_SPEED / 2;
				else
					vx = -SIMON_WALKING_SPEED / 2;

			}
			int ani;
			if (isInvisible)
				ani = SIMON_ANI_ATTACK__INVISIBLE;
			else
				ani = SIMON_ANI_ATTACK;
			bool isLastFrame = animations[ani]->getLastFrame();
			bool nextIsLastFrame = animations[ani]->getNextIsLastFrame();
			if (isHurt)
			{
				isAttack = false;
				lastAttackTime = GetTickCount();
				timeMakeWeapon = GetTickCount();
				animations[ani]->reset();
				isAttack = false;
				isUseSubWeapon = false;

			}
			else if (isLastFrame)
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
	if (isHurt == false)
	{

		DWORD now = GetTickCount();
		if (now - lastJumpTime >= SIMON_RESET_JUMP_TIME)
		{
			isCanJump = true;
		}
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
	for (int i = 0; i < simonWeapon.size(); i++)
	{
		if (simonWeapon[i] != NULL)
		{
			if (dynamic_cast<Whip*>(simonWeapon[i]))
			{
				if (isHurt)
				{
					simonWeapon[i]->ResetAnimation();
					DELETE_POINTER(simonWeapon[i]);
				}
				else if (simonWeapon[i]->GetLastFrame())
				{
					simonWeapon[i]->ResetAnimation();
					DELETE_POINTER(simonWeapon[i]);
				}
			}
			else
			{
				if (simonWeapon[i]->GetHealth() <= 0)
				{
					DELETE_POINTER(simonWeapon[i]);
				}
			}
		}
	}
}

void CSimon::MakeSubWeapon(float x, float y, int nx)
{
	if (isUseSubWeapon)
	{
		for (int i = 0; i < subWeaponQuantity; i++)
		{
			Weapon* weapon = NULL;
			switch (typeSubWeapon)
			{
			case SIMON_WEAPON::DANGER:
			{
				weapon = new WeaponDanger(x, y, nx);
				break;
			}
			case SIMON_WEAPON::AXE:
			{
				weapon = new WeaponAxe(x, y, nx);
				break;
			}
			case SIMON_WEAPON::HOLY_WATER:
			{
				weapon = new WeaponHolyWater(x, y, nx);
				break;
			}
			}
			simonWeapon.push_back(weapon);
		}
		switch (typeSubWeapon)
		{
		case SIMON_WEAPON::DANGER:
		{
			heart -= SIMON_HEART_USE_WEAPON::DANGER_HEART;
			break;
		}
		case SIMON_WEAPON::AXE:
		{
			heart -= SIMON_HEART_USE_WEAPON::AXE_HEART;
			break;
		}
		case SIMON_WEAPON::HOLY_WATER:
		{
			heart -= SIMON_HEART_USE_WEAPON::HOLY_WATER_HEART;
			break;
		}
		case SIMON_WEAPON::STOP_WATCH:
		{
			isUsingStopWatch = true;
			timeUsingStopWatch = GetTickCount();
			heart -= SIMON_HEART_USE_WEAPON::STOP_WATCH_HEART;
			SoundController::Play(SIMON_SOUND::ENABLE_STOPWATCH);

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
		Whip* whip = new Whip(x, y, nx, weaponLevel);
		simonWeapon.push_back(whip);
	}

}

void CSimon::OnStairUp()
{
	if (isSit)
	{
		state = SIMON_STATE_SIT;
		return;
	}
	if (isAttack)
	{
		state = SIMON_STATE_ATTACK;
		return;
	}
	if (isAutoGoToStair == false
		&& isOnStair
		&& isAutoGoOutStair == false)
	{
		DWORD now = GetTickCount();
		if (now - endWalkOnStairTime > SIMON_TIME_EACH_STAIR_STEP
			&& onStairDistance >= SIMON_ON_STAIR_DISTANCE)
		{
			if (stairNx == stairNy)
			{
				this->ny = 1;
				this->nx = 1;
			}
			else
			{
				this->ny = 1;
				this->nx = -1;
			}
			onStairDistance = 0;
		}

	}

}

void CSimon::OnStairDown()
{

	if (isSit)
	{
		state = SIMON_STATE_SIT;
		return;
	}
	if (isAttack)
	{
		state = SIMON_STATE_ATTACK;
		return;
	}
	if (isAutoGoToStair == false
		&& isOnStair
		&& isAutoGoOutStair == false)
	{
		DWORD now = GetTickCount();
		if (now - endWalkOnStairTime > SIMON_TIME_EACH_STAIR_STEP
			&& onStairDistance >= SIMON_ON_STAIR_DISTANCE)
		{
			if (stairNx == stairNy)
			{
				this->ny = -1;
				this->nx = -1;
			}
			else
			{
				this->ny = -1;
				this->nx = 1;
			}

			onStairDistance = 0;


		}

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
		if (isOnGround)
		{
			vx = 0; //Khi ngồi không được di chuyển
			isSit = true;
		}

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
	if (isOnGround)
	{
		vy = -SIMON_JUMP_SPEED_Y;
		isJump = true;
		isCanJump = false;
		lastJumpTime = GetTickCount();
		isOnGround = false;
	}

}

void CSimon::WalkingLeft()
{
	if (isAttack)
	{
		state = SIMON_STATE_ATTACK;
		return;
	}
	if (isHurt)
		return;
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
	if (isHurt)
		return;
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
	isOnGround = true;
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

void CSimon::Reset()
{
	isDeath = false;
	isJump = false;
	isSit = false;
	isAttack = false;
	isHurt = false;
	isUntouchable = false;
	health = 8;
	heart = 5;
	ChangeSubWeapon(NONE);
	SetState(SIMON_STATE_IDLE);
	onStairDistance = 0;
	isCanOutStair = false;
	isCanOnStair = false;
	subWeaponQuantity = 1;
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


