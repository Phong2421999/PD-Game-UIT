﻿#pragma once
#include "FrameWork/GameObject.h"
#include "CStaticObject.h"
#include "FrameWork/debug.h"

#include "GameConst.h"
#include "GameWeaponLib.h"

#include "SimonConst.h"

#include "CSpawn.h"
#include "Ground.h"

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
	bool isResetSitAfterAttack;
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
	int heart;			//Số lượng tim để sử dụng subweapon

	Weapon* simonWeapon;

	static CSimon *__instance;

	SIMON_WEAPON typeSubWeapon;

	int currentScene;	//id của scene hiện tại
	int score;			//Điểm người chơi
	int live;			//Số mạng của simon

	//Tự động di chuyển khi chuyển sence
	bool isAutoGo;
	float autoGoDistance;
	float simonAutoGoDistance;
	int enemyId;
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
		isEnoughHeart = false;
		isJumpAttack = false;
		isResetSitAfterAttack = false;
		lastAttackTime = -1;
		lastAttackSide = 1;
		isHasSubWeapon = false;
		typeSubWeapon = SIMON_WEAPON::NONE;
		weaponLevel = SIMON_WEAPON_LEVEL_1;
		heart = 5;
		health = 8;
		currentScene = 0;
		score = 0;
		live = 3;
		isAutoGo = false;
		autoGoDistance = 0;
		simonAutoGoDistance = 0;
	}
#pragma region set thuộc tính
	//set thuộc tính
	void setAutoGoDistance(float dis)
	{
		this->autoGoDistance = dis;
	}
	void setAutoGo(bool b)
	{
		this->isAutoGo = b;
	}
	void setResetSitAffterAttack(bool b)
	{
		this->isResetSitAfterAttack = b;
	}
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
	void setSit(bool b)
	{
		this->isSit = b;
	}
	void setSceneId(int id)
	{
		this->currentScene = id;
	}
#pragma endregion

#pragma region //get thuộc tính
	SIMON_WEAPON getSubWeapon() {
		return typeSubWeapon;
	}
	int getState()
	{
		return state;
	}
	bool getAutoGo()
	{
		return isAutoGo;
	}
	int getWeaponLevel() {
		return weaponLevel;
	}
	int getLive()
	{
		return live;
	}
	int getScore()
	{
		return score;
	}
	int getHeart()
	{
		return heart;
	}
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
	int getCurrentScene()
	{
		return currentScene;
	}
#pragma endregion

	
	

	//Xử lí khi chạm vào enemies
	void StartUntouchable()
	{
		isUntouchable = true;
		startUntouchableTime = GetTickCount();
	}
	//Load simon weapon

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