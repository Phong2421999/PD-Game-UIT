#include "PressStart.h"
#include "Simon.h"
#include "Scenes.h"

PressStart::PressStart() {
	this->AddAnimation(PRESSSTART_IDLE_ANI);
	this->AddAnimation(PRESSSTART_ANI);
	ani = 0;
}


void PressStart::Render() {
	animations[ani]->Render(x, y);
	RenderBoundingBox(x, y);
}


void PressStart::RenderCurrentFrame() {
	animations[ani]->RenderCurrentFrame(x, y);
}

void PressStart::GetBoundingBox(float &left, float &top, float &right, float &bottom) {

}

void PressStart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGame *game = CGame::GetInstance();
	if (game->GetPressStart())
	{
		ani = 1;
		if (animations[1]->getLastFrame())
		{
			CSimon *simon = CSimon::getInstance();
			simon->setSceneId(-1);
			Scenes::GetInstance()->NextScenes();
			Scenes::GetInstance()->Get(0)->StartLoadScene();
			simon->nx = -1;
			simon->setAutoGo(true);
			simon->setAutoGoDistance(150);
			game->SetStartIntro(true);
		}
	}
}