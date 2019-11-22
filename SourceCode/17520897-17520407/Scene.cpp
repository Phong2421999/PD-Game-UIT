#include "Scene.h"

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
		int id;
		float x, y, Width, Height;
		Objects->QueryIntAttribute("id", &id);
		for (Object = Objects->FirstChildElement(); Object != NULL; Object = Object->NextSiblingElement())
		{
			Object->QueryFloatAttribute("x", &x);
			Object->QueryFloatAttribute("y", &y);
			Object->QueryFloatAttribute("width", &Width);
			Object->QueryFloatAttribute("height", &Height);
			if (id == 0)
			{
				CGround* ground = new CGround();
				ground->SetWidthHeigth(Width, Height);
				ground->SetPosition(x, y);
				objects.push_back(ground);
			}
			else if (id == 1) {
				CLargeCandle* largeCandle = new CLargeCandle();
				largeCandle->SetPosition(x, y);
				largeCandle->SetWidthHeight(Width, Height);
				objects.push_back(largeCandle);
			}
			else if (id == 2) {
				CSmallCandle* smallCandle = new CSmallCandle();
				smallCandle->SetPosition(x, y);
				smallCandle->SetWidthHeight(Width, Height);
				objects.push_back(smallCandle);
			}
			else if (id == 3)
			{
				CWall* wall = new CWall();
				wall->SetPosition(x, y);
				wall->SetWidthHeight(Width, Height);
				objects.push_back(wall);
			}
			else if (id == -1)
			{
				int sceneId, simonAutoGo;
				int isDoor, camAutoGo;
				float simonAutoGoDistance;
				Object->QueryIntAttribute("sceneId", &sceneId);
				Object->QueryIntAttribute("simonAutoGo", &simonAutoGo);
				Object->QueryFloatAttribute("simonAutoGoDistance", &simonAutoGoDistance);
				Object->QueryIntAttribute("camAutoGo", &camAutoGo);
				Object->QueryIntAttribute("isDoor", &isDoor);

				ChangeSceneObjects* changeScene = new ChangeSceneObjects();
				changeScene->SetPosition(x, y);
				changeScene->SetWidthHeight(Width, Height);
				changeScene->SetSceneId(sceneId);
				changeScene->SetAutoGoDistance(simonAutoGoDistance);
				if (camAutoGo == 1)
				{
					changeScene->SetCamAutoGo(true);
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
			}
			else if (id == -2)
			{
				int enemyId, quantityEachSpawn, timeEachSpawn, spawnerId, delaySpawnTime, xEnemy, yEnemy;
				Object->QueryIntAttribute("enemyId", &enemyId);
				Object->QueryIntAttribute("xEnemy", &xEnemy);
				Object->QueryIntAttribute("yEnemy", &yEnemy);
				Object->QueryIntAttribute("spawnerId", &spawnerId);
				Object->QueryIntAttribute("quantityEachSpawn", &quantityEachSpawn);
				Object->QueryIntAttribute("timeEachSpawn", &timeEachSpawn);
				Object->QueryIntAttribute("delaySpawnTime", &delaySpawnTime);

				CSpawn* spawn = new CSpawn();
				spawn->SetPosition(x, y);
				spawn->SetPositionEnemy(xEnemy, yEnemy);
				spawn->SetWidthHeight(Width, Height);
				spawn->SetSpawnEnemyType(enemyId);
				spawn->SetSpawnerId(spawnerId);
				spawn->SetQuantitySpawnEnemy(quantityEachSpawn);
				spawn->SetTimeEachSpawn(timeEachSpawn);
				spawn->SetDelaySpawnTime(delaySpawnTime);

				objects.push_back(spawn);
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
			}
			else if (id == -4)
			{
				int type, itemId;
				Object->QueryIntAttribute("type", &type);
				Object->QueryIntAttribute("itemId", &itemId);
				CHiddenWall* hiddenWall = new CHiddenWall(x, y, type, itemId);
				hiddenWall->SetWidthHeight(Width, Height);
				objects.push_back(hiddenWall);
			}
			else if (id == -5)
			{
				LockSimon* lockSimon = new LockSimon();
				lockSimon->SetWidthHeight(Width, Height);
				lockSimon->SetPosition(x, y);
				objects.push_back(lockSimon);
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
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->makeWeapon)
		{
			if (dynamic_cast<CUglyFish*>(objects[i]))
			{
				float x, y;
				objects[i]->GetPosition(x, y);
				int nx = objects[i]->getDirection();
				WeaponProjectile * weapon = new WeaponProjectile(x, y, nx);
				weaponEnemies.push_back(weapon);
			}
			else if (dynamic_cast<CBossBat*>(objects[i]))
			{
				float x, y;
				objects[i]->GetPosition(x, y);
				int nx = objects[i]->getDirection();
				WeaponProjectile * weapon = new WeaponProjectile(x, y, nx);
				weaponEnemies.push_back(weapon);
			}
		}
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
	if (simon->getUsingStopWatch() == false || simon->getUsingCross() == false)
	{
		if (spawner->quantitySpawned == spawner->quantityEachSpawn)
		{
			spawner->canSpawn = false;
		}
		if (spawner->quantityEnemyDied == spawner->quantityEachSpawn)
		{
			if (now - spawner->lastSpawnTime > spawner->delaySpawnTime)
			{
				spawner->quantitySpawned = 0;
				spawner->quantityEnemyDied = 0;
				if (spawner->enemyId != PANTHER_ID && spawner->enemyId != 100)
				{
					spawner->canSpawn = true;
				}
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

				}
				else if (spawner->enemyId == PANTHER_ID)
				{
					CPanther* panther = new CPanther(spawner->xEnemy, spawner->yEnemy);
					spawner->quantitySpawned += 1;
					objects.push_back(panther);
				}
				else if (spawner->enemyId == BAT_ID)
				{
					CBat* bat = new CBat(cx, sy);
					spawner->quantitySpawned += 1;
					objects.push_back(bat);
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
					}
					spawner->quantitySpawned += 1;
					objects.push_back(fish);
				}
				else if (spawner->enemyId == BOSS_BAT_ID)
				{
					CBossBat* bossBat = new CBossBat();
					bossBat->SetIsBoss(true);
					spawner->quantitySpawned += 1;
					objects.push_back(bossBat);
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

	if (((x > cx - 86) || (x + width > cx - 86)) && x < cx + SCREEN_WIDTH + 86 || x < -150)
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
			for (int i = 0; i < objects.size(); i++)
			{
				if (isInGrid(objects[i]))
				{
					if (dynamic_cast<ChangeSceneObjects*>(objects[i]))
					{
						objects[i]->Update(dt);
					}
				}

			}
			CSimon::getInstance()->Update(dt);
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

			//lấy objects để tính colisions
			for (int i = 0; i < objects.size(); i++)
			{
				if (isInGrid(objects[i]))
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
				}

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
							}
							if (hiddenWall->getItemId() == 1)
							{
								PotRoast* potRoast = new PotRoast(x, y);
								listItems.push_back(potRoast);
							}
							if (hiddenWall->getItemId() == 2)
							{
								DoubleShot* doubleShot = new DoubleShot(x, y);
								listItems.push_back(doubleShot);
							}

						}
						if (objects[i]->GetKillBySimon())
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
									hit->SetMakeItem(STATIC_OBJECT);

								if (dynamic_cast<CEnemies*> (objects[i]))
								{
									hit->SetMakeItem(ENEMY);
									CSpawner::GetInstance()->quantityEnemyDied++;
								}
								objects[i]->GetPosition(x, y);
								hit->SetPosition(x, y);
								effects.push_back(hit);
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
							}
							CSpawner::GetInstance()->quantityEnemyDied++;
						}
						else if (dynamic_cast<CEnemies*> (objects[i]))
						{
							CSpawner::GetInstance()->quantityEnemyDied++;
						}
						objects.erase(objects.begin() + i);
					}
					else
						objects[i]->SetState(SIMON_STATE_DIE);

				}


			}
			simon->UpdateSimonWeapon(dt, &coWeaponObjects);
			UpdateWeaponEnemies(dt, &coWeaponEnemies);

			//Gọi update với colision tính được
			if (simon->getUsingStopWatch())
			{
				for (int i = 0; i < objects.size(); i++)
				{
					if (isInGrid(objects[i]))
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
						else if (dynamic_cast<CSimon*> (objects[i])) {
							objects[i]->Update(dt, &coObjects);
						}
						else if (dynamic_cast<HiddenObjects*>(objects[i]))
						{
							objects[i]->Update(dt, &coHiddenObjects);
						}
					}
				}

			}
			else if (simon->getUsingCross())
			{
				backGroundColor = D3DCOLOR_XRGB(169, 169, 169); // Màu xám
				for (int i = 0; i < objects.size(); i++)
				{
					if (isInGrid(objects[i]))
					{
						if (dynamic_cast<CEnemies*>(objects[i])) {
							objects.erase(objects.begin() + i);
						}
						else if (dynamic_cast<CSimon*> (objects[i])) {
							objects[i]->Update(dt, &coObjects);
						}
					}
				}
			}
			else
			{
				backGroundColor = D3DCOLOR_XRGB(0, 0, 0);
				for (int i = 0; i < objects.size(); i++)
				{
					if (dynamic_cast<CEnemies*>(objects[i])) {
						float x, y;
						objects[i]->GetPosition(x, y);
					}
					if (isInGrid(objects[i]))
					{
						if (dynamic_cast<CItems*> (objects[i]))
						{
							objects[i]->Update(dt, &coItemObjects);
						}
						else if (dynamic_cast<CEnemies*>(objects[i])) {

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
						else if (dynamic_cast<CSimon*> (objects[i])) {
							objects[i]->Update(dt, &coObjects);
						}
						else if (dynamic_cast<HiddenObjects*>(objects[i]))
						{
							objects[i]->Update(dt, &coHiddenObjects);
						}
					}
				}
			}


			//simon->UpdateCheckStair(&coCheckStairObjects);

			for (int i = 0; i < listItems.size(); i++)
			{
				if (listItems[i]->GetHealth() > 0)
				{
					listItems[i]->Update(dt, &coItemObjects);
				}
				else
				{
					if (dynamic_cast<MoneyBag*>(listItems[i]))
					{
						float x, y;
						listItems[i]->GetPosition(x, y);
						CEffect * moneyEffect = new CMoneyEffect(x, y, listItems[i]->GetGameItem());
						effects.push_back(moneyEffect);
						listItems.erase(listItems.begin() + i);
					}
					else
					{
						listItems.erase(listItems.begin() + i);
					}
				}
			}

			for (int i = 0; i < effects.size(); i++)
			{
				if (isInGrid(effects[i]))
				{
					if (effects[i]->GetLastFrame())
					{

						float x, y;
						effects[i]->GetPosition(x, y);
						SmallHeart* smallHeart = new SmallHeart(x, y);
						listItems.push_back(smallHeart);
						if (effects[i]->GetKillBySimon())
						{
							if (effects[i]->GetMakeItem() == STATIC_OBJECT)
							{
								int rand = Random(0, 30);
								/*if (CSimon::getInstance()->getWeaponLevel() < 3)
								{
									WhipUpgrade* whipUpgrade = new WhipUpgrade(x, y);
									listItems.push_back(whipUpgrade);
								}
								else if (rand >= 0 && rand < 2)
								{
									LargeHeart* largeHeart = new LargeHeart(x, y);
									listItems.push_back(largeHeart);
								}
								else if (rand >= 2 && rand < 8)
								{
									if (CSimon::getInstance()->getSubWeapon() != SIMON_WEAPON::DANGER)
									{
										Danger* danger = new Danger(x, y);
										listItems.push_back(danger);
									}
									else
									{
										SmallHeart* smallHeart = new SmallHeart(x, y);
										listItems.push_back(smallHeart);
									}
								}
								else if (rand == 8)
								{
									if (CSimon::getInstance()->getSubWeapon() != SIMON_WEAPON::AXE &&
										CSimon::getInstance()->getCurrentScene() == 3)
									{
										Axe* axe = new Axe(x, y);
										listItems.push_back(axe);
									}
									else
									{
										SmallHeart* smallHeart = new SmallHeart(x, y);
										listItems.push_back(smallHeart);
									}
								}
								else if (rand == 9)
								{
									if (CSimon::getInstance()->getSubWeapon() != SIMON_WEAPON::HOLY_WATER)
									{
										HolyWater* holyWater = new HolyWater(x, y);
										listItems.push_back(holyWater);
									}
									else
									{
										SmallHeart* smallHeart = new SmallHeart(x, y);
										listItems.push_back(smallHeart);
									}
								}
								else if (rand >= 10 && rand <= 15)
								{
									MoneyBag* moneyBag = new MoneyBag(x, y);
									listItems.push_back(moneyBag);
								}
								else if (rand == 16)
								{
									if (CSimon::getInstance()->getSubWeapon() != SIMON_WEAPON::STOP_WATCH)
									{
										StopWatch* stopWatch = new StopWatch(x, y);
										listItems.push_back(stopWatch);
									}
									else
									{
										SmallHeart* smallHeart = new SmallHeart(x, y);
										listItems.push_back(smallHeart);
									}
								}
								else if (rand == 17)
								{
									Cross* cross = new Cross(x, y);
									listItems.push_back(cross);
								}
								else if (rand == 28)
								{
									InviPotion * inviPotion = new InviPotion(x, y);
									listItems.push_back(inviPotion);
								}
								else
								{
									SmallHeart* smallHeart = new SmallHeart(x, y);
									listItems.push_back(smallHeart);
								}*/
							}
							if (effects[i]->GetMakeItem() == ENEMY)
							{
								int rand = Random(1, 100);
								if (rand == 1)
								{
									LargeHeart* largeHeart = new LargeHeart(x, y);
									listItems.push_back(largeHeart);
								}
								if (rand >= 2 && rand <= 10)
								{
									MoneyBag* moneyBag = new MoneyBag(x, y);
									listItems.push_back(moneyBag);
								}
								if (rand == 99)
								{
									SmallHeart* smallHeart = new SmallHeart(x, y);
									listItems.push_back(smallHeart);
								}
							}
						}
						effects[i]->reset();
						effects.erase(effects.begin() + i);
					}
					else
					{
						effects[i]->Update(dt, NULL);
					}
				}
			}

		}
		else
		{
			for (int i = 0; i < objects.size(); i++)
			{
				if (objects[i]->GetHealth() <= 0)
					objects.erase(objects.begin() + i);
			}
			for (int i = 0; i < listItems.size(); i++)
			{
				if (listItems[i]->GetHealth() <= 0)
					listItems.erase(listItems.begin() + i);
				else
					listItems[i]->SetMakeTime(GetTickCount());
			}
			simon->UpdateFreeze(dt);
		}

		float cx, cy;
		simon->GetPosition(cx, cy);

		cx -= SCREEN_WIDTH / 2 - 32;
		cy -= SCREEN_HEIGHT / 2;
		if (cx <= 0)
		{
			game->SetCamPos(0.0f, 0.0f /*cy*/);
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

	if (isCanLoadScene)
	{
		float camX = game->GetCamPos_x();
		float camY = game->GetCamPos_y();
		int weaponSpriteId = boardGame->GetSubWeapon(simon->getSubWeapon());
		if (simon->getUsingDoubleShot())
		{
			if (simon->x < SCREEN_WIDTH / 2)
			{
				sprites->Get(SPRITE_DOUBLE_SHOT_ID)->Draw(floor(camX + DOUBLE_SHOT_ICON_POS_X - 1), floor(camY + DOUBLE_SHOT_ICON_POS_Y));
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
			sprites->Get(SPRITE_SIMON_HEALTH_CELL_ID)->Draw(floor(camX + posX - 1) + i * CELL_MARGIN, floor(camY + posY));

			if (SIMON_MAX_HEALTH - simon->GetHealth() * 2 > 0)
			{
				for (int j = simon->GetHealth() * 2; j < SIMON_MAX_HEALTH; j++) {
					sprites->Get(SPRITE_LOST_HEALTH_ID)->Draw(floor(camX + posX - 1) + j * CELL_MARGIN, floor(camY + posY));
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

				sprites->Get(weaponSpriteId)->Draw(floor(camX + drawPosX - 1), floor(camY + drawPosY));
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
		CMap::GetInstance()->Get(mapId)->Render();
		if (simon->getAutoGo() || game->GetCamAutoGo())
		{
			for (int i = 0; i < objects.size(); i++)
			{
				if (dynamic_cast<ChangeSceneObjects*> (objects[i]))
				{
					objects[i]->Render();
				}
			}
			simon->Render();
		}
		else
		{
			if (simon->getFreeze() == true)
			{
				for (int i = 0; i < objects.size(); i++)
				{
					if (isInGrid(objects[i]))
					{
						if (dynamic_cast<CSimon*> (objects[i]) == false)
						{
							objects[i]->RenderCurrentFrame();
						}
						else
							objects[i]->Render();
					}

				}
				for (int i = 0; i < effects.size(); i++)
				{
					if (isInGrid(effects[i]))
					{
						effects[i]->RenderCurrentFrame();
					}
				}

				for (int i = 0; i < listItems.size(); i++)
				{
					if (isInGrid(listItems[i]))
					{
						listItems[i]->RenderCurrentFrame();
					}

				}
			}
			else if (simon->getUsingStopWatch())
			{
				for (int i = 0; i < objects.size(); i++)
				{
					if (isInGrid(objects[i]))
					{
						if (dynamic_cast<CEnemies*>(objects[i]))
							objects[i]->RenderCurrentFrame();
						else
							objects[i]->Render();
					}
				}
				for (int i = 0; i < effects.size(); i++)
				{
					if (isInGrid(effects[i]))
					{
						effects[i]->Render();
					}
				}
				for (int i = 0; i < listItems.size(); i++)
				{
					if (isInGrid(listItems[i]))
					{
						listItems[i]->Render();
					}
				}

				for (int i = 0; i < weaponEnemies.size(); i++)
					if (isInGrid(weaponEnemies[i]))
					{
						weaponEnemies[i]->RenderCurrentFrame();
					}
			}
			else
			{
				for (int i = 0; i < objects.size(); i++)
				{
					if (isInGrid(objects[i]))
						objects[i]->Render();
				}
				for (int i = 0; i < effects.size(); i++)
				{
					if (isInGrid(effects[i]))
						effects[i]->Render();
				}
				for (int i = 0; i < listItems.size(); i++)
				{
					if (isInGrid(listItems[i]))
						listItems[i]->Render();
				}
				for (int i = 0; i < weaponEnemies.size(); i++)
				{
					if (isInGrid(weaponEnemies[i]))
						weaponEnemies[i]->Render();

				}
			}
		}

	}

}

void Scene::StartLoadScene()
{
	CSimon::getInstance()->SetPosition(simonStartX, simonStartY);
	scenceWidth = this->sceneWidthEachMap;
	this->timeStartLoadScene = GetTickCount();
	isCanLoadScene = false;
	lastTimeEachStage = GetTickCount();
}

void Scene::Reset()
{
	objects.clear();
	listItems.clear();
	effects.clear();
	letters.clear();
	LoadSceneResource();
	CSimon::getInstance()->Reset();
	CBoardGame::GetInstance()->setLimitTime(300);
	CSpawner::GetInstance()->resetAfterResetScene();

}

void Scene::Clear()
{
	objects.clear();
	listItems.clear();
	effects.clear();
	letters.clear();
	LoadSceneResource();
	CSpawner::GetInstance()->resetAfterResetScene();
}