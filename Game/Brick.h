#pragma once
#include "Entity.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class Brick : public Entity
{
public:

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	Brick();
	~Brick();
};