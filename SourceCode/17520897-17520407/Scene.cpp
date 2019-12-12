#include "Scene.h"
#include "Scenes.h"
Scene::Scene(int sceneWidthEachMap, int loadBlackScene, int stage, DWORD timeLoadBlackScene, string sceneGameObjects, int mapId)
{
	this->sceneWidthEachMap = sceneWidthEachMap;
	this->timeLoadBlackScene = timeLoadBlackScene;
	this->stage = stage;
	this->objectsPath = sceneGameObjects;
	this->mapId = mapId;
	if (loadBlackScene == 1)
	{
		isLoadBlackScene = true;
	}
	else
	{
		isLoadBlackScene = false;

	}
	isCanLoadScene = false;
	simonStartX = 0;
	simonStartY = 0;
	hasSetRenderOpenDoor = false;


}

void Scene::LoadSceneResource()
{
	Grid::GetInstance()->clear();
	CMap::GetInstance()->Get(mapId)->LoadTile();
	CBoardGame::GetInstance()->LoadBackBoard(TEX_BLACK_BOARD_ID, "textures\\board.png");

	ifstream inpLetters("TXT\\BoardGame.txt", ios::in);
	int lettersQuantity, letterWidth, letterHeight, ColumLetterBoard, RowLetterBoard;
	float subWeapon_posX, subWeapon_posY;

	float simonHealthBar_posX, simonHealthBar_posY;
	float enemyHealthBar_posX, enemyHealthBar_posY;

	inpLetters >> lettersQuantity >> RowLetterBoard >> ColumLetterBoard >> letterWidth >> letterHeight >> subWeapon_posX >> subWeapon_posY >> simonHealthBar_posX >> simonHealthBar_posY >> enemyHealthBar_posX >> enemyHealthBar_posY;

	CBoardGame::GetInstance()->GetBoardInfo(RowLetterBoard, ColumLetterBoard, letterWidth, letterHeight, subWeapon_posX, subWeapon_posY, simonHealthBar_posX, simonHealthBar_posY, enemyHealthBar_posX, enemyHealthBar_posY);

	CBoardGame::GetInstance()->LoadFont(TEX_FONT_ID);

	for (int i = 0; i < lettersQuantity; i++)
	{
		Letter l;
		inpLetters >> l.x >> l.y >> l.letter;
		letters.push_back(l);
	}

	TiXmlDocument mapObjects(this->objectsPath.c_str());
	if (!mapObjects.LoadFile())
	{
		DebugOut(L"Can't read XML file: %s", this->objectsPath.c_str());
		MessageBox(NULL, L"Can't Read XML File", L"Error", MB_OK);
		return;
	}
	// get info root
	TiXmlElement* root = mapObjects.RootElement();
	TiXmlElement* Objects = nullptr;
	TiXmlElement* Object = nullptr;
	Grid* grid = Grid::GetInstance();
	for (Objects = root->FirstChildElement(); Objects != NULL; Objects = Objects->NextSiblingElement())
	{
		int id, gridId;
		float x, y, Width, Height;
		Objects->QueryIntAttribute("id", &id);
		for (Object = Objects->FirstChildElement(); Object != NULL; Object = Object->NextSiblingElement())
		{
			Object->QueryFloatAttribute("x", &x);
			Object->QueryFloatAttribute("y", &y);
			Object->QueryFloatAttribute("width", &Width);
			Object->QueryFloatAttribute("height", &Height);
			Object->QueryIntAttribute("Grid", &gridId);
			if (id == 0)
			{
				CGround* ground = new CGround();
				ground->SetWidthHeigth(Width, Height);
				ground->SetPosition(x, y);
				objects.push_back(ground);
				grid->add(ground, gridId);
			}
			else if (id == 1) {
				int itemId;
				Object->QueryIntAttribute("itemId", &itemId);
				CLargeCandle* largeCandle = new CLargeCandle();
				largeCandle->SetPosition(x, y);
				largeCandle->SetWidthHeight(Width, Height);
				largeCandle->SetItemId(itemId);
				objects.push_back(largeCandle);
				grid->add(largeCandle, gridId);

			}
			else if (id == 2) {
				int itemId;
				Object->QueryIntAttribute("itemId", &itemId);
				CSmallCandle* smallCandle = new CSmallCandle();
				smallCandle->SetPosition(x, y);
				smallCandle->SetWidthHeight(Width, Height);
				smallCandle->SetItemId(itemId);
				objects.push_back(smallCandle);
				grid->add(smallCandle, gridId);

			}
			else if (id == 3)
			{
				CWall* wall = new CWall();
				wall->SetPosition(x, y);
				wall->SetWidthHeight(Width, Height);
				objects.push_back(wall);
				grid->add(wall, gridId);

			}
			else if (id == -1)
			{
				int sceneId, simonAutoGo;
				int isDoor, camAutoGo, isLoadBlackScene, timeLoadBlackScene;
				float simonAutoGoDistance;
				float simonStartPosX, simonStartPosY;
				Object->QueryIntAttribute("sceneId", &sceneId);
				Object->QueryIntAttribute("simonAutoGo", &simonAutoGo);
				Object->QueryFloatAttribute("simonAutoGoDistance", &simonAutoGoDistance);
				Object->QueryFloatAttribute("simonStartPosX", &simonStartPosX);
				Object->QueryFloatAttribute("simonStartPosY", &simonStartPosY);
				Object->QueryIntAttribute("camAutoGo", &camAutoGo);
				Object->QueryIntAttribute("isDoor", &isDoor);
				Object->QueryIntAttribute("isLoadBlackScene", &isLoadBlackScene);
				Object->QueryIntAttribute("timeLoadBlackScene", &timeLoadBlackScene);
				ChangeSceneObjects* changeScene = new ChangeSceneObjects();
				changeScene->SetPosition(x, y);
				changeScene->SetWidthHeight(Width, Height);
				changeScene->SetSceneId(sceneId);
				changeScene->SetAutoGoDistance(simonAutoGoDistance);
				changeScene->SetSimonStartPos(simonStartPosX, simonStartPosY);
				changeScene->SetTimeLoadBlackScene(timeLoadBlackScene);
				if (camAutoGo == 1)
				{
					changeScene->SetCamAutoGo(true);
				}
				if (isLoadBlackScene == 1)
				{
					changeScene->SetLoadBlackScene(true);
				}
				if (isDoor)
				{
					changeScene->SetIsDoor(true);
				}
				if (simonAutoGo == 1)
				{
					changeScene->SetSimonAutoGo(true);
					changeScene->SetAutoGoDistance(simonAutoGoDistance);
				}
				objects.push_back(changeScene);
				grid->add(changeScene, gridId);

			}
			else if (id == -2)
			{
				int enemyId, canRespawn, quantityEachSpawn, timeEachSpawn, spawnerId, delaySpawnTime, xEnemy, yEnemy;
				Object->QueryIntAttribute("enemyId", &enemyId);
				Object->QueryIntAttribute("xEnemy", &xEnemy);
				Object->QueryIntAttribute("yEnemy", &yEnemy);
				Object->QueryIntAttribute("spawnerId", &spawnerId);
				Object->QueryIntAttribute("quantityEachSpawn", &quantityEachSpawn);
				Object->QueryIntAttribute("timeEachSpawn", &timeEachSpawn);
				Object->QueryIntAttribute("delaySpawnTime", &delaySpawnTime);
				Object->QueryIntAttribute("canRespawn", &canRespawn);

				CSpawn* spawn = new CSpawn();
				spawn->SetPosition(x, y);
				spawn->SetRespawn(canRespawn);
				spawn->SetPositionEnemy(xEnemy, yEnemy);
				spawn->SetWidthHeight(Width, Height);
				spawn->SetSpawnEnemyType(enemyId);
				spawn->SetSpawnerId(spawnerId);
				spawn->SetQuantitySpawnEnemy(quantityEachSpawn);
				spawn->SetTimeEachSpawn(timeEachSpawn);
				spawn->SetDelaySpawnTime(delaySpawnTime);

				objects.push_back(spawn);
				grid->add(spawn, gridId);

			}
			else if (id == -3)
			{
				int ny, nx;
				Object->QueryIntAttribute("ny", &ny);
				Object->QueryIntAttribute("nx", &nx);
				CheckStair* checkStair = new CheckStair();
				checkStair->SetPosition(x, y);
				checkStair->SetWidthHeight(Width, Height);
				checkStair->SetNxNy(nx, ny);
				objects.push_back(checkStair);
				grid->add(checkStair, gridId);

			}
			else if (id == -4)
			{
				int type, itemId;
				Object->QueryIntAttribute("type", &type);
				Object->QueryIntAttribute("itemId", &itemId);
				CHiddenWall* hiddenWall = new CHiddenWall(x, y, type, itemId);
				hiddenWall->SetWidthHeight(Width, Height);
				objects.push_back(hiddenWall);
				grid->add(hiddenWall, gridId);

			}
			else if (id == -5)
			{
				LockSimon* lockSimon = new LockSimon();
				lockSimon->SetWidthHeight(Width, Height);
				lockSimon->SetPosition(x, y);
				objects.push_back(lockSimon);
				grid->add(lockSimon, gridId);

			}
			else if (id == -99)
			{
				CDestroy* detroy = new CDestroy();
				int type;
				Object->QueryIntAttribute("type", &type);

				if (type == 1)
					detroy->SetType(RIGHT);
				else if (type == -1)
					detroy->SetType(LEFT);
				else
				{
					float x, y;
					Object->QueryFloatAttribute("x", &x);
					Object->QueryFloatAttribute("y", &y);
					detroy->SetType(BOTTOM);
					detroy->SetPosition(x, y);
				}
				objects.push_back(detroy);
				grid->add(detroy, gridId);

			}
		}
	}
	CSimon* simon = CSimon::getInstance();
	objects.push_back(simon);
}

void Scene::UpdateBoardGame(DWORD dt) {
	CBoardGame * boardGame = CBoardGame::GetInstance();
	CSimon *simon = CSimon::getInstance();
	DWORD now = GetTickCount();
	if (boardGame->getLimitTime() <= 0)
	{
		simon->TouchEnemy(-simon->nx);
		simon->SetHealth(0);
	}
	if (now - lastTimeEachStage >= 1000)
	{
		lastTimeEachStage = GetTickCount();
		int time = boardGame->getLimitTime();
		boardGame->setLimitTime(--time);
	}
	for (int i = 0; i < letters.size(); i++)
	{
		int n = 0;
		int temp;
		if (i < 6) {
			temp = simon->getScore();
			for (int j = 0; j < (0 + SCORE_LENGTH) - i; j++) // Bắt đầu là 0 muốn chia 6 lần trong trường hợp này thì i = 0, 1, 2, 3, 4, 5
			{
				n = temp % 10;
				temp = temp / 10;
			}
		}
		if (i >= 6 && i < 10) {
			temp = boardGame->getLimitTime();
			for (int j = 0; j < (6 + TIME_LENGTH) - i; j++) // Bắt đầu là 6 muốn chia 4 lần trong trường hợp này thì i = 6, 7, 8, 9
			{
				n = temp % 10;
				temp = temp / 10;
			}
		}
		if (i >= 10 && i < 12) {
			temp = this->stage;
			for (int j = 0; j < (10 + STAGE_LENGTH) - i; j++) // Bắt đầu là 10 muốn chia 2 lần trong trường hợp này thì i = 10, 11
			{
				n = temp % 10;
				temp = temp / 10;
			}
		}
		if (i >= 12 && i < 14) {
			temp = simon->getHeart();
			for (int j = 0; j < (12 + HEART_LENGTH) - i; j++) // Bắt đầu là 12 muốn chia 2 lần trong trường hợp này thì i = 12, 13
			{
				n = temp % 10;
				temp = temp / 10;
			}
		}
		if (i >= 14 && i < 16) {
			temp = simon->getLive();
			for (int j = 0; j < (14 + LIVE_LENGTH) - i; j++) // Bắt đầu là 14 muốn chia 2 lần trong trường hợp này thì i = 14, 15
			{
				n = temp % 10;
				temp = temp / 10;
			}
		}
		letters.at(i).letter = boardGame->GetWithNumber(n);
	}

}

void Scene::UpdateWeaponEnemies(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	for (int i = 0; i < weaponEnemies.size(); i++)
	{
		if (weaponEnemies[i]->GetHealth() > 0)
		{
			weaponEnemies[i]->Update(dt, coObjects);
		}
		else
		{
			weaponEnemies.erase(weaponEnemies.begin() + i);
		}
	}
}

void Scene::MakeWeaponEnemies(DWORD dt) {
	Grid* grid = Grid::GetInstance();
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->makeWeapon)
		{
			float x, y;
			objects[i]->GetPosition(x, y);
			int nx = objects[i]->getDirection();
			WeaponProjectile * weapon = new WeaponProjectile(x, y, nx);
			weaponEnemies.push_back(weapon);
			grid->add(weapon, WEAPONENEMIES_GRID);
			/*if (dynamic_cast<CUglyFish*>(objects[i]))
			{
				float x, y;
				objects[i]->GetPosition(x, y);
				int nx = objects[i]->getDirection();
				WeaponProjectile * weapon = new WeaponProjectile(x, y, nx);
				weaponEnemies.push_back(weapon);
				grid->add(weapon, -1);
			}
			else if (dynamic_cast<CBossBat*>(objects[i]))
			{
				float x, y;
				objects[i]->GetPosition(x, y);
				int nx = objects[i]->getDirection();
				WeaponProjectile * weapon = new WeaponProjectile(x, y, nx);
				weaponEnemies.push_back(weapon);
			}*/
		}
	}
}

void Scene::MakeEnemies(DWORD dt)
{
	CSpawner* spawner = CSpawner::GetInstance();
	CSimon* simon = CSimon::getInstance();
	Grid* grid = Grid::GetInstance();

	float cx, cy;
	float sx, sy;
	cx = CGame::GetInstance()->GetCamPos_x();
	cy = CGame::GetInstance()->GetCamPos_y();
	CSimon::getInstance()->GetPosition(sx, sy);
	int lastNx = 1;
	DWORD now = GetTickCount();

	if (simon->getUsingStopWatch() == false || simon->getUsingCross() == false)
	{
		if (spawner->quantitySpawned == spawner->quantityEachSpawn)
		{
			spawner->canSpawn = false;
		}
		if (spawner->quantityEnemyDied == spawner->quantityEachSpawn
			&& spawner->canRespawn)
		{
			if (now - spawner->lastSpawnTime > spawner->delaySpawnTime)
			{
				spawner->quantitySpawned = 0;
				spawner->quantityEnemyDied = 0;
				spawner->canSpawn = true;
			}
		}

		if (spawner->quantitySpawned < spawner->quantityEachSpawn
			&& spawner->canSpawn)
		{
			if (now - spawner->lastSpawnTime > spawner->timeEachSpawn)
			{
				if (spawner->enemyId == GHOST_ID)
				{
					CGhost* ghost = new CGhost(cx, cy);
					spawner->quantitySpawned += 1;
					objects.push_back(ghost);
					grid->add(ghost, ENEMIES_GRID);

				}
				else if (spawner->enemyId == PANTHER_ID)
				{
					CPanther* panther = new CPanther(spawner->xEnemy, spawner->yEnemy);
					spawner->quantitySpawned += 1;
					objects.push_back(panther);
					grid->add(panther, ENEMIES_GRID);

				}
				else if (spawner->enemyId == BAT_ID)
				{
					CBat* bat = new CBat(cx, sy);
					spawner->quantitySpawned += 1;
					objects.push_back(bat);
					grid->add(bat, ENEMIES_GRID);

				}
				else if (spawner->enemyId == FISH_ID)
				{
					float x, y;
					CUglyFish* fish = new CUglyFish(cx, cy);
					fish->GetPosition(x, y);
					for (int i = 0; i < QUANTITY_EFFECT_SPLASH; i++)
					{
						if (i == 0)
						{
							y = SPLASH_Y_SIDE;
						}
						else if (i == 1)
						{
							y = SPLASH_Y_CENTER;
							x = x + SPLASH_OFFSET_LEFT;
						}
						else
						{
							y = SPLASH_Y_SIDE;
							x = x + SPLASH_OFFSET_RIGHT;
						}
						CEffect * splash = new CSplash(x, y);
						effects.push_back(splash);
						grid->add(splash, EFFECTS_GRID);

					}
					spawner->quantitySpawned += 1;
					objects.push_back(fish);
					grid->add(fish, ENEMIES_GRID);
				}
				else if (spawner->enemyId == BOSS_BAT_ID)
				{
					CBossBat* bossBat = new CBossBat();
					bossBat->SetIsBoss(true);
					spawner->quantitySpawned += 1;
					objects.push_back(bossBat);
					grid->add(bossBat, ENEMIES_GRID);
				}
				spawner->lastSpawnTime = GetTickCount();
			}
		}
	}
}

bool Scene::isInGrid(LPGAMEOBJECT obj)
{
	float x, y;
	float width, height;
	float cx = CGame::GetInstance()->GetCamPos_x();
	float sx, sy;
	CSimon::getInstance()->GetPosition(sx, sy);
	obj->GetPosition(x, y);
	obj->GetWidthHeight(width, height);

	if (((x + width > cx - GRID_OFFSET)) && x < cx + SCREEN_WIDTH + GRID_OFFSET || x < -150)
	{
		return true;
	}

	return false;
}


void Scene::Update(DWORD dt)
{
	CGame*game = CGame::GetInstance();
	CSimon*simon = CSimon::getInstance();
	CAnimations *animations = CAnimations::GetInstance();
	//Caculate grid
	Grid* grid = Grid::GetInstance();
	vector<int> gridIds;
	grid->caculateGrid(gridIds);
	//
	float cx;
	cx = CGame::GetInstance()->GetCamPos_x();
	this->deltaTime = dt;

	if (isLoadBlackScene)
	{
		DWORD now = GetTickCount();
		if (now - timeStartLoadScene > timeLoadBlackScene)
		{
			isCanLoadScene = true;
		}
	}
	else
	{
		isCanLoadScene = true;
	}
	if (game->GetCamAutoGo() && isCanLoadScene)
	{
		game->AutoGoCam(dt);
		if (game->GetCamAutoGoDistance() >= SCREEN_WIDTH / 2 - 16 && hasSetRenderOpenDoor == false)
		{
			game->SetRenderOpenDoor(true);
			hasSetRenderOpenDoor = true;
		}
		if (game->GetCamAutoGoDistance() >= SCREEN_WIDTH - 16)
		{
			game->SetCamAutoGo(false);
			game->SetCamAutoGoDistance(0);
			simon->setAutoGo(false);
			simon->setAutoGoDistance(0);
		}
		if (game->GetCamAutoGo())
		{
			for (int gridId = 0; gridId < gridIds.size(); gridId++)
			{
				objects.clear();
				grid->get(gridIds[gridId], objects);
				for (int i = 0; i < objects.size(); i++)
				{
					if (dynamic_cast<ChangeSceneObjects*>(objects[i]))
					{
						objects[i]->Update(dt);
					}
				}
			}
			simon->Update(dt);

		}

	}
	else if (isCanLoadScene)
	{
		if (simon->getFreeze() == false)
		{
			vector<LPGAMEOBJECT> coObjects;
			vector<LPGAMEOBJECT> coEnemies;
			vector<LPGAMEOBJECT> coWeaponEnemies;
			vector<LPGAMEOBJECT> coWeaponObjects;
			vector<LPGAMEOBJECT> coItemObjects;
			vector<LPGAMEOBJECT> coChangeScence;
			vector<LPGAMEOBJECT> coSpawn;
			vector<LPGAMEOBJECT> coDestroy;
			vector<LPGAMEOBJECT> coHiddenObjects;
			vector<LPGAMEOBJECT> coCheckStairObjects;

			UpdateBoardGame(dt);
			MakeEnemies(dt); // luôn gọi trước khi update các thứ khác
			MakeWeaponEnemies(dt);
#pragma region CaculateCollision
			for (int gridId = 0; gridId < gridIds.size(); gridId++)
			{
				objects.clear();
				grid->get(gridIds[gridId], objects);
				objects.push_back(simon);
				//lấy objects để tính colisions
				for (int i = 0; i < objects.size(); i++)
				{
					if (dynamic_cast<CheckStair*>(objects[i]))
					{
						coCheckStairObjects.push_back(objects[i]);
					}
					if (dynamic_cast<CSimon*> (objects[i]))
					{
						coChangeScence.push_back(objects[i]);
						coSpawn.push_back(objects[i]);
						coWeaponEnemies.push_back(objects[i]);
					}
					if (dynamic_cast<CGround*> (objects[i]))
					{
						coEnemies.push_back(objects[i]);
					}
					if (dynamic_cast<CGround*> (objects[i])
						|| (dynamic_cast<CSimon*> (objects[i])
							|| (dynamic_cast<CWall*>(objects[i])))
						)
					{
						coItemObjects.push_back(objects[i]);
						coHiddenObjects.push_back(objects[i]);
					}
					if (!dynamic_cast<CSimon*> (objects[i])
						&& !dynamic_cast<ChangeSceneObjects*> (objects[i])
						&& !dynamic_cast<CItems*> (objects[i])
						&& !dynamic_cast<CSpawn*>(objects[i])
						)
					{
						coWeaponObjects.push_back(objects[i]);
					}
					if (dynamic_cast<CEnemies*> (objects[i])
						|| dynamic_cast<CSpawn*>(objects[i])
						)
					{
						coDestroy.push_back(objects[i]);
					}
					/*if (simon->getUntouchable())
					{
						if (dynamic_cast<CGround*> (objects[i]))
						{
							coObjects.push_back(objects[i]);
						}
					}
					else
					{*/
					if (dynamic_cast<CGround*>(objects[i]))
					{
						coObjects.push_back(objects[i]);
					}
					//}

					if (objects[i]->GetHealth() <= 0)
					{
						if (dynamic_cast<CSimon*>(objects[i]) == false)
						{
							if (dynamic_cast<CHiddenWall*>(objects[i]))
							{
								CHiddenWall* hiddenWall = dynamic_cast<CHiddenWall*>(objects[i]);
								float x, y;
								hiddenWall->GetPosition(x, y);
								for (int i = 0; i < QUANTITY_EFFECT_WALL; i++)
								{
									CEffect * breakingWall = new CBreakingWall(x, y);
									effects.push_back(breakingWall);
									grid->add(breakingWall, EFFECTS_GRID);
								}
								if (hiddenWall->getItemId() == 1)
								{
									PotRoast* potRoast = new PotRoast(x, y);
									listItems.push_back(potRoast);
									grid->add(potRoast, ITEMS_GRID);
								}
								if (hiddenWall->getItemId() == 2)
								{
									DoubleShot* doubleShot = new DoubleShot(x, y);
									listItems.push_back(doubleShot);
									grid->add(doubleShot, ITEMS_GRID);
								}

							}
							else if (objects[i]->GetKillBySimon())
							{
								if (objects[i]->GetIsBoss() == false)
								{
									float x, y;
									CEffect * hit = new CHit();
									if (objects[i]->GetKillBySimon())
									{
										hit->SetKillBySimon(true);
									}
									if (dynamic_cast<CStaticObject*>(objects[i]))
									{
										CStaticObject* staticObjects = dynamic_cast<CStaticObject*>(objects[i]);
										int itemId = staticObjects->GetItemId();
										hit->SetItemId(itemId);
										hit->SetMakeItem(STATIC_OBJECT);
									}

									if (dynamic_cast<CEnemies*> (objects[i]))
									{
										hit->SetMakeItem(ENEMY);
										CSpawner::GetInstance()->quantityEnemyDied++;
									}
									objects[i]->GetPosition(x, y);
									hit->SetPosition(x, y);
									//effects.push_back(hit);
									grid->add(hit, EFFECTS_GRID);
									vector<LPGAMEOBJECT> test;
									grid->get(EFFECTS_GRID, test);
								}
								else
								{
									if (dynamic_cast<CBossBat *>(objects[i]))
									{
										float x, y;
										objects[i]->GetPosition(x, y);

										for (int i = 0; i < 3; i++)
										{
											for (int j = 0; j < 2; j++)
											{
												CEffect * hit = new CHit();
												hit->SetPosition(x + 16 * i, y + 16 * j);
												hit->SetKillBySimon(true);
												hit->SetMakeItem(ENEMY);
												effects.push_back(hit);
												grid->add(hit, EFFECTS_GRID);
											}
										}

									}
								}
							}
							else if (dynamic_cast<CUglyFish*>(objects[i]))
							{

								float x, y;
								objects[i]->GetPosition(x, y);
								for (int i = 0; i < QUANTITY_EFFECT_SPLASH; i++)
								{
									if (i == 0)
									{
										y = SPLASH_Y_SIDE;
									}
									else if (i == 1)
									{
										y = SPLASH_Y_CENTER;
										x = x + SPLASH_OFFSET_LEFT;
									}
									else
									{
										y = SPLASH_Y_SIDE;
										x = x + SPLASH_OFFSET_RIGHT;
									}
									CEffect * splash = new CSplash(x, y);
									effects.push_back(splash);
									grid->add(splash, EFFECTS_GRID);
								}
								CSpawner::GetInstance()->quantityEnemyDied++;
							}
							else if (dynamic_cast<CEnemies*> (objects[i]))
							{
								CSpawner::GetInstance()->quantityEnemyDied++;
							}
							/*objects.erase(objects.begin() + i);*/
							grid->eraseObject(gridIds[gridId], i);
						}
						else
							simon->SetState(SIMON_STATE_DIE);

					}


				}
			}
#pragma endregion

			simon->UpdateSimonWeapon(dt, &coWeaponObjects);
			UpdateWeaponEnemies(dt, &coWeaponEnemies);

#pragma region Update

			//Gọi update với colision tính được
			if (simon->getUsingStopWatch())
			{
#pragma region UpdateStopWatch
				for (int gridId = 0; gridId < gridIds.size(); gridId++)
				{
					objects.clear();
					grid->get(gridIds[gridId], objects);
					for (int i = 0; i < objects.size(); i++)
					{
						if (dynamic_cast<CItems*> (objects[i]))
						{
							objects[i]->Update(dt, &coItemObjects);
						}
						else if (dynamic_cast<CDestroy*> (objects[i]))
						{
							objects[i]->Update(dt, &coDestroy);
						}
						else if (dynamic_cast<ChangeSceneObjects*> (objects[i]))
						{
							objects[i]->Update(dt, &coChangeScence);
						}
						else if (dynamic_cast<HiddenObjects*>(objects[i]))
						{
							objects[i]->Update(dt, &coHiddenObjects);
						}
					}
				}
				simon->Update(dt, &coObjects);
#pragma endregion

			}
			else if (simon->getUsingCross())
			{
				backGroundColor = D3DCOLOR_XRGB(169, 169, 169); // Màu xám
				for (int gridId = 0; gridId < gridIds.size(); gridId++)
				{
					objects.clear();
					grid->get(gridIds[gridId], objects);
					for (int i = 0; i < objects.size(); i++)
					{
						if (dynamic_cast<CEnemies*>(objects[i])) {
							/*objects.erase(objects.begin() + i);*/
							grid->eraseObject(gridIds[gridId], i);
						}
					}
				}
				simon->Update(dt, &coObjects);
			}
			else
			{
				backGroundColor = D3DCOLOR_XRGB(0, 0, 0);
				for (int gridId = 0; gridId < gridIds.size(); gridId++)
				{
					objects.clear();
					grid->get(gridIds[gridId], objects);
					for (int i = 0; i < objects.size(); i++)
					{
						if (dynamic_cast<CEnemies*>(objects[i])) {

							objects[i]->Update(dt, &coEnemies);
						}
						else if (dynamic_cast<CSpawn*> (objects[i]))
						{
							objects[i]->Update(dt, &coSpawn);
						}
						else if (dynamic_cast<CDestroy*> (objects[i]))
						{
							objects[i]->Update(dt, &coDestroy);
						}
						else if (dynamic_cast<ChangeSceneObjects*> (objects[i]))
						{
							objects[i]->Update(dt, &coChangeScence);
						}
						else if (dynamic_cast<HiddenObjects*>(objects[i]))
						{
							objects[i]->Update(dt, &coHiddenObjects);
						}

					}
				}
				simon->Update(dt, &coObjects);
			}


			simon->UpdateCheckStair(&coCheckStairObjects);


#pragma region UpdateItems
			objects.clear();
			grid->get(ITEMS_GRID, objects);
			for (int i = 0; i < objects.size(); i++)
			{
				CItems* item = dynamic_cast<CItems*>(objects[i]);
				if (item->GetHealth() > 0)
				{
					item->Update(dt, &coItemObjects);
				}
				else
				{
					if (dynamic_cast<MoneyBag*>(item))
					{
						float x, y;
						item->GetPosition(x, y);
						CEffect * moneyEffect = new CMoneyEffect(x, y, item->GetGameItem());
						grid->add(moneyEffect, EFFECTS_GRID);
						grid->eraseObject(ITEMS_GRID, i);
					}
					else
					{
						grid->eraseObject(ITEMS_GRID, i);
					}
				}
			}
#pragma endregion

#pragma region UpdateEffects
			objects.clear();
			grid->get(EFFECTS_GRID, objects);
			for (int i = 0; i < objects.size(); i++)
			{
				CEffect* effect = dynamic_cast<CEffect*>(objects[i]);
				if (effect->GetLastFrame())
				{

					float x, y;
					effect->GetPosition(x, y);
					if (effect->GetKillBySimon())
					{
						if (effect->GetMakeItem() == STATIC_OBJECT)
						{
							CItems* item = NULL;
							if (CSimon::getInstance()->getWeaponLevel() < SIMON_WEAPON_LEVEL_2
								&& CSimon::getInstance()->getCurrentScene() > 0)
							{
								item = new WhipUpgrade(x, y);
							}
							else
							{
								int itemId = effect->GetItemId();
								if (itemId == -1)
								{
									int rand = Random(1, 100);
									if (rand <= 66)
									{
										item = new SmallHeart(x, y);
									}
									else
									{
										item = new MoneyBag(x, y);
									}
								}
								if (itemId == 0)
									item = new LargeHeart(x, y);
								if (itemId == 1)
									item = new WhipUpgrade(x, y);
								if (itemId == 2)
									item = new Danger(x, y);
								if (itemId == 3)
									item = new HolyWater(x, y);
								if (itemId == 4)
									item = new Cross(x, y);
								if (itemId == 5)
									item = new InviPotion(x, y);
								if (itemId == 6)
									item = new Axe(x, y);
							}
							grid->add(item, ITEMS_GRID);
						}
						if (effect->GetMakeItem() == ENEMY)
						{
							int rand = Random(1, 100);
							if (rand == 1)
							{
								LargeHeart* largeHeart = new LargeHeart(x, y);
								grid->add(largeHeart, ITEMS_GRID);
							}
							if (rand >= 2 && rand <= 10)
							{
								MoneyBag* moneyBag = new MoneyBag(x, y);
								grid->add(moneyBag, ITEMS_GRID);
							}
							if (rand == 99)
							{
								SmallHeart* smallHeart = new SmallHeart(x, y);
								grid->add(smallHeart, ITEMS_GRID);
							}
						}
					}
					effect->reset();
					grid->eraseObject(EFFECTS_GRID, i);
				}
				else
				{
					effect->Update(dt);
				}
			}
#pragma endregion
		}
		else
		{
			simon->UpdateFreeze(dt);
			for (int gridId = 0; gridId < gridIds.size(); gridId++)
			{
				objects.clear();
				grid->get(gridIds[gridId], objects);
				for (int i = 0; i < objects.size(); i++)
				{
					if (objects[i]->GetHealth() <= 0)
						grid->eraseObject(gridIds[gridId], i);
				}
			}
			objects.clear();
			grid->get(ITEMS_GRID, objects);
			for (int i = 0; i < objects.size(); i++)
			{
				CItems* item = dynamic_cast<CItems*>(objects[i]);
				if (item->GetHealth() <= 0)
					grid->eraseObject(ITEMS_GRID, i);
				else
					item->SetMakeTime(GetTickCount());
			}
		}
#pragma endregion

		float cx, cy;
		simon->GetPosition(cx, cy);

		cx -= SCREEN_WIDTH / 2 - 32;
		cy -= SCREEN_HEIGHT / 2;
		if (cx <= LOCK_CAMERA_X)
		{
			game->SetCamPos(LOCK_CAMERA_X, 0.0f /*cy*/);
		}
		else if (cx >= SCENCE_WITDH - SCREEN_WIDTH)
		{
			game->SetCamPos(SCENCE_WITDH - SCREEN_WIDTH, 0.0f /*cy*/);
		}
		else
		{
			game->SetCamPos(cx, 0.0f);
		}
	}
	else
	{
		game->SetCamPos(0.0f, 0.0f);
	}

}

void Scene::Render()
{
	CGame *game = CGame::GetInstance();
	CSimon *simon = CSimon::getInstance();
	CSprites *sprites = CSprites::GetInstance();
	CBoardGame *boardGame = CBoardGame::GetInstance();
	Grid* grid = Grid::GetInstance();
	vector<int> gridIds;
	grid->caculateGrid(gridIds);
	if (isCanLoadScene)
	{
#pragma region RenderBoardGame


		float camX = game->GetCamPos_x();
		float camY = game->GetCamPos_y();
		int weaponSpriteId = boardGame->GetSubWeapon(simon->getSubWeapon());
		if (simon->getUsingDoubleShot())
		{
			if (simon->x < SCREEN_WIDTH / 2)
			{
				sprites->Get(SPRITE_DOUBLE_SHOT_ID)->Draw(floor(camX + DOUBLE_SHOT_ICON_POS_X), floor(camY + DOUBLE_SHOT_ICON_POS_Y));
			}
			else
			{
				sprites->Get(SPRITE_DOUBLE_SHOT_ID)->Draw(floor(camX + DOUBLE_SHOT_ICON_POS_X), floor(camY + DOUBLE_SHOT_ICON_POS_Y));
			}
		}
		sprites->Get(BLACK_BOARD_ID)->Draw(camX, camY);

		for (int i = 0; i < SIMON_MAX_HEALTH; i++) {
			float posX, posY;
			boardGame->GetPositionSimonHealthBar(posX, posY);
			sprites->Get(SPRITE_SIMON_HEALTH_CELL_ID)->Draw(floor(camX + posX) + i * CELL_MARGIN, floor(camY + posY));

			if (SIMON_MAX_HEALTH - simon->GetHealth() * 2 > 0)
			{
				for (int j = simon->GetHealth() * 2; j < SIMON_MAX_HEALTH; j++) {
					sprites->Get(SPRITE_LOST_HEALTH_ID)->Draw(floor(camX + posX) + j * CELL_MARGIN, floor(camY + posY));
				}
			}
		}

		for (int i = 0; i < ENEMY_MAX_HEALTH; i++) {
			float posX, posY;
			boardGame->GetPositionEnemyHealthBar(posX, posY);
			sprites->Get(SPRITE_ENEMY_HEALTH_CELL_ID)->Draw(floor(camX + posX) + i * CELL_MARGIN, floor(camY + posY));

			if (ENEMY_MAX_HEALTH - BOSS_HEALTH > 0)
			{
				for (int j = BOSS_HEALTH; j < ENEMY_MAX_HEALTH; j++) {
					sprites->Get(SPRITE_LOST_HEALTH_ID)->Draw(floor(camX + posX) + j * CELL_MARGIN, floor(camY + posY));
				}
			}
		}

		if (weaponSpriteId != -1)
		{
			float posX, posY, drawPosX, drawPosY;
			boardGame->GetPositionSubWeapon(posX, posY);
			switch (weaponSpriteId)
			{
			case SPRITE_DANGER_ID:
				drawPosX = posX + DAGGER_ITEM_PADDING_LEFT;
				drawPosY = posY;
				break;
			case SPRITE_AXE_ID:
				drawPosX = posX + AXE_ITEM_PADDING_LEFT;
				drawPosY = posY + AXE_ITEM_PADDING_TOP;
				break;
			case SPRITE_HOLY_WATER_ID:
				drawPosX = posX + HOLY_WATER_ITEM_PADDING_LEFT;
				drawPosY = posY + HOLY_WATER_ITEM_PADDING_TOP;
				break;
			case SPRITE_STOP_WATCH_ID:
				drawPosX = posX + STOP_WATCH_ITEM_PADDING_LEFT;
				drawPosY = posY + STOP_WATCH_ITEM_PADDING_TOP;
				break;
			}

			if (simon->x < SCREEN_WIDTH / 2)
			{

				sprites->Get(weaponSpriteId)->Draw(floor(camX + drawPosX), floor(camY + drawPosY));
			}
			else
			{
				sprites->Get(weaponSpriteId)->Draw(floor(camX + drawPosX), floor(camY + drawPosY));
			}
		}

		for (int i = 0; i < letters.size(); i++)
		{
			int id = letters.at(i).letter;
			float x, y;
			if (simon->x < SCREEN_WIDTH / 2)
			{
				x = floor(camX + letters.at(i).x - 1);
				y = floor(letters.at(i).y + camY);
			}
			else
			{
				x = floor(camX + letters.at(i).x);
				y = floor(letters.at(i).y + camY);
			}

			boardGame->Get(id)->Draw(x, y);
		}
#pragma endregion

		CMap::GetInstance()->Get(mapId)->Render();
		if (simon->getAutoGo() || game->GetCamAutoGo())
		{
#pragma region RenderAutoGo
			for (int gridId = 0; gridId < gridIds.size(); gridId++)
			{
				objects.clear();
				grid->get(gridIds[gridId], objects);
				for (int i = 0; i < objects.size(); i++)
				{
					if (dynamic_cast<ChangeSceneObjects*> (objects[i]))
					{
						objects[i]->Render();
					}
				}
			}
			simon->Render();
		}
#pragma endregion
		else
		{
			if (simon->getFreeze() == true)
			{
#pragma region RenderFreeze
				for (int gridId = 0; gridId < gridIds.size(); gridId++)
				{
					objects.clear();
					grid->get(gridIds[gridId], objects);
					for (int i = 0; i < objects.size(); i++)
					{
						objects[i]->RenderCurrentFrame();
					}
				}
				simon->Render();
				//
				objects.clear();
				grid->get(EFFECTS_GRID, objects);
				for (int i = 0; i < objects.size(); i++)
				{
					objects[i]->RenderCurrentFrame();
				}
				objects.clear();
				grid->get(ITEMS_GRID, objects);
				for (int i = 0; i < objects.size(); i++)
				{
					objects[i]->RenderCurrentFrame();
				}
			}
#pragma endregion
			else if (simon->getUsingStopWatch())
			{
#pragma region RenderStopWatch
				for (int i = 0; i < objects.size(); i++)
				{
					if (dynamic_cast<CEnemies*>(objects[i]))
						objects[i]->RenderCurrentFrame();
					else if (!dynamic_cast<CSimon*>(objects[i]))
						objects[i]->Render();
				}
				objects.clear();
				grid->get(EFFECTS_GRID, objects);
				for (int i = 0; i < objects.size(); i++)
				{
					objects[i]->RenderCurrentFrame();
				}
				objects.clear();
				grid->get(ITEMS_GRID, objects);
				for (int i = 0; i < objects.size(); i++)
				{
					objects[i]->RenderCurrentFrame();
				}
				objects.clear();
				grid->get(ENEMIES_GRID, objects);
				for (int i = 0; i < objects.size(); i++)
				{
					objects[i]->RenderCurrentFrame();
				}
				simon->Render();
#pragma endregion
			}
			else
			{
#pragma region Render
				for (int gridId = 0; gridId < gridIds.size(); gridId++)
				{
					objects.clear();
					grid->get(gridIds[gridId], objects);
					for (int i = 0; i < objects.size(); i++)
					{
						objects[i]->Render();
					}
				}
				objects.clear();
				grid->get(EFFECTS_GRID, objects);
				for (int i = 0; i < objects.size(); i++)
				{
					objects[i]->Render();
				}
				objects.clear();
				grid->get(ITEMS_GRID, objects);
				for (int i = 0; i < objects.size(); i++)
				{
					objects[i]->Render();
				}
				objects.clear();
				grid->get(WEAPONENEMIES_GRID, objects);
				for (int i = 0; i < objects.size(); i++)
				{
					objects[i]->Render();
				}
				simon->Render();
#pragma endregion
			}
		}

	}

}

void Scene::StartLoadScene()
{
	LoadSceneResource();
	float x, y;
	Scenes* scenes = Scenes::GetInstance();
	scenes->GetSimonStartPos(x, y);
	CSimon* simon = CSimon::getInstance();
	simon->SetPosition(x, y);
	simon->setOnStairDistance(99);
	simon->setCanOutStair(false);
	simon->setCanOnStair(false);
	scenceWidth = this->sceneWidthEachMap;
	this->timeStartLoadScene = GetTickCount();
	isCanLoadScene = false;
	lastTimeEachStage = GetTickCount();
	isLoadBlackScene = scenes->GetLoadBlackScene();
	timeLoadBlackScene = scenes->GetTimeLoadBlackScene();
	lockCameraX = 0.0f;
}

void Scene::Reset()
{
	objects.clear();
	listItems.clear();
	effects.clear();
	letters.clear();
	bossHealth = 16;
	scenceWidth = this->sceneWidthEachMap;
	this->timeStartLoadScene = GetTickCount();
	isCanLoadScene = false;
	lastTimeEachStage = GetTickCount();
	CSimon* simon = CSimon::getInstance();
	simon->SetPosition(simonStartX, simonStartY);
	simon->Reset();
	isLoadBlackScene = true;
	timeLoadBlackScene = 400;
	CBoardGame::GetInstance()->setLimitTime(300);
	CSpawner::GetInstance()->resetAfterResetScene();
	lockCameraX = 0.0f;
	LoadSceneResource();
}

void Scene::Clear()
{
	objects.clear();
	listItems.clear();
	effects.clear();
	letters.clear();
	CSpawner::GetInstance()->resetAfterResetScene();
}