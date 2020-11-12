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
#include "PlayerV2.h"
#include "MiniSophia.h"
#include "HUD.h"
#include "Brick.h"
#include "Gate.h"
#include "PowerUp.h"
#include "GunUp.h"

#include "Centipede.h"
#include "Golem.h"
#include "Gunner.h"
#include "Domes.h"
#include "Floaters.h"
#include "Insect.h"

#include "MainJasonBullet.h"
#include "ElectricBullet.h"
#include "BigSophiaBullet.h"

#include <iostream>
#include <fstream>

#include"Entity.h"

using namespace std;

class PlayScene : public Scene
{
public:
	int typeSophia;
	//void SetIsMiniSophia() { type = 0; }
	//bool isMiniSophia
protected:
	Player* player;
	PlayerV2* playerV2;
	MiniSophia* sophia;
	HUD* gameHUD;
#pragma region Bullet
	Bullet* bullet1;
	Bullet* bullet2;
	Bullet* bullet3;
	Bullet* supBullet;
	Bullet* bigBullet1;
	Bullet* bigBullet2;
	Bullet* bigBullet3;
#pragma endregion
	//Bullet* bulletBigSophia[2];
	PowerUp* powerUp;
	GunUp* gunUp;
	vector<LPGAMEENTITY> listObjects;
	vector<LPGAMEENTITY> listEnemies;
	vector<LPBULLET> listBullets;
	vector<LPBULLET> listBigBullets;
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
	void PlayerGotCar();
	void PlayerTouchEnemy();
	void PlayerCollideItem();
	virtual void LoadSceneObjects();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	Item* RandomItem(float x, float y);
	Item* DropItem(EntityType createrType, float x, float y, int idCreater = 0);

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


