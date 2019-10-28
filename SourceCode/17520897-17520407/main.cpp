#include <windows.h>
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

#include "GameConst.h"

#include "tinyxml.h"

#include "CSimonKeyHandler.h"

#include "GameObjectLib.h"
#include "GameItemLib.h"
#include "GameEnemyLib.h"

#include "Scenes.h"




CGame *game;

CSimon *simon;
CAnimations * animations;

int sceneId;

CSimonKeyHandler * keyHandler;

Scenes* scenes;

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
	//Lấy các file để load textures
	ifstream fileTextures("TXT\\TexturesFile.txt", ios::in);
	int texId, quantity, R, G, B;
	string texFilePath;
	fileTextures >> quantity;
	for (int i = 0; i < quantity; i++)
	{
		fileTextures >> texId >> texFilePath >> R >> G >> B;
		textures->Add(texId, texFilePath.c_str(), D3DCOLOR_XRGB(R, G, B));
	}

	//Load tất cả map
	CMap * map = CMap::GetInstance();
	ifstream fileMap("TXT\\Map.txt", ios::in);
	int mapId, texMapId;
	string mapPath, tileMapPath;
	fileMap >> quantity;
	for (int i = 0; i < quantity; i++)
	{
		fileMap >> mapId >> mapPath >> texMapId >> tileMapPath >> R >> G >> B;
		map->Add(mapId, mapPath.c_str(), texMapId, tileMapPath.c_str(), D3DCOLOR_XRGB(R, G, B));
	}

	//Load tất cả animations
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

	//Load tất cả scene - không đặt instance được vì trong scene có gọi singleton - Quản lý scene duy nhất ở đây
	scenes = new Scenes();
	fstream fileSence("TXT\\Scenes.txt", ios::in);
	fileSence >> quantity;
	int sceneId, sceneWidth, sceneMapId;
	string sceneGameObjectPath;
	for (int i = 0; i < quantity; i++)
	{
		fileSence >> sceneId >> sceneWidth >> sceneMapId >> sceneGameObjectPath;
		Scene* scene = new Scene(scenceWidth);
		scene->LoadSceneResource(sceneMapId, sceneGameObjectPath.c_str());
		scenes->Add(sceneId, scene);
		if (sceneId == 0) //Set vị trí ban đầu cho màn đi vào lâu đài
		{
			simon->SetPosition(SIMON_START_GAME_POSITION_X, SIMON_START_GAME_POSITION_Y);
		}
	}
}

void Update(DWORD dt)
{
	sceneId = simon->getCurrentScene();
	scenes->Get(sceneId)->Update(dt);
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

		scenes->Get(sceneId)->Render();

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