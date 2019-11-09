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
	int quantityEachSpawn;
	int timeEachSpawn;
	int spawnerId;
	int delaySpawnTime;
public:
	CSpawn() {
		spawnerId = -1;
	}
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	bool IsTouchSimon(LPGAMEOBJECT gameObjet);

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

