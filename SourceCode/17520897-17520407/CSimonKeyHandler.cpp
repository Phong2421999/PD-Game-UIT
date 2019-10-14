#include "CSimonKeyHandler.h"

void CSimonKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
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
	}
}

void CSimonKeyHandler::OnKeyUp(int KeyCode)
{
	if (KeyCode == DIK_DOWN)
	{
		simon->ResetAfterSit();
		simon->SetState(SIMON_STATE_IDLE);
	}
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSimonKeyHandler::KeyState(BYTE *states)
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
	else if (game->IsKeyDown(DIK_UP))
	{
		if (simon->getHasSubWeapon()
			&& simon->getEnoughHeart()
			&& simon->getAttack() == false)
		{
			if (game->IsKeyDown(DIK_F) && simon->getSit() == false)
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
