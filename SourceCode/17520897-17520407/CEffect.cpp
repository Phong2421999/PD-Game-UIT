#pragma once
#include "CEffect.h"

void CEffect::Render()
{
	//animations[0]->Render(x, y);
	RenderBoundingBox(x,y);
}

bool CEffect::GetLastFrame() {
	return animations[0]->getLastFrame();
}

void CEffect::reset() {
	animations[0]->reset();
}