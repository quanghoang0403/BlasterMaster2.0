#include "Domes.h"

void Domes::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + DOMES_BBOX_WIDTH;
	bottom = y + DOMES_BBOX_HEIGHT;
}

void Domes::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{

}

void Domes::Render()
{
	if (vx > 0)
		direction = 1;
	else
		direction = -1;

	int ani = DOMES_ANI_WALKING;
	if (state == DOMES_STATE_DIE) {
		ani = DOMES_ANI_DIE;
	}
	//DebugOut(L"[xxxxxx] direction: %s\n", direction);
	animationSet->at(ani)->Render(direction, x, y);

	RenderBoundingBox();
}

Domes::Domes()
{
	SetState(DOMES_STATE_WALKING);
}

void Domes::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case DOMES_STATE_DIE:
		y += DOMES_BBOX_HEIGHT - DOMES_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case DOMES_STATE_WALKING:
		vx = -DOMES_WALKING_SPEED;
	}
}
