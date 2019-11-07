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

#include "tinyxml.h"

struct Letter
{
	float x, y;
	int letter;
};

class Scene {
public:
	CGame *game;
	CMap * map;
	CSimon *simon;
	CBoardGame *boardGame;
	CAnimations * animations;

	vector<LPGAMEOBJECT> objects;
	vector<LPITEMS> listItems;
	vector<LPEFT> effects;
	vector<Letter> letters;

	int mapId;
	int sceneWidthEachMap;

	DWORD timeStartLoadScene;
	DWORD lastTimeEachStage;
	DWORD timeLoadBlackScene;
	bool isLoadBlackScene;
	bool isCanLoadScene;

	float simonStartX;
	float simonStartY;

	int stage;

	DWORD deltaTime;

	bool hasSetRenderOpenDoor;
	
public:
	Scene(int sceneWidthEachMap, int loadBlackScene, int stage, DWORD timeLoadBlackScene);
	void LoadSceneResource(int mapId, LPCSTR senceGameObjects);
	void Update(DWORD dt);
	void UpdateBoardGame(DWORD dt);
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
	void clear()
	{
		objects.clear();
		listItems.clear();
		effects.clear();
		letters.clear();
	}
};

typedef Scene* LPSCENE;