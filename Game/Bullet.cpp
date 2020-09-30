#include "Bullet.h"
Bullet::Bullet()
{
	isDone = true;
	damage = 1;
}

Bullet::~Bullet()
{
}

void Bullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	/*left = x;
	top = y;
	right = x + CENTIPEDE_BBOX_WIDTH;
	if (state == CENTIPEDE_STATE_DIE)
		bottom = y + CENTIPEDE_BBOX_HEIGHT_DIE;
	else
		bottom = y + CENTIPEDE_BBOX_HEIGHT;*/
}

void Bullet::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	Entity::Update(dt, coObjects);

	/*x += dx;
	y += dy;

	if (x > 330 || x < 0) {
		Bullet::SetState(BULLET_JASON_STATE_READY);
	}*/
}

void Bullet::Render()
{
	//if (player->isGunFlippingg() == true)
	//{
	//	vy = -BULLET_SPEED;
	//	ani = SMALL_BULLET_JASON_ANI_TOP;
	//	animation_set->at(ani)->Render(x, y, alpha);
	//}
	//else
	//{
	//	if (player->direction == 1)
	//		vx = BULLET_SPEED;
	//	else
	//		vx = -BULLET_SPEED;
	//	ani = SMALL_BULLET_JASON_ANI_RIGHT;
	//	animation_set->at(ani)->RenderVer2(player->direction, x, y, alpha);
	//}
	////DebugOut(L"[xxxxxx] direction: %s\n", direction);
	//if (isDone)
	//	return;
	//animationSet->at(0)->Render(direction, x, y);
	//RenderBoundingBox();
}
