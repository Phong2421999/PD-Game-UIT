#pragma once
#include<d3dx9.h>
#include "Sprites.h"
/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
	void Flip(float FlipX, float FlipY) {
		sprite->Flip(FlipX, FlipY);
	}
};

typedef CAnimationFrame *LPANIMATION_FRAME;
