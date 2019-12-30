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
	grid = new Grid();


}

void Scene::LoadSceneResource()
{
	CSpawner::GetInstance()->isActive = true;
	grid->clear();
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
			if (id == MAKE_OBJECTS::GROUND)
			{
				CGround* ground = new CGround();
				ground->SetWidthHeigth(Width, Height);
				ground->SetPosition(x, y);
				grid->add(ground, gridId);
			}
			else if (id == MAKE_OBJECTS::LARGECANDLE) {
				int itemId;
				Object->QueryIntAttribute("itemId", &itemId);
				CLargeCandle* largeCandle = new CLargeCandle();
				largeCandle->SetPosition(x, y);
				largeCandle->SetWidthHeight(Width, Height);
				largeCandle->SetItemId(itemId);
				grid->add(largeCandle, gridId);

			}
			else if (id == MAKE_OBJECTS::SMALLCANDLE) {
				int itemId;
				Object->QueryIntAttribute("itemId", &itemId);
				CSmallCandle* smallCandle = new CSmallCandle();
				smallCandle->SetPosition(x, y);
				smallCandle->SetWidthHeight(Width, Height);
				smallCandle->SetItemId(itemId);
				grid->add(smallCandle, gridId);

			}
			else if (id == MAKE_OBJECTS::WALL)
			{
				CWall* wall = new CWall();
				wall->SetPosition(x, y);
				wall->SetWidthHeight(Width, Height);
				grid->add(wall, gridId);

			}
			else if (id == MAKE_OBJECTS::CHANGESCENE)
			{
				int sceneId;
				int  timeLoadBlackScene;
				float simonAutoGoDistance = 0;
				float simonStartPosX, simonStartPosY;
				bool isDoor = false, camAutoGo = false, isLoadBlackScene = false, simonAutoGo = false;
				Object->QueryIntAttribute("sceneId", &sceneId);
				Object->QueryFloatAttribute("simonAutoGoDistance", &simonAutoGoDistance);
				Object->QueryFloatAttribute("simonStartPosX", &simonStartPosX);
				Object->QueryFloatAttribute("simonStartPosY", &simonStartPosY);
				Object->QueryBoolAttribute("camAutoGo", &camAutoGo);
				Object->QueryBoolAttribute("isDoor", &isDoor);
				Object->QueryBoolAttribute("isLoadBlackScene", &isLoadBlackScene);
				Object->QueryBoolAttribute("simonAutoGo", &simonAutoGo);
				Object->QueryIntAttribute("timeLoadBlackScene", &timeLoadBlackScene);
				ChangeSceneObjects* changeScene = new ChangeSceneObjects();
				changeScene->SetPosition(x, y);
				changeScene->SetWidthHeight(Width, Height);
				changeScene->SetSceneId(sceneId);
				changeScene->SetAutoGoDistance(simonAutoGoDistance);
				changeScene->SetSimonStartPos(simonStartPosX, simonStartPosY);
				changeScene->SetTimeLoadBlackScene(timeLoadBlackScene);
				changeScene->SetCamAutoGo(camAutoGo);
				changeScene->SetLoadBlackScene(isLoadBlackScene);
				changeScene->SetIsDoor(isDoor);
				changeScene->SetSimonAutoGo(simonAutoGo);
				changeScene->SetAutoGoDistance(simonAutoGoDistance);
				grid->add(changeScene, gridId);
				this->simonStartX = simonStartPosX;
				this->simonStartY = simonStartPosY;
			}
			else if (id == MAKE_OBJECTS::SPAWN)
			{
				int enemyId, canRespawn, quantityEachSpawn, timeEachSpawn, spawnerId, delaySpawnTime;
				int offsetWithSimon;
				int  xEnemy, yEnemy;
				int enemyMode;
				float xTarget, yTarget;
				bool setBoss = false;
				Object->QueryIntAttribute("enemyId", &enemyId);
				Object->QueryIntAttribute("xEnemy", &xEnemy);
				Object->QueryIntAttribute("yEnemy", &yEnemy);
				Object->QueryIntAttribute("spawnerId", &spawnerId);
				Object->QueryIntAttribute("quantityEachSpawn", &quantityEachSpawn);
				Object->QueryIntAttribute("timeEachSpawn", &timeEachSpawn);
				Object->QueryIntAttribute("delaySpawnTime", &delaySpawnTime);
				Object->QueryIntAttribute("canRespawn", &canRespawn);
				Object->QueryIntAttribute("offsetWithSimon", &offsetWithSimon);
				Object->QueryIntAttribute("enemyMode", &enemyMode);
				Object->QueryFloatAttribute("xTarget", &xTarget);
				Object->QueryFloatAttribute("yTarget", &yTarget);
				Object->QueryBoolAttribute("isBoss", &setBoss);
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
				spawn->SetOffsetWithSimon(offsetWithSimon);
				spawn->SetTargetPosition(xTarget, yTarget);
				spawn->SetBoss(setBoss);
				spawn->SetEnemyMode(enemyMode);
				grid->add(spawn, gridId);
			}
			else if (id == MAKE_OBJECTS::CHECKSTAIR)
			{
				int ny, nx;
				Object->QueryIntAttribute("ny", &ny);
				Object->QueryIntAttribute("nx", &nx);
				CheckStair* checkStair = new CheckStair();
				checkStair->SetPosition(x, y);
				checkStair->SetWidthHeight(Width, Height);
				checkStair->SetNxNy(nx, ny);
				grid->add(checkStair, gridId);

			}
			else if (id == MAKE_OBJECTS::HIDDENWALL)
			{
				int type, itemId;
				Object->QueryIntAttribute("type", &type);
				Object->QueryIntAttribute("itemId", &itemId);
				CHiddenWall* hiddenWall = new CHiddenWall(x, y, type, itemId);
				hiddenWall->SetWidthHeight(Width, Height);
				grid->add(hiddenWall, gridId);

			}
			else if (id == MAKE_OBJECTS::LOCK)
			{
				LockSimon* lockSimon = new LockSimon();
				lockSimon->SetWidthHeight(Width, Height);
				lockSimon->SetPosition(x, y);
				grid->add(lockSimon, gridId);

			}
			else if (id == MAKE_OBJECTS::DESTROY)
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
				grid->add(detroy, gridId);
			}
		}
	}
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

void Scene::MakeEnemies(DWORD dt)
{
	CSpawner* spawner = CSpawner::GetInstance();
	CSimon* simon = CSimon::getInstance();

	float cx, cy;
	float sx, sy;
	cx = CGame::GetInstance()->GetCamPos_x();
	cy = CGame::GetInstance()->GetCamPos_y();
	CSimon::getInstance()->GetPosition(sx, sy);
	int lastNx = 1;
	DWORD now = GetTickCount();

	if (simon->getUsingStopWatch() == false || simon->getUsingCross() == false
		&& spawner->isActive)
	{
		if (spawner->quantitySpawned >= spawner->quantityEachSpawn)
		{
			spawner->canSpawn = false;
		}
		if (spawner->quantityEnemyDied >= spawner->quantityEachSpawn
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
				if (spawner->enemyId == MONKEY_EAGLE_ID)
				{
					int rand = Random(10, 12);
					CEagle* eagle = new CEagle();
					Monkey* monkey = new Monkey();
					eagle->setIdleTime(70 * rand);
					monkey->setTimeActive(rand * 50);
					float x, y;
					eagle->GetPosition(x, y);
					monkey->SetPosition(x + EAGLE_BB_WIDTH / 3, y + EAGLE_BB_HEIGHT / 1.2);
					spawner->quantitySpawned += 1;
					grid->add(monkey, ENEMIES_GRID);
					grid->add(eagle, ENEMIES_GRID);
				}
				else if (spawner->enemyId == FINAL_BOSS_ID)
				{
					FinalBoss* finalBoss = new FinalBoss();
					finalBoss->SetPosition(spawner->xEnemy, spawner->yEnemy);
					finalBoss->SetTargetPosition(spawner->xTarget, spawner->yTarget);
					grid->add(finalBoss, ENEMIES_GRID);
					spawner->quantitySpawned += 1;
				}
				else if (spawner->enemyId == SKELETON_ID)
				{
					Skeleton *skeleton = new Skeleton();
					skeleton->SetPosition(spawner->xEnemy, spawner->yEnemy);
					skeleton->SetOffsetWithSimon(spawner->offsetWithSimon);
					skeleton->SetMode(spawner->enemyMode);
					grid->add(skeleton, ENEMIES_GRID);
					spawner->quantitySpawned += 1;

				}
				else if (spawner->enemyId == GHOST_ID)
				{
					CGhost* ghost = new CGhost(cx, cy);
					spawner->quantitySpawned += 1;
					grid->add(ghost, ENEMIES_GRID);

				}
				else if (spawner->enemyId == PANTHER_ID)
				{
					CPanther* panther = new CPanther(spawner->xEnemy, spawner->yEnemy);
					spawner->quantitySpawned += 1;
					grid->add(panther, ENEMIES_GRID);

				}
				else if (spawner->enemyId == BAT_ID)
				{
					CBat* bat = new CBat(cx, sy);
					spawner->quantitySpawned += 1;
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
						grid->add(splash, EFFECTS_GRID);

					}
					spawner->quantitySpawned += 1;
					grid->add(fish, ENEMIES_GRID);
				}
				else if (spawner->enemyId == BOSS_BAT_ID)
				{
					CBossBat* bossBat = new CBossBat();
					spawner->setBoss ? DebugOut(L"\nBoss") : DebugOut(L"\n?");
					bossBat->SetIsBoss(spawner->setBoss);
					bossBat->SetPosition(spawner->xEnemy, spawner->yEnemy);
					bossBat->SetTargetPosition(spawner->xTarget, spawner->yTarget);
					spawner->quantitySpawned += 1;
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
				int id = gridIds[gridId];
				for (int i = 0; i < grid->gridObjects[id].size(); i++)
				{
					if (dynamic_cast<ChangeSceneObjects*>(grid->gridObjects[id][i]))
					{
						grid->gridObjects[id][i]->Update(dt);
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
			vector<LPGAMEOBJECT> coMonkey;
			vector<LPGAMEOBJECT> coWeaponObjects;
			vector<LPGAMEOBJECT> coItemObjects;
			vector<LPGAMEOBJECT> coDestroy;
			vector<LPGAMEOBJECT> coHiddenObjects;
			vector<LPGAMEOBJECT> coCheckStairObjects;

			UpdateBoardGame(dt);
			MakeEnemies(dt); // luôn gọi trước khi update các thứ khác
			//MakeWeaponEnemies(dt);
#pragma region CaculateCollision
			for (int gridId = 0; gridId < gridIds.size(); gridId++)
			{
				int id = gridIds[gridId];
				//lấy objects để tính colisions
				for (int i = 0; i < grid->gridObjects[id].size(); i++)
				{
					if (dynamic_cast<CheckStair*>(grid->gridObjects[id][i]))
					{
						coCheckStairObjects.push_back(grid->gridObjects[id][i]);
					}
					if (dynamic_cast<CGround*> (grid->gridObjects[id][i])
						|| dynamic_cast<CWall*> (grid->gridObjects[id][i]))
					{
						coMonkey.push_back(grid->gridObjects[id][i]);
					}
					if (dynamic_cast<CGround*> (grid->gridObjects[id][i]))
					{
						coEnemies.push_back(grid->gridObjects[id][i]);
					}
					if (dynamic_cast<CGround*> (grid->gridObjects[id][i])
						|| (dynamic_cast<CSimon*> (grid->gridObjects[id][i])
							|| (dynamic_cast<CWall*>(grid->gridObjects[id][i])))
						)
					{
						coItemObjects.push_back(grid->gridObjects[id][i]);
						coHiddenObjects.push_back(grid->gridObjects[id][i]);
					}
					if (!dynamic_cast<CSimon*> (grid->gridObjects[id][i])
						&& !dynamic_cast<ChangeSceneObjects*> (grid->gridObjects[id][i])
						&& !dynamic_cast<CItems*> (grid->gridObjects[id][i])
						&& !dynamic_cast<CSpawn*>(grid->gridObjects[id][i])
						)
					{
						coWeaponObjects.push_back(grid->gridObjects[id][i]);
					}
					if (dynamic_cast<CEnemies*> (grid->gridObjects[id][i]))
					{
						coDestroy.push_back(grid->gridObjects[id][i]);
					}
					if (dynamic_cast<CGround*>(grid->gridObjects[id][i]))
					{
						coObjects.push_back(grid->gridObjects[id][i]);
					}
#pragma region UpdateHeath<0


					if (grid->gridObjects[id][i]->GetHealth() <= 0)
					{

						if (dynamic_cast<CHiddenWall*>(grid->gridObjects[id][i]))
						{
							CHiddenWall* hiddenWall = dynamic_cast<CHiddenWall*>(grid->gridObjects[id][i]);
							float x, y;
							hiddenWall->GetPosition(x, y);
							for (int i = 0; i < QUANTITY_EFFECT_WALL; i++)
							{
								CEffect * breakingWall = new CBreakingWall(x, y);
								grid->add(breakingWall, EFFECTS_GRID);
							}
							if (hiddenWall->getItemId() == 1)
							{
								PotRoast* potRoast = new PotRoast(x, y);
								grid->add(potRoast, ITEMS_GRID);
							}
							if (hiddenWall->getItemId() == 2)
							{
								DoubleShot* doubleShot = new DoubleShot(x, y);
								grid->add(doubleShot, ITEMS_GRID);
							}

						}
						else if (grid->gridObjects[id][i]->GetKillBySimon())
						{
							if (grid->gridObjects[id][i]->GetIsBoss() == false)
							{
								float x, y;
								CEffect * hit = new CHit();
								if (grid->gridObjects[id][i]->GetKillBySimon())
								{
									hit->SetKillBySimon(true);
								}
								if (dynamic_cast<CStaticObject*>(grid->gridObjects[id][i]))
								{
									CStaticObject* staticObjects = dynamic_cast<CStaticObject*>(grid->gridObjects[id][i]);
									int itemId = staticObjects->GetItemId();
									hit->SetItemId(itemId);
									hit->SetMakeItem(STATIC_OBJECT);
								}
								if (dynamic_cast<CEnemies*> (grid->gridObjects[id][i]))
								{
									hit->SetMakeItem(ENEMY);
									CSpawner::GetInstance()->quantityEnemyDied++;
								}
								grid->gridObjects[id][i]->GetPosition(x, y);
								hit->SetPosition(x, y);

								grid->add(hit, EFFECTS_GRID);
							}
							else
							{
								if (dynamic_cast<CBossBat*>(grid->gridObjects[id][i]))
								{
									float x, y;
									grid->gridObjects[id][i]->GetPosition(x, y);
									for (int i = 0; i < 3; i++)
									{
										for (int j = 0; j < 2; j++)
										{
											CEffect * hit = new CHit();
											hit->SetPosition(x + 16 * i, y + 16 * j);
											hit->SetKillBySimon(true);
											hit->SetMakeItem(ENEMY);
											grid->add(hit, EFFECTS_GRID);
										}
									}

								}
							}
						}
						else if (dynamic_cast<CUglyFish*>(grid->gridObjects[id][i]))
						{

							float x, y;
							grid->gridObjects[id][i]->GetPosition(x, y);
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
								grid->add(splash, EFFECTS_GRID);
							}
							CSpawner::GetInstance()->quantityEnemyDied++;
						}
						else if (dynamic_cast<CEnemies*> (grid->gridObjects[id][i]))
						{
							CSpawner::GetInstance()->quantityEnemyDied++;
						}
						grid->gridObjects[id].erase(grid->gridObjects[id].begin() + i);


					}

#pragma endregion

				}

			}
			// effect for enemies
#pragma endregion

			simon->UpdateSimonWeapon(dt, &coWeaponObjects);


#pragma region UpdateItems
			for (int i = 0; i < grid->gridObjects[ITEMS_GRID].size(); i++)
			{
				CItems* item = dynamic_cast<CItems*>(grid->gridObjects[ITEMS_GRID][i]);
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
						grid->gridObjects[ITEMS_GRID].erase(grid->gridObjects[ITEMS_GRID].begin() + i);
					}
					else
					{
						grid->gridObjects[ITEMS_GRID].erase(grid->gridObjects[ITEMS_GRID].begin() + i);
					}
				}
			}
#pragma endregion

#pragma region UpdateEffects

			for (int i = 0; i < grid->gridObjects[EFFECTS_GRID].size(); i++)
			{
				CEffect* effect = dynamic_cast<CEffect*>(grid->gridObjects[EFFECTS_GRID][i]);
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
								if (itemId == MAKE_ITEMS::ITEMS_LARGEHEART)
									item = new LargeHeart(x, y);
								if (itemId == MAKE_ITEMS::ITEMS_WHIPUPGRADE)
									item = new WhipUpgrade(x, y);
								if (itemId == MAKE_ITEMS::ITEMS_DANGER)
									item = new Danger(x, y);
								if (itemId == MAKE_ITEMS::ITEMS_HOLYWATER)
									item = new HolyWater(x, y);
								if (itemId == MAKE_ITEMS::ITEMS_CROSS)
									item = new Cross(x, y);
								if (itemId == MAKE_ITEMS::ITEMS_INVIPOTION)
									item = new InviPotion(x, y);
								if (itemId == MAKE_ITEMS::ITEMS_AXE)
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
					grid->gridObjects[EFFECTS_GRID].erase(grid->gridObjects[EFFECTS_GRID].begin() + i);
					effect->reset();
				}
				else
				{
					effect->Update(dt);
				}
			}
#pragma endregion
#pragma region Update

			//Gọi update với colision tính được
			if (simon->getUsingStopWatch())
			{
#pragma region UpdateStopWatch
				for (int gridId = 0; gridId < gridIds.size(); gridId++)
				{
					int id = gridIds[gridId];
					for (int i = 0; i < grid->gridObjects[id].size(); i++)
					{
						if (dynamic_cast<CDestroy*> (grid->gridObjects[id][i]))
						{
							grid->gridObjects[id][i]->Update(dt, &coDestroy);
						}
						else if (dynamic_cast<ChangeSceneObjects*> (grid->gridObjects[id][i]))
						{
							grid->gridObjects[id][i]->Update(dt);
						}
						else if (dynamic_cast<HiddenObjects*>(grid->gridObjects[id][i]))
						{
							grid->gridObjects[id][i]->Update(dt, &coHiddenObjects);
						}
					}
				}
				simon->Update(dt, &coObjects);
#pragma endregion

			}
			else if (simon->getUsingCross())
			{
				backGroundColor = D3DCOLOR_XRGB(169, 169, 169); // Màu xám
				for (int i = 0; i < grid->gridObjects[ENEMIES_GRID].size(); i++)
				{
					if (dynamic_cast<CEnemies*>(grid->gridObjects[ENEMIES_GRID][i]))
					{
						grid->gridObjects[ENEMIES_GRID].erase(grid->gridObjects[ENEMIES_GRID].begin() + i);
					}
				}
				simon->Update(dt, &coObjects);
			}
			else
			{
				backGroundColor = D3DCOLOR_XRGB(0, 0, 0);
				for (int gridId = 0; gridId < gridIds.size(); gridId++)
				{
					int id = gridIds[gridId];
					for (int i = 0; i < grid->gridObjects[id].size(); i++)
					{
						if (dynamic_cast<Monkey*>(grid->gridObjects[id][i])) {

							grid->gridObjects[id][i]->Update(dt, &coMonkey);
						}
						else if (dynamic_cast<CEnemies*>(grid->gridObjects[id][i])) {

							grid->gridObjects[id][i]->Update(dt, &coEnemies);
						}
						else if (dynamic_cast<CDestroy*> (grid->gridObjects[id][i]))
						{
							grid->gridObjects[id][i]->Update(dt, &coDestroy);
						}
						else if (dynamic_cast<HiddenObjects*>(grid->gridObjects[id][i]))
						{
							grid->gridObjects[id][i]->Update(dt, &coHiddenObjects);
						}
						else
						{
							grid->gridObjects[id][i]->Update(dt);
						}
					}
				}
				simon->Update(dt, &coObjects);
			}


			simon->UpdateCheckStair(&coCheckStairObjects);
		}
		else
		{
			simon->UpdateFreeze(dt);
			for (int gridId = 0; gridId < gridIds.size(); gridId++)
			{
				int id = gridIds[gridId];
				for (int i = 0; i < grid->gridObjects[id].size(); i++)
				{
					if (grid->gridObjects[id][i]->GetHealth() <= 0)
						grid->gridObjects[id].erase(grid->gridObjects[id].begin() + i);
				}
			}
			for (int i = 0; i < grid->gridObjects[ITEMS_GRID].size(); i++)
			{
				CItems* item = dynamic_cast<CItems*>(grid->gridObjects[ITEMS_GRID][i]);
				if (item->GetHealth() <= 0)
					grid->gridObjects[ITEMS_GRID].erase(grid->gridObjects[ITEMS_GRID].begin() + i);
				else
					item->SetMakeTime(GetTickCount());
			}
		}
#pragma endregion

		float cx, cy;
		simon->GetPosition(cx, cy);

		cx -= SCREEN_WIDTH / 2 - 32;
		cy -= SCREEN_HEIGHT / 2;
		if (isLockCamX)
		{
			game->SetCamPos(LOCK_CAMERA_X, 0.0f /*cy*/);
		}
		else
		{
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
	grid->caculateGrid(gridIds);
	if (isCanLoadScene)
	{
#pragma region RenderBoardGame


		float camX = game->GetCamPos_x();
		float camY = game->GetCamPos_y();
		int weaponSpriteId = boardGame->GetSubWeapon(simon->getSubWeapon());
		if (simon->getUsingDoubleShot())
		{
			sprites->Get(SPRITE_DOUBLE_SHOT_ID)->Draw(floor(camX + DOUBLE_SHOT_ICON_POS_X), floor(camY + DOUBLE_SHOT_ICON_POS_Y));
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

			sprites->Get(weaponSpriteId)->Draw(floor(camX + drawPosX), floor(camY + drawPosY));
		}

		for (int i = 0; i < letters.size(); i++)
		{
			int id = letters.at(i).letter;
			float x, y;

			x = floor(camX + letters.at(i).x);
			y = floor(letters.at(i).y + camY);

			boardGame->Get(id)->Draw(x, y);
		}
#pragma endregion

		CMap::GetInstance()->Get(mapId)->Render();
		if (simon->getAutoGo() || game->GetCamAutoGo())
		{
#pragma region RenderAutoGo
			for (int gridId = 0; gridId < gridIds.size(); gridId++)
			{
				int id = gridIds[gridId];
				for (int i = 0; i < grid->gridObjects[id].size(); i++)
				{
					if (dynamic_cast<ChangeSceneObjects*> (grid->gridObjects[id][i]))
					{
						grid->gridObjects[id][i]->Render();
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
					int id = gridIds[gridId];
					for (int i = 0; i < grid->gridObjects[id].size(); i++)
					{
						grid->gridObjects[id][i]->RenderCurrentFrame();
					}
				}
				simon->Render();
				//
				for (int i = 0; i < grid->gridObjects[EFFECTS_GRID].size(); i++)
				{
					grid->gridObjects[EFFECTS_GRID][i]->RenderCurrentFrame();
				}
				for (int i = 0; i < grid->gridObjects[ITEMS_GRID].size(); i++)
				{
					grid->gridObjects[ITEMS_GRID][i]->RenderCurrentFrame();
				}
				for (int i = 0; i < grid->gridObjects[WEAPONENEMIES_GRID].size(); i++)
				{
					grid->gridObjects[WEAPONENEMIES_GRID][i]->RenderCurrentFrame();
				}
			}
#pragma endregion
			else if (simon->getUsingStopWatch())
			{
#pragma region RenderStopWatch
				for (int gridId = 0; gridId < gridIds.size(); gridId++)
				{
					int id = gridIds[gridId];
					for (int i = 0; i < grid->gridObjects[id].size(); i++)
					{
						grid->gridObjects[id][i]->Render();
					}
				}
				for (int i = 0; i < grid->gridObjects[EFFECTS_GRID].size(); i++)
				{
					grid->gridObjects[EFFECTS_GRID][i]->Render();
				}
				for (int i = 0; i < grid->gridObjects[ITEMS_GRID].size(); i++)
				{
					grid->gridObjects[ITEMS_GRID][i]->Render();
				}
				for (int i = 0; i < grid->gridObjects[ENEMIES_GRID].size(); i++)
				{
					grid->gridObjects[ENEMIES_GRID][i]->RenderCurrentFrame();
				}
				simon->Render();
#pragma endregion
			}
			else
			{
#pragma region Render
				for (int gridId = 0; gridId < gridIds.size(); gridId++)
				{
					int id = gridIds[gridId];
					for (int i = 0; i < grid->gridObjects[id].size(); i++)
					{
						grid->gridObjects[id][i]->Render();
					}
				}
				for (int i = 0; i < grid->gridObjects[EFFECTS_GRID].size(); i++)
				{
					grid->gridObjects[EFFECTS_GRID][i]->Render();
				}
				for (int i = 0; i < grid->gridObjects[ITEMS_GRID].size(); i++)
				{
					grid->gridObjects[ITEMS_GRID][i]->Render();
				}
				for (int i = 0; i < grid->gridObjects[WEAPONENEMIES_GRID].size(); i++)
				{
					grid->gridObjects[WEAPONENEMIES_GRID][i]->Render();
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
	vector<Letter>().swap(letters);
	bossHealth = DEFAULT_BOSS_HEATH;
	scenceWidth = this->sceneWidthEachMap;
	this->timeStartLoadScene = GetTickCount();
	isCanLoadScene = false;
	lastTimeEachStage = GetTickCount();
	CSimon* simon = CSimon::getInstance();
	simon->SetPosition(simonStartX, simonStartY);
	simon->Reset();
	isLoadBlackScene = true;
	timeLoadBlackScene = TIME_LOAD_BLACK_SCENE;
	CBoardGame::GetInstance()->setLimitTime(LIMIT_TIME);
	CSpawner::GetInstance()->resetAfterResetScene();
	lockCameraX = 0.0f;
	LoadSceneResource();
}

void Scene::Clear()
{
	vector<Letter>().swap(letters);
	CSpawner::GetInstance()->resetAfterResetScene();
}