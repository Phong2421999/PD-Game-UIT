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

public:
	Scene(int sceneWidth);
	void LoadSceneResource(int mapId, LPCSTR senceGameObjects);
	void Update(DWORD dt);
	void Render();
};

typedef Scene* LPSCENE;