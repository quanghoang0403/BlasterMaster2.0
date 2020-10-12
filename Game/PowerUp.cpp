#include "PowerUp.h"

PowerUp::PowerUp(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEM_POWERUP));
	tag = EntityType::POWERUP;

	this->posX = posX;
	this->posY = posY;

	displayTimer = new Timer(POWERUP_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = POWERUP_DELAY;
}

PowerUp::~PowerUp() {}