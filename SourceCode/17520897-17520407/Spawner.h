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
	float offsetWithSimon;

	float xTarget, yTarget;
	bool setBoss;
	bool isActive;
	int enemyMode;
public:
	CSpawner()
	{
		enemyMode = 0;
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
		offsetWithSimon = 0;
		xTarget = 0;
		yTarget = 0;
		setBoss = false;
		isActive = true;
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
