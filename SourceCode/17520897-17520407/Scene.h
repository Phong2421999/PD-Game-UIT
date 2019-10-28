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


class Scene {
public:
	CGame *game;
	CMap * map;
	CSimon *simon;
	CAnimations * animations;

	vector<LPGAMEOBJECT> objects;
	vector<LPITEMS> listItems;
	vector<LPEFT> effects;

	int mapId;
	int sceneWidth;

	DWORD timeStartLoadScene;
	DWORD timeLoadBlackScene;
	bool isLoadBlackScene;
	bool isCanLoadScene;

	float simonStartX;
	float simonStartY;

public:
	Scene(int sceneWidth, int loadBlackScene, DWORD timeLoadBlackScene);
	void LoadSceneResource(int mapId, LPCSTR senceGameObjects);
	void Update(DWORD dt);
	void Render();
	void StartLoadScene();
	void SetSimonStartPos(float x, float y)
	{
		this->simonStartX = x;
		this->simonStartY = y;
	}
};

typedef Scene* LPSCENE;