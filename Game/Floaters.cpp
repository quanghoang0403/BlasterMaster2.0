#include "Floaters.h"

void Floaters::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FLOATERS_BBOX_WIDTH;
	bottom = y + FLOATERS_BBOX_HEIGHT;
}

Floaters::Floaters(float x, float y, LPGAMEENTITY t)
{
	enemyType = FLOATERS;
	this->x = x;
	this->y = y;
	this->target = t;
	health = FLOATERS_MAXHEALTH;
	isActive = false;
	isDamaged = false;
	randomSpeed();
	delayTimer->Start();
	SetState(FLOATERS_STATE_FLY);
	vx = vxR;
	vy = vyR;
	
}

void Floaters::Attack()
{
	bullet.push_back(new BulletFloaters(x, y, target->x, target->y));
	isDamaged = 1;
}

void Floaters::randomSpeed()
{
	
	random_device rm;
	mt19937 t(rm());
	uniform_real_distribution<float> rand(0, FLOATERS_SPEED_MAXVY);
	uniform_int_distribution<int>	randi(1, 6);
	uniform_int_distribution<int>	randj(1, 6);
	float res;
	for (int i = 0; i < randi(t); ++i) {
		if (i % 2 == 0)
			res = rand(t);
		else
			res = -rand(t);
	}
	for (int i = 0; i < randj(t); ++i) {
		if (i % 2 == 0)
			vxR = FLOATERS_SPEED_CONSTVX;
		else
			vxR = -FLOATERS_SPEED_CONSTVX;
	}
	vyR = res * vxR;
	
}

int Floaters::randomTimeAttack()
{
	random_device rm;
	mt19937 t(rm());
	uniform_int_distribution<int>	randi(1, FLOATERS_MAXTIME_ATTACK);
	return randi(t);
}

void Floaters::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	Entity::Update(dt);

	if (delayTimer->IsTimeUp())
	{
		Attack();
		delayTimeranishot->Reset();
		delayTimeranishot->Start();
		SetState(FLOATERS_STATE_ATTACK);
		
	}
	else
	{
		SetState(FLOATERS_STATE_FLY);
	}
	for (int i = 0; i < bullet.size(); i++)
	{
		bullet.at(i)->Update(dt, coObjects);
		//DebugOut(L"\nsadad:  %d", bullet.size());
	}
	

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
	if (state != FLOATERS_STATE_DIE)
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

#pragma region Collision Brick
		if (!nx && !ny)
		{
			vx = -vx;
			vy = -vy;
		}
		else if (!nx)
			vy = -vy;
		else if (!ny)
			vx = -vx;
#pragma endregion

	}
	
	
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Floaters::Render()
{
	if (isDeath)
		return;
	
	int ani;
	if (health <= 0)
	{
		ani = FLOATERS_ANI_DIE;
		animationSet->at(ani)->OldRender(x, y);
	}
	else if (delayTimeranishot->IsTimeUp())
	{
		ani = FLOATERS_ANI_FLY;
		animationSet->at(ani)->OldRender(x, y);
		
	}
	else if (!delayTimeranishot->IsTimeUp())
	{
		ani = FLOATERS_ANI_ATTACK;
		animationSet->at(ani)->OldRender(x, y);

	}
	
	
	for (int i = 0; i < bullet.size(); i++)
	{
		bullet.at(i)->Render();
	}
	RenderBoundingBox();
}



void Floaters::SetState(int state)
{
	Entity::SetState(state);

	switch (state)
	{
	case FLOATERS_STATE_DIE:
		y += FLOATERS_BBOX_HEIGHT - FLOATERS_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
			
	case FLOATERS_STATE_FLY:
		
		break;

	case FLOATERS_STATE_ATTACK:
		delayTimer->Reset(randomTimeAttack());
		delayTimer->Start();
		
	
		break;
	default:
		break;
	}
}

void Floaters::Activation()
{

}
