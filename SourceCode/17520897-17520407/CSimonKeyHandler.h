#pragma once
#include "FrameWork/Game.h"
#include "Simon.h"
class CSimonKeyHandler : public CKeyEventHandler
{
private:
	CSimon* simon;
	CGame* game;
public:
	CSimonKeyHandler()
	{
		simon = CSimon::getInstance();
		game = CGame::GetInstance();
	}
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};



