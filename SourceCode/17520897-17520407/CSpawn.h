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
	bool isCanSpawn;
	bool simonHasTouch;
	int enemyId;
	int spawnerId;
	int quantityEachSpawn;
public:
	CSpawn() {
		isCanSpawn = true;
		simonHasTouch = false;
		spawnerId = -1;
	}
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	bool IsTouchSimon(LPGAMEOBJECT gameObjet);

	
	void SetWidthHeight(float width, float height)
	{
		this->width = width;
		this->height = height;
	};
	void SetCanSpwan(bool b) {
		this->isCanSpawn = b;
	}
	void SetSimonHasTouch(bool b)
	{
		this->simonHasTouch = b;
	}
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
	bool GetCanSpawn() {
		return isCanSpawn;
	}
	bool GetSimonHasTouch()
	{
		return this->simonHasTouch;
	}
};

