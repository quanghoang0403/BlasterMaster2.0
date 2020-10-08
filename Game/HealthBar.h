#pragma once
#include "Animations.h"

#include <vector>

#define HEALTH_TYPE_GUN_NULL			0
#define HEALTH_TYPE_GUN_UNIT			1
#define HEALTH_TYPE_PLAYER_NULL			2
#define HEALTH_TYPE_PLAYER_UNIT			3

#define HEALTH_SPACE_UNIT				8.2

class HealthBar
{
	float posX, posY;
	int currentOwnerHealth, maxOwnerHealth;
	std::vector<LPANIMATION_SET> health;
	bool isAllies;
public:
	HealthBar(int maxHealth, bool isAllies);
	~HealthBar();

	void Update(int currentHealth, float X, float Y);
	void Render();

	void SetPosition(float X, float Y) { posX = X; posY = Y; }
	float GetPosX() { return posX; }
	float GetPosY() { return posY; }
	void ReceivePos(float& x, float& y) { x = this->posX; y = this->posY; }
	void SetPosX(float X) { this->posX = X; }
	void SetPosY(float Y) { this->posY = Y; }
};

