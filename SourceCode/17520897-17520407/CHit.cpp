#include "CHit.h"
#include "SoundController.h"
CHit::CHit()
{
	this->AddAnimation(ANI_HIT);
	SoundController::Play(HITEFFECT_SOUND_ID);
}

void CHit::Render() {
	animations[ANI_HIT_ID]->Render(x, y);
}