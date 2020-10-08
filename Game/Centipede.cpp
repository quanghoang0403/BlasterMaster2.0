#include "Centipede.h"
Centipede::Centipede()
{
	tag = EntityType::CENTIPEDE;
	SetState(CENTIPEDE_STATE_WALKING);
}

void Centipede::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CENTIPEDE_BBOX_WIDTH;
	bottom = y + CENTIPEDE_BBOX_HEIGHT;
}

void Centipede::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	Entity::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
	x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}

}

void Centipede::Render()
{
	if (vx > 0)
		direction = 1;
	else
		direction = -1;

	int ani = CENTIPEDE_ANI_WALKING;
	if (state == CENTIPEDE_STATE_DIE) {
		ani = CENTIPEDE_ANI_DIE;
	}
	//DebugOut(L"[xxxxxx] direction: %s\n", direction);
	animationSet->at(ani)->Render(direction, x, y);

	RenderBoundingBox();
}

void Centipede::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case CENTIPEDE_STATE_DIE:
		y += CENTIPEDE_BBOX_HEIGHT - CENTIPEDE_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case CENTIPEDE_STATE_WALKING:
		vx = -CENTIPEDE_WALKING_SPEED;
	}
}