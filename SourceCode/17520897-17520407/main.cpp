﻿#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include <string>
#include <iostream>

#include "FrameWork/GameObject.h"
#include "FrameWork/Textures.h"
#include "FrameWork/CAnimations.h"
#include "CMap.h"

#include "FrameWork/debug.h"
#include "FrameWork/Game.h"

#include "Simon.h"
#include "LargeCandle.h"
#include "CStaticObject.h"
#include "Ground.h"
#include "CTestEnemy.h"

#include "CHit.h"
#include "WhipUpgrade.h"
#include "LargeHeart.h"
#include "SmallHeart.h"
#include "Danger.h"

#include "GameConst.h"

#include "tinyxml.h"

#include "CSimonKeyHandler.h"



CGame *game;

CSimon *simon;
CGround* ground;
CMap * map = CMap::GetInstance();
CAnimations * animations;


CSimonKeyHandler * keyHandler;

vector<LPGAMEOBJECT> objects;
vector<LPITEMS> listItems;
vector<LPEFT> effects;


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_BBOX, "textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_OBJECTS, "textures\\ObjectsAndEffect.png", D3DCOLOR_XRGB(34, 177, 76));
	textures->Add(ID_TEX_ITEMS, "textures\\Items.png", D3DCOLOR_XRGB(128, 0, 0));
	textures->Add(ID_TEX_ENEMIES, "textures\\Enemies-Castle.png", D3DCOLOR_XRGB(96, 68, 106));
	textures->Add(ID_TEX_SIMON, "textures\\TexturesV3.png", D3DCOLOR_XRGB(34, 177, 76));

	map->Add(ID_MAP1, "Textures\\readfile_map_1.txt", ID_TEX_MAP1, "Textures\\tileset_map1.png", D3DCOLOR_XRGB(255, 0, 255));
	map->Get(ID_MAP1)->LoadTile();


	CSprites * sprites = CSprites::GetInstance();

	LPDIRECT3DTEXTURE9 directTexture;

	TiXmlDocument doc("XML/Textures.xml");

	if (!doc.LoadFile())
	{
		DebugOut(L"Can't read XML file");
		MessageBox(NULL, L"Can't Read XML File", L"Error", MB_OK);
		return;
	}
	else
	{
		DebugOut(L"[INFO]Read XML success\n");
	}
	// get info root
	TiXmlElement* root = doc.RootElement();
	TiXmlElement* sprite = nullptr;
	TiXmlElement* animation = nullptr;
	TiXmlElement* texture = nullptr;
	// gameObjectId = 0 -- Simon

	for (texture = root->FirstChildElement(); texture != NULL; texture = texture->NextSiblingElement())
	{
		int textureId;
		int gameObjectId;
		texture->QueryIntAttribute("textureId", &textureId);
		texture->QueryIntAttribute("gameObjectId", &gameObjectId);

		directTexture = textures->Get(textureId);
		for (animation = texture->FirstChildElement(); animation != NULL; animation = animation->NextSiblingElement())
		{
			int aniId, frameTime;
			animation->QueryIntAttribute("frameTime", &frameTime);
			LPANIMATION ani;
			ani = new CAnimation(frameTime);
			for (sprite = animation->FirstChildElement(); sprite != NULL; sprite = sprite->NextSiblingElement())
			{
				int left, top, right, bottom, id;
				sprite->QueryIntAttribute("id", &id);
				sprite->QueryIntAttribute("top", &top);
				sprite->QueryIntAttribute("left", &left);
				sprite->QueryIntAttribute("right", &right);
				sprite->QueryIntAttribute("bottom", &bottom);
				sprites->Add(id, left, top, right, bottom, directTexture);
				ani->Add(id);
			}
			animation->QueryIntAttribute("aniId", &aniId);
			animations->Add(aniId, ani);
			if (gameObjectId == 0)
			{
				simon->AddAnimation(aniId);
			}
		};
	}

	float x, y;
	float  Width, Height;
	int Quantity, id;

	ifstream inp("Textures\\readfile_map_1_gameobjects.txt", ios::in);
	inp >> Quantity;
	for (int i = 0; i < Quantity; i++) {
		inp >> id >> x >> y >> Width >> Height;
		if (id == 0)
		{
			ground = new CGround();
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
	
	}
	inp.close();


	simon->SetPosition(32.0f, 32.0f);
	objects.push_back(simon);
}

void Update(DWORD dt)
{
	if (simon->getFreeze() == false)
	{
		vector<LPGAMEOBJECT> coObjects;
		vector<LPGAMEOBJECT> coWeaponObjects;
		vector<LPGAMEOBJECT> coItemObjects;

		//lấy objects để tính colisions
		for (int i = 0; i < objects.size(); i++)
		{
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
		simon->UpdateSimonWeapon(dt, &coWeaponObjects);

		for (int i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<CItems*> (objects[i]))
			{
				objects[i]->Update(dt, &coItemObjects);
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
				animations->Get(ANI_HIT)->reset();
				if (x == 90 || x == 340)
				{
					if (x == 90)
					{
						SmallHeart* smallHeart = new SmallHeart();
						smallHeart->SetWidthHeight(SMALL_HEART_WIDTH, SMALL_HEART_HEIGHT);
						smallHeart->SetPosition(x, y);
						listItems.push_back(smallHeart);
					}
					else
					{
						LargeHeart* largeHeart = new LargeHeart();
						largeHeart->SetWidthHeight(LARGE_HEART_WIDTH, LARGE_HEART_HEIGHT);
						largeHeart->SetPosition(x, y);
						listItems.push_back(largeHeart);
					}
				}
				else
				{
					if (x == 600)
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
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->GetHealth() <= 0)
				objects.erase(objects.begin() + i);
		}
		for (int i = 0; i < listItems.size(); i++)
		{
			if (listItems[i]->GetHealth() <= 0)
				listItems.erase(listItems.begin() + i);
		}
		simon->UpdateFreeze(dt);
	}

}

void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		map->Get(ID_MAP1)->Render();

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

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			game->ProcessKeyboard();
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	simon = CSimon::getInstance();
	animations = CAnimations::GetInstance();

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSimonKeyHandler();
	game->InitKeyboard(keyHandler);


	LoadResources();
	DebugOut(L"[INFO] Init WinMain Success\n");
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}