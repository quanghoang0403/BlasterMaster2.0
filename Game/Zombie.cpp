#include "Zombie.h"

Zombie::Zombie(float posX, float posY, int direction)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ZOMBIE));
	tag = EntityType::ZOMBIE;

	this->posX = posX;
	this->posY = posY;
	this->direction = direction;

	this->SetState(ZOMBIE_STATE_WALKING);

	health = ZOMBIE_MAXHEALTH;
	isDead = false;
}

Zombie::~Zombie() {}

void Zombie::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	if (health <= 0 || posX < 0 || posX > SCREEN_WIDTH * 2 || posY > BOTTOM_SCREEN)
	{
		SetState(ZOMBIE_STATE_DIE);
		return;
	}

	Entity::Update(dt);
	vY += ZOMBIE_GRAVITY * dt;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEENTITY> bricks;
	//Zombie only collision with bricks
	coEvents.clear();
	bricks.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == EntityType::BRICK ||
			coObjects->at(i)->GetType() == EntityType::BREAKABLEBRICK)
			bricks.push_back(coObjects->at(i));

	// turn off collision when die 
	if (state != ZOMBIE_STATE_DIE)
		CalcPotentialCollisions(&bricks, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		posX += dx;
		posY += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		posX += min_tx * dx + nx * 0.1f;
		posY += min_ty * dy + ny * 0.1f;

		if (nx != 0 && ny == 0)
		{
			direction *= -1;
			vX *= -1;
		}
		else if (ny == -1)
			vY = 0;
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

}

void Zombie::Render()
{
	if (isDead)
		return;

	animationSet->at(state)->Render(direction, posX, posY);

	RenderBoundingBox();
}

void Zombie::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case ZOMBIE_STATE_DIE:
		vX = 0;
		vY = 0;
		health = 0;
		isDead = true;
		break;
	case ZOMBIE_STATE_WALKING:
		vX = ZOMBIE_WALKING_SPEED_X * direction;
		break;
	}
}


void Zombie::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	//not clean
	if (!isDead) {
		l = posX;
		t = posY;
		r = posX + ZOMBIE_BBOX_WIDTH;
		b = posY + ZOMBIE_BBOX_HEIGHT;
	}
}
