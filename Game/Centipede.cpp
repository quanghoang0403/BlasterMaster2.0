﻿#include "Centipede.h"
Centipede::Centipede()
{
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
	// Calculate dx, dy 
	Entity::Update(dt);
#pragma region Xử lý vy
	// Simple fall down
	vy += CENTIPEDE_GRAVITY * dt;
#pragma endregion

#pragma region Xử lý vx
	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
#pragma endregion

#pragma region Xử lý va chạm
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEENTITY> bricks;

	coEvents.clear();
	bricks.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == EntityType::BRICK)
			bricks.push_back(coObjects->at(i));


	// turn off collision when die 
	if (state != CENTIPEDE_STATE_DIE)
		CalcPotentialCollisions(&bricks, coEvents);



	// No collision occured, proceed normally
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


		x += min_tx * dx + nx * 0.1f;
		y += min_ty * dy + ny * 0.1f;

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
#pragma endregion
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