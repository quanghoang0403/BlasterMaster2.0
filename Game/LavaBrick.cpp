#include "LavaBrick.h"

void LavaBrick::Render()
{
	RenderBoundingBox();
}

void LavaBrick::Update(DWORD dt, vector<LPGAMEENTITY>* objects)
{
}

void LavaBrick::Activation()
{
}

void LavaBrick::GetCenterBoundingBox(float& x, float& y)
{
}

float LavaBrick::GetDistance(D3DXVECTOR2 pos, D3DXVECTOR2 target)
{
	return 1;
}


bool LavaBrick::IsContain(RECT rect1, RECT rect2)
{
	return 0;
}

void LavaBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + frameW;
	b = y + frameH;
}

LavaBrick::LavaBrick()
{
	tag = EntityType::ENEMY;
	this->frameH = BRICK_BBOX_HEIGHT;
	this->frameW = BRICK_BBOX_WIDTH;
}