#include "HUD.h"

HUD::HUD(int initPlayerHB, int initGunHealth)
{
	UIanimationSet = CAnimationSets::GetInstance()->Get(ANIMATION_SET_PLAYERHP);

	playerHB = new HealthBar(initPlayerHB, true);
	gunHB = new HealthBar(initGunHealth, true);
}

HUD::~HUD() {}

void HUD::Update(float posX, float posY, int currentPlayerHealth, int currentGunHealth)
{
	this->posX = posX;
	this->posY = posY;

	playerHB->Update(currentPlayerHealth, posX - 140, posY);
	gunHB->Update(currentGunHealth, posX - 140, posY + 20);
}

void HUD::Render(Player* playerInfo)
{
	UIanimationSet->at(0)->Render(-1, posX, posY);
	UIanimationSet->at(2)->Render(-1, posX + 50, posY);//dong nay kh on roi`
	// ? sao kh co get animation set v
	/*this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_PLAYERHP));*/
	playerHB->Render();
	gunHB->Render();
}
