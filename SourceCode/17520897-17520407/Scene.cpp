#include "Scene.h"

Scene::Scene(int sceneWidth, int loadBlackScene, DWORD timeLoadBlackScene)
{
	game = CGame::GetInstance();
	map = CMap::GetInstance();
	simon = CSimon::getInstance();
	animations = CAnimations::GetInstance();
	this->sceneWidth = sceneWidth;
	this->timeLoadBlackScene = timeLoadBlackScene;
	SCENCE_WITDH = scenceWidth;
	if (loadBlackScene == 1)
		isLoadBlackScene = true;
	else
		isLoadBlackScene = false;
	isCanLoadScene = false;
	simonStartX = 0;
	simonStartY = 0;
}

void Scene::LoadSceneResource(int mapId, LPCSTR senceGameObjects)
{
	this->mapId = mapId;
	map->Get(mapId)->LoadTile();
	ifstream inp(senceGameObjects, ios::in);
	float x, y;
	float  Width, Height;
	int Quantity, id;
	inp >> Quantity;
	for (int i = 0; i < Quantity; i++) {
		inp >> id >> x >> y >> Width >> Height;
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
		else if (id == -1)
		{
			int loadSceneId;
			inp >> loadSceneId;
			ChangeSceneObjects* changeScene = new ChangeSceneObjects();
			changeScene->SetPosition(x, y);
			changeScene->SetWidthHeight(Width, Height);
			changeScene->SetSceneId(loadSceneId);
			objects.push_back(changeScene);
		}
	}
	inp.close();

	objects.push_back(simon);
}

void Scene::Update(DWORD dt)
{
	if (isLoadBlackScene)
	{
		DWORD now = GetTickCount();
		if (now - timeStartLoadScene > timeLoadBlackScene)
			isCanLoadScene = true;
	}
	else
	{
		isCanLoadScene = true;
	}
	if (isCanLoadScene)
	{
		if (simon->getFreeze() == false)
		{
			vector<LPGAMEOBJECT> coObjects;
			vector<LPGAMEOBJECT> coWeaponObjects;
			vector<LPGAMEOBJECT> coItemObjects;
			vector<LPGAMEOBJECT> coChangeScence;

			//lấy objects để tính colisions
			for (int i = 0; i < objects.size(); i++)
			{
				if ((dynamic_cast<CSimon*> (objects[i])))
				{
					coChangeScence.push_back(objects[i]);
				}
				if (dynamic_cast<CGround*> (objects[i]) || (dynamic_cast<CSimon*> (objects[i])))
				{
					coItemObjects.push_back(objects[i]);
				}
				if (!dynamic_cast<CGround*> (objects[i])
					&& !dynamic_cast<CSimon*> (objects[i]))
				{
					coWeaponObjects.push_back(objects[i]);
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
					if (!dynamic_cast<CItems*>(objects[i]) && !dynamic_cast<CStaticObject*> (objects[i]))
						coObjects.push_back(objects[i]);
				}
				if (objects[i]->GetHealth() <= 0)
				{
					float x, y;
					objects[i]->GetPosition(x, y);
					CHit * hit = new CHit();
					hit->SetPosition(x, y);
					effects.push_back(hit);
					objects.erase(objects.begin() + i);
				}
			}


			//Gọi update với colision tính được

			for (int i = 0; i < objects.size(); i++)
			{
				if (dynamic_cast<CItems*> (objects[i]))
				{
					objects[i]->Update(dt, &coItemObjects);
				}
				else if (dynamic_cast<ChangeSceneObjects*> (objects[i]))
				{
					objects[i]->Update(dt, &coChangeScence);
				}
				else {
					objects[i]->Update(dt, &coObjects);
				}
			}


			simon->UpdateSimonWeapon(dt, &coWeaponObjects);


			for (int i = 0; i < effects.size(); i++)
			{
				if (effects[i]->GetLastFrame())
				{
					float x, y;
					effects[i]->GetPosition(x, y);
					animations->Get(ANI_HIT)->reset();

					if (x == 90)
					{
						SmallHeart* smallHeart = new SmallHeart();
						smallHeart->SetWidthHeight(SMALL_HEART_WIDTH, SMALL_HEART_HEIGHT);
						smallHeart->SetPosition(x, y);
						listItems.push_back(smallHeart);
					}
					else if (x == 340)
					{
						LargeHeart* largeHeart = new LargeHeart();
						largeHeart->SetWidthHeight(LARGE_HEART_WIDTH, LARGE_HEART_HEIGHT);
						largeHeart->SetPosition(x, y);
						listItems.push_back(largeHeart);
					}
					else if (x == 600)
					{
						Danger* danger = new Danger();
						danger->SetWidthHeight(DANGER_WIDTH, DANGER_HEIGHT);
						danger->SetPosition(x, y);
						listItems.push_back(danger);
					}
					else
					{
						WhipUpgrade* whipUpgrade = new WhipUpgrade();
						whipUpgrade->SetWidthHeight(WHIP_WIDTH, WHIP_HEIGHT);
						whipUpgrade->SetPosition(x, y);
						listItems.push_back(whipUpgrade);
					}

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

		cx -= SCREEN_WIDTH / 2;
		cy -= SCREEN_HEIGHT / 2;
		if (cx <= 0)
		{
			CGame::GetInstance()->SetCamPos(0.0f, 0.0f /*cy*/);
		}
		else if (cx >= SCENCE_WITDH - SCREEN_WIDTH)
		{
			CGame::GetInstance()->SetCamPos(SCENCE_WITDH - SCREEN_WIDTH, 0.0f /*cy*/);
		}
		else
		{
			CGame::GetInstance()->SetCamPos(cx, 0.0f);
		}

	}
	else
	{
		CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
	}

}

void Scene::Render()
{
	if (isCanLoadScene)
	{
		map->Get(mapId)->Render();
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

void Scene::StartLoadScene()
{
	this->timeStartLoadScene = GetTickCount();
	isCanLoadScene = false;
	simon->SetPosition(simonStartX, simonStartY);
}