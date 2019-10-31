#include "ChangeSceneObjects.h"

void ChangeSceneObjects::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CSimon*> (coObjects->at(i)))
		{
			if (this->checkAABBTouch(coObjects->at(i)))
			{
				simon->setSceneId(this->sceneId);
				if (simonAutoGo)
				{
					simon->setAutoGo(true);
					simon->setAutoGoDistance(this->simonAutoGoDistance);
				}
				if (camAutoGo)
				{
					CGame::GetInstance()->SetCamAutoGo(true);
				}
			}
		}
	}
	if (animations[0]->getLastFrame())
	{
		DebugOut(L"\nLast frame");
	}
	if (isDoor)
	{
		if (CGame::GetInstance()->GetRenderDoorChangeScene() && isCanRender)
		{
			if (animations[0]->getLastFrame())
			{
				DebugOut(L"\nLastFrame");
				simon->setCanAutoGo(true);
				this->isCanRender = false;
			}
		}
	}
}

void ChangeSceneObjects::Render()
{

	if (isDoor)
	{
		if (CGame::GetInstance()->GetRenderDoorChangeScene() && isCanRender)
		{
			animations[0]->Render(x, y);
		}
		else
		{
			animations[0]->RenderCurrentFrame(x, y);
		}
	}
	RenderBoundingBox(x, y);

}