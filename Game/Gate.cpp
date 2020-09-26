#include "Gate.h"

Gate::Gate(float posX, float posY, int switchId, float simonPosX, float simonPosY, int simonState/*, bool rsCam*/)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_GATE));
	tag = EntityType::GATE;
	this->x = posX;
	this->y = posY;
	gateSwitchSceneId = switchId;
	newSimonPosX = simonPosX;
	newSimonPosY = simonPosY;
	newSimonState = simonState;
	//isNeedResetCam = rsCam;
}

Gate::~Gate() {}

void Gate::Render()
{
	RenderBoundingBox();

	//if (gateSwitchSceneId == 2 || gateSwitchSceneId == 4)	//Gate tai stage 1 3 khong ve~
	//	return;

	//animationSet->at(0)->Render(-direction, posX, posY);
}

void Gate::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + GATE_BBOX_WIDTH;
	b = y + GATE_BBOX_HEIGHT;
}
