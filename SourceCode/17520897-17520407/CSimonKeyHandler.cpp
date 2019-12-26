#include "CSimonKeyHandler.h"
#include "Grid.h"
void CSimonKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (simon->getAutoGo() == false
		&& game->GetCamAutoGo() == false
		&& simon->getAutoGoToStair() == false
		&& simon->getAuToGoOutStair() == false
		&& simon->getHurt() == false)
	{
		switch (KeyCode)
		{
		case DIK_SPACE:
			if (simon->getOnStair() == false)
			{
				if (simon->getCanJump()
					&& simon->getLock() == false) // Sau 1 khoảng thời gian mới có thể nhảy
				{
					simon->SetState(SIMON_STATE_JUMP);
				}
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
			if (simon->getCanOnStair()
				&& simon->getStairActiveNy() < 0
				&& simon->getCanSetStair())
			{
				simon->setOnStair(true);
			}
			else if (simon->getOnStair() == false
				&& simon->getAuToGoOutStair() == false
				&& simon->getAutoGoToStair() == false)
				simon->SetState(SIMON_STATE_SIT);
			break;
		case DIK_F1:
			isRenderBBox = !isRenderBBox;
			break;
		case DIK_F2:
			simon->setHasSubWeapon(true);
			simon->ChangeSubWeapon(SIMON_WEAPON::DANGER);
			simon->setHeart(99);
			break;
		case DIK_F3:
			simon->setHasSubWeapon(true);
			simon->ChangeSubWeapon(SIMON_WEAPON::STOP_WATCH);
			simon->setHeart(99);
			break;
		case DIK_F4:
			simon->setHasSubWeapon(true);
			simon->setUsingCross(true);
			simon->setHeart(99);
			break;
		case DIK_F5:
			simon->setHasSubWeapon(true);
			simon->ChangeSubWeapon(SIMON_WEAPON::HOLY_WATER);
			simon->setHeart(99);
			break;
		case DIK_F6:
			simon->setHasSubWeapon(true);
			simon->setUsingDoubleShot(true);
			simon->setHeart(99);
			break;
		case DIK_F7:
			simon->SetPosition(SCENCE_WITDH - 96, 32.0f);
			simon->SetState(SIMON_STATE_IDLE);
			break;
		case DIK_1:
			float x, y;
			simon->GetPosition(x, y);
			DebugOut(L"\nSimonX: %f, SimonY: %f", x, y);
			break;
		case DIK_2:
			simon->SetHealth(1);
			break;
		case DIK_3:
			simon->SetHealth(9999999);
			break;
		case DIK_4:
			simon->SetPosition(32, 32);
		}
	}
}

void CSimonKeyHandler::OnKeyUp(int KeyCode)
{
	if (simon->getAutoGo() == false
		&& game->GetCamAutoGo() == false
		&& simon->getAutoGoToStair() == false
		&& simon->getAuToGoOutStair() == false
		&& simon->getHurt() == false)
	{
		if (KeyCode == DIK_DOWN)
		{
			if (simon->getSit())
				simon->setResetSitAffterAttack(true);
		}
		DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	}
}

void CSimonKeyHandler::KeyState(BYTE *states)
{
	// disable control key when Mario die
	if (simon->getAutoGo() == false
		&& game->GetCamAutoGo() == false
		&& simon->getAutoGoToStair() == false
		&& simon->getAuToGoOutStair() == false
		&& simon->getHurt() == false)
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
				if (simon->getOnStair()
					&& simon->getAuToGoOutStair() == false
					&& simon->getAutoGoToStair() == false)
				{
					if (simon->getCanOutStair()
						&& simon->ny > 0)
					{
						simon->y -= SIMON_PULL_UP_OUT_STAIR;
						simon->setAutoGoOutStair(true);
						simon->setAutoGoDistance(SIMON_AUTO_GO_STAIR_DISTANCE);

					}
					else
					{
						if (simon->getStairNx() == simon->getStairNy())
							simon->SetState(SIMON_STATE_ON_STAIR_UP);
						else
							simon->SetState(SIMON_STATE_ON_STAIR_DOWN);

					}
				}
				else
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
				if (simon->getOnStair()
					&& simon->getAuToGoOutStair() == false
					&& simon->getAutoGoToStair() == false)
				{

					if (simon->getCanOutStair()
						&& simon->ny > 0)
					{
						simon->y -= 9.0f;
						simon->setAutoGoOutStair(true);
						simon->setAutoGoDistance(12.0f);

					}
					else
					{
						if (simon->getStairNx() == simon->getStairNy())
							simon->SetState(SIMON_STATE_ON_STAIR_DOWN);
						else
							simon->SetState(SIMON_STATE_ON_STAIR_UP);
					}
				}
				else
					simon->SetState(SIMON_STATE_WALKING_LEFT);

			}
		else if (game->IsKeyDown(DIK_UP))
		{
			if (game->IsKeyDown(DIK_F) && simon->getAttack() == false)
			{
				if (simon->getHasSubWeapon()
					&& simon->getEnoughHeart())
				{

					simon->setUseSubWeapon(true);
				}
			}
			else
			{
				if (simon->getCanOnStair()
					&& simon->getOnGround()
					&& simon->getStairActiveNy() > 0
					&& simon->getCanSetStair())
				{

					simon->setOnStair(true);

				}

				if (simon->getOnStair()
					&& simon->getAuToGoOutStair() == false
					&& simon->getAutoGoToStair() == false)
				{
					if (simon->getCanOutStair()
						&& simon->ny > 0)
					{
						simon->y -= SIMON_PULL_UP_OUT_STAIR;
						simon->setAutoGoOutStair(true);
						simon->setAutoGoDistance(SIMON_AUTO_GO_STAIR_DISTANCE);

					}
					else
					{
						simon->SetState(SIMON_STATE_ON_STAIR_UP);
					}
				}
				else if (simon->getJump() == false
					&& simon->getSit() == false
					&& simon->getAttack() == false)
					simon->SetState(SIMON_STATE_IDLE);

			}
		}

		else if (game->IsKeyDown(DIK_DOWN))
		{
			if (simon->getCanOnStair()
				&& simon->getStairActiveNy() < 0
				&& simon->getCanSetStair()
				&& simon->getOnGround())
			{
				simon->setOnStair(true);
			}
			else if (simon->getOnStair()
				&& simon->getAuToGoOutStair() == false
				&& simon->getAutoGoToStair() == false)
			{
				simon->SetState(SIMON_STATE_ON_STAIR_DOWN);
			}
			else
			{
				simon->SetState(SIMON_STATE_SIT);
			}
		}

		else if (simon->GetState() != SIMON_STATE_SIT
			&& simon->GetState() != SIMON_STATE_JUMP
			&& simon->GetState() != SIMON_STATE_ATTACK)
		{
			if (simon->getOnStair())
			{
				if (simon->ny > 0)
					simon->SetState(SIMON_STATE_ON_STAIR_IDLE_UP);
				else
					simon->SetState(SIMON_STATE_ON_STAIR_IDLE_DOWN);
			}
			else
				simon->SetState(SIMON_STATE_IDLE);

		}
	}

}
