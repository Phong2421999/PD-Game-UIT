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
#include "Ground.h"

#include "GameConst.h"

#include "tinyxml.h"




CGame *game;

CSimon *simon;
CGround* ground;
CMap * map = CMap::GetInstance();

vector<LPGAMEOBJECT> objects;

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (simon->getCanJump())
		{
			simon->SetState(SIMON_STATE_JUMP);
		}	
		break;
	case DIK_ESCAPE: // reset
		simon->SetState(SIMON_STATE_IDLE);
		simon->SetPosition(30.0f, 0.0f);
		simon->SetSpeed(0, 0);
		break;
	case DIK_F: //attack
		if (simon->getJump())
		{

		}
		else if (simon->getJump())
		{

		}
		else
		{
			simon->SetState(SIMON_STATE_ATTACK);
		}
		break;
	case DIK_F1:
		isRenderBBox = !isRenderBBox;
		break;
	case DIK_DOWN:
			simon->SetState(SIMON_STATE_SIT);
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	if (KeyCode == DIK_DOWN)
	{
		simon->ResetAfterSit();
		simon->SetState(SIMON_STATE_IDLE);
	}
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	// disable control key when Mario die 
	if (simon->GetState() == SIMON_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (simon->getJump())
		{
			return;
		}
		else
		{
			simon->SetState(SIMON_STATE_WALKING_RIGHT);

		}
	}
	else if (game->IsKeyDown(DIK_LEFT))
		if (simon->getJump())
		{
			return;
		}
		else
		{
			simon->SetState(SIMON_STATE_WALKING_LEFT);

		}
	else if(game->IsKeyDown(DIK_DOWN))
		simon->SetState(SIMON_STATE_SIT);
	else if(simon->GetState() != SIMON_STATE_SIT 
		&& simon->GetState() != SIMON_STATE_JUMP 
		&& simon->GetState() != SIMON_STATE_ATTACK)
		simon->SetState(SIMON_STATE_IDLE);
}



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
	textures->Add(111111, "textures\\Level1.png", D3DCOLOR_XRGB(255, 255, 255));

	map->Add(ID_MAP_LEVEL1, "textures\\Level1.png", 111111);
	map->Get(ID_MAP_LEVEL1)->SetMapPosition(0, 24);
	map->Get(ID_MAP_LEVEL1)->LoadMap();

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

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
	simon = new CSimon();
	// gameObjectId = 0 -- Simon
	for (texture = root->FirstChildElement(); texture != NULL; texture = texture->NextSiblingElement())
	{
		int textureId;
		int gameObjectId;
		const char * textureFile;
		textureFile = texture->Attribute("textureFile");
		texture->QueryIntAttribute("textureId", &textureId);
		texture->QueryIntAttribute("gameObjectId", &gameObjectId);
		int R, G, B;
		texture->QueryIntAttribute("R", &R);
		texture->QueryIntAttribute("G", &G);
		texture->QueryIntAttribute("B", &B);
		textures->Add(textureId, textureFile, D3DCOLOR_XRGB(R, B, G));

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
				DebugOut(L"add ani\n");
			}
		};
	}
	
	

	ground = new CGround();
	ground->SetWidthHeigth(780, 8);
	ground->SetPosition(0.0f, 170.0f);


	simon->SetPosition(32.0f, 32.0f);

	ground->AddAnimation(562);

	objects.push_back(simon);
	objects.push_back(ground);

}


void Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
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

		map->Get(ID_MAP_LEVEL1)->Draw();

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

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

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();
	DebugOut(L"[INFO] Init WinMain Success\n");
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}