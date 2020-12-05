#include "ElectricBullet.h"

ElectricBullet::ElectricBullet()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ELECTRIC_BULLET));
	x = 0;
	y = 0;
	alpha = 0;
	isCollisionBrick = 0;
	damage = 2;
	//timeDelayed = 0;
	//timeDelayMax = ELECTRIC_DELAY;
}

ElectricBullet::~ElectricBullet() {}

void ElectricBullet::Update(DWORD dt, vector<LPGAMEENTITY>* colliable_objects)
{
	if (isDone == true)
	{
		alpha = 0;
	}
	else
	{
		timeDelayed += dt;
		Entity::Update(dt);

#pragma region Xử lý va chạm
		for (UINT i = 0; i < colliable_objects->size(); i++)
		{
			if (colliable_objects->at(i)->GetType() == EntityType::ENEMY)
			{
				if (this->IsCollidingObject(colliable_objects->at(i)))
				{
					colliable_objects->at(i)->AddHealth(-damage);
					isCollisionEnemies = 1;
					vx = 0;
					vy = 0;
				}
			}
		}
#pragma endregion
	}
}

void ElectricBullet::Render()
{
	if (!isDone)
	{
		if (!isCountBack)
		{
			animationSet->at(0)->ResetCurrentFrame();
			isCountBack = true;
		}
		animationSet->at(0)->OldRender(x, y, alpha);
		if (animationSet->at(0)->GetFrame() == 9)
		{
			isDone = true;
			//timeDelayed = 0;
			isCountBack = false;
		}
		RenderBoundingBox();
	}
}

void ElectricBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (!isDone)
	{
		l = x;
		t = y + 13;
		r = x + ELECTRIC_BULLET_JASON_BBOX_WIDTH;
		b = y + ELECTRIC_BULLET_JASON_BBOX_HEIGHT + 13;
	}
}