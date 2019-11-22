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
	int xEnemy, yEnemy;
	int delaySpawnTime;
	int timeEachSpawn;
	int spawnerId;
	int quantityEachSpawn;
	bool canRespawn;
public:
	CSpawner()
	{
		lastSpawnTime = 0;
		canSpawn = true;
		canRespawn = true;
		quantityEnemyDied = 0;
		quantitySpawned = 0;
		quantityEachSpawn = 0;
		enemyId = -1;
		xEnemy = 0;
		yEnemy = 0;
		delaySpawnTime = 0;
		timeEachSpawn = 0;
		spawnerId = -1;
	}
	static CSpawner * GetInstance();
	void Reset()
	{
		lastSpawnTime = GetTickCount();
		canRespawn = true;
		canSpawn = true;
		xEnemy = 0;
		yEnemy = 0;
		quantityEnemyDied = 0;
		quantitySpawned = 0;
		quantityEachSpawn = 0;
	}
	void resetAfterUsingCross()
	{
		lastSpawnTime = GetTickCount();
		canSpawn = true;
		quantityEnemyDied = 0;
		quantitySpawned = 0;
	}
	void resetAfterResetScene()
	{
		lastSpawnTime = GetTickCount();
		canSpawn = true;
		canRespawn = true;
		xEnemy = 0;
		yEnemy = 0;
		quantityEnemyDied = 0;
		quantitySpawned = 0;
		quantityEachSpawn = 0;
		enemyId = -999;
	}

};
