#include "Eyeballs.h"

void Eyeballs::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDeath)
	{
		left = x;
		top = y;
		right = x + EYEBALLS_BBOX_WIDTH;
		bottom = y + EYEBALLS_BBOX_HEIGHT;
	}
}

Eyeballs::Eyeballs(float x, float y, LPGAMEENTITY t)
{

	enemyType = EYEBALLS;
	this->x = x;
	this->y = y;
	this->target = t;
	health = EYEBALLS_MAXHEALTH;
	isActive = false;
	isDamaged = false;
	isDeath = 0;
	
}

void Eyeballs::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	Entity::Update(dt);


#pragma region Xử lý tiền va chạm
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEENTITY> bricks;

	coEvents.clear();
	bricks.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == EntityType::BRICK)
			bricks.push_back(coObjects->at(i));

	// turn off collision when die
	if (state != EYEBALLS_STATE_DIE)
		CalcPotentialCollisions(&bricks, coEvents);

#pragma endregion



#pragma region Xử lý logic khi va chạm
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);


		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

	}


	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void Eyeballs::Render()
{
	if (isDeath)
		return;
	int ani;
	if (health <= 0)
	{
		ani = EYEBALLS_ANI_DIE;
		animationSet->at(ani)->Render(direction, x, y);
		if (animationSet->at(ani)->GetFrame() == 3)
			SetState(EYEBALLS_STATE_DIE);
	}
	else
	{
		if (vx > 0)
			direction = 1;
		else
			direction = -1;
		ani = EYEBALLS_ANI_FLY;
		animationSet->at(ani)->Render(direction, x, y);
	}
	RenderBoundingBox();
}



void Eyeballs::SetState(int state)
{
	Entity::SetState(state);

	switch (state)
	{
	case EYEBALLS_STATE_DIE:
		vx = 0;
		vy = 0;
		break;

	case EYEBALLS_STATE_FLY:


		break;

	case EYEBALLS_STATE_ATTACK:
		


		break;

	default:
		break;
	}
}

void Eyeballs::Activation()
{
}

void Eyeballs::Attack()
{
}
