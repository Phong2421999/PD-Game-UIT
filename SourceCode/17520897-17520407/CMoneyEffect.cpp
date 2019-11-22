#pragma once
#include "CMoneyEffect.h"

CMoneyEffect::CMoneyEffect(float x, float y, GAME_ITEM moneyType)
{
	this->AddAnimation(ANI_RED_BAG_EFFECT);
	this->AddAnimation(ANI_PURPLE_BAG_EFFECT);
	this->AddAnimation(ANI_WHITE_BAG_EFFECT);

	this->x = x + 10;
	this->y = y - 10	;

	switch (moneyType)
	{
	case RED_MONEY_BAG:
		ani = ANI_RED_BAG_EFFECT_ID;
		break;
	case PURPLE_MONEY_BAG:
		ani = ANI_PURPLE_BAG_EFFECT_ID;
		break;
	case WHITE_MONEY_BAG:
		ani = ANI_WHITE_BAG_EFFECT_ID;
		break;
	}
}
bool CMoneyEffect::GetLastFrame() {
	return animations[ani]->getLastFrame();
}

void CMoneyEffect::Render() {
	animations[ani]->Render(x, y);
}

void CMoneyEffect::reset()
{
	animations[ani]->reset();
}