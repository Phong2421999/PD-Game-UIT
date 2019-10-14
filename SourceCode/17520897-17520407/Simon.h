#pragma once
#include "FrameWork/GameObject.h"
#include "CStaticObject.h"
#include "FrameWork/debug.h"

#include "GameConst.h"
#include "SimonConst.h"

#include"CEnemies.h"

#include "Ground.h"
#include "Weapon.h"
#include "Whip.h"
#include "WeaponDanger.h"

class CSimon: public CGameObject
{
private:
	bool isJump;
	bool isSit;
	bool isAttack;
	bool isFreeze;
	bool isFalling;
	bool isJumpAttack;

	bool isCanJump;
	bool isCanAttack;
	bool isUntouchable;

	DWORD startAttackTime;
	DWORD lastAttackTime;
	DWORD lastJumpTime;
	DWORD timeMakeWeapon;
	DWORD startUntouchableTime;

	DWORD timeFreeze;

	bool isUseSubWeapon;
	bool isHasSubWeapon;

	int lastAttackSide;

	bool isEnoughHeart;
	int heart;

	Weapon* simonWeapon;

	static CSimon *__instance;

	SIMON_WEAPON typeSubWeapon;
public:

	static CSimon* getInstance();
	CSimon()
	{
		isJump = false;
		isSit = false;
		isAttack = false;
		isFreeze = false;
		isCanAttack = true;
		isCanJump = true;
		lastAttackTime = -1;
		lastAttackSide = 1;
		isUseSubWeapon = false;
		isHasSubWeapon = false;
		isEnoughHeart = false;
		isJumpAttack = false;
		lastAttackTime = -1;
		lastAttackSide = 1;
		typeSubWeapon = SIMON_WEAPON::NONE;
		weaponLevel = SIMON_WEAPON_LEVEL_1;
		heart = 5;
	}
	//set thuộc tính
	void setUntouchable()
	{
		this->isUntouchable = !isUntouchable;
	}
	void setCanAttack(bool isCanAttack)
	{
		this->isCanAttack = isCanAttack;
	}
	void setUseSubWeapon(bool b)
	{
		this->isUseSubWeapon = b;
	}
	void setHasSubWeapon(bool b)
	{
		this->isHasSubWeapon = b;
	}
	void setFreeze(bool freeze)
	{
		this->isFreeze = freeze;
		timeFreeze = 0;
	}
	//get thuộc tính
	bool getUseSubWeapon()
	{
		return isUseSubWeapon;
	}
	bool getEnoughHeart()
	{
		return isEnoughHeart;
	}
	bool getHasSubWeapon()
	{
		return isHasSubWeapon;
	}
	bool getJump() {
		return isJump;
	}
	bool getAttack()
	{
		return isAttack;
	}
	bool getSit()
	{
		return isSit;
	}
	bool getCanAttack()
	{
		return isCanAttack;
	}
	bool getCanJump()
	{
		return isCanJump;
	}
	bool getUntouchable()
	{
		return isUntouchable;
	}
	bool getFreeze()
	{
		return isFreeze;
	}
	//Xử lí khi chạm vào enemies
	void StartUntouchable()
	{
		isUntouchable = true;
		startUntouchableTime = GetTickCount();
	}


	//Method của simon
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	void UpdateSimonWeapon(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	//Xử lí đóng băng simon khi nhặt WHIP_UPGRADE
	void UpdateFreeze(DWORD dt);
	void SetState(int state);
	void AddItem(GAME_ITEM type);
	void UpgradeWhip();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	//Xử lí các điều khiển của nhân vật
	void Jump();
	void Sit();
	void WalkingLeft();
	void WalkingRight();
	void Attack();
	void ChangeSubWeapon(SIMON_WEAPON type);

	//Xử lí khi animtion đang tấn công - không cho đánh liên tục và kết thúc việc đánh - gọi trong update
	void Attacking(DWORD dt);
	//Xử lí khi đang nhảy - không cho nhảy liên tục - gọi trong update
	void Jumping();

	// Update kiểm tra vũ khi
	void UsingWeapon();

	// Kiểm tra tym và tạo sub weapom
	void MakeSubWeapon(float x, float y, int nx);

	//Xử lí khi đang ngồi - Không cho phép di chuyển và nhảy - chỉ được đánh - gọi trong set state
	void Sitting();

	//Xử lí BBox tránh bị chạm;
	void ResetAfterSit();
	void ResetAfterJump();



};