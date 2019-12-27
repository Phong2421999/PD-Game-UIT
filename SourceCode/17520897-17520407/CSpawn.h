#pragma once
#include "FrameWork/GameObject.h"
#include "Simon.h"
#include "GameEnemyLib.h"
#include "Spawner.h"
#define GHOST 0

class CSpawn: public CGameObject
{
private:
	int width, height;
	int enemyId;
	int xEnemy, yEnemy;
	int quantityEachSpawn;
	int timeEachSpawn;
	int spawnerId;
	int delaySpawnTime;
	bool canRespawn;
	float offsetWithSimon;
	float xTarget, yTarget;
	bool setBoss;
	int enemyMode;
public:
	CSpawn() {
		spawnerId = -1;
		canRespawn = true;
		offsetWithSimon = 0;
		setBoss = false;
		enemyMode = 0;
		xTarget = yTarget = 0;
		xEnemy = 0;
		yEnemy = 0;
	}
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	bool IsTouchSimon();
	void SetPositionEnemy(float x, float y)
	{
		this->xEnemy = x;
		this->yEnemy = y;
	}
	void SetTargetPosition(float xTarget, float yTarget)
	{
		this->xTarget = xTarget;
		this->yTarget = yTarget;
	}
	void SetEnemyMode(int m)
	{
		this->enemyMode = m;
	}
	void SetBoss(bool b)
	{
		this->setBoss = b;
	}
	void SetRespawn(int canRespawn)
	{
		canRespawn == 1 ? this->canRespawn = true : this->canRespawn = false;
	}
	bool GetRespawn()
	{
		return canRespawn;
	}

	void SetOffsetWithSimon(float offset)
	{
		this->offsetWithSimon = offset;
	}
	float GetOffsetWithSimon()
	{
		return this->offsetWithSimon;
	}

	void SetDelaySpawnTime(int delaySpawnTime)
	{
		this->delaySpawnTime = delaySpawnTime;
	}
	int GetDelaySpawnTime()
	{
		return delaySpawnTime;
	}

	void SetTimeEachSpawn(int timeEachSpawn) {
		this->timeEachSpawn = timeEachSpawn;
	}
	int GetTimeEachSpawn() {
		return timeEachSpawn;
	}

	void SetSpawnerId(int id) {
		this->spawnerId = id;
	}
	int GetSpawnerId() {
		return spawnerId;
	}

	void SetWidthHeight(float width, float height)
	{
		this->width = width;
		this->height = height;
	};
	void SetSpawnEnemyType(int type)
	{
		this->enemyId = type;
	};
	void SetQuantitySpawnEnemy(int quantity)
	{
		this->quantityEachSpawn = quantity;
	};
	int GetQuantitySpawnEnemy()
	{
		return quantityEachSpawn;
	};
	int GetSpawnEnemyType() {
		return enemyId;
	}
};

