#include "WhipUpgrade.h"


WhipUpgrade::WhipUpgrade() {
	this->AddAnimation(ANI_WHIP_UPGRADE);
}

void WhipUpgrade::Render() {
	animations[0]->Render(x, y);
	RenderBoundingBox();
}

void WhipUpgrade::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}