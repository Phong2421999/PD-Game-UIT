#include "ChangeSceneObjects.h"

void ChangeSceneObjects::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (CGame::GetInstance()->GetCamAutoGo() == false)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CSimon*> (coObjects->at(i)))
			{
				CSimon* simon = dynamic_cast<CSimon*> (coObjects->at(i));
				if (simon->getState()!=SIMON_STATE_JUMP
					&& simon->getAttack() == false)
				{
					if (this->checkAABBTouch(coObjects->at(i)))
					{
						simon->setSceneId(this->sceneId);
						if (camAutoGo)
						{
							CGame::GetInstance()->SetCamAutoGo(true);
							simon->setAutoGoDistance(simonAutoGoDistance);
						}
						if (simonAutoGo)
						{
							simon->setAutoGo(true);
							simon->setAutoGoDistance(this->simonAutoGoDistance);
						}

					}
				}
			}
		}
	}
	if (isDoor)
	{
		if (CGame::GetInstance()->GetRenderOpenDoor())
		{
			CGame::GetInstance()->SetStopCamAutoGo(true);
			if (animations[aniId]->getNextIsLastFrame())
			{
				simon->setAutoGo(true);
				simon->setAutoGoDistance(this->simonAutoGoDistance);
				this->isCanRender = false;
				CGame::GetInstance()->SetRenderOpenDoor(false);
				animations[aniId]->reset();
				aniId = 1;
			}
		}
		if (CGame::GetInstance()->GetRenderCloseDoor())
		{
			CGame::GetInstance()->SetStopCamAutoGo(true);
			if (animations[aniId]->getNextIsLastFrame())
			{
				CGame::GetInstance()->SetStopCamAutoGo(false);
				CGame::GetInstance()->SetRenderCloseDoor(false);
				animations[aniId]->reset();
				aniId = 0;
				this->isCanRender = false;
			}
		}
	}
}

void ChangeSceneObjects::Render()
{

	if (isDoor)
	{
		if ((CGame::GetInstance()->GetRenderOpenDoor()||CGame::GetInstance()->GetRenderCloseDoor()))
		{
			animations[aniId]->Render(x, y);
		}
		else
		{
			animations[aniId]->RenderCurrentFrame(x, y);
		}

	}
	RenderBoundingBox(x, y);

}