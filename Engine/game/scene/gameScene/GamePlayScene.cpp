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

	map_ = std::make_unique<Map>();
	map_->Init();

	player_ = std::make_unique<Player>();
	player_->Init(); player_->SetMap(map_.get());

}

void GamePlayScene::Finalize()
{
}

void GamePlayScene::Update()
{
	testObj_->Update();

	map_->Update();

	player_->Update();
}

void GamePlayScene::Draw()
{	
	testObj_->Draw();

	map_->Draw();

	player_->Draw();
}
