#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "CKeyEventHandler.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#define KEYBOARD_BUFFER_SIZE 1024
#define CAM_AUTO_GO_SPEED 0.07f
class CGame
{
	static CGame * __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;		// Sprite helper library to help us draw 2D image on the screen 
	D3DXIMAGE_INFO info;

	float cam_x = 0.0f;
	float cam_y = 0.0f;

	bool isCamAutoGo;
	float camAutoGoDistance;

	bool isRenderOpenDoor;
	bool isRenderCloseDoor;
	bool isStopCamAutoGo;
	
	bool isGameStart;
	bool isStartIntro;
public:
	void Init(HWND hWnd);
	void InitKeyboard(LPKEYEVENTHANDLER handler);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);


	//Set
	void SetStartIntro(bool b)
	{
		this->isStartIntro = b;
	}
	void SetStartGame(bool b)
	{
		this->isGameStart = b;
	}
	void SetCamAutoGo(bool b)
	{
		this->isCamAutoGo = b;
	}
	void SetCamAutoGoDistance(float dis)
	{
		this->camAutoGoDistance = dis;
	}
	void SetRenderOpenDoor(bool b)
	{
		this->isRenderOpenDoor = b;
	}
	void SetRenderCloseDoor(bool b)
	{
		this->isRenderCloseDoor = b;
	}
	void SetStopCamAutoGo(bool b)
	{
		this->isStopCamAutoGo = b;
	}
	//Get
	bool GetStartIntro()
	{
		return isStartIntro;
	}
	bool GetStartGame()
	{
		return isGameStart;
	}
	bool GetCamAutoGo()
	{
		return isCamAutoGo;
	}
	float GetCamAutoGoDistance()
	{
		return camAutoGoDistance;
	}
	bool GetRenderOpenDoor()
	{
		return isRenderOpenDoor;
	}
	bool GetRenderCloseDoor()
	{
		return isRenderCloseDoor;
	}
	//CamAutoGo
	void AutoGoCam(DWORD dt)
	{
		if (isStopCamAutoGo == false)
		{
			float dx = CAM_AUTO_GO_SPEED * dt;
			cam_x += floor(dx);
			camAutoGoDistance += floor(dx);
		}
	}

	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }


	static CGame * GetInstance();

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float &t,
		float &nx,
		float &ny);
	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	float GetCamPos_x() { return cam_x ;}
	float GetCamPos_y() { return cam_y ; }

	bool checkAABBTouch(float left, float top, float right, float bottom,
		float checkLeft, float checkTop, float checkRight, float Bottom);
	HWND GetHWnd()
	{
		return hWnd;
	}
	~CGame();
};