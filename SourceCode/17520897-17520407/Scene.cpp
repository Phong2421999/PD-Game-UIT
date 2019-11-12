#include "Scene.h"

Scene::Scene(int sceneWidthEachMap, int loadBlackScene, int stage, DWORD timeLoadBlackScene)
{
	this->sceneWidthEachMap = sceneWidthEachMap;
	this->timeLoadBlackScene = timeLoadBlackScene;
	this->stage = stage;
	if (loadBlackScene == 1)
		isLoadBlackScene = true;
	else
		isLoadBlackScene = false;
	isCanLoadScene = false;
	simonStartX = 0;
	simonStartY = 0;
	hasSetRenderOpenDoor = false;

}

void Scene::LoadSceneResource(int mapId, LPCSTR senceGameObjects)
{
	this->mapId = mapId;
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

	TiXmlDocument mapObjects(senceGameObjects);
	if (!mapObjects.LoadFile())
	{
		DebugOut(L"Can't read XML file: %s", senceGameObjects);
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
		Objects->QueryFloatAttribute("width", &Width);
		Objects->QueryFloatAttribute("height", &Height);
		for (Object = Objects->FirstChildElement(); Object != NULL; Object = Object->NextSiblingElement())
		{
			Object->QueryFloatAttribute("x", &x);
			Object->QueryFloatAttribute("y", &y);
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
			else if (id == 100) {
				CHiddenWall* hiddenWall = new CHiddenWall();
				hiddenWall->SetPosition(x, y);
				hiddenWall->SetWidthHeight(Width, Height);
				objects.push_back(hiddenWall);
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
				int enemyId, quantityEachSpawn, timeEachSpawn, spawnerId, delaySpawnTime;
				Object->QueryIntAttribute("enemyId", &enemyId);
				Object->QueryIntAttribute("spawnerId", &spawnerId);
				Object->QueryIntAttribute("quantityEachSpawn", &quantityEachSpawn);
				Object->QueryIntAttribute("timeEachSpawn", &timeEachSpawn);
				Object->QueryIntAttribute("delaySpawnTime", &delaySpawnTime);

				CSpawn* spawn = new CSpawn();
				spawn->SetPosition(x, y);
				spawn->SetWidthHeight(Width, Height);
				spawn->SetSpawnEnemyType(enemyId);
				spawn->SetSpawnerId(spawnerId);
				spawn->SetQuantitySpawnEnemy(quantityEachSpawn);
				spawn->SetTimeEachSpawn(timeEachSpawn);
				spawn->SetDelaySpawnTime(delaySpawnTime);

				objects.push_back(spawn);
			}
			else if (id == -99)
			{
				CDestroy* detroy = new CDestroy();
				int type;
				Object->QueryIntAttribute("type", &type);
				if (type == 1)
					detroy->SetType(RIGHT);
				else
					detroy->SetType(LEFT);
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
	if (now - lastTimeEachStage >= 1000)
	{
		lastTimeEachStage = GetTickCount();
		int time = boardGame->getLimitTime();
		boardGame->setLimitTime(--time);
	}
	for (int i = 0; i < letters.size(); i++)
	{
		int n;
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

void Scene::UpdateEnemies(DWORD dt)
{
	CSpawner* spawner = CSpawner::GetInstance();
	float cx, cy;
	float sx, sy;
	cx = CGame::GetInstance()->GetCamPos_x();
	cy = CGame::GetInstance()->GetCamPos_y();
	CSimon::getInstance()->GetPosition(sx, sy);

	int lastNx = 1;
	DWORD now = GetTickCount();
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
			if (spawner->enemyId != PANTHER_ID)
			{
				spawner->canSpawn = true;
			}
		}
	}

	if (spawner->quantitySpawned < spawner->quantityEachSpawn 
		&& spawner->canSpawn)
	{
		DebugOut(L"\nnow %d", now);
		DebugOut(L"\nspawner->lastSpawnTime %d", spawner->lastSpawnTime);

		if (now - spawner->lastSpawnTime > spawner->timeEachSpawn)
		{
			if (spawner->enemyId == GHOST_ID)
			{
				CGhost* ghost = new CGhost(cx, sy);
				spawner->quantitySpawned += 1;
				objects.push_back(ghost);

			}
			else if (spawner->enemyId == PANTHER_ID)
			{
				CPanther* panther = new CPanther(350, 100);
				spawner->quantitySpawned += 1;
				objects.push_back(panther);
			}
			else if (spawner->enemyId == BAT_ID)
			{
				CBat* bat = new CBat(cx, sy);
				spawner->quantitySpawned += 1;
				objects.push_back(bat);
			}
			spawner->lastSpawnTime = GetTickCount();
		}
	}
}

void Scene::Update(DWORD dt)
{
	CGame*game = CGame::GetInstance();
	CSimon*simon = CSimon::getInstance();
	CAnimations *animations = CAnimations::GetInstance();

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
				if (dynamic_cast<ChangeSceneObjects*>(objects[i]))
				{
					objects[i]->Update(dt);
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
			vector<LPGAMEOBJECT> coWeaponObjects;
			vector<LPGAMEOBJECT> coItemObjects;
			vector<LPGAMEOBJECT> coChangeScence;
			vector<LPGAMEOBJECT> coSpawn;
			vector<LPGAMEOBJECT> coDestroy;
			UpdateBoardGame(dt);
			UpdateEnemies(dt); // luôn gọi trước khi update các thứ khác

			//lấy objects để tính colisions
			for (int i = 0; i < objects.size(); i++)
			{
				if (dynamic_cast<CSimon*> (objects[i]))
				{
					coChangeScence.push_back(objects[i]);
					coSpawn.push_back(objects[i]);
				}
				if (dynamic_cast<CGround*> (objects[i]))
				{
					coEnemies.push_back(objects[i]);
				}
				if (dynamic_cast<CGround*> (objects[i]) 
					|| (dynamic_cast<CSimon*> (objects[i]))
					)
				{
					coItemObjects.push_back(objects[i]);
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
				if (simon->getUntouchable())
				{
					if (dynamic_cast<CGround*> (objects[i]))
					{
						coObjects.push_back(objects[i]);
					}
				}
				else
				{
					if (!dynamic_cast<CItems*>(objects[i]) 
						&& !dynamic_cast<CStaticObject*> (objects[i]) 
						&& !dynamic_cast<CSpawn*> (objects[i])
						)
					{
						coObjects.push_back(objects[i]);
					}
				}
				if (objects[i]->GetHealth() <= 0)
				{
					if (objects[i]->GetKillBySimon())
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
						objects.erase(objects.begin() + i);
					}
					else
					{
						if (dynamic_cast<CEnemies*> (objects[i]))
						{
							CSpawner::GetInstance()->quantityEnemyDied++;
						}
						objects.erase(objects.begin() + i);
					}
					
				}
			}


			//Gọi update với colision tính được
			simon->UpdateSimonWeapon(dt, &coWeaponObjects);

			for (int i = 0; i < objects.size(); i++)
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
				else {
					objects[i]->Update(dt, &coObjects);
				}
			}



			for (int i = 0; i < effects.size(); i++)
			{
				if (effects[i]->GetLastFrame())
				{
					float x, y;
					effects[i]->GetPosition(x, y);
					if (effects[i]->GetKillBySimon())
					{
						if (effects[i]->GetMakeItem() == STATIC_OBJECT)
						{

							int rand = Random(1, 10);
							animations->Get(ANI_HIT)->reset();
							/*if (rand == 1)
							{
								LargeHeart* largeHeart = new LargeHeart(x, y);
								listItems.push_back(largeHeart);
							}*/
							/*if ( CSimon::getInstance()->getWeaponLevel() < 3)
							{
								WhipUpgrade* whipUpgrade = new WhipUpgrade(x, y);
								listItems.push_back(whipUpgrade);
							}
							else*/ 
						/*	if ( CSimon::getInstance()->getSubWeapon() != SIMON_WEAPON::DANGER)
							{
								Danger* danger = new Danger(x, y);
								listItems.push_back(danger);
							}*/
						/*	if (rand >=2  && rand <= 8)
							{
								Axe* axe = new Axe(x, y);
								listItems.push_back(axe);
							}*/
							if (rand >=2  && rand <= 8)
							{
								HolyWater* holyWater = new HolyWater(x, y);
								listItems.push_back(holyWater);
							}
						/*	else if (rand >= 2 && rand <= 8)
							{
								StopWatch* stopWatch = new StopWatch(x, y);
								listItems.push_back(stopWatch);
							}*/
							/*else if (rand >= 2 && rand <= 8)
							{
								MoneyBag* moneyBag = new MoneyBag(x, y);
								listItems.push_back(moneyBag);
							}*/
							/*else if (rand >= 2 && rand <= 8)
							{
								SmallHeart* smallHeart = new SmallHeart(x, y);
								listItems.push_back(smallHeart);
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
							animations->Get(ANI_HIT)->reset();
							if (rand == 1)
							{
								LargeHeart* largeHeart = new LargeHeart(x, y);
								listItems.push_back(largeHeart);
							}
							if (rand == 99)
							{
								SmallHeart* smallHeart = new SmallHeart(x, y);
								listItems.push_back(smallHeart);
							}
						}
					}
					animations->Get(ANI_HIT)->reset();
					effects.erase(effects.begin() + i);
				}
			}

			for (int i = 0; i < listItems.size(); i++)
			{
				if (listItems[i]->GetHealth() > 0)
					listItems[i]->Update(dt, &coItemObjects);
				else
					listItems.erase(listItems.begin() + i);
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
			simon->Render();
			for (int i = 0; i < objects.size(); i++)
			{
				if (dynamic_cast<ChangeSceneObjects*> (objects[i]))
				{
					objects[i]->Render();
				}
			}
		}
		else
		{
			if (simon->getFreeze() == true)
			{
				for (int i = 0; i < objects.size(); i++)
				{
					if (dynamic_cast<CSimon*> (objects[i]) == false)
					{
						objects[i]->RenderCurrentFrame();
					}
					else
						objects[i]->Render();
				}
				for (int i = 0; i < effects.size(); i++)
					effects[i]->RenderCurrentFrame();
				for (int i = 0; i < listItems.size(); i++)
					listItems[i]->RenderCurrentFrame();
			}
			else
			{
				for (int i = 0; i < objects.size(); i++)
					objects[i]->Render();
				for (int i = 0; i < effects.size(); i++)
					effects[i]->Render();
				for (int i = 0; i < listItems.size(); i++)
					listItems[i]->Render();
			}
		}

	}

}

void Scene::StartLoadScene()
{
	scenceWidth = this->sceneWidthEachMap;
	this->timeStartLoadScene = GetTickCount();
	isCanLoadScene = false;
	CSimon::getInstance()->SetPosition(simonStartX, simonStartY);
	lastTimeEachStage = GetTickCount();
}