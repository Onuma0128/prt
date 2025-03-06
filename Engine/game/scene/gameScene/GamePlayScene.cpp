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

	Coll();
}

void GamePlayScene::Draw()
{
	testObj_->Draw();

	map_->Draw();

	player_->Draw();

	enemyManager_->Draw();
}

void GamePlayScene::Coll()
{
	for (auto& enemy : enemyManager_->GetEnemys()) {
		for (auto& bullet : player_->GetBullets()) {

			// マップとの当たり判定
			Vector2 bulletPos = bullet->GetSprite()->GetPosition();
			Vector2 enemyPos = enemy->GetSprite()->GetPosition();
			float enemySize = enemy->GetSprite()->GetSize().x /2 ;


			float length = std::sqrtf(std::powf(enemyPos.x - bulletPos.x, 2) + std::powf(enemyPos.y - bulletPos.y, 2));

			if (length <= enemySize + bullet->GetRad()) {
				bullet->SetDead();
				enemy->SetDead();
			}
		}
	}


}
