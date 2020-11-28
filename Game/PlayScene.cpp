#include "PlayScene.h"
#include "Textures.h"
#include "Stair.h"
#include "GateV2.h"

#define MINI_SOPHIA	0
#define JASON		1
#define BIG_SOPHIA	2

#define OBJECT_TYPE_BRICK		1
#define OBJECT_TYPE_GATE		2
#define OBJECT_TYPE_GATEV2		200
#define	OBJECT_TYPE_STAIR		300

#define OBJECT_TYPE_CENTIPEDE			10
#define OBJECT_TYPE_GOLEM				11
#define OBJECT_TYPE_GUNNER				12
#define OBJECT_TYPE_DOMES				13
#define OBJECT_TYPE_FLOATERS			14
#define OBJECT_TYPE_INSECT				15
#define OBJECT_TYPE_LAVA_BRICK			16


#define DX_GET_OUT_CAR		7
#define HUD_Y				20
#define NUMBER_BULLET		3
#define DEFLECT_X_BIGSOPHIA_TO_FIRE	7
#define DEFLECT_Y_BIGSOPHIA_TO_FIRE	11
#define SPEED_CAM_WORLD1		0.223
#define SPEED_CAM_WORLD1_MINU	0.0375
#define SPEED_CAM_WORLD2		0.15
#define POSY_CAM_WORLD2	1800

#define INTRO	0
#define PLAY	1
#define END		-1

PlayScene::PlayScene() : Scene()
{
	keyHandler = new PlayScenceKeyHandler(this);
	typeSophia = 1;
	LoadBaseObjects();
	ChooseMap(STAGE_1*3);
}

void PlayScene::LoadBaseObjects()
{
	texturesFilePath = ToLPCWSTR("Resources/Scene/textures_playscene.txt");
	LoadBaseTextures();
	if (introScene == NULL)
	{
		introScene = new IntroScene(0,0);
		DebugOut(L"[INFO] intro scene CREATED! \n");
	}
	if (player == NULL)
	{
		player = new Player(44, 143.5);
		DebugOut(L"[INFO] player CREATED! \n");
	}
	if (playerV2 == NULL)
	{
		playerV2 = new PlayerV2(131, 1905);
		DebugOut(L"[INFO] playerv2 CREATED! \n");
	}
	if (sophia == NULL)
	{
		sophia = new MiniSophia(55, 100);
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
	if (supBullet == NULL)
	{
		supBullet = new ElectricBullet();
		DebugOut(L"[INFO] supBullet CREATED! \n");
	}
	if (bigBullet1 == NULL)
	{
		bigBullet1 = new BigSophiaBullet();
		listBigBullets.push_back(bigBullet1);
		DebugOut(L"[INFO] BigBullet CREATED! \n");
	}
	if (bigBullet2 == NULL)
	{
		bigBullet2 = new BigSophiaBullet();
		listBigBullets.push_back(bigBullet2);
		DebugOut(L"[INFO] BigBullet CREATED! \n");
	}
	if (bigBullet3 == NULL)
	{
		bigBullet3 = new BigSophiaBullet();
		listBigBullets.push_back(bigBullet3);
		DebugOut(L"[INFO] BigBullet CREATED! \n");
	}
	if (powerUp == NULL)
	{
		powerUp = new PowerUp(100,150);
		listItems.push_back(powerUp);
		DebugOut(L"[INFO] powerUp CREATED! \n");
	}
	else
	{
		powerUp = NULL;
		powerUp = new PowerUp(100, 150);
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

void PlayScene::GetObjectFromGrid()
{
	//for (int i = 0; i < listObjectLoad.size(); i++)
		//delete listObjectLoad[i];
	listObjectLoad.clear();
	//for (int i = 0; i < listGates.size(); i++)
	//	delete listGates[i];
	listGates.clear();
	//for (int i = 0; i < listStairs.size(); i++)
	//	delete listStairs[i];
	listStairs.clear();
	//for (int i = 0; i < listEnemies.size(); i++)
	//		delete listEnemies[i];
	listEnemies.clear();
	//for (int i = 0; i < listObjects.size(); i++)
	//	delete listObjects[i];
	grid->GetListObject(gameCamera->GetCamx(), gameCamera->GetCamy(), listObjectLoad);
	for (UINT i = 0; i < listObjectLoad.size(); i++)
	{
		if (dynamic_cast<Gate*>(listObjectLoad[i]))
			listGates.push_back(listObjectLoad[i]);
		if (dynamic_cast<GateV2*>(listObjectLoad[i]))
			listGates.push_back(listObjectLoad[i]);
		if (dynamic_cast<Stair*>(listObjectLoad[i]))
			listStairs.push_back(listObjectLoad[i]);
		if (dynamic_cast<Golem*>(listObjectLoad[i]))
			listEnemies.push_back(listObjectLoad[i]);
		if (dynamic_cast<Gunner*>(listObjectLoad[i]))
			listEnemies.push_back(listObjectLoad[i]);
		if (dynamic_cast<Centipede*>(listObjectLoad[i]))
			listEnemies.push_back(listObjectLoad[i]);
		if (dynamic_cast<Domes*>(listObjectLoad[i]))
			listEnemies.push_back(listObjectLoad[i]);
		if (dynamic_cast<Floaters*>(listObjectLoad[i]))
			listEnemies.push_back(listObjectLoad[i]);
		if (dynamic_cast<Insect*>(listObjectLoad[i]))
			listEnemies.push_back(listObjectLoad[i]);
		if (dynamic_cast<LavaBrick*>(listObjectLoad[i]))
			listEnemies.push_back(listObjectLoad[i]);
	}
}

void PlayScene::ChooseMap(int whatMap)
{
	idStage = whatMap;
	Game::GetInstance()->SetKeyHandler(this->GetKeyEventHandler());
	int convertSimple = idStage / STAGE_1;
	sceneFilePath = listSceneFilePath[convertSimple - 1];
	mapWidth = listWidth[idStage / STAGE_1 - 1];
	mapHeight = listHeight[idStage / STAGE_1 - 1];
	if (grid == NULL)
	{
		grid = new Grid(mapWidth, mapHeight);
		DebugOut(L"[INFO] GRID CREATED! \n");
	}
	else
		grid->Reset(mapWidth, mapHeight);
	totalObjectsIntoGrid.clear();
	LoadSceneObjects();
}

void PlayScene::PlayerGotGate()
{
	for (UINT i = 0; i < listGates.size(); i++)
	{
		if (listGates[i]->GetType() == EntityType::GATE)
		{
			if (player->IsCollidingObject(listGates[i]))
			{
				Gate* gate = dynamic_cast<Gate*>(listGates[i]);
				typeSophia = gate->typePlayer;
				int tempMap = gate->GetIdScene() * STAGE_1;
				float tempx = gate->newPlayerx;
				float tempy = gate->newPlayery;
				int tempState = gate->newPlayerState;
				tempNeed = gate->directionCam;
				camMap1X = gate->camPosX;
				camMap1Y = gate->camPosY;
				Unload();

				//DebugOut(L"toa do cam x %f \n ", gameCamera->GetCamx());
				//DebugOut(L"toa do cam y %f \n ", gameCamera->GetCamy());
				ChooseMap(tempMap);

				player->SetPosition(tempx, tempy);
				player->Setvx(0);
				player->Setvy(0);
				player->SetState(tempState);

			}
			else if (sophia->IsCollidingObject(listGates[i]))
			{
				Gate* gate = dynamic_cast<Gate*>(listGates[i]);
				if (gate->typePlayer==2)
					typeSophia = gate->typePlayer;
				int tempMap = gate->GetIdScene() * STAGE_1;
				float tempx = gate->newPlayerx;
				float tempy = gate->newPlayery;
				int tempState = gate->newPlayerState;
				tempNeed = gate->directionCam;
				camMap1X = gate->camPosX;
				camMap1Y = gate->camPosY;
				Unload();

				//DebugOut(L"toa do cam x %f \n ", gameCamera->GetCamx());
				//DebugOut(L"toa do cam y %f \n ", gameCamera->GetCamy());
				ChooseMap(tempMap);

				sophia->SetPosition(tempx, tempy);
				sophia->Setvx(0);
				sophia->Setvy(0);
				sophia->SetState(tempState);
			}
		}
	}
}

void PlayScene::PlayerGotCar()
{
	if (sophia->IsCollidingObject(player))
		typeSophia = 1;
}

void PlayScene::PlayerTouchStair()
{
	for (UINT i = 0; i < listStairs.size(); i++)
	{
		if (sophia->IsCollidingObject(listStairs[i]))
			isTouchStair = true;
		else
		{
			isTouchStair = false;
			sophia->isOnStair = false;
			sophia->SetState(SOPHIA_MINI_STATE_IDLE);
		}
	}
}

void PlayScene::PlayerGotGateV2()
{
	for (UINT i = 0; i < listGates.size(); i++)
	{

		if (listGates[i]->GetType() == EntityType::GATEV2)
		{
			//DebugOut(L"khong va cham %d \n", i);
			if (playerV2->IsCollidingObject(listGates[i]))
			{
				GateV2* gateV2 = dynamic_cast<GateV2*>(listGates[i]);
				playerV2->AutoRun(gateV2->directionCam);
				nCamXGo = gateV2->intoXGo;
				nCamXBack = gateV2->intoXBack;
				nCamYGo = gateV2->intoYGo;
				nCamYBack = gateV2->intoYBack;
				directMoveCam = gateV2->directionCam;
			}
		}
	}
}

void PlayScene::PlayerTouchEnemy()
{
	for (UINT i = 0; i < listEnemies.size(); i++)
	{
		if (typeSophia == JASON)
		{
			if (player->IsCollidingObject(listEnemies[i]))
				player->SetInjured(1);
			if (supBullet->IsCollidingObject(listEnemies[i]))
			{
				listEnemies[i]->AddHealth(-1);
				DebugOut(L"mau quai %d \n", listEnemies[i]->health);
			}
		}
		else if (typeSophia == MINI_SOPHIA)
		{
			if (sophia->IsCollidingObject(listEnemies[i]))
				sophia->SetInjured(1);
		}
		else if (typeSophia == BIG_SOPHIA)
		{
			if (playerV2->IsCollidingObject(listEnemies[i]))
				playerV2->SetInjured(1);
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
	if (playerV2->isAutoRun)
		return;
	switch (KeyCode)
	{
	case DIK_ESCAPE:
		DestroyWindow(Game::GetInstance()->GetWindowHandle());
	case DIK_DOWN:
		if (sophia->isOnStair == false && playScene->isTouchStair == true)
		{
			sophia->isOnStair = true;
		}
		break;
	case DIK_V:
		if (!sophia->isOnStair)
			sophia->SetState(SOPHIA_MINI_STATE_CRAWL);
		break;
	case DIK_UP:
		if (sophia->isOnStair == false && playScene->isTouchStair == true)
		{
			sophia->isOnStair = true;
		}
		break;
	case DIK_SPACE:
		if (typeSophia == JASON)
			player->SetState(SOPHIA_STATE_JUMP);
		else if (typeSophia == MINI_SOPHIA)
			sophia->SetState(SOPHIA_MINI_STATE_JUMP);
		break;
	case DIK_A:
		playScene->Unload();
		playScene->ChooseMap(STAGE_1);
		player->SetPosition(30, 60);
		player->SetHealth(MAX_HEALTH);
		player->isDoneDeath = false;
		player->isDeath = false;
		playScene->typeSophia = JASON;
		break;
	case DIK_Q:
		playScene->typeSophia = BIG_SOPHIA;
		playerV2->SetPosition(30, 60);
		break;
	case DIK_Z:
		if (typeSophia == JASON)
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
		else if (typeSophia == MINI_SOPHIA)
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
			for (int i = 0; i < playScene->listBigBullets.size(); i++)
			{
				if (playScene->listBigBullets[i]->isDone == true)
				{
					if (playScene->listBigBullets[i]->damage <4)
						playScene->listBigBullets[i]->BigSophiaFire(direction, directionY, x + 2 * direction * DEFLECT_X_BIGSOPHIA_TO_FIRE, y + DEFLECT_Y_BIGSOPHIA_TO_FIRE + 2*directionY*DEFLECT_Y_BIGSOPHIA_TO_FIRE, 2);
					else
						playScene->listBigBullets[i]->BigSophiaFire(direction, directionY, x, y + DEFLECT_Y_BIGSOPHIA_TO_FIRE /2 +  directionY * DEFLECT_Y_BIGSOPHIA_TO_FIRE, 2);
						//playScene->listBigBullets[i]->BigSophiaFire(direction, directionY, x + 2 * direction * DEFLECT_X_BIGSOPHIA_TO_FIRE, y + DEFLECT_Y_BIGSOPHIA_TO_FIRE /2+ 2 * directionY * DEFLECT_Y_BIGSOPHIA_TO_FIRE, dame);
					//DebugOut(L"toa do x %f \n", playScene->listBigBullets[i]->x);
					//DebugOut(L"toa do y %f \n", playScene->listBigBullets[i]->x);
					break;
				}
			}

		}
		break;
	case DIK_X:
		supBullet->Fire(1, direction, isTargetTop, x, y + 17);
		break;
	case DIK_U:
		if (typeSophia == MINI_SOPHIA)
			playScene->PlayerGotCar();
		if (typeSophia == JASON)
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
		for (int i = 0; i < playScene->listBigBullets.size(); i++)
		{
			if (playScene->listBigBullets[i]->GetBBARGB() == 0)
				playScene->listBigBullets[i]->SetBBARGB(200);
			else
				playScene->listBigBullets[i]->SetBBARGB(0);
		}
		for (int i = 0; i < playScene->listGates.size(); i++)
		{
			if (playScene->listGates[i]->GetBBARGB() == 0)
				playScene->listGates[i]->SetBBARGB(200);
			else
				playScene->listGates[i]->SetBBARGB(0);
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
	PlayerV2* playerV2 = ((PlayScene*)scence)->playerV2;
	PlayScene* playScene = dynamic_cast<PlayScene*>(scence);
	vector<LPGAMEENTITY> listObj = ((PlayScene*)scence)->listObjects;
	if (playerV2->isAutoRun)
		return;
	switch (KeyCode)
	{
	case DIK_UP:
		//player->SetState(SOPHIA_STATE_GUN_UNFLIP);
		player->SetPressUp(false);
		player->SetState(SOPHIA_STATE_GUN_UNFLIP);
		playerV2->Setvy(0);
		break;
	case DIK_DOWN:
		playerV2->Setvy(0);
		break;
	case DIK_SPACE:
		player->SetPressSpace(false);
		break;
	case DIK_RIGHT:
	case DIK_LEFT:
		player->SetState(SOPHIA_STATE_IDLE2);
		playerV2->Setvx(0);
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
	if (typeSophia == MINI_SOPHIA)
	{
		if (sophia->isOnStair)
		{
			if (Game::GetInstance()->IsKeyDown(DIK_UP))
			{
				sophia->SetState(SOPHIA_MINI_STATE_UP_STAIR);
			}
			else if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
			{
				sophia->SetState(SOPHIA_MINI_STATE_DOWN_STAIR);
			}
			else if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
				sophia->SetState(SOPHIA_MINI_STATE_WALKING_LEFT);
			else if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
				sophia->SetState(SOPHIA_MINI_STATE_WALKING_RIGHT);
			else
			{
				sophia->SetState(SOPHIA_MINI_STATE_IDLE_STAIR);
				DebugOut(L"idle stair 1");
			}
		}
		else
		{
			if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
				sophia->SetState(SOPHIA_MINI_STATE_WALKING_LEFT);
			else if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
				sophia->SetState(SOPHIA_MINI_STATE_WALKING_RIGHT);
			else
			{
				if (sophia->isCrawl == false)
				{
					sophia->SetState(SOPHIA_MINI_STATE_IDLE);
				}
				else
				{
					//if (!sophia->isOnStair)
					sophia->SetState(SOPHIA_MINI_STATE_CRAWL_STOP);
				}
			}
		}
	}
	if (!playerV2->isAutoRun)
	{
#pragma endregion
		if (player->GetState() == SOPHIA_STATE_DIE) return;

		if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
		{
			if (typeSophia == JASON)
				player->SetState(SOPHIA_STATE_WALKING_RIGHT);
			else
			{
				playerV2->SetState(SOPHIA_BIG_STATE_WALKING_RIGHT);
			}
		}
		else if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			if (typeSophia == JASON)
				player->SetState(SOPHIA_STATE_WALKING_LEFT);
			else
				playerV2->SetState(SOPHIA_BIG_STATE_WALKING_LEFT);
		}
		else if (Game::GetInstance()->IsKeyDown(DIK_UP))
		{
			if (typeSophia == BIG_SOPHIA)
				playerV2->SetState(SOPHIA_BIG_STATE_WALKING_TOP);
		}
		else if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
		{
			if (typeSophia == BIG_SOPHIA)
				playerV2->SetState(SOPHIA_BIG_STATE_WALKING_BOT);
		}
		else
		{
			if (typeSophia == JASON)
				player->SetState(SOPHIA_STATE_IDLE);
			else
				playerV2->SetState(SOPHIA_BIG_STATE_IDLE);
		}

		if (Game::GetInstance()->IsKeyDown(DIK_SPACE))
		{
			if (typeSophia == JASON)
				player->SetPressSpace(true);
		}

		if (Game::GetInstance()->IsKeyDown(DIK_UP))
		{
			if (typeSophia == JASON)
				player->SetPressUp(true);
		}
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

	listWidth.push_back(atoi(tokens[1].c_str()));
	listHeight.push_back(atoi(tokens[2].c_str()));
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
	//Unit *unit = NULL;
	switch (object_type)
	{
	case OBJECT_TYPE_BRICK:
	{
		obj = new Brick(atof(tokens[4].c_str()),atof(tokens[5].c_str()));
		obj->SetPosition(x, y);
		//LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		
		//obj->SetAnimationSet(ani_set);
		listObjects.push_back(obj);
		//totalObjectsIntoGrid.push_back(obj);
		DebugOut(L"[test] add brick %d !\n", (int)(x/ (SCREEN_WIDTH/2)));
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
		float camX = atoi(tokens[9].c_str());
		int camY = atoi(tokens[10].c_str());
		obj = new Gate(x, y, switchId, playerPosX, playerPosY, playerState, isResetCamera, typePlayer, camX, camY);
		//listGates.push_back(obj);
		totalObjectsIntoGrid.push_back(obj);
		DebugOut(L"[test] add gate %d !\n", (int)(x / (SCREEN_WIDTH / 2)));
		break;
	}
	case OBJECT_TYPE_GATEV2:
	{
		int direct = atoi(tokens[7].c_str());
		float newCamXGo = atoi(tokens[3].c_str());
		float newCamXBack = atoi(tokens[4].c_str());
		float newCamYGo = atoi(tokens[5].c_str());
		float newCamYBack = atoi(tokens[6].c_str());
		obj = new GateV2(x, y, newCamXGo, newCamXBack, newCamYGo, newCamYBack, direct);
		//listGates.push_back(obj);
		totalObjectsIntoGrid.push_back(obj);
		DebugOut(L"[test] add gatev2 %d !\n", (int)(x / (SCREEN_WIDTH / 2)));
		break;
	}
	case OBJECT_TYPE_STAIR:
	{
		obj = new Stair(x, y);
		//listStairs.push_back(obj);
		totalObjectsIntoGrid.push_back(obj);
		DebugOut(L"[test] add gatev2 %d !\n", (int)(x / (SCREEN_WIDTH / 2)));;
		break;
	}
	case OBJECT_TYPE_GOLEM:
	{
		obj = new Golem(x,y,player);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		//listEnemies.push_back(obj);
		totalObjectsIntoGrid.push_back(obj);
		DebugOut(L"[test] add Golem %d !\n", (int)(x / (SCREEN_WIDTH / 2)));
		break;
	}
	case OBJECT_TYPE_GUNNER:
	{
		obj = new Gunner();
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		//listEnemies.push_back(obj);
		totalObjectsIntoGrid.push_back(obj);
		DebugOut(L"[test] add Gunner %d !\n", (int)(x / (SCREEN_WIDTH / 2)));
		break;
	}
	case OBJECT_TYPE_CENTIPEDE:
	{
		//obj = new Centipede(x,y,player);
		obj = new Centipede(x,y,player);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		//listEnemies.push_back(obj);
		totalObjectsIntoGrid.push_back(obj);
		DebugOut(L"[test] add centipede %d !\n", (int)(x / (SCREEN_WIDTH / 2)));
		break;
	}
	case OBJECT_TYPE_DOMES:
	{
		obj = new Domes(x, y, player);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		//listEnemies.push_back(obj);
		totalObjectsIntoGrid.push_back(obj);
		DebugOut(L"[test] add domes %d !\n", (int)(x / (SCREEN_WIDTH / 2)));
		break;
	}
	case OBJECT_TYPE_FLOATERS:
	{
		obj = new Floaters(x, y, player);

		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		//listEnemies.push_back(obj);
		totalObjectsIntoGrid.push_back(obj);
		DebugOut(L"[test] add floaters %d !\n", (int)(x / (SCREEN_WIDTH / 2)));
		break;
	}
	case OBJECT_TYPE_INSECT:
	{
		obj = new Insect(x, y, player);

		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		//listEnemies.push_back(obj);
		totalObjectsIntoGrid.push_back(obj);
		DebugOut(L"[test] add Insect %d !\n", (int)(x / (SCREEN_WIDTH / 2)));;
		break;
	}
	case OBJECT_TYPE_LAVA_BRICK:
	{
		obj = new LavaBrick();
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		//listEnemies.push_back(obj);
		totalObjectsIntoGrid.push_back(obj);
		DebugOut(L"[test] add Insect %d !\n", (int)(x / (SCREEN_WIDTH / 2)));;
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
		}
	}

	f.close();
	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"Resources\\bbox.png", D3DCOLOR_XRGB(255, 255, 0));
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
	grid->PushObjectIntoGrid(totalObjectsIntoGrid);
	DebugOut(L"[INFO] Done push object into grid \n");

}

void PlayScene::Unload()
{
	//for (int i = 0; i < listObjectLoad.size(); i++)
		//delete listObjectLoad[i];
	//listObjectLoad.clear();
	//for (int i = 0; i < totalObjectsIntoGrid.size(); i++)
		//delete totalObjectsIntoGrid[i];
	//totalObjectsIntoGrid.clear();
	for (int i = 0; i < listObjects.size(); i++)
		delete listObjects[i];
	listObjects.clear();
	for (int i = 0; i < listGates.size(); i++)
		delete listGates[i];
	listGates.clear();
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
	mapWidth = listWidth[idStage / STAGE_1 - 1];
	mapHeight = listHeight[idStage / STAGE_1 - 1];
	if (typeScene == -1)
	{
		if (posX < (509-270))
		{
			posX += 0.05 * dt;
		}
		gameCamera->SetCamPos(posX, 0);
	}
	else
	{
		if (typeSophia == JASON)
		{
			player->GetPosition(cx, cy);
			if (tempNeed)
			{
				//timeResetCam += dt;
				gameCamera->SetCamPos(camMap1X, camMap1Y);
				posY = camMap1Y;
				//if (timeResetCam > 1000)
				tempNeed = 0;
			}
			else
			{
				if (player->Getx() + SCREEN_WIDTH / 2 >= mapWidth)
					cx = mapWidth - SCREEN_WIDTH;
				else
				{
					if (player->Getx() < SCREEN_WIDTH / 2)
						cx = 0;
					else
						cx -= SCREEN_WIDTH / 2;
				}

				if (cy + SCREEN_HEIGHT >= mapHeight)
				{

					cy = mapHeight - SCREEN_HEIGHT;
					posY = cy;
				}
				else
				{
					if (player->Gety() < SCREEN_HEIGHT / 3)
					{
						posY = 0;
					}
					else
					{
						//DebugOut(L"cy - posY %f \n", cy - posY);
						if ((cy - posY) < (SCREEN_HEIGHT / 4))
						{
							posY -= SPEED_CAM_WORLD1 * dt;
						}
						if ((cy - posY) > (SCREEN_HEIGHT / 2))
						{
							posY += SPEED_CAM_WORLD1 * dt;
						}
					}
				}
				//DebugOut(L"toa do cam x %f \n ", cx);
				//DebugOut(L"toa do cam y %f \n ", posY);
				gameCamera->SetCamPos(cx, posY);
			}

		}
		else if (typeSophia == MINI_SOPHIA)
		{
			sophia->GetPosition(cx, cy);
			if (tempNeed)
			{
				gameCamera->SetCamPos(camMap1X, camMap1Y);
				posY = camMap1Y;
				tempNeed = 0;
			}
			else
			{
				if (sophia->Getx() + SCREEN_WIDTH / 2 >= mapWidth)
					cx = mapWidth - SCREEN_WIDTH;
				else
				{
					if (sophia->Getx() < SCREEN_WIDTH / 2)
						cx = 0;
					else
						cx -= SCREEN_WIDTH / 2;
				}

				if (posY + SCREEN_HEIGHT >= mapHeight)
				{

					cy = mapHeight - SCREEN_HEIGHT;
					posY = cy;
					//DebugOut(L"trong hop tren = %d \n", mapHeight);
					//DebugOut(L"screen height= %d \n", SCREEN_HEIGHT);
				}
				else
				{
					if (sophia->Gety() < SCREEN_HEIGHT / 3)
					{
						posY = 0;
						//DebugOut(L"trong hop giua = %d \n", mapHeight);
					}
					else
					{
						//DebugOut(L"cy - posY %f \n", cy - posY);
						if ((cy - posY) < (SCREEN_HEIGHT / 4))
						{
							if (sophia->isOnStair)
								posY -= SPEED_CAM_WORLD1_MINU * dt;
							else
								posY -= SPEED_CAM_WORLD1 * dt;
						}
						if ((cy - posY) > (SCREEN_HEIGHT / 2))
						{
							if (sophia->isOnStair)
								posY += SPEED_CAM_WORLD1_MINU * dt;
							else
								posY += SPEED_CAM_WORLD1 * dt;
						}
						//DebugOut(L"trong hop duoi = %d \n", mapHeight);
					}
				}
				//DebugOut(L"toa do cam x %f \n ", cx);
				//DebugOut(L"toa do cam y %f \n ", posY);
				gameCamera->SetCamPos(cx, posY);
			}
		}
		else
		{
			//DebugOut(L"xxxxx %d \n", playerV2->direction);
			if (directMoveCam == -1)
			{
				posX = 0;
				posY = POSY_CAM_WORLD2;
				directMoveCam = 0;
			}
			PlayerGotGateV2();
			if (directMoveCam == 1 || directMoveCam == 2)
			{
				if (playerV2->direction > 0)
				{
					if (posX < nCamXGo)
						posX += SPEED_CAM_WORLD2 * dt;
					else
					{
						posX = nCamXGo + 1;
						directMoveCam = 0;
					}
				}
				else if (playerV2->direction < 0)
				{
					if (posX > nCamXBack)
						posX -= SPEED_CAM_WORLD2 * dt;
					else
					{
						posX = nCamXBack - 1;
						directMoveCam = 0;
					}
				}
				else if (playerV2->directionY < 0)
				{
					if (posY > nCamYGo)
						posY -= SPEED_CAM_WORLD2 * dt;
					else
					{
						posY = nCamYGo - 1;
						directMoveCam = 0;
					}
				}
				else if (playerV2->directionY > 0)
				{
					if (posY < nCamYBack)
						posY += SPEED_CAM_WORLD2 * dt;
					else
					{
						posY = nCamYBack + 1;
						directMoveCam = 0;
					}
				}
			}
			//DebugOut(L"cam oldX, %f \n", oldPosX);
			//DebugOut(L"cam X, %f \n", posX);
			gameCamera->SetCamPos(posX, posY);
		}

		if (typeSophia == JASON)
			gameHUD->Update(cx, HUD_Y, player->GetHealth(), player->GetgunDam());	//move x follow camera
		if (typeSophia == MINI_SOPHIA)
			gameHUD->Update(cx, HUD_Y, sophia->GetHealth(), sophia->GetgunDam());	//move x follow camera
		//if (typeSophia == BIG_SOPHIA)
		//	gameHUD->Update(cx, HUD_Y, playerV2->GetHealth(), playerV2->GetgunDam());	//move x follow camera
#pragma endregion
		GetObjectFromGrid();
		if (listItems.size() > 0)
			PlayerCollideItem();
		PlayerGotGate();
		PlayerTouchEnemy();
		PlayerTouchStair();

#pragma region Objects Updates
		vector<LPGAMEENTITY> coObjects;
		//introScene->Update(dt, &listObjects);
		if (typeScene == 0)
		{
			return;
		}
		for (int i = 0; i < listObjects.size(); i++)
			coObjects.push_back(listObjects[i]);
		for (int i = 0; i < listEnemies.size(); i++)
			coObjects.push_back(listEnemies[i]);
		if (typeSophia == BIG_SOPHIA)
			playerV2->Update(dt, &listObjects);
		else
		{
			if (typeSophia == MINI_SOPHIA)
				sophia->Update(dt, &listObjects);
			else
				player->Update(dt, &listObjects);
		}
		supBullet->Update(dt, &listObjects);
		for (int i = 0; i < listBullets.size(); i++)
			listBullets[i]->Update(dt, &coObjects);
		for (int i = 0; i < listStairs.size(); i++)
			listStairs[i]->Update(dt, &listObjects);
		for (int i = 0; i < listBigBullets.size(); i++)
			listBigBullets[i]->Update(dt, &coObjects);
		for (int i = 0; i < listObjects.size(); i++)
			listObjects[i]->Update(dt, &listObjects);
		for (int i = 0; i < listItems.size(); i++)
			listItems[i]->Update(dt, &listObjects);
		for (int i = 0; i < listEnemies.size(); i++)
			listEnemies[i]->Update(dt, &listObjects);
		if (sophia->isDoneDeath == true || player->isDoneDeath == true || playerV2->isDoneDeath == true)
		{
			Unload();
			ChooseMap(STAGE_1);
			typeSophia = JASON;
			player->SetPosition(30, 60);
			player->SetHealth(MAX_HEALTH);
			player->isDoneDeath = false;
			player->isDeath = false;

			playerV2->SetPosition(30, 60);
			playerV2->SetHealth(MAX_HEALTH);
			playerV2->isDoneDeath = false;
			playerV2->isDeath = false;

			sophia->SetPosition(30, 60);
			sophia->SetHealth(MAX_HEALTH);
			sophia->isDoneDeath = false;
			sophia->isDeath = false;
		}
	}
#pragma endregion
}

void PlayScene::Render()
{
	if (typeScene == INTRO)
	{
		introScene->SetType(0);
		introScene->Render();
		if (introScene->animationSet->at(0)->GetFrame() >= 120)
			typeScene = 1;
	}
	else if (typeScene == END)
	{
		introScene->SetType(1);
		introScene->Render();
	}
	else
	{
		LPDIRECT3DTEXTURE9 maptextures = CTextures::GetInstance()->Get(idStage / STAGE_1 + 10);
		Game::GetInstance()->OldDraw(0, 0, maptextures, 0, 0, mapWidth, mapHeight);
		for (int i = 0; i < listObjects.size(); i++)
			listObjects[i]->Render();
		for (int i = 0; i < listItems.size(); i++)
			listItems[i]->Render();
		for (int i = 0; i < listBigBullets.size(); i++)
			listBigBullets[i]->Render();
		for (int i = 0; i < listGates.size(); i++)
			listGates[i]->Render();
		for (int i = 0; i < listStairs.size(); i++)
			listStairs[i]->Render();
		if (typeSophia == BIG_SOPHIA)
			playerV2->Render();
		else
			player->Render();
		if (typeSophia == MINI_SOPHIA)
			sophia->Render();
		supBullet->Render();
		for (int i = 0; i < listBullets.size(); i++)
			listBullets[i]->Render();
		for (int i = 0; i < listEnemies.size(); i++)
			listEnemies[i]->Render();
		gameHUD->Render(player);
	}
}

