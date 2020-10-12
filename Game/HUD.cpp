#include "HUD.h"

HUD::HUD(int initPlayerHB, int initGunHealth)
{
	UIanimationSet = CAnimationSets::GetInstance()->Get(ANIMATION_SET_PLAYERHP);
	gunHB = new HealthBar(initGunHealth, true);
	playerHB = new HealthBar(initPlayerHB, false);
}

HUD::~HUD() {}

void HUD::Update(float posX, float posY, int currentPlayerHealth, int currentGunHealth)
{
	this->posX = posX;
	this->posY = posY;

	gunHB->Update(currentGunHealth, posX + 2, posY + 7.8); // Hard code -> Dieu chinh khoang cach cac unit mau cua Gun #LKP
	playerHB->Update(currentPlayerHealth, posX + 3, posY + 112.5); // Hard code -> Dieu chinh khoang cach cac unit mau cua Player #LKP
}

void HUD::Render(Player* playerInfo)
{
	UIanimationSet->at(HEALTH_TYPE_GUN_NULL)->Render(1, posX, posY + ARTICULAR_GUNPOWER_HEALTHBAR_Y);
	UIanimationSet->at(HEALTH_TYPE_PLAYER_NULL)->Render(1, posX, posY + ARTICULAR_PLAYER_HEALTHBAR_Y);
	gunHB->Render();
	playerHB->Render();
}