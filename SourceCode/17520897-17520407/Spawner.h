#pragma once
#include <d3d9.h>

class CSpawner
{
public:
	static CSpawner* __instance;
	int quantitySpawned;
	int quantityEnemyDied;
	bool canSpawn;
	DWORD lastSpawnTime;

	int enemyId;
	int delaySpawnTime;
	int timeEachSpawn;
	int spawnerId;
	int quantityEachSpawn;
public:
	CSpawner()
	{
		lastSpawnTime = 0;
		canSpawn = true;
		quantityEnemyDied = 0;
		quantitySpawned = 0;
		quantityEachSpawn = 0;
		enemyId = -1;
		delaySpawnTime = 0;
		timeEachSpawn = 0;
		spawnerId = -1;
	}
	static CSpawner * GetInstance();
	void reset()
	{
		lastSpawnTime = 0;
		canSpawn = true;
		quantityEnemyDied = 0;
		quantitySpawned = 0;
		quantityEachSpawn = 0;
	}

};
