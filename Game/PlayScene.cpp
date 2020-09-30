#include "PlayScene.h"
#include "Textures.h"

#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GATE	2

PlayScene::PlayScene() : Scene()
{
	keyHandler = new PlayScenceKeyHandler(this);
	LoadBaseObjects();
	ChooseMap(STAGE_1);
}

void PlayScene::LoadBaseObjects()
{
	texturesFilePath = ToLPCWSTR("Resources/Scene/textures_playscene.txt");
	LoadBaseTextures();
	if (player == NULL)
	{
		player = new Player(17, 25);
		DebugOut(L"[INFO] Simon CREATED! \n");
	}
	if (bullet1 == NULL)
	{
		bullet1 = new SmallJasonBullet();
		listBullets.push_back(bullet1);
		DebugOut(L"[INFO] Bullet1 CREATED! \n");
	}
	if (bullet2 == NULL)
	{
		bullet2 = new SmallJasonBullet();
		listBullets.push_back(bullet2);
		DebugOut(L"[INFO] Bullet2 CREATED! \n");
	}
	if (bullet3 == NULL)
	{
		bullet3 = new SmallJasonBullet();
		listBullets.push_back(bullet3);
		DebugOut(L"[INFO] Bullet3 CREATED! \n");
	}
	//if (supBullet == NULL)
	//{
	//	//bullet1 = new Bullet(0, 115);
	//	DebugOut(L"[INFO] supBullet CREATED! \n");
	//}
	gameCamera = Camera::GetInstance();
}

void PlayScene::ChooseMap(int whatMap)
{
	idStage = whatMap;
	Game::GetInstance()->SetKeyHandler(this->GetKeyEventHandler());
	int convertSimple = idStage / STAGE_1;
	sceneFilePath = listSceneFilePath[convertSimple - 1];
	LoadSceneObjects();
}

void PlayScene::Update(DWORD dt)
{
#pragma region Camera
	float cx, cy;
	player->GetPosition(cx, cy);
	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2; 
	gameCamera->SetCamPos(cx, 0.0f);//cy khi muon camera move theo y player 

#pragma endregion
	PlayerGotGate();
#pragma region Objects Updates
	vector<LPGAMEENTITY> coObjects;
	for (int i = 0; i < listObjects.size(); i++)
		coObjects.push_back(listObjects[i]);
	player->Update(dt, &coObjects);
	for (int i = 0; i < listBullets.size(); i++)
		listBullets[i]->Update(dt, &coObjects);
	for (int i = 0; i < listObjects.size(); i++)
		listObjects[i]->Update(dt, &coObjects);	
#pragma endregion
}

bool PlayScene::PlayerPassingStage(float DistanceXWant, int directionGo)
{
	if (directionGo == 1)	//cua o ben phai
	{
		if (player->GetPosX() < DistanceXWant)
		{
			player->SetDirection(directionGo);
			player->SetState(SOPHIA_STATE_IDLE);
			return false;
		}
	}
	else
		if (directionGo == -1)	//cua o ben trai
		{
			if (player->GetPosX() > DistanceXWant)
			{
				player->SetDirection(directionGo);
				player->SetState(SOPHIA_STATE_IDLE);
				return false;
			}
		}
	return true;
}

void PlayScene::PlayerGotGate()
{
	for (UINT i = 0; i < listObjects.size(); i++)
	{
		if (listObjects[i]->GetType() == EntityType::GATE)
		{
			if (player->IsCollidingObject(listObjects[i]))
			{
        		Gate* gate = dynamic_cast<Gate*>(listObjects[i]);
				int tempMap = gate->GetIdScene() * STAGE_1;
				float tempPosX = gate->newPlayerPosX;
				float tempPosY = gate->newPlayerPosY;
				int tempState = gate->newPlayerState;
				bool tempNeed = gate->isNeedResetCam;
				/*if (idStage == STAGE_1)
				{
					if (!PlayerPassingStage(listObjects[i]->GetPosX() + 20.0f, 1))
						return;
				}
				else if (idStage == STAGE_2_2 && tempMap == STAGE_3_1)
				{
					if (!PlayerPassingStage(listObjects[i]->GetPosX(), -1))
						return;
				}
				else if (idStage == STAGE_3_2 && tempMap == STAGE_4)
				{
					if (!PlayerPassingStage(listObjects[i]->GetPosX() + 10.0f, 1))
						return;
				}*/
				Unload();
				if(tempNeed)
					gameCamera->SetCamPos(0, 0);
				ChooseMap(tempMap);
				player->SetPosition(tempPosX, tempPosY);
				player->SetVx(0);
				player->SetVy(0);
				player->SetState(tempState);
			}
		}
	}
}

void PlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	Player* player = ((PlayScene*)scence)->player;
	Bullet* bullet1 = ((PlayScene*)scence)->bullet1;
	PlayScene* playScene = dynamic_cast<PlayScene*>(scence);
	vector<LPGAMEENTITY> listObjects = ((PlayScene*)scence)->listObjects;
	vector<LPBULLET> listBullets = ((PlayScene*)scence)->listBullets;
	switch (KeyCode)
	{

	case DIK_SPACE:
		player->SetState(SOPHIA_STATE_JUMP);
		break;
	case DIK_A:
		playScene->Unload();
		playScene->ChooseMap(STAGE_1);
		player->SetPosition(6, 60);
		/*player->Reset();*/
		break;
	case DIK_Z:
		DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
		float x, y;
		int direction, isTargetTop;
		player->GetInfoForBullet(direction, isTargetTop, x, y);
		for (int i = 0; i < listBullets.size(); i++)
		{
			if (listBullets[i]->isDone == true)
			{
				listBullets[i]->Fire(direction, isTargetTop, x, y);
				break;
			}
		}
		break;
	}
}

void PlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	Player* player = ((PlayScene*)scence)->player;
	PlayScene* playScene = dynamic_cast<PlayScene*>(scence);
	vector<LPGAMEENTITY> listObj = ((PlayScene*)scence)->listObjects;
	switch (KeyCode)
	{
	case DIK_UP:
		//player->SetState(SOPHIA_STATE_GUN_UNFLIP);
		player->SetPressUp(false);
		player->SetState(SOPHIA_STATE_GUN_UNFLIP);
		break;
	}
}

void PlayScenceKeyHandler::KeyState(BYTE* states)
{
	Player* player = ((PlayScene*)scence)->player;
	PlayScene* playScene = dynamic_cast<PlayScene*>(scence);
	vector<LPGAMEENTITY> listObjects = ((PlayScene*)scence)->listObjects;
	vector<LPBULLET> listBullets = ((PlayScene*)scence)->listBullets;
	if (player->GetState() == SOPHIA_STATE_DIE) return;
	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
		player->SetState(SOPHIA_STATE_WALKING_RIGHT);
	else if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		player->SetState(SOPHIA_STATE_WALKING_LEFT);
	}
	/*else if (game->IsKeyDown(DIK_SPACE))
	{
		player->SetPressSpace();
	}*/
	else
		player->SetState(SOPHIA_STATE_IDLE);

	if (Game::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		player->SetPressSpace();
	}

	if (Game::GetInstance()->IsKeyDown(DIK_UP))
	{
		player->SetPressUp(true);
	}

	if (Game::GetInstance()->IsKeyDown(DIK_Z))
	{
	}
}

void PlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void PlayScene::_ParseSection_CLEARTEXTURES(string line)
{
	vector<string> tokens = split(line);
	int idClear = atoi(tokens[0].c_str());
	CTextures::GetInstance()->ClearAt(idClear);
	DebugOut(L"[INFO] Cleared Texture %d!\n", idClear);
}

void PlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void PlayScene::_ParseSection_CLEARSPRITES(string line)
{
	vector<string> tokens = split(line);
	int idClear = atoi(tokens[0].c_str());
	CSprites::GetInstance()->ClearAt(idClear);
	DebugOut(L"[INFO] Cleared Sprite %d!\n", idClear);
}

void PlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void PlayScene::_ParseSection_CLEARANIMATIONS(string line)
{
	vector<string> tokens = split(line);
	int idClear = atoi(tokens[0].c_str());
	CAnimations::GetInstance()->ClearAt(idClear);
	DebugOut(L"[INFO] Cleared Animation %d!\n", idClear);
}

void PlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void PlayScene::_ParseSection_CLEARANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);
	int idClear = atoi(tokens[0].c_str());
	CAnimationSets::GetInstance()->ClearAt(idClear);
	DebugOut(L"[INFO] Cleared Animation Set %d!\n", idClear);
}

void PlayScene::_ParseSection_SCENEFILEPATH(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return;

	listSceneFilePath.push_back(ToLPCWSTR(tokens[0]));
	mapWidth = atoi(tokens[1].c_str());
	mapHeight = atoi(tokens[2].c_str());
	//Hien tai chi lay mapWidth/Height cua list cuoi cung` :P co the dem vo tung file scene rieng de phan biet (hoac khong can, camera co chay toi duoc dau)
}

void PlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	int ani_set_id = atoi(tokens[3].c_str());
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	Entity* obj = NULL;
	switch (object_type)
	{
	case OBJECT_TYPE_BRICK:
	{
		obj = new Brick(); 
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		listObjects.push_back(obj);
		DebugOut(L"[test] add brick !\n");
		break;
	}
	case OBJECT_TYPE_GATE:
	{
		int switchId = atoi(tokens[3].c_str());
		float playerPosX = atoi(tokens[4].c_str());
		float playerPosY = atoi(tokens[5].c_str());
		int playerState = atoi(tokens[6].c_str());
		int isResetCamera = atoi(tokens[7].c_str());
		obj = new Gate(x, y, switchId, playerPosX, playerPosY, playerState, isResetCamera);
		listObjects.push_back(obj);
		DebugOut(L"[test] add gate !\n");
		break;
	}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}
}

void PlayScene::LoadBaseTextures()
{
	DebugOut(L"[INFO] Start loading TEXTURES resources from : %s \n", texturesFilePath);

	ifstream f;
	f.open(texturesFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") {
			section = SCENE_SECTION_TEXTURES; continue;
		}
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[SCENE]") {
			section = SCENE_SECTION_SCENEFILEPATH; continue;
		}

		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_SCENEFILEPATH: _ParseSection_SCENEFILEPATH(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading TEXTURES resources %s\n", texturesFilePath);
}

void PlayScene::LoadSceneObjects()
{
	DebugOut(L"[INFO] Start loading scene111 resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[CLEARTEXTURES]") {
			section = SCENE_SECTION_CLEARTEXTURES; continue;
		}
		if (line == "[CLEARSPRITES]") {
			section = SCENE_SECTION_CLEARSPRITES; continue;
		}
		if (line == "[CLEARANIMATIONS]") {
			section = SCENE_SECTION_CLEARANIMATIONS; continue;
		}
		if (line == "[CLEARANIMATIONSETS]") {
			section = SCENE_SECTION_CLEARANIMATION_SETS; continue;
		}
		if (line == "[TEXTURES]") {
			section = SCENE_SECTION_TEXTURES; continue;
		}
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[TILEMAP]") {
			section = SCENE_SECTION_TILEMAP; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_CLEARTEXTURES: _ParseSection_CLEARTEXTURES(line); break;
		case SCENE_SECTION_CLEARSPRITES: _ParseSection_CLEARSPRITES(line); break;
		case SCENE_SECTION_CLEARANIMATIONS: _ParseSection_CLEARANIMATIONS(line); break;
		case SCENE_SECTION_CLEARANIMATION_SETS: _ParseSection_CLEARANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		//case SCENE_SECTION_TILEMAP:	_ParseSection_TILEMAP(line); break;
		}
	}

	f.close();
	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"Resources\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void PlayScene::Unload()
{
	for (int i = 0; i < listObjects.size(); i++)
		delete listObjects[i];
	listObjects.clear();
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void PlayScene::Render()
{
	//gameMap->Draw();
	for (int i = 0; i < listObjects.size(); i++)
		listObjects[i]->Render();
	player->Render();
	for (int i = 0; i < listBullets.size(); i++)
		listBullets[i]->Render();
}

