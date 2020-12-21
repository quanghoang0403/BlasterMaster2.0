#pragma once
#include "Bullet.h"
#include "MainJasonBullet.h"
#include <math.h>
#define ANIMATION_SET_THREE_BULLET		5	

#define ELECTRIC_BULLET_ANI_JASON			0

#define ELECTRIC_BULLET_JASON_BBOX_WIDTH	14
#define ELECTRIC_BULLET_JASON_BBOX_HEIGHT	16

#define THREE_BULLET_DELAY	700
class ThreeBullet : public Bullet
{
public:
	MainJasonBullet* bullet_top;
	MainJasonBullet* bullet_mid;
	MainJasonBullet* bullet_bot;
	ThreeBullet();
	~ThreeBullet();
	//void Fire(int direc, int isTargetTop, float x, float y) { x = x; y = y; };
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEENTITY>* colliable_objects = NULL);
	void Render();
	void FireThreeBullet(int direction, float posX, float posY);
};


