#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>

#include "Scene.h"
#include "SceneManager.h"
#include "Game.h"
#include "Camera.h"

#include "Player.h"
#include "HUD.h"
#include "Brick.h"
#include "Gate.h"
#include "PowerUp.h"
#include "GunUp.h"

#include "Centipede.h"
#include "Golem.h"
#include "Gunner.h"
#include "Domes.h"

#include "MainJasonBullet.h"
#include "ElectricBullet.h"


#include <iostream>
#include <fstream>

#include"Entity.h"

using namespace std;

class PlayScene : public Scene
{
protected:
	Player* player;
	HUD* gameHUD;
	Bullet* bullet1;
	Bullet* bullet2;
	Bullet* bullet3;
	Bullet* supBullet;
	PowerUp* powerUp;
	GunUp* gunUp;
	vector<LPGAMEENTITY> listObjects;
	vector<LPBULLET> listBullets;
	vector<LPCWSTR> listSceneFilePath;
	vector<LPGAMEITEM> listItems;
	Camera* gameCamera;

	int idStage;
	int mapWidth, mapHeight;
	int camMaxWidth;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_CLEARTEXTURES(string line);
	void _ParseSection_CLEARSPRITES(string line);
	void _ParseSection_CLEARANIMATIONS(string line);
	void _ParseSection_CLEARANIMATION_SETS(string line);

	//Get stage objects' link and tilemap resources
	void _ParseSection_SCENEFILEPATH(string line);


public:
	PlayScene();

	void LoadBaseObjects();
	void LoadBaseTextures();
	void ChooseMap(int whatStage);
	bool PlayerPassingStage(float DistanceXWant, int directionGo);
	void PlayerGotGate();
	void PlayerCollideItem();
	virtual void LoadSceneObjects();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	Item* RandomItem(float posX, float posY);
	Item* DropItem(EntityType createrType, float posX, float posY, int idCreater = 0);

	friend class PlayScenceKeyHandler;
};


class PlayScenceKeyHandler : public ScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	PlayScenceKeyHandler(Scene* s) :ScenceKeyHandler(s) {};
};


