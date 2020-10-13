#include "GunUp.h"

GunUp::GunUp(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEM_GUNUP));
	tag = EntityType::GUNUP;

	this->x = posX;
	this->y = posY;

	displayTimer = new Timer(GUN_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = GUN_DELAY;
}

GunUp::~GunUp() {}