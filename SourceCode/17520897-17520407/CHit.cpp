#include "CHit.h"

CHit::CHit()
{
	this->AddAnimation(ANI_HIT);
}

void CHit::Render() {
	animations[0]->Render(x, y);
}