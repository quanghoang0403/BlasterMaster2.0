#include "ThreeBullet.h"

ThreeBullet::ThreeBullet()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_THREE_BULLET));
	x = 0;
	y = 0;
	alpha = 0;
	isCollisionEnemies = 0;
	isDone = true;
	damage = 2;
	timeDelayed = 0;
	timeDelayMax = THREE_BULLET_DELAY;
	bullet_top = new MainJasonBullet();
	bullet_mid = new MainJasonBullet();
	bullet_bot = new MainJasonBullet();
	damage = 2;
}

ThreeBullet::~ThreeBullet() {}

void ThreeBullet::Update(DWORD dt, vector<LPGAMEENTITY>* colliable_objects)
{
	bullet_top->Update(dt, colliable_objects);
	bullet_mid->Update(dt, colliable_objects);
	bullet_bot->Update(dt, colliable_objects);
}

void ThreeBullet::Render()
{
	bullet_top->Render();
	bullet_mid->Render();
	bullet_bot->Render();
}

void ThreeBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

void ThreeBullet::FireThreeBullet(int direction, float posX, float posY)
{
	bullet_top->isThreeBullet = 1;
	bullet_mid->isThreeBullet = 2;
	bullet_bot->isThreeBullet = 3;
	bullet_top->Fire(1, direction, 0, posX, posY);
	bullet_mid->Fire(1, direction, 0, posX, posY);
	bullet_bot->Fire(1, direction, 0, posX, posY);
}