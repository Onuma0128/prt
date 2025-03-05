#include "GamePlayScene.h"

#include "ParticleManager.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "Input.h"

#include "imgui.h"
#include "titleScene/TitleScene.h"

void GamePlayScene::Initialize()
{
	// 追加

	testObj_ = std::make_unique<TestObject>();
	testObj_->Init();

	// マップを生成
	map_ = std::make_unique<Map>();
	map_->Init();

	player_ = std::make_unique<Player>();
	player_->Init(); player_->SetMap(map_.get());


	// 敵を生成
	enemyManager_ = std::make_unique<EnemyManager>();
	enemyManager_->SetMap(map_.get());
	enemyManager_->Init();
}

void GamePlayScene::Finalize()
{
}

void GamePlayScene::Update()
{
	testObj_->Update();

	map_->Update();

	player_->Update();

	enemyManager_->Update();
}

void GamePlayScene::Draw()
{	
	testObj_->Draw();

	map_->Draw();

	player_->Draw();

	enemyManager_->Draw();
}
