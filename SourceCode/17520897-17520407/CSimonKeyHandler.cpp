#include "CSimonKeyHandler.h"

void CSimonKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (simon->getAutoGo() == false && game->GetCamAutoGo() == false)
	{
		switch (KeyCode)
		{
		case DIK_SPACE:
			if (simon->getCanJump()) // Sau 1 khoảng thời gian mới có thể nhảy
			{
				simon->SetState(SIMON_STATE_JUMP);
			}
			break;
		case DIK_ESCAPE: // reset
			simon->SetState(SIMON_STATE_IDLE);
			simon->SetPosition(30.0f, 0.0f);
			simon->SetSpeed(0, 0);
			simon->setSceneId(0);
			break;
		case DIK_F: //attack
			if (simon->getCanAttack()) // Sau 1 khoảng thời gian mới có thể đánh
				simon->SetState(SIMON_STATE_ATTACK);
			break;
		case DIK_DOWN:
			simon->SetState(SIMON_STATE_SIT);
			break;
		case DIK_F1:
			isRenderBBox = !isRenderBBox;
			break;
		case DIK_F2:
			simon->setUntouchable();
			break;
		case DIK_F3:
			simon->SetPosition(1500.0f, 32.0f);
			break;
		case DIK_F4:
			simon->SetPosition(600.0f, 32.0f);
			break;
		
		}
	}
}

void CSimonKeyHandler::OnKeyUp(int KeyCode)
{
	if (simon->getAutoGo() == false && game->GetCamAutoGo() == false)
	{
		if (KeyCode == DIK_DOWN)
		{
			simon->setResetSitAffterAttack(true);
		}
		DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	}
}

void CSimonKeyHandler::KeyState(BYTE *states)
{
	// disable control key when Mario die
	if (simon->getAutoGo() == false && game->GetCamAutoGo() == false)
	{

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
		else if (game->IsKeyDown(DIK_UP))
		{
			if (simon->getHasSubWeapon()
				&& simon->getEnoughHeart())
			{
				if (game->IsKeyDown(DIK_F) && simon->getAttack() == false)
				{
					simon->setUseSubWeapon(true);
				}
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
		else if (game->IsKeyDown(DIK_DOWN))
			simon->SetState(SIMON_STATE_SIT);
		else if (simon->GetState() != SIMON_STATE_SIT
			&& simon->GetState() != SIMON_STATE_JUMP
			&& simon->GetState() != SIMON_STATE_ATTACK)
			simon->SetState(SIMON_STATE_IDLE);
	}

}
