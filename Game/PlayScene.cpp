#include "PlayScene.h"
#include "Textures.h"

#define OBJECT_TYPE_BRICK		1
#define OBJECT_TYPE_GATE		2

#define OBJECT_TYPE_CENTIPEDE	10
#define OBJECT_TYPE_GOLEM		11
#define OBJECT_TYPE_GUNNER		12
#define OBJECT_TYPE_DOMES		13

#define DX_GET_OUT_CAR		7
#define HUD_Y				20


PlayScene::PlayScene() : Scene()
{
	keyHandler = new PlayScenceKeyHandler(this);
	typeSophia = 1;
	LoadBaseObjects();
	ChooseMap(STAGE_1);
}

void PlayScene::LoadBaseObjects()
{
	texturesFilePath = ToLPCWSTR("Resources/Scene/textures_playscene.txt");
	//texturesFilePath = ToLPCWSTR("Resources/Scene/base.txt");
	LoadBaseTextures();
	if (player == NULL)
	{
		player = new Player(135, 100);
		DebugOut(L"[INFO] player CREATED! \n");
	}
	if (playerV2 == NULL)
	{
		playerV2 = new PlayerV2(165, 100);
		DebugOut(L"[INFO] playerv2 CREATED! \n");
	}
	if (sophia == NULL)
	{
		sophia = new MiniSophia(105, 100);
		DebugOut(L"[INFO] sophia CREATED! \n");
	}
	if (gameHUD == NULL)
	{
		gameHUD = new HUD(player->GetHealth(), player->GetgunDam());
		DebugOut(L"[INFO] HUD CREATED! %d \n", player->GetHealth());
	}
	//gameHUD = new HUD(player->GetHealth(), player->GetgunDam());
	if (bullet1 == NULL)
	{
		bullet1 = new MainJasonBullet();
		listBullets.push_back(bullet1);
		DebugOut(L"[INFO] Bullet1 CREATED! \n");
	}
	if (bullet2 == NULL)
	{
		bullet2 = new MainJasonBullet();
		listBullets.push_back(bullet2);
		DebugOut(L"[INFO] Bullet2 CREATED! \n");
	}
	if (bullet3 == NULL)
	{
		bullet3 = new MainJasonBullet();
		listBullets.push_back(bullet3);
		DebugOut(L"[INFO] Bullet3 CREATED! \n");
	}
	if (bullet4 == NULL)
	{
		bullet4 = new BigSophiaBullet();
		DebugOut(L"[INFO] Bullet3 CREATED! \n");
	}
	if (supBullet == NULL)
	{
		supBullet = new ElectricBullet();
		DebugOut(L"[INFO] supBullet CREATED! \n");
	}
	for (int i = 0; i < 3; i++)
	{
		if (bulletBigSophia[i] == NULL)
		{
			bulletBigSophia[i] = new BigSophiaBullet();
			DebugOut(L"[INFO] Bullet big sophia CREATED! \n");
		}
	}
	if (powerUp == NULL)
	{
		powerUp = new PowerUp(100,150);
		listItems.push_back(powerUp);
		DebugOut(L"[INFO] powerUp CREATED! \n");
	}
	if (gunUp == NULL)
	{
		gunUp = new GunUp(200, 150);
		listItems.push_back(gunUp);
		DebugOut(L"[INFO] gunUp CREATED! \n");
	}
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


bool PlayScene::PlayerPassingStage(float DistanceXWant, int directionGo)
{
	if (directionGo == 1)	//cua o ben phai
	{
		if (player->Getx() < DistanceXWant)
		{
			player->SetDirection(directionGo);
			player->SetState(SOPHIA_STATE_IDLE);
			return false;
		}
	}
	else
		if (directionGo == -1)	//cua o ben trai
		{
			if (player->Getx() > DistanceXWant)
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
				//int newX = player->x -= 100;
				//player->SetPosition(newX, 40);
        		Gate* gate = dynamic_cast<Gate*>(listObjects[i]);
				typeSophia = gate->typePlayer;
				int tempMap = gate->GetIdScene() * STAGE_1;
				float tempx = gate->newPlayerx;
				float tempy = gate->newPlayery;
				int tempState = gate->newPlayerState;
				bool tempNeed = gate->isNeedResetCam;
				/*if (idStage == STAGE_1)
				{
					if (!PlayerPassingStage(listObjects[i]->Getx() + 20.0f, 1))
						return;
				}
				else if (idStage == STAGE_2_2 && tempMap == STAGE_3_1)
				{
					if (!PlayerPassingStage(listObjects[i]->Getx(), -1))
						return;
				}
				else if (idStage == STAGE_3_2 && tempMap == STAGE_4)
				{
					if (!PlayerPassingStage(listObjects[i]->Getx() + 10.0f, 1))
						return;
				}*/
				Unload();
				if(tempNeed)
					gameCamera->SetCamPos(0, 0);
				ChooseMap(tempMap);
				if (typeSophia == 1)
				{
					player->SetPosition(tempx, tempy);
					player->Setvx(0);
					player->Setvy(0);
					player->SetState(tempState);
				}
				else if (typeSophia == 0)
				{
					sophia->SetPosition(tempx, tempy);
					sophia->Setvx(0);
					sophia->Setvy(0);
					sophia->SetState(tempState);
				}
				else 
				{
					player->SetPosition(tempx, tempy);
					playerV2->SetPosition(tempx, tempy);
					playerV2->Setvx(0);
					playerV2->Setvy(0);
					playerV2->SetState(tempState);
				}
			}
		}
	}
}

void PlayScene::PlayerGotCar()
{
	if (sophia->IsCollidingObject(player))
		typeSophia = 1;
}

void PlayScene::PlayerTouchEnemy()
{
	for (UINT i = 0; i < listEnemies.size(); i++)
	{
		if (player->IsCollidingObject(listEnemies[i]))
		{
			player->SetInjured(1);
		}
	}
}

void PlayScene::PlayerCollideItem()
{
	for (UINT i = 0; i < listItems.size(); i++)
	{
		if (!listItems[i]->GetIsDone())
		{
			if (player->IsCollidingObject(listItems[i]))
			{
				switch (listItems[i]->GetType())
				{
				case EntityType::POWERUP:
				{
					if (player->GetHealth() + POWER_HP_RESTORE <= MAX_HEALTH)
						player->AddHealth(POWER_HP_RESTORE);
					else
						player->SetHealth(MAX_HEALTH);
					listItems[i]->SetIsDone(true);
					break;
				}
				case EntityType::GUNUP:
				{
					if (player->GetgunDam() + GUN_HP_RESTORE <= MAX_HEALTH)
						player->AddgunDam(GUN_HP_RESTORE);
					else
						player->SetgunDam(MAX_HEALTH);
					listItems[i]->SetIsDone(true);
					break;
				}
				default:
					break;
				}
			}
		}
	}
}

void PlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
#pragma region Init
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	int typeSophia = ((PlayScene*)scence)->typeSophia;
	Player* player = ((PlayScene*)scence)->player;
	PlayerV2* playerV2 = ((PlayScene*)scence)->playerV2;
	MiniSophia* sophia = ((PlayScene*)scence)->sophia;
	Bullet* bullet1 = ((PlayScene*)scence)->bullet1;
	Bullet* bullet2 = ((PlayScene*)scence)->bullet2;
	Bullet* bullet3 = ((PlayScene*)scence)->bullet3;
	Bullet* supBullet = ((PlayScene*)scence)->supBullet;
	PlayScene* playScene = dynamic_cast<PlayScene*>(scence);
	vector<LPGAMEENTITY> listObjects = ((PlayScene*)scence)->listObjects;
	vector<LPGAMEENTITY> listEnemies = ((PlayScene*)scence)->listEnemies;
	vector<LPGAMEITEM> listItems = ((PlayScene*)scence)->listItems;
	vector<LPBULLET> listBullets = ((PlayScene*)scence)->listBullets;
	float x, y;
	int direction, directionY, isTargetTop, dame;
	player->GetInfoForBullet(direction, isTargetTop, x, y);
#pragma endregion
	switch (KeyCode)
	{
	case DIK_ESCAPE:
		DestroyWindow(Game::GetInstance()->GetWindowHandle());
	case DIK_DOWN:
		sophia->SetState(SOPHIA_MINI_STATE_CRAWL);
		break;
	case DIK_SPACE:
		if (typeSophia ==1)
			player->SetState(SOPHIA_STATE_JUMP);
		else if (typeSophia == 0)
			sophia->SetState(SOPHIA_MINI_STATE_JUMP);
		break;
	case DIK_A:
		playScene->Unload();
		playScene->ChooseMap(STAGE_1);
		player->SetPosition(6, 60);
		player->SetHealth(MAX_HEALTH);
		/*player->Reset();*/
		break;
	case DIK_Z:
		if (typeSophia ==1)
		{
			for (int i = 0; i < listBullets.size(); i++)
			{
				if (listBullets[i]->isDone == true)
				{
					listBullets[i]->Fire(1, direction, isTargetTop, x, y);
					break;
				}
			}
		}
		else if (typeSophia == 0)
		{
			sophia->GetInfoForBullet(direction, x, y);
			for (int i = 0; i < listBullets.size(); i++)
			{
				if (listBullets[i]->isDone == true)
				{
					listBullets[i]->Fire(0, direction, isTargetTop, x - DX_GET_OUT_CAR, y + DX_GET_OUT_CAR/2);
					break;
				}
			}
		}
		else
		{
			playerV2->GetInfoBigSophia(direction, directionY, x, y, dame);
			for (int i = 0; i < listBullets.size(); i++)
			{
				if (playScene->bulletBigSophia[i]->isDone == true)
				{
					playScene->bulletBigSophia[i]->BigSophiaFire(direction, isTargetTop, x - DX_GET_OUT_CAR, y + DX_GET_OUT_CAR / 2, dame);
					break;
				}
			}

		}
		break;
	case DIK_X:
		supBullet->Fire(1, direction, isTargetTop, x, y);
		break;
	case DIK_U:
		if (typeSophia == 0)
			playScene->PlayerGotCar();
		if (typeSophia == 1)
		{
			playScene->typeSophia = 0;
			player->SetState(SOPHIA_STATE_OUT);
			sophia->direction = direction;
			sophia->SetPosition(x + DX_GET_OUT_CAR, y);
			sophia->SetState(SOPHIA_MINI_STATE_OUT);
		}
		break;
#pragma region F6
	case DIK_F6:
		for (int i = 0; i < listObjects.size(); i++)
		{
			if (listObjects[i]->GetBBARGB() == 0)
				listObjects[i]->SetBBARGB(200);
			else
				listObjects[i]->SetBBARGB(0);
		}
		for (int i = 0; i < listItems.size(); i++)
		{
			if (listItems[i]->GetBBARGB() == 0)
				listItems[i]->SetBBARGB(200);
			else
				listItems[i]->SetBBARGB(0);
		}
		for (int i = 0; i < listEnemies.size(); i++)
		{
			if (listEnemies[i]->GetBBARGB() == 0)
				listEnemies[i]->SetBBARGB(200);
			else
				listEnemies[i]->SetBBARGB(0);
		}
		for (int i = 0; i < listBullets.size(); i++)
		{
			if (playScene->bulletBigSophia[i]->GetBBARGB() == 0)
				playScene->bulletBigSophia[i]->SetBBARGB(200);
			else
				playScene->bulletBigSophia[i]->SetBBARGB(0);
		}

		if (player->GetBBARGB() == 0)
			player->SetBBARGB(200);
		else
			player->SetBBARGB(0);

		if (playerV2->GetBBARGB() == 0)
			playerV2->SetBBARGB(200);
		else
			playerV2->SetBBARGB(0);

		if (sophia->GetBBARGB() == 0)
			sophia->SetBBARGB(200);
		else
			sophia->SetBBARGB(0);

		if (bullet1->GetBBARGB() == 0)
			bullet1->SetBBARGB(200);
		else
			bullet1->SetBBARGB(0);

		if (bullet2->GetBBARGB() == 0)
			bullet2->SetBBARGB(200);
		else
			bullet2->SetBBARGB(0);

		if (bullet3->GetBBARGB() == 0)
			bullet3->SetBBARGB(200);
		else
			bullet3->SetBBARGB(0);

		if (supBullet->GetBBARGB() == 0)
			supBullet->SetBBARGB(200);
		else
			supBullet->SetBBARGB(0);
		break;
#pragma endregion
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
	case DIK_SPACE:
		player->SetPressSpace(false);
		break;
	}
}

void PlayScenceKeyHandler::KeyState(BYTE* states)
{
#pragma region INIT
	int typeSophia = ((PlayScene*)scence)->typeSophia;
	Player* player = ((PlayScene*)scence)->player;
	PlayerV2* playerV2 = ((PlayScene*)scence)->playerV2;
	MiniSophia* sophia = ((PlayScene*)scence)->sophia;
	Bullet* bullet1 = ((PlayScene*)scence)->bullet1;
	Bullet* bullet2 = ((PlayScene*)scence)->bullet2;
	Bullet* bullet3 = ((PlayScene*)scence)->bullet3;
	Bullet* supBullet = ((PlayScene*)scence)->supBullet;

	PlayScene* playScene = dynamic_cast<PlayScene*>(scence);
	vector<LPGAMEENTITY> listObjects = ((PlayScene*)scence)->listObjects;
	vector<LPGAMEITEM> listItems = ((PlayScene*)scence)->listItems;
	vector<LPBULLET> listBullets = ((PlayScene*)scence)->listBullets;
#pragma endregion
	if (player->GetState() == SOPHIA_STATE_DIE) return;

	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		if (typeSophia == 1)
			player->SetState(SOPHIA_STATE_WALKING_RIGHT);
		else if (typeSophia == 0)
			sophia->SetState(SOPHIA_MINI_STATE_WALKING_RIGHT);
		else
		{
			playerV2->SetState(SOPHIA_BIG_STATE_WALKING_RIGHT);
		}
	}
	else if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		if (typeSophia == 1)
			player->SetState(SOPHIA_STATE_WALKING_LEFT);
		else if (typeSophia == 0)
			sophia->SetState(SOPHIA_MINI_STATE_WALKING_LEFT);
		else
			playerV2->SetState(SOPHIA_BIG_STATE_WALKING_LEFT);
	}
	else if (Game::GetInstance()->IsKeyDown(DIK_UP))
	{
		if (typeSophia == 2)
			playerV2->SetState(SOPHIA_BIG_STATE_WALKING_TOP);
	}
	else if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		if (typeSophia == 2)
			playerV2->SetState(SOPHIA_BIG_STATE_WALKING_BOT);
	}
	else
	{
		if (typeSophia == 1)
			player->SetState(SOPHIA_STATE_IDLE);
		else if (typeSophia == 0)
		{
			if (sophia->GetIsCrawl() == false)
				sophia->SetState(SOPHIA_MINI_STATE_IDLE);
			else
				sophia->SetState(SOPHIA_MINI_STATE_CRAWL_STOP);
		}
		else
			playerV2->SetState(SOPHIA_BIG_STATE_IDLE);
	}

	if (Game::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		if (typeSophia == 1)
			player->SetPressSpace(true);
	}

	if (Game::GetInstance()->IsKeyDown(DIK_UP))
	{
		if (typeSophia == 1)
			player->SetPressUp(true);
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
		obj = new Brick(atof(tokens[4].c_str()),atof(tokens[5].c_str()));
		obj->SetPosition(x, y);
		//LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		
		//obj->SetAnimationSet(ani_set);
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
		int typePlayer = atoi(tokens[8].c_str());
		obj = new Gate(x, y, switchId, playerPosX, playerPosY, playerState, isResetCamera, typePlayer);
		listObjects.push_back(obj);
		DebugOut(L"[test] add gate !\n");
		break;
	}
	case OBJECT_TYPE_GOLEM:
	{
		obj = new Golem(x,y,player);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		DebugOut(L"[test] add Golem !\n");
		break;
	}
	case OBJECT_TYPE_GUNNER:
	{
		obj = new Gunner();
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		DebugOut(L"[test] add Gunner !\n");
		break;
	}
	case OBJECT_TYPE_CENTIPEDE:
	{
		//obj = new Centipede(x,y,player);
		obj = new Centipede(x,y,player);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		DebugOut(L"[test] add centipede !\n");
		break;
	}
	case OBJECT_TYPE_DOMES:
	{
		obj = new Domes(x, y, player);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		DebugOut(L"[test] add domes !\n");
		break;
	}
	default:
		DebugOut(L"[ERRO] Invalid object type: %d\n", object_type);
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
		if (line == "[MAPTEXTURES]") {
			section = SCENE_SECTION_MAPTEXTURES; continue;
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
	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"Resources\\bbox.png", D3DCOLOR_XRGB(255, 255, 0));
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void PlayScene::Unload()
{
	for (int i = 0; i < listObjects.size(); i++)
		delete listObjects[i];
	listObjects.clear();
	for (int i = 0; i < listItems.size(); i++)
		delete listItems[i];
	listItems.clear();
	for (int i = 0; i < listEnemies.size(); i++)
		delete listEnemies[i];
	listEnemies.clear();
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

Item* PlayScene::RandomItem(float x, float y)
{

	int bagrandom = rand() % 100;
	int random = rand() % 100;
	if (random <= 30)
		return new PowerUp(x, y);
	else if (30 < random && random <= 60)
		return new PowerUp(x, y);
	else if (60< random && random <= 100)
		return new PowerUp(x, y);
}

Item* PlayScene::DropItem(EntityType createrType, float x, float y, int idCreater)
{
	if (createrType == ENEMY)
		return new PowerUp(x, y);
	return new PowerUp(x, y);
}

void PlayScene::Update(DWORD dt)
{
#pragma region Camera

	float cx, cy;
	if (typeSophia == 1)
	{
		player->GetPosition(cx, cy);
		if (player->Getx() + SCREEN_WIDTH / 2 >= mapWidth)
			cx -= mapWidth - SCREEN_WIDTH / 2;
		else
		{
			if (player->Getx() < SCREEN_WIDTH / 2)
				cx = 0;
			else
				cx -= SCREEN_WIDTH / 2;
		}
		cy -= SCREEN_HEIGHT / 2;
	}
	else if (typeSophia == 0)
	{
		sophia->GetPosition(cx, cy);
		if (sophia->Getx() + SCREEN_WIDTH / 2 >= mapWidth)
			cx -= (mapWidth - SCREEN_WIDTH / 2 + DX_GET_OUT_CAR);
		else
		{
			if (sophia->Getx() < SCREEN_WIDTH / 2 + DX_GET_OUT_CAR)
				cx = 0;
			else
				cx -= (SCREEN_WIDTH / 2 + DX_GET_OUT_CAR);
		}
		cy -= SCREEN_HEIGHT / 2;
	}
	else
	{
		playerV2->GetPosition(cx, cy);
		if (playerV2->Getx() + SCREEN_WIDTH / 2 >= mapWidth)
			cx -= mapWidth - SCREEN_WIDTH / 2;
		else
		{
			if (playerV2->Getx() < SCREEN_WIDTH / 2)
				cx = 0;
			else
				cx -= SCREEN_WIDTH / 2;
		}
		cy -= SCREEN_HEIGHT / 2;
	}
	gameCamera->SetCamPos(cx, 0.0f);//cy khi muon camera move theo y player 
	gameHUD->Update(cx, HUD_Y, player->GetHealth(), player->GetgunDam());	//move x follow camera
#pragma endregion

	if (listItems.size() > 0)
		PlayerCollideItem();
	PlayerGotGate();
	PlayerTouchEnemy();

#pragma region Objects Updates
	vector<LPGAMEENTITY> coObjects;
	for (int i = 0; i < listObjects.size(); i++)
		coObjects.push_back(listObjects[i]);
	for (int i = 0; i < listEnemies.size(); i++)
		coObjects.push_back(listEnemies[i]);
	player->Update(dt, &listObjects);
	playerV2->Update(dt, &listObjects);
	sophia->Update(dt, &listObjects);
	supBullet->Update(dt, &listObjects);
	for (int i = 0; i < listBullets.size(); i++)
	{
		bulletBigSophia[i]->Update(dt, &coObjects);
		listBullets[i]->Update(dt, &coObjects);
	}
	for (int i = 0; i < listObjects.size(); i++)
		listObjects[i]->Update(dt, &listObjects);
	for (int i = 0; i < listItems.size(); i++)
		listItems[i]->Update(dt, &listObjects);
	for (int i = 0; i < listEnemies.size(); i++)
		listEnemies[i]->Update(dt, &listObjects);
#pragma endregion

}

void PlayScene::Render()
{
	//gameMap->Draw();
	LPDIRECT3DTEXTURE9 maptextures = CTextures::GetInstance()->Get(idStage / STAGE_1 + 10);
	Game::GetInstance()->OldDraw(0,0, maptextures,0,0,mapWidth, mapHeight);
	for (int i = 0; i < listObjects.size(); i++)
		listObjects[i]->Render();
	for (int i = 0; i < listItems.size(); i++)
		listItems[i]->Render();
	for (int i = 0; i < 3; i++)
		bulletBigSophia[i]->Render();

	if (typeSophia == 2)
		playerV2->Render();
	else 
		player->Render();
	if (typeSophia == 0)
		sophia->Render();
	supBullet->Render();
	for (int i = 0; i < listBullets.size(); i++)
		listBullets[i]->Render();
	for (int i = 0; i < listEnemies.size(); i++)
		listEnemies[i]->Render();
	gameHUD->Render(player);
}

