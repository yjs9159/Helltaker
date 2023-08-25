#include "yaChapter7.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaTexture.h"
#include "yaResources.h"
#include "yaBackGround.h"
#include "yaSpriteRenderer.h"
#include "yaTransform.h"
#include "yaObject.h"
#include "yaPlayer.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaMonster.h"
#include "yaNpc.h"
#include "yaRock.h"
#include "yaKey.h"
#include "yaLockBox.h"
#include "yaSceneChange.h"
#include "yaFire.h"

namespace ya
{
	int Chapter7::MapInfo7[9][8] =
	{
		// 0 => 바닥
		// 1 => wall
		// 2 => player
		// 3 => monster
		// 4 => rock
		{ 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 0, 0, 1, 1 },
		{ 1, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 4, 4, 4, 1 },
		{ 1, 3, 4, 0, 3, 4, 0, 1 },
		{ 1, 0, 1, 3, 0, 0, 2, 1 },
		{ 1, 0, 1, 1, 0, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	ya::Chapter7::Chapter7()
		: LeftTop(Vector2(350.0f + 72 / 2, 58.0f + 68 / 2))
	{
	}

	ya::Chapter7::~Chapter7()
	{
	}

	void ya::Chapter7::Initialize()
	{
		// Scene Change 생성 및 애니메이션 재생
		SceneChange* S_C = object::Instantiate<SceneChange>(eLayerType::SceneChange);

		Transform* tr_SC = S_C->GetComponent<Transform>();
		tr_SC->SetPosition(Vector2(640.0f, 360.0f));

		Animator* at_SC = S_C->AddComponent<Animator>();
		at_SC->CreateAnimationFolder(L"Change", L"..\\Resources\\Texture\\levelchange\\bmp", Vector2(0.0f, 0.0f));
		at_SC->PlayAnimation(L"Change", false);
		at_SC->SetScale(Vector2(0.7f, 0.7f));


		Texture* Chapter7 = Resources::Load<Texture>(L"Chapter7"
			, L"..\\Resources\\Texture\\chapterbg\\chapterBG0007.bmp");


		BackGround* bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(Chapter7);
		bgsr->SetScale(Vector2(0.7f, 0.7f));
		bgsr->SetAffectCamera(false);
		//bgsr->SetAlpha(0.2f);
		bg->GetComponent<Transform>()->SetPosition(Vector2(640.0f, 360.0f));


		Player* player = object::Instantiate<Player>(eLayerType::Player); // 플레이어 생성
		Transform* tr = player->GetComponent<Transform>();
		tr->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 6, LeftTop.y + MOVE_TILE_HEIGHT * 5)); // 플레이어 시작위치

		Animator* at = player->AddComponent<Animator>();
		at->CreateAnimationFolder(L"player_rightidle", L"..\\Resources\\Texture\\player\\player_idle\\right_idle", Vector2(0.0f, 10.0f));
		at->CreateAnimationFolder(L"player_leftidle", L"..\\Resources\\Texture\\player\\player_idle\\left_idle", Vector2(0.0f, 10.0f));
		at->CreateAnimationFolder(L"player_rightrun", L"..\\Resources\\Texture\\player\\player_run\\right_run", Vector2(0.0f, 10.0f));
		at->CreateAnimationFolder(L"player_leftrun", L"..\\Resources\\Texture\\player\\player_run\\left_run", Vector2(0.0f, 10.0f));
		at->CreateAnimationFolder(L"player_rightattack", L"..\\Resources\\Texture\\player\\player_attack\\right_attack", Vector2(0.0f, -10.0f));
		at->CreateAnimationFolder(L"player_leftattack", L"..\\Resources\\Texture\\player\\player_attack\\left_attack", Vector2(0.0f, -10.0f));
		at->CreateAnimationFolder(L"player_rightsuccess", L"..\\Resources\\Texture\\player\\player_success\\right_success", Vector2(0.0f, -10.0f));
		at->PlayAnimation(L"player_rightidle", true);
		at->SetScale(Vector2(0.8f, 0.8f));
		at->SetAffectedCamera(true);

		Collider* col = player->AddComponent<Collider>();
		col->SetSize(Vector2(85.0f, 90.0f));
		col->SetOffset(Vector2(0.0f, -10.0f));

		Monster* monster1 = object::Instantiate<Monster>(eLayerType::Monster); // 몬스터1 생성
		Transform* tr_M1 = monster1->GetComponent<Transform>();
		tr_M1->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 3, LeftTop.y + MOVE_TILE_HEIGHT * 5)); // 몬스터1 시작위치

		Animator* at_M1 = monster1->AddComponent<Animator>();
		at_M1->CreateAnimationFolder(L"Monster_RightIdle", L"..\\Resources\\Texture\\obstacle\\undead_idle\\right_idle", Vector2(0.0f, -10.0f));
		at_M1->PlayAnimation(L"Monster_RightIdle", true);
		at_M1->SetScale(Vector2(0.8f, 0.8f));

		col = monster1->AddComponent<Collider>();
		col->SetSize(Vector2(80.0f, 80.0f));

		Monster* monster2 = object::Instantiate<Monster>(eLayerType::Monster); // 몬스터2 생성
		Transform* tr_M2 = monster2->GetComponent<Transform>();
		tr_M2->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 4, LeftTop.y + MOVE_TILE_HEIGHT * 4)); // 몬스터2 시작위치

		Animator* at_M2 = monster2->AddComponent<Animator>();
		at_M2->CreateAnimationFolder(L"Monster_RightIdle", L"..\\Resources\\Texture\\obstacle\\undead_idle\\right_idle", Vector2(0.0f, -10.0f));
		at_M2->PlayAnimation(L"Monster_RightIdle", true);
		at_M2->SetScale(Vector2(0.8f, 0.8f));

		col = monster2->AddComponent<Collider>();
		col->SetSize(Vector2(80.0f, 80.0f));

		Monster* monster3 = object::Instantiate<Monster>(eLayerType::Monster); // 몬스터3 생성

		Transform* tr_M3 = monster3->GetComponent<Transform>();
		tr_M3->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 1, LeftTop.y + MOVE_TILE_HEIGHT * 4)); // 몬스터3 시작위치

		Animator* at_M3 = monster3->AddComponent<Animator>();
		at_M3->CreateAnimationFolder(L"Monster_RightIdle", L"..\\Resources\\Texture\\obstacle\\undead_idle\\right_idle", Vector2(0.0f, -10.0f));
		at_M3->PlayAnimation(L"Monster_RightIdle", true);
		at_M3->SetScale(Vector2(0.8f, 0.8f));

		col = monster3->AddComponent<Collider>();
		col->SetSize(Vector2(80.0f, 80.0f));


		Npc* justice = object::Instantiate<Npc>(eLayerType::Npc); // Npc pandemonica 생성

		Transform* tr_justice = justice->GetComponent<Transform>();
		tr_justice->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 4, LeftTop.y + MOVE_TILE_HEIGHT * 1)); // Npc pandemonica 시작위치

		Animator* at_justice = justice->AddComponent<Animator>();
		at_justice->CreateAnimationFolder(L"justice ", L"..\\Resources\\Texture\\npc\\justice", Vector2(0.0f, -10.0f));
		at_justice->PlayAnimation(L"justice ", true);
		at_justice->SetScale(Vector2(0.8f, 0.8f));

		col = justice->AddComponent<Collider>();
		col->SetSize(Vector2(80.0f, 80.0f));


		// Rock 1 생성 및 이미지 로드
		Rock* rock1 = object::Instantiate<Rock>(eLayerType::Rock);

		Transform* tr_Rock1 = rock1->GetComponent<Transform>();
		tr_Rock1->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 2, LeftTop.y + MOVE_TILE_HEIGHT * 4));

		Texture* Rock1 = Resources::Load<Texture>(L"Rock1_7"
			, L"..\\Resources\\Texture\\obstacle\\rock\\Rock004.png");

		SpriteRenderer* Rock1sr = rock1->AddComponent<SpriteRenderer>();
		Rock1sr->SetImage(Rock1);
		Rock1sr->SetScale(Vector2(0.75f, 0.75f));


		// Rock 2 생성 및 이미지 로드
		Rock* rock2 = object::Instantiate<Rock>(eLayerType::Rock);

		Transform* tr_Rock2 = rock2->GetComponent<Transform>();
		tr_Rock2->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 4, LeftTop.y + MOVE_TILE_HEIGHT * 3));

		Texture* Rock2 = Resources::Load<Texture>(L"Rock2_7"
			, L"..\\Resources\\Texture\\obstacle\\rock\\Rock001.png");

		SpriteRenderer* Rock2sr = rock2->AddComponent<SpriteRenderer>();
		Rock2sr->SetImage(Rock2);
		Rock2sr->SetScale(Vector2(0.75f, 0.75f));


		// Rock 3 생성 및 이미지 로드
		Rock* rock3 = object::Instantiate<Rock>(eLayerType::Rock);

		Transform* tr_Rock3 = rock3->GetComponent<Transform>();
		tr_Rock3->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 5, LeftTop.y + MOVE_TILE_HEIGHT * 3));

		Texture* Rock3 = Resources::Load<Texture>(L"Rock3_7"
			, L"..\\Resources\\Texture\\obstacle\\rock\\Rock005.png");

		SpriteRenderer* Rock3sr = rock3->AddComponent<SpriteRenderer>();
		Rock3sr->SetImage(Rock3);
		Rock3sr->SetScale(Vector2(0.75f, 0.75f));


		// Rock 4 생성 및 이미지 로드
		Rock* rock4 = object::Instantiate<Rock>(eLayerType::Rock);

		Transform* tr_Rock4 = rock4->GetComponent<Transform>();
		tr_Rock4->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 5, LeftTop.y + MOVE_TILE_HEIGHT * 4));

		Texture* Rock4 = Resources::Load<Texture>(L"Rock4_7"
			, L"..\\Resources\\Texture\\obstacle\\rock\\Rock008.png");

		SpriteRenderer* Rock4sr = rock4->AddComponent<SpriteRenderer>();
		Rock4sr->SetImage(Rock4);
		Rock4sr->SetScale(Vector2(0.75f, 0.75f));


		// Rock 5 생성 및 이미지 로드
		Rock* rock5 = object::Instantiate<Rock>(eLayerType::Rock);

		Transform* tr_Rock5 = rock5->GetComponent<Transform>();
		tr_Rock5->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 6, LeftTop.y + MOVE_TILE_HEIGHT * 3));

		Texture* Rock5 = Resources::Load<Texture>(L"Rock5_7"
			, L"..\\Resources\\Texture\\obstacle\\rock\\Rock003.png");

		SpriteRenderer* Rock5sr = rock5->AddComponent<SpriteRenderer>();
		Rock5sr->SetImage(Rock5);
		Rock5sr->SetScale(Vector2(0.75f, 0.75f));


		// Key 생성 및 이미지 로드
		Key* myKey = object::Instantiate<Key>(eLayerType::myKey);

		Transform* tr_Key = myKey->GetComponent<Transform>();
		tr_Key->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 2, LeftTop.y + MOVE_TILE_HEIGHT * 3));

		Animator* at_Key = myKey->AddComponent<Animator>();
		at_Key->CreateAnimationFolder(L"myKey", L"..\\Resources\\Texture\\obstacle\\Key", Vector2(10.0f, 0.0f));
		at_Key->PlayAnimation(L"myKey", true);
		at_Key->SetScale(Vector2(0.8f, 0.8f));


		// LockBox 생성 및 이미지 로드
		LockBox* lockbox = object::Instantiate<LockBox>(eLayerType::LockBox);

		Transform* tr_Box = lockbox->GetComponent<Transform>();
		tr_Box->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 5, LeftTop.y + MOVE_TILE_HEIGHT * 2));

		Texture* Box = Resources::Load<Texture>(L"Box"
			, L"..\\Resources\\Texture\\obstacle\\lockbox\\lockbox001.png");

		SpriteRenderer* sr_Box = lockbox->AddComponent<SpriteRenderer>();
		sr_Box->SetImage(Box);
		sr_Box->SetScale(Vector2(0.75f, 0.75f));


		// Fire 1 base
		Fire* Fire7_1base = object::Instantiate<Fire>(eLayerType::Fire);

		Transform* tr7_1Firebase = Fire7_1base->GetComponent<Transform>();
		tr7_1Firebase->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 0 + 3, LeftTop.y + MOVE_TILE_HEIGHT * 5 + 6));

		Texture* Fire7_1Base = Resources::Load<Texture>(L"Fire7_1Base"
			, L"..\\Resources\\Texture\\fire\\FLAMEbase0001.png");

		SpriteRenderer* Fire7_1Sr = Fire7_1base->AddComponent<SpriteRenderer>();
		Fire7_1Sr->SetImage(Fire7_1Base);
		Fire7_1Sr->SetScale(Vector2(0.75f, 0.75f));


		// Fire 1
		Fire* Fire7_1 = object::Instantiate<Fire>(eLayerType::Fire);

		Transform* tr7_1Fire = Fire7_1->GetComponent<Transform>();
		tr7_1Fire->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 0, LeftTop.y + MOVE_TILE_HEIGHT * 5));

		Animator* at7_1Fire = Fire7_1->AddComponent<Animator>();
		at7_1Fire->CreateAnimationFolder(L"Fire7_1", L"..\\Resources\\Texture\\fire\\fire", Vector2(4.0f, -30.0f));
		at7_1Fire->PlayAnimation(L"Fire7_1", true);
		at7_1Fire->SetScale(Vector2(0.4f, 0.5f));


		// Fire 2 base
		Fire* Fire7_2base = object::Instantiate<Fire>(eLayerType::Fire);

		Transform* tr7_2Firebase = Fire7_2base->GetComponent<Transform>();
		tr7_2Firebase->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 6, LeftTop.y + MOVE_TILE_HEIGHT * 0 - 5));

		Texture* Fire7_2Base = Resources::Load<Texture>(L"Fire7_2Base"
			, L"..\\Resources\\Texture\\fire\\FLAMEbase0002.png");

		SpriteRenderer* Fire7_2Sr = Fire7_2base->AddComponent<SpriteRenderer>();
		Fire7_2Sr->SetImage(Fire7_2Base);
		Fire7_2Sr->SetScale(Vector2(0.75f, 0.75f));


		// Fire 3 base
		Fire* Fire7_3base = object::Instantiate<Fire>(eLayerType::Fire);

		Transform* tr7_3Firebase = Fire7_3base->GetComponent<Transform>();
		tr7_3Firebase->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 7 + 3, LeftTop.y + MOVE_TILE_HEIGHT * 1 - 36));

		Texture* Fire7_3Base = Resources::Load<Texture>(L"Fire7_3Base"
			, L"..\\Resources\\Texture\\fire\\FLAMEbase0001.png");

		SpriteRenderer* Fire7_3Sr = Fire7_3base->AddComponent<SpriteRenderer>();
		Fire7_3Sr->SetImage(Fire7_3Base);
		Fire7_3Sr->SetScale(Vector2(0.75f, 0.75f));


		// Fire 2
		Fire* Fire7_2 = object::Instantiate<Fire>(eLayerType::Fire);

		Transform* tr7_2Fire = Fire7_2->GetComponent<Transform>();
		tr7_2Fire->SetPosition(Vector2(LeftTop.x + MOVE_TILE_WIDTH * 7, LeftTop.y + MOVE_TILE_HEIGHT * 0));

		Animator* at7_2Fire = Fire7_2->AddComponent<Animator>();
		at7_2Fire->CreateAnimationFolder(L"Fire7_2", L"..\\Resources\\Texture\\fire\\fire", Vector2(5.0f, -7.0f));
		at7_2Fire->PlayAnimation(L"Fire7_2", true);
		at7_2Fire->SetScale(Vector2(0.4f, 0.5f));
	}

	void ya::Chapter7::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::H))
		{
			SceneManager::LoadScene(L"HomeScene");
		}
		if (Input::GetKeyDown(eKeyCode::T))
		{
			SceneManager::LoadScene(L"TitleScene");
		}
		if (Input::GetKeyDown(eKeyCode::E))
		{
			SceneManager::LoadScene(L"EndingScene");
		}
		if (Input::GetKeyDown(eKeyCode::Chapter1))
		{
			SceneManager::LoadScene(L"Chapter1");
		}
		if (Input::GetKeyDown(eKeyCode::Chapter2))
		{
			SceneManager::LoadScene(L"Chapter2");
		}
		if (Input::GetKeyDown(eKeyCode::Chapter3))
		{
			SceneManager::LoadScene(L"Chapter3");
		}
		if (Input::GetKeyDown(eKeyCode::Chapter4))
		{
			SceneManager::LoadScene(L"Chapter4");
		}
		if (Input::GetKeyDown(eKeyCode::Chapter5))
		{
			SceneManager::LoadScene(L"Chapter5");
		}
		if (Input::GetKeyDown(eKeyCode::Chapter6))
		{
			SceneManager::LoadScene(L"Chapter6");
		}
		if (Input::GetKeyDown(eKeyCode::Chapter7))
		{
			SceneManager::LoadScene(L"Chapter7");
		}
		if (Input::GetKeyDown(eKeyCode::Chapter8))
		{
			SceneManager::LoadScene(L"Chapter8");
		}
	}

	void ya::Chapter7::Render(HDC hdc)
	{
		Scene::Render(hdc);

		//int maxRow = 720 / (TILE_HEIGHT * 3) + 1;
		//for (size_t y = 0; y < maxRow; y++)
		//{
		//	MoveToEx(hdc, 0, TILE_HEIGHT * y * 4 - 10, NULL);      //      라인(선) 시작
		//	LineTo(hdc, 1280, TILE_HEIGHT * y * 4 - 10);        //          라인(선) 끝
		//}

		//int maxColumn = 1280 / (TILE_WIDTH * 3) + 1;
		//for (size_t x = 0; x < maxColumn; x++)
		//{
		//	MoveToEx(hdc, TILE_WIDTH * x * 4 - 10, 0, NULL);      //      라인(선) 시작
		//	LineTo(hdc, TILE_WIDTH * x * 4 - 10, 720);        //          라인(선) 끝
		//}
	}
}
