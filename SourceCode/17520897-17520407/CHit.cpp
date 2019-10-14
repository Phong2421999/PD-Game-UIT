#include "CHit.h"

CHit::CHit()
{
	this->AddAnimation(ANI_HIT);
}

void CHit::Render() {
	animations[ANI_HIT_ID]->Render(x, y);
}