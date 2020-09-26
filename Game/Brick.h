#pragma once
#include "Entity.h"

#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32

class Brick : public Entity
{
public:

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};