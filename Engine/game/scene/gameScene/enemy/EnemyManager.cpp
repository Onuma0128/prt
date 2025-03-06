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
		}
		else if (i == 1) {
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

	// デスフラグが立った弾を削除
	enemys_.remove_if([](const std::unique_ptr<Enemy>& bullet) { return bullet->IsDead(); });
}

void EnemyManager::Draw()
{

	// 描画
	for (auto& enemy : enemys_) {
		enemy->Draw();
	}
}

void EnemyManager::PopEnemy(Vector2 popPos)
{
	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
	enemy->SetMap(map_);
	enemy->Init(Vector2{ 600,320 });
	enemys_.push_back(std::move(enemy));
}

void EnemyManager::RondomPopEnemy()
{
	Vector2 mapPos =  map_->GetSprite()->GetPosition();
	Vector2 mapSize = map_->GetSprite()->GetSize();
	Vector2 popRand{};

	popRand.x = static_cast<float>(rand() % static_cast<int>(mapSize.x) - (static_cast<int>(mapSize.x) / 2));
	popRand.y = static_cast<float>(rand() % static_cast<int>(mapSize.y) - (static_cast<int>(mapSize.y) / 2));


	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
	enemy->SetMap(map_);
	enemy->Init(mapPos + popRand);
	enemys_.push_back(std::move(enemy));
}

void EnemyManager::AllDeathEnemy()
{
	for (auto& enemy : enemys_) {
		enemy->SetDead();
	}
	// デスフラグが立った弾を削除
	enemys_.remove_if([](const std::unique_ptr<Enemy>& bullet) { return bullet->IsDead(); });
}
