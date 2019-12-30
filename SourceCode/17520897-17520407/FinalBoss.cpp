#include "FinalBoss.h"

FinalBoss::FinalBoss() {
	this->AddAnimation(FINAL_BOSS_ANI_FACE);
	this->AddAnimation(FINAL_BOSS_ANI_BODY_START_ATTACK);
	this->AddAnimation(FINAL_BOSS_ANI_BODY_ATTACK);
	this->AddAnimation(FINAL_BOSS_ANI_CHAOS_IDLE);
	this->AddAnimation(FINAL_BOSS_ANI_CHAOS_START_ATTACK);
	this->AddAnimation(FINAL_BOSS_ANI_CHAOS_ATTACK);
	ani = FINAL_BOSS_ANI_FACE_INDEX;
	bodyAni = FINAL_BOSS_ANI_BODY_START_ATTACK_INDEX;
	nx = -1;
	mode = FINAL_BOSS_NOMAL_MODE;
	width = FINAL_BOSS_NOMAL_BB_WIDTH;
	height = FINAL_BOSS_NOMAL_BB_HEIGHT;
	this->state = FINAL_BOSS_STATE_START;
	isHasBody = false;
	makeTime = GetTickCount();
	xTarget = yTarget = 0;
	vy = -FACE_START_VY;
	isInvisiable = false;
	isHurt = false;
	isFirstAttack = true;
	isHasFace = true;
	this->health = 1;
	damageCount = 0;
	isHightJump = false;
	isJump = true;
}
void FinalBoss::Render() {

	if (mode == FINAL_BOSS_NOMAL_MODE)
	{

		switch (state)
		{
		case FINAL_BOSS_STATE_START:
			ani = FINAL_BOSS_ANI_FACE_INDEX;
			break;
		case FINAL_BOSS_STATE_START_ATTACK:
			bodyAni = FINAL_BOSS_ANI_BODY_START_ATTACK_INDEX;
			break;
		case FINAL_BOSS_STATE_ATTACK:
			bodyAni = FINAL_BOSS_ANI_BODY_ATTACK_INDEX;
			break;
		}
		float xBody;
		if (nx > 0)
			xBody = x - OFFSET_FOR_BODY_FLIP_X;
		else
			xBody = x - OFFSET_FOR_BODY_X;
		if (isInvisiable == false)
		{
			if (this->nx < 0)
			{
				if (isHasBody)
					animations[bodyAni]->Render(xBody, y);
				if (isHasFace)
					animations[ani]->Render(x, y);
			}
			else
			{
				if (isHasBody)
					animations[bodyAni]->RenderFlipX(xBody, y, FLIP_OFFSET_FOR_BODY);
				if (isHasFace)
					animations[ani]->RenderFlipX(x, y, FLIP_OFFSET_FOR_HEAD);
			}
			RenderBoundingBox(x, y);
		}
	}
	else
	{
		switch (state)
		{
		case CHAOS_BOSS_STATE_IDLE:
			ani = FINAL_BOSS_ANI_CHAOS_IDLE_INDEX;
			break;
		case CHAOS_BOSS_STATE_START_ATTACK:
			if (isShot)
				ani = FINAL_BOSS_ANI_CHAOS_IDLE_INDEX;
			else
				ani = FINAL_BOSS_ANI_CHAOS_START_ATTACK_INDEX;
			break;
		case CHAOS_BOSS_STATE_ATTACK:
			ani = FINAL_BOSS_ANI_CHAOS_ATTACK_INDEX;
			break;
		}
		if (this->nx < 0)
			animations[ani]->Render(x, y);
		else
			animations[ani]->RenderFlipX(x, y, 25);
		RenderBoundingBox(x, y);
	}
	for (int i = 0; i < weapons.size(); i++)
	{
		if (weapons[i] != NULL)
		{
			weapons[i]->Render();
		}
	}
}
void FinalBoss::RenderCurrentFrame() {

	if (mode == FINAL_BOSS_NOMAL_MODE)
	{
		for (int i = 0; i < weapons.size(); i++)
		{
			if (weapons[i] != NULL)
			{
				weapons[i]->Render();
			}
		}
		switch (state)
		{
		case FINAL_BOSS_STATE_START:
			ani = FINAL_BOSS_ANI_FACE_INDEX;
			break;
		case FINAL_BOSS_STATE_START_ATTACK:
			bodyAni = FINAL_BOSS_ANI_BODY_START_ATTACK_INDEX;
			break;
		case FINAL_BOSS_STATE_ATTACK:
			bodyAni = FINAL_BOSS_ANI_BODY_ATTACK_INDEX;
			break;
		}
		float xBody;
		if (nx > 0)
			xBody = x - OFFSET_FOR_BODY_FLIP_X;
		else
			xBody = x - OFFSET_FOR_BODY_X;
		if (isInvisiable == false)
		{
			if (this->nx < 0)
			{
				if (isHasBody)
					animations[bodyAni]->RenderCurrentFrame(xBody, y);
				if (isHasFace)
					animations[ani]->RenderCurrentFrame(x, y);
			}
			else
			{
				if (isHasBody)
					animations[bodyAni]->RenderCurrentFrameFlipX(xBody, y, FLIP_OFFSET_FOR_BODY);
				if (isHasFace)
					animations[ani]->RenderCurrentFrameFlipX(x, y, FLIP_OFFSET_FOR_HEAD);
			}
			RenderBoundingBox(x, y);
		}
	}
	else
	{
		switch (state)
		{
		case CHAOS_BOSS_STATE_IDLE:
			ani = FINAL_BOSS_ANI_CHAOS_IDLE_INDEX;
			break;
		case CHAOS_BOSS_STATE_START_ATTACK:
			ani = FINAL_BOSS_ANI_CHAOS_START_ATTACK_INDEX;
			break;
		case CHAOS_BOSS_STATE_ATTACK:
			ani = FINAL_BOSS_ANI_CHAOS_ATTACK_INDEX;
			break;
		}
		if (this->nx < 0)
			animations[ani]->RenderCurrentFrame(x, y);
		else
			animations[ani]->RenderCurrentFrameFlipX(x, y, FLIP_OFFSET_FOR_CHAOS);

		RenderBoundingBox(x, y);
	}
}

void FinalBoss::Damage(int damage)
{
	if (isActive)
	{
		if (mode == FINAL_BOSS_NOMAL_MODE)
		{
			health -= damage;
			if (this->health <= 0)
			{
				DebugOut(L"\nChangeMode");
				health = FINAL_BOSS_MAX_HEATH;
				mode = FINAL_BOSS_CHAOS_MODE;
				isHasBody = false;
				isInvisiable = false;
				isHasFace = true;
				width = CHAOS_BOSS_BB_WIDTH;
				height = CHAOS_BOSS_BB_HEIGHT;
				y -= PULL_UP_CHAOS_BOSS;
				lastTimeAttack = GetTickCount();
			}
			else
				isHasFace = false;
		}
		else
		{
			damageCount += damage;
			if (damageCount >= TAKE_DAMAGE_COUNT)
			{
				health -= damage;
				damageCount = 0;
			}
		}

	}
}

void FinalBoss::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	bossHealth = this->health;
	CSimon *simon = CSimon::getInstance();
	float sx, sy;
	simon->GetPosition(sx, sy);
	CGameObject::Update(dt);
	DWORD now = GetTickCount();
	for (int i = 0; i < weapons.size(); i++)
	{
		if (weapons[i] != NULL)
		{
			if (weapons[i]->GetHealth() <= 0)
			{
				DELETE_POINTER(weapons[i]);
			}
			else
			{
				float weaponVx;
				float weaponVy;
				weapons[i]->GetSpeed(weaponVx, weaponVy);
				if (nx > 0)
					weaponVx += FINAL_BOSS_WEAPON_VX_PLUS;
				else
					weaponVx -= FINAL_BOSS_WEAPON_VX_PLUS;
				if (mode == FINAL_BOSS_CHAOS_MODE)
				{
					if (i == FINAL_BOSS_TOP_WEAPON_INDEX)
						weaponVy += CHAOS_BOSS_TOP_WEAPON_VY_PLUS;
					if (i == FINAL_BOSS_MIDDLE_WEAPON_INDEX)
						weaponVy += CHAOS_BOSS_MIDDLE_WEAPON_VY_PLUS;
					if (i == FINAL_BOSS_BOTTOM_WEAPON_INDEX)
						weaponVy += CHAOS_BOSS_BOTTOM_WEAPON_VY_PLUS;
				}
				else
				{
					if (i != FINAL_BOSS_MIDDLE_WEAPON_INDEX)
					{

						if (i == FINAL_BOSS_BOTTOM_WEAPON_INDEX)
							weaponVy -= FINAL_BOSS_WEAPON_VY_PLUS;
						else weaponVy += FINAL_BOSS_WEAPON_VY_PLUS;
					}
				}
				weapons[i]->SetSpeed(weaponVx, weaponVy);
				weapons[i]->Update(dt);
			}
		}
	}
	if (mode == FINAL_BOSS_NOMAL_MODE)
	{
		switch (state)
		{
		case FINAL_BOSS_STATE_START:
			if (y <= yTarget)
			{
				y = yTarget;
				isHasBody = true;
				state = FINAL_BOSS_STATE_START_ATTACK;
				lastTimeAttack = GetTickCount();
			}
			else
			{
				y += dy;
				lockCameraX = CGame::GetInstance()->GetCamPos_x();
				isLockCamX = true;
			}
			break;
		case FINAL_BOSS_STATE_START_ATTACK:
			if (isInvisiable)
			{
				if (now - lastTimeInvisiable > FINAL_BOSS_INVISIABLE_DELAY)
				{
					isInvisiable = false;
					lastTimeAttack = GetTickCount();
					isHasFace = true;
					if (isFirstAttack == false)
					{
						if ((sx + SIMON_OFFSET_TO_BBOX_X + SIMON_BBOX_WIDTH / 2) > (lockCameraX + SCREEN_WIDTH) / 2)
						{
							nx = 1;
							int maxRand = (lockCameraX + SCREEN_WIDTH) / 2 - FINAL_BOSS_MIN_START_ATTACK_OFFSET;
							int minRand = (lockCameraX + FINAL_BOSS_MIN_START_ATTACK_OFFSET);
							float random = rand() % maxRand + minRand;
							x = random;
						}
						else
						{
							nx = -1;
							int minRand = (lockCameraX + SCREEN_WIDTH) / 2;
							int maxRand = (lockCameraX + SCREEN_WIDTH - FINAL_BOSS_MAX_START_ATTACK_OFFSET);
							float random = rand() % maxRand + minRand;
							x = random;
						}
					}
				}
			}
			else
			{
				isActive = true;
				if (now - lastTimeAttack > FINAL_BOSS_START_ATTACK_DELAY)
				{
					state = FINAL_BOSS_STATE_ATTACK;
					lastTimeAttack = GetTickCount();
					isStartAttack = true;
				}
			}
			break;
		case FINAL_BOSS_STATE_ATTACK:
			if (isStartAttack)
			{
				MakeWeapon();
				isStartAttack = false;
			}
			isFirstAttack = false;
			if (now - lastTimeAttack > FINAL_BOSS_ATTACK_DELAY)
			{
				state = FINAL_BOSS_STATE_START_ATTACK;
				lastTimeInvisiable = GetTickCount();
				isInvisiable = true;
			}
			break;
		}
	}
	else
	{
		vy += CHAOS_BOSS_GRAVITY * dt;
		if (sx <= LOCK_CAMERA_X || (sx) >= LOCK_CAMERA_X + CHAOS_BOSS_OFFSET_MAX_X)
		{
			isHightJump = true;
		}
		else
		{
			isHightJump = false;
		}
		if (x <= LOCK_CAMERA_X)
			x = LOCK_CAMERA_X;
		if (x >= CGame::GetInstance()->GetCamPos_x() + CHAOS_BOSS_OFFSET_MAX_X)
			x = CGame::GetInstance()->GetCamPos_x() + CHAOS_BOSS_OFFSET_MAX_X;
		DWORD now = GetTickCount();
		if (sx < x)
			nx = -1;
		else
			nx = 1;
		if (isLock)
		{
			state = CHAOS_BOSS_STATE_IDLE;
			vx = 0;
			if (now - lastLockTime > CHAOS_BOSS_LOCK_TIME)
			{
				isLock = false;
			}
		}
		else
		{
			isLock = false;
			switch (state)
			{
			case CHAOS_BOSS_STATE_IDLE:
				vx = 0;
				isAttack = false;
				if (now - lastTimeAttack > CHAOS_BOSS_START_ATTACK_DELAY)
				{
					state = CHAOS_BOSS_STATE_START_ATTACK;
				}
				break;
			case CHAOS_BOSS_STATE_START_ATTACK:
				if (abs(sx - x) >= CHAO_BOSS_SHOT_SIMON_DISTANCE)
				{
					isShot = true;
					isHightJump = false;
					isJump = false;
				}
				else
					isJump = true;
				if (animations[ani]->getLastFrame()
					&& isAttack == false)
				{
					if (isShot)
					{
						MakeWeapon();
						vx = 0;
					}
					else {
						if (isHightJump)
							vy = -CHAOS_BOSS_HIGHT_JUMP_VY;
						else
							vy = -CHAOS_BOSS_SHORT_JUMP_VY;
						vx = (abs(x - (sx + SIMON_OFFSET_TO_BBOX_X)) / dt) / TIME_TO_TOUCH_SIMON_VX;
					}
					if (sx < x)
						vx = -vx;
					lastTimeAttack = GetTickCount();
					animations[FINAL_BOSS_ANI_CHAOS_START_ATTACK_INDEX]->reset();
					state = CHAOS_BOSS_STATE_ATTACK;
				}
				break;
			case CHAOS_BOSS_STATE_ATTACK:
				if (isShot)
				{
					if (now - lastTimeAttack > CHAOS_BOSS_SHOT_DELAY)
					{
						isShot = false;
						state = CHAOS_BOSS_STATE_IDLE;
						lastTimeAttack = GetTickCount();
					}
				}
				else
				{
					lastTimeAttack = GetTickCount();
				}
				isAttack = true;
				break;
			}
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
				x += min_tx * dx + nx * 0.4f;	// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty * dy + ny * 0.4f;
				if (nx != 0) vx = 0;
				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					if (dynamic_cast<CGround *>(e->obj))// if e->obj is Goomba 
					{
						if (isAttack && isJump && isShot == false)
						{
							isAttack = false;
							isJump = false;
							state = CHAOS_BOSS_STATE_IDLE;
						}
					}
				}
			}
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}
	}
	if (checkAABBTouch(simon))
	{
		simon->TouchEnemy(nx);
	}
}
void FinalBoss::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	if (isHasFace && isInvisiable == false)
	{
		left = x;
		top = y;
		right = x + width;
		bottom = y + height;
	}
}

void FinalBoss::MakeWeapon() {
	weapons.clear();
	for (int i = 0; i < FINAL_BOSS_WEAPON_QUANTITY; i++)
	{
		WeaponProjectile *weapon = new WeaponProjectile(x, y, nx);
		float offsetX, offsetY;
		if (mode == FINAL_BOSS_NOMAL_MODE)
		{
			offsetX = FINAL_BOSS_WEAPON_OFFSET_X;
			offsetY = FINAL_BOSS_WEAPON_OFFSET_Y;
			if (nx > 0)
				offsetX = -offsetX;
		}
		else
		{
			offsetX = CHAOS_BOSS_BB_WIDTH / 2;
			offsetY = FINAL_BOSS_WEAPON_OFFSET_Y;
		}
		weapon->SetPositionWithEnemey(offsetX, offsetY);
		float weaponSpeedX = FINAL_BOSS_WEAPON_VX;
		if (nx < 0)
			weaponSpeedX = -weaponSpeedX;
		weapon->SetSpeed(weaponSpeedX, 0);
		weapons.push_back(weapon);
	}
}
