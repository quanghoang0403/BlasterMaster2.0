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
#include "Brick.h"
#include "Gate.h"

#include <iostream>
#include <fstream>

using namespace std;

class PlayScene : public Scene
{
protected:
	Player* player;
	std::vector<LPGAMEENTITY> listObjects;
	std::vector<LPCWSTR> listSceneFilePath;
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
	virtual void LoadSceneObjects();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

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


