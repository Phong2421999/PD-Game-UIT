#pragma once
#include "IntroGate.h"
#include "FrameWork/debug.h"
#include "Scenes.h"

void IntroGate::Render()
{
	//animations[0]->Render(x, y);
	RenderBoundingBox(x, y);
}

void IntroGate::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x; //0
	top = y; // 50
	right = x + width; //700
	bottom = y + height; // 58

	//r - l =700 b-t = 7= 8;
}

void IntroGate::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CSimon *simon = CSimon::getInstance();
	if (this->checkAABBTouch(simon)) {
		simon->setAutoGo(false);
		simon->SetSpeed(0, 0);
		simon->setAutoGoDistance(0);
		simon->SetState(SIMON_STATE_INTO_GATE);
		if (isTouchSimon)
		{
			DWORD now = GetTickCount();
			if (now - timeTocuhSimon >= 3500)
			{
				Scenes::GetInstance()->NextScenes();
				CGame::GetInstance()->SetStartGame(true);
			}
		}
		else
		{
			isTouchSimon = true;
			timeTocuhSimon = GetTickCount();
		}
	}
}
