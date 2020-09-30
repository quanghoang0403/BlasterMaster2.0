#pragma once
#include "Bullet.h"
#include <math.h>

#define BULLET_SPEED					0.25f
#define SMALL_BULLET_BBOX_WIDTH			8
#define SMALL_BULLET_BBOX_HEIGHT		6

#define SMALL_BULLET_JASON_ANI_RIGHT	0
#define SMALL_BULLET_JASON_ANI_TOP		1
#define SMALL_BULLET_JASON_BANG_ANI		2

#define ANIMATION_SET_SMALL_JASON_BULLET		4

class SmallJasonBullet : public Bullet
{
public:
	SmallJasonBullet();
	~SmallJasonBullet();


	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEENTITY>* colliable_objects = NULL);
	void Render();
};

