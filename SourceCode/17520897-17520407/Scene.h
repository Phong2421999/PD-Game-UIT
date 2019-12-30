#pragma once

#include <string>
#include <iostream>
#include <fstream>


#include "FrameWork/GameObject.h"
#include "FrameWork/Textures.h"
#include "FrameWork/CAnimations.h"

#include "FrameWork/debug.h"
#include "FrameWork/Game.h"

#include "GameConst.h"

#include "tinyxml.h"

#include "GameEnemyLib.h"
#include "GameObjectLib.h"
#include "GameItemLib.h"

#include "Simon.h"
#include "CMap.h"
#include "CBoardGame.h"
#include "CDestroy.h"
#include "tinyxml.h"

#include "Spawner.h"

#include "WeaponEnemies.h"
#include "LockSimon.h"
#include "PotRoast.h"

#include "Monkey.h"
#include "CEagle.h"
#include "Skeleton.h"
#include "FinalBoss.h"


#include "Grid.h"

struct Letter
{
	float x, y;
	int letter;
};

class Scene {
public:

	vector<Letter> letters;

	int mapId;
	int sceneWidthEachMap;

	DWORD timeStartLoadScene;
	DWORD lastTimeEachStage;
	DWORD timeSpawn;
	DWORD timeLoadBlackScene;
	bool isLoadBlackScene;
	bool isCanLoadScene;

	float simonStartX;
	float simonStartY;

	int stage;

	DWORD deltaTime;

	bool hasSetRenderOpenDoor;

	string objectsPath;

	vector<int> gridIds;

	Grid *grid;

public:
	Scene(int sceneWidthEachMap, int loadBlackScene, int stage, DWORD timeLoadBlackScene, string sceneGameObjects, int mapId);
	void LoadSceneResource();

	void Update(DWORD dt);
	void UpdateBoardGame(DWORD dt);
	void Reset();
	void Clear();
	bool isInGrid(LPGAMEOBJECT obj);

	void MakeEnemies(DWORD dt);
	//void UpdateWeaponEnemies(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	//void MakeWeaponEnemies(DWORD dt);
	void Render();
	void StartLoadScene();
	int Random(int minN, int maxN) {
		return minN + rand() % (maxN + 1 - minN);
	}
	void SetSimonStartPos(float x, float y)
	{
		this->simonStartX = x;
		this->simonStartY = y;
	}
	
};

typedef Scene* LPSCENE;