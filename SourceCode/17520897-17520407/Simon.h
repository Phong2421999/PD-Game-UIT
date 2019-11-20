﻿#pragma once
#include "FrameWork/GameObject.h"
#include "CStaticObject.h"
#include "FrameWork/debug.h"

#include "GameConst.h"
#include "GameWeaponLib.h"

#include "SimonConst.h"

#include "CSpawn.h"
#include "Ground.h"

#include "CheckStair.h"

class CSimon : public CGameObject
{
private:
	bool isJump;
	bool isSit;
	bool isAttack;
	bool isFreeze;
	bool isOnStair;
	bool isFalling;
	bool isJumpAttack;
	bool isAutoGoToStair;
	bool isAutoGoOutStair;

	bool isCanJump;
	bool isCanAttack;
	bool isResetSitAfterAttack;
	bool isUntouchable;
	bool isCanOnStair;
	bool isCanOutStair;
	bool isCanSetStair;

	bool isUsingStopWatch;
	bool isUsingCross;

	float autoGoToStairDistance;
	float onStairDistance;

	DWORD startAttackTime;
	DWORD lastAttackTime;
	DWORD lastJumpTime;
	DWORD timeMakeWeapon;
	
	DWORD timeUsingStopWatch;
	DWORD timeUsingCross;

	DWORD startUntouchableTime;
	DWORD endWalkOnStairTime;

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

	STAIR_TYPE stairType;
	//Tự động di chuyển khi chuyển sence
	bool isAutoGo;
	float autoGoDistance;
	float simonAutoGoDistance;
	int enemyId;

	int stairNx;
	int stairNy;
	int stairActiveNy;

public:

	static CSimon* getInstance();
	CSimon()
	{
		onStairDistance = 0;
		isCanOutStair = false;
		isCanSetStair = false;
		isJump = false;
		isSit = false;
		isAttack = false;
		isOnStair = false;
		isFreeze = false;
		isCanAttack = true;
		isCanJump = true;
		isCanOnStair = false;
		isUsingStopWatch = false;
		isUsingCross = false;
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
		heart = 5;
		health = 8;
		currentScene = 0;
		score = 1;
		live = 3;
		isAutoGo = false;
		autoGoDistance = 0;
		simonAutoGoDistance = 0; 
		endWalkOnStairTime = GetTickCount();
		stairNx = 0;
		stairNy = 0;
		stairActiveNy = 0;
		ny = 0;
		isAutoGoOutStair = false;
	}
#pragma region set thuộc tính
	//set thuộc tính
	void setCanOutStair(bool b)
	{
		this->isCanOutStair = b;
	}
	void setStairActiveNy(float y)
	{
		this->stairActiveNy = y;
	}
	void setCanSetStair(bool b)
	{
		this->isCanSetStair = b;
	}
	void setAutoGoOutStair(bool b)
	{
		this->isAutoGoOutStair = b;
	}
	void setStairNx(int nx)
	{
		this->stairNx = nx;
	}
	void setStairNy(int ny)
	{
		this->stairNy = ny;
	}
	void setStairType(STAIR_TYPE type)
	{
		this->stairType = type;
	}
	void setOnStair(bool b)
	{
		this->isOnStair = b;
	}
	
	void setAutoGoToStair(bool b)
	{
		this->isAutoGoToStair = b;
	}
	void setCanOnStair(bool b)
	{
		this->isCanOnStair = b;
	}
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
	void setUsingStopWatch(bool b)
	{
		this->isUsingStopWatch = b;
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
	int getStairActiveNy()
	{
		return stairActiveNy;
	}
	bool getCanSetStair()
	{
		return isCanSetStair;
	}
	bool getAuToGoOutStair()
	{
		return isAutoGoOutStair;
	}
	SIMON_WEAPON getSubWeapon() {
		return typeSubWeapon;
	}
	STAIR_TYPE getStairType()
	{
		return stairType;
	}
	bool getCanOutStair()
	{
		return isCanOutStair;
	}
	int getStairNx()
	{
		return stairNx;
	}
	int getStairNy()
	{
		return stairNy;
	}
	bool getAutoGoToStair()
	{
		return isAutoGoToStair;
	}
	bool getUsingCross()
	{
		return isUsingCross;
	}
	bool getUsingStopWatch()
	{
		return isUsingStopWatch;
	}
	bool getOnStair()
	{
		return isOnStair;
	}
	bool getCanOnStair()
	{
		return isCanOnStair;
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

	void TouchEnemy(int nx);
	//Load simon weapon

	//Method của simon
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void UpdateCheckStair(vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	void UpdateSimonWeapon(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	//Xử lí đóng băng simon khi nhặt WHIP_UPGRADE
	void UpdateFreeze(DWORD dt);

	void SetState(int state);
	void AddItem(GAME_ITEM type);
	void UpgradeWhip();
	void UpdateStopWatch();
	void UpdateCross();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	//Xử lí các điều khiển của nhân vật
	void Jump();
	void Sit();
	void WalkingLeft();
	void WalkingRight();
	void Attack();
	void OnStairUp();
	void OnStairDown();
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