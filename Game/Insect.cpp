#include "Insect.h"

void Insect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + INSECT_BBOX_WIDTH;
	bottom = y + INSECT_BBOX_HEIGHT;
}

Insect::Insect(float x, float y, LPGAMEENTITY t)
{
	
	enemyType = INSECT;
	this->x = x;
	this->y = y;
	nx = -1;
	this->target = t;

	health = INSECT_MAXHEALTH;
	isActive = false;
}

void Insect::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
}

void Insect::Render()
{
	if (isDeath)
		return;
	int ani;
	if (health <= 0)
	{
		ani = INSECT_ANI_DIE;
		animationSet->at(ani)->OldRender(x, y);
				
	}
	else
	{
		if (vx > 0)
			direction = 1;
		else
			direction = -1;
		ani = INSECT_ANI_FLY;
		animationSet->at(ani)->Render(direction, x, y);
	}
	RenderBoundingBox();
}



void Insect::SetState(int state)
{

}

void Insect::Activation()
{
}
