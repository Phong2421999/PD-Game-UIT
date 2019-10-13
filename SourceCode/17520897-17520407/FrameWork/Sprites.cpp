#include "Sprites.h"
#include "../FrameWork/debug.h"


void CSprite::Draw(float x, float y, int alpha)
{
	CGame * game = CGame::GetInstance();
	game->Draw(x,y, texture, left, top, right, bottom, alpha);
}

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
	spriteHandler = CGame::GetInstance()->GetSpriteHandler();
}


void CSprite::DrawFlipX(float x, float y, float offsetX, int alpha)
{
	spriteHandler = CGame::GetInstance()->GetSpriteHandler();
	float cam_x = CGame::GetInstance()->GetCamPos_x();
	float cam_y = CGame::GetInstance()->GetCamPos_y();
	D3DXVECTOR3 p(floor(x - cam_x), floor(y - cam_y), 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	D3DXMATRIX oldTransform, middleTransform;
	spriteHandler->GetTransform(&oldTransform);
	D3DXMatrixTransformation2D(&middleTransform, &D3DXVECTOR2(p.x + offsetX, p.x), 0.0f, &D3DXVECTOR2(-1.0f, 1.0f), NULL, 0.0f, NULL);
	D3DXMATRIX newTransform = oldTransform * middleTransform;
	spriteHandler->SetTransform(&newTransform);
	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
	spriteHandler->SetTransform(&oldTransform);
}
