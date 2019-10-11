#pragma once
#include "CEffect.h"

void CEffect::Render()
{
	//animations[0]->Render(x, y);
	RenderBoundingBox();
}

bool CEffect::GetLastFrame() {
	return animations[0]->getLastFrame();
}