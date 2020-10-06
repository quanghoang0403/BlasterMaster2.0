#pragma once
#include "Entity.h"
#include "HealthBar.h"
#include "Player.h"

using namespace std;

//#define MAX_TEXTLENGHT_SCORE					6
//#define MAX_TEXTLENGHT_REMAININGTIME			4
//#define MAX_TEXTLENGHT_STAGE					2
//#define MAX_TEXTLENGHT_MANA						2
//#define MAX_TEXTLENGHT_LIVE						2

class HUD 
{
	float posX, posY;

	LPANIMATION_SET UIanimationSet;

	HealthBar* playerHB;
	HealthBar* gunHB;
	LPSPRITE UIExtraShot;
	LPANIMATION_SET playerSubWeaponAnimationSet;
public:
	HUD(int initPlayerHealth = 16, int initGunHealth = 16);
	~HUD();

	void Update(float posX, float posY, int currentPlayerHealth, int currentGunHealth);
	void Render(Player* playerInfo);
};

