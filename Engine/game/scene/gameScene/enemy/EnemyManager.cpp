#include "EnemyManager.h"

#include "gameScene/map/Map.h"

void EnemyManager::Init()
{

	// 初期化
	for (int i = 0; i < 2; ++i) {
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
		enemy->SetMap(map_);
		if (i == 0) {
			enemy->Init(Vector2{ 600,320 });
		} else if (i == 1) {
			enemy->Init(Vector2{ 640,400 });
		}
		enemys_.push_back(std::move(enemy));
	}


	global_->AddValue<float>("Enemy", "thetaSpeed", 60.0f);
}

void EnemyManager::Update()
{

	// 更新
	for (auto& enemy : enemys_) {
		enemy->Update();
	}
}

void EnemyManager::Draw()
{

	// 描画
	for (auto& enemy : enemys_) {
		enemy->Draw();
	}
}
