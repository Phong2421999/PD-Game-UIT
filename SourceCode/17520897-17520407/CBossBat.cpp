#include "CBossBat.h"
#include "Simon.h"

CBossBat::CBossBat()
{
	this->AddAnimation(ANI_BOSS_BAT_IDLE);
	this->AddAnimation(ANI_BOSS_BAT_FLY);
	this->width = BOSS_BAT_WIDTH;
	this->height = BOSS_BAT_HEIGHT;

	x = y = 0;

	yLastFrame = y;

	ani = ANI_ID_BOSS_BAT_IDLE;

	status = 0;
	vx = vy = 0;

	isUsingCurve = false;
	isWaiting = false;
	isBossActive = false;
	isActive = true;

	health = 16;

	startSpawnTime = GetTickCount();

	weapon = nullptr;

	bounderLeft = 0;
	bounderRight = 0;
	isBoss = false;
}

void CBossBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	if (weapon)
	{
		if (weapon->GetHealth() <= 0)
		{
			delete weapon;
			weapon = NULL;
		}
		else
			weapon->Update(dt);
	}
	DWORD now = GetTickCount();
	//if (now - startSpawnTime >= BOSS_BAT_ACTIVE_TIME && isBossActive == false)
	//{
	//	isBossActive = true;
	//	Start(); // boss chuyển trạng thái
	//}
	CSimon::getInstance()->GetPosition(sx, sy);
	if (sx + SIMON_OFFSET_TO_BBOX_X + SIMON_BBOX_WIDTH >= x && isBossActive == false)
	{
		Start(); // boss chuyển trạng thái
		isBossActive = true;
		if (isBoss)
		{
			lockCameraX = SCENCE_WITDH - SCREEN_WIDTH;
			isLockCamX = true;
		}
	}
	if (isBossActive && isBoss)
	{
		bossHealth = this->health;
		CSpawner::GetInstance()->canRespawn = false;
		CSpawner::GetInstance()->canSpawn = false;
		CSpawner::GetInstance()->isActive = false;
	}
	float cx, cy;
	cx = CGame::GetInstance()->GetCamPos_x();
	cy = CGame::GetInstance()->GetCamPos_y();

	x += dx;
	y += dy;
	switch (status)
	{
	case BOSS_FLY_START_1:
	{
		if (y >= yTarget)
		{
			status = BOSS_FLY_START_2; // qua trạng thái bay khởi động 2

			vy = 0; // khi đi tới được yTarget thì ngưng bay xuống 

			/*	--
				-------- Tính toán vị trí tiếp theo để bay
			*/
			xBefore = x; // lưu lại ví trí đã di chuyển
			yBefore = y;

			xTarget = x + 40;

			float dTarget = xTarget - xBefore; // Quãng đường từ vị trí hiện tại tới target
			vx = (dTarget / (1000.0f)); // Vận tốc cần để đi đến target trong 1.0s

			vy = 0.12f; // tạo độ cong
		}
		break;
	}
	case BOSS_FLY_START_2:
	{
		if (isWaiting == false)
		{
			// tạo độ cong
			vy -= 0.0001f * dt;


			if (vy < 0)
				vy = 0;

			if (x >= xTarget)
			{
				// di chuyển xong đến ví trí 2
				// cho ngừng bay
				vx = 0;
				vy = 0;


				isWaiting = true; // bật trạng thái chờ
				TimeWaited = GetTickCount();
			}
		}
		else
		{
			//TimeWaited += dt; // lấy thời gian của game
			if (now - TimeWaited >= 1000) // đợi theo thời gian của game
			{

				DebugOut(L"\n Waited Done!");
				isWaiting = false; // ngừng chờ

				StartCurves(); // bay cong 
			}
		}
		break;
	}
	case BOSS_FLY_CURVE:
	{
		/*	--
			-------- Kiểm tra nếu đi đến target thì ngừng bay
			-------- abs(x - xBefore) : quãng đường của boss đã đi được
			-------- abs(xTarget - xBefore) : quãng đường đi đến target
		*/
		float ya = Curve(y1, y2);

		float yb = Curve(y2, y3);

		float yc = Curve(ya, yb);

		vy = (yc - yLastFrame/*Khoảng cách y của frame trước và y dự tính đi*/) / 100; // curve mỗi 100ms
		if (abs(x - xBefore) >= abs(xTarget - xBefore))
		{
			vx = 0;
			vy = 0;
			isUsingCurve = false;

			StartStaight(); // Bắt đầu đi thẳng
			break;
		}

		break;
	}
	case BOSS_FLY_STRAIGHT_1:
	{
		/*	--
			-------- Kiểm tra nếu đi đến target thì ngừng bay
			-------- abs(x - xBefore) : quãng đường của boss đã đi được
			-------- abs(xTarget - xBefore) : quãng đường đi đến target
		*/
		if (abs(x - xBefore) >= abs(xTarget - xBefore) ||
			abs(y - yBefore) >= abs(yTarget - yBefore))
		{
			vx = vy = 0;

			StartStaight();

		}
		break;
	}
	case BOSS_FLY_STRAIGHT_2:
	{
		if (isWaiting == false) //Không trong trạng thái chờ
		{
			/*	--
				-------- Kiểm tra nếu đi đến target thì ngừng bay
				-------- abs(x - xBefore) : quãng đường của boss đã đi được
				-------- abs(xTarget - xBefore) : quãng đường đi đến target
			*/
			if (abs(x - xBefore) >= abs(xTarget - xBefore) ||
				abs(y - yBefore) >= abs(yTarget - yBefore))
			{
				vx = vy = 0;

				isWaiting = true; // bật trạng thái chờ
				TimeWaited = GetTickCount(); // reset lại time đã chờ
			}
		}
		else
		{
			if (now - TimeWaited >= 1000) // đợi theo thời gian của game
			{
				isWaiting = false;
				int random = rand() % 3;
				switch (random)
				{
				case 0: //	33 %
					isBossAttack = false;
					StartAttack();
					break;

				default: // 66%
					StartCurves();
					break;
				}
			}

		}


		break;
	}
	case BOSS_ATTACK:
	{
		if (isBossAttack)
		{
			this->makeWeapon = false;
			StartStaight();
		}
		break;
	}
	}


	if (x < cx
		|| cx + SCREEN_WIDTH < x + BOSS_BAT_WIDTH //Width cua bosss
		|| y > SCREEN_HEIGHT
		) // ra khỏi cam thì xử lí hướng tiếp theo
	{
		switch (status)
		{
		case BOSS_FLY_CURVE:
		{
			isUsingCurve = false;
			StartStaight();
			break;
		}

		case BOSS_FLY_STRAIGHT_1:
		{
			StartStaight();
			break;
		}

		case BOSS_FLY_STRAIGHT_2:
		{
			int random = rand() % 3;
			switch (random)
			{
			case 0: //	33 %
				isBossAttack = false;
				StartAttack();
				break;

			default: // 66%
				StartCurves();
				break;
			}

			break;
		}
		}
	}

	CSimon* simon = CSimon::getInstance();
	if (this->checkAABBTouch(simon) && simon->getUntouchable() == false)
	{
		if (simon->getDeath() == false)
		{
			simon->TouchEnemy(-simon->nx);
			simon->Damage(1);
		}
	}
	yLastFrame = y;// lưu lại y frame hiện tại
}


void CBossBat::Start()
{
	status = BOSS_FLY_START_1; //Bắt đầu bay khởi động lần 1
	ani = ANI_ID_BOSS_BAT_FLY;
	vy = 0.05f;
	vx = 0.0f;
	yBefore = y;
	yTarget = y + 20; //Lúc đầu đi xuống 20px
}

void CBossBat::StartCurves()
{
	DebugOut(L"\n Curves!");

	xBefore = x;
	yBefore = y;

	x1 = x;
	y1 = y;

	x2 = sx;
	y2 = sy + 8;

	if (sx < x) // simon bên trái boss
		//xTarget = rand() % (SCREEN_WIDTH / 5) + (int)sx;
		xTarget = CGame::GetInstance()->GetCamPos_x();
	else // simon bên phải boss
		//xTarget = rand() % (int)sx + ((int)sx - (SCREEN_WIDTH / 5));
		xTarget = CGame::GetInstance()->GetCamPos_x() + BOUNDER_OFFSET;

	yTarget = sy - RandomNumber(8, 16);

	x3 = xTarget;
	y3 = yTarget;

	float disNeedToGo = xTarget - xBefore; // quãng đường cần bay
	float directBossToTarget = x - xTarget; // tính hướng bay của boss
	vx = (directBossToTarget / (abs(disNeedToGo) *1000.0f / 100)) * -1; // vận tốc cần đi đên target // quy ước: cứ 1 giây đi 120px

	isUsingCurve = true;
	status = BOSS_FLY_CURVE;
}

void CBossBat::StartStaight()
{
	DebugOut(L"\n Staight!");

	switch (status)
	{
	case BOSS_FLY_STRAIGHT_1:
		status = BOSS_FLY_STRAIGHT_2;
		break;
	default:
		status = BOSS_FLY_STRAIGHT_1;
		break;
	}

	/*	--
	-------- Random vị trí đi tiếp theo
	*/
	xBefore = x;
	yBefore = y;


	xTarget = RandomNumber(CGame::GetInstance()->GetCamPos_x(), CGame::GetInstance()->GetCamPos_x() + BOUNDER_OFFSET);
	yTarget = RandomNumber(BOSS_BAT_MIN_FLY_Y, BOSS_BAT_MAX_FLY_Y);

	/*	--
	-------- Tính vx, vy di chuyển đến target trong 1 giây
	*/
	vx = (xTarget - xBefore) / (1000);
	vy = (yTarget - yBefore) / (1000);
}

void CBossBat::StartAttack()
{
	if (isBossAttack == false && this->makeWeapon == false)
	{
		vx = vy = 0;
		status = BOSS_ATTACK;
		isBossAttack = true;
		if (y > SCREEN_HEIGHT / 3)
		{
			float sx, sy;
			int weaponNx;
			CSimon::getInstance()->GetPosition(sx, sy);
			if (sx < x)
				weaponNx = -1;
			else
				weaponNx = 1;
			this->makeWeapon = true;
			weapon = new WeaponProjectile(x, y, weaponNx);
			if (weaponNx > 0)
				weapon->SetPositionWithEnemey(BOSS_BAT_WIDTH);
			else
				weapon->SetPositionWithEnemey(BOSS_BAT_WIDTH - 4);
		}
		if (sx - x > 0)
			nx = 1;
		else
			nx = -1;
	}

}

float CBossBat::Curve(float y1, float y2)
{
	/*	--
	-------- Phần trăm quãng đường đã đi được của boss tương ứng như t của Bézier curve
	*/
	float percHasGone = abs((x - xBefore) / (xTarget - xBefore));


	/*	--
	-------- Phần trăm quãng đường đi được chỉ trong khoảng 0 < percHasGone < 1 (0% -> 100%)
	*/
	if (percHasGone < 1)
	{
		percHasGone = percHasGone - (percHasGone / 100);

		float driff = y2 - y1;

		return y1 + (driff * percHasGone);
	}
}

int CBossBat::RandomNumber(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

void CBossBat::Render() {
	animations[ani]->Render(x, y);
	RenderBoundingBox(x, y);
	if (weapon)
		weapon->Render();
}

void CBossBat::RenderCurrentFrame()
{
	animations[ani]->RenderCurrentFrame(x, y);
	if (weapon)
		weapon->RenderCurrentFrame();
}

bool CBossBat::IsTouchSimon(LPGAMEOBJECT gameObject) {

	if (checkAABBTouch(gameObject))
		return true;

	LPCOLLISIONEVENT collitionEvent = this->SweptAABBEx(gameObject);
	if (collitionEvent->t >= 0 && collitionEvent->t <= 1.0f)
		return true;

	return false;
}

void CBossBat::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}
