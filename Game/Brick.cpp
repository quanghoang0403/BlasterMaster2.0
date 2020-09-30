#include "Brick.h"
Brick::Brick()
{
	tag = EntityType::BRICK;
}

void Brick::Render()
{
	animationSet->at(0)->Render(-1, x, y);
	RenderBoundingBox();
}

void Brick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}