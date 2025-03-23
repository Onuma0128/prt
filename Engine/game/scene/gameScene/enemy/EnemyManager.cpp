#include "EnemyManager.h"

#include <numbers>

#include "gameScene/player/Player.h"
#include "gameScene/map/Map.h"

void EnemyManager::Init()
{

	// 初期化
	for (int i = 0; i < 2; ++i) {
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
		enemy->SetMap(map_);
		enemy->SetPlayer(player_);
		if (i == 0) {
			enemy->Init(Vector2{ 600,320 });
		}
		else if (i == 1) {
			enemy->Init(Vector2{ 640,400 });
		}

		enemys_.push_back(std::move(enemy));
	}


	global_->AddValue<float>("Enemy", "thetaSpeed", 60.0f);
	global_->AddValue<int>("Enemy", "poisonCount", 10);
}

void EnemyManager::Update()
{

	// 更新
	for (auto& enemy : enemys_) {
		enemy->Update();
		if (enemy->GetPoisonTime() >= 1.0f) {
			enemy->SetPoisonTime();
			std::unique_ptr<EnemyPoison> poison = std::make_unique<EnemyPoison>();
			poison->sprite = std::make_unique<Sprite>();
			poison->sprite->Initialize("white1x1.png");
			poison->sprite->SetAnchorPoint(Vector2{ 0.5f,0.5f });
			poison->sprite->SetSize(Vector2{ 16.0f,16.0f });
			poison->sprite->SetPosition(enemy->GetSprite()->GetPosition());
			poison->velocity = {};
			poison->isActive = true;
			enemyPoisons_.push_back(std::move(poison));
		}
	}

	// 毒の数が10個を超えたら縮む
	int count = global_->GetValue<int>("Enemy", "poisonCount");
	if (poisonCount_ >= count) {
		poisonCount_ = 0;
		map_->SetIsMaxPoison(true);
	}

	if (!map_->GetIsMaxPoison()) {
		poisonCount_ = enemyPoisons_.size();
	} else {
		for (auto& poison : enemyPoisons_) {
			Vector2 position{};
			Vector2 center = map_->GetSprite()->GetPosition();
			float radius = map_->GetSprite()->GetSize().x / 2.0f;
			position.x = center.x + radius * std::cosf(std::numbers::pi / 2.0f);
			position.y = center.y + radius * std::sinf(std::numbers::pi / 2.0f);

			if (poison->velocity.Length() == 0.0f) {
				poison->velocity = Normalize(position - poison->sprite->GetPosition());
			}

			position = poison->sprite->GetPosition();
			position += poison->velocity * 2.0f;
			poison->sprite->SetPosition(position);
		}
	}
	for (auto& poison : enemyPoisons_) {
		float length = (map_->GetSprite()->GetPosition() - poison->sprite->GetPosition()).Length();
		if (length > (map_->GetSprite()->GetSize().x / 2.0f + 32.0f)) {
			poison->isActive = false;
		}
		if (length > (map_->GetSprite()->GetSize().x / 2.0f)) {
			Vector2 position = poison->sprite->GetPosition();
			position += poison->velocity * 2.0f;
			poison->sprite->SetPosition(position);
		}
		poison->sprite->Update();
	}

	// デスフラグが立った弾を削除
	enemys_.remove_if([](const std::unique_ptr<Enemy>& bullet) { return bullet->IsDead(); });


	enemyPoisons_.remove_if([](const std::unique_ptr<EnemyPoison>& poison) {
		return !poison->isActive;
	});
}

void EnemyManager::Draw()
{
	for (auto& poison : enemyPoisons_) {
		poison->sprite->Draw();
	}

	// 描画
	for (auto& enemy : enemys_) {
		enemy->Draw();
	}
}

void EnemyManager::PopEnemy(Vector2 popPos)
{
	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
	enemy->SetMap(map_);
	enemy->SetPlayer(player_);
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
	enemy->SetPlayer(player_);
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
