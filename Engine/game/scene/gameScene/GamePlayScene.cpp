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
	input_ = Input::GetInstance();


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

	Pop();



	testObj_->Update();

	map_->Update();

	player_->Update();

	enemyManager_->Update();

	// 当たり判定
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
		Vector2 enemyPos = enemy->GetSprite()->GetPosition();
		float enemySize = enemy->GetSprite()->GetSize().x / 2;
		float length{};

		// 敵と弾の当たり判定
		for (auto& bullet : player_->GetBullets()) {

			// マップとの当たり判定
			Vector2 bulletPos = bullet->GetSprite()->GetPosition();

			length = std::sqrtf(std::powf(enemyPos.x - bulletPos.x, 2) + std::powf(enemyPos.y - bulletPos.y, 2));

			// 衝突判定
			if (length <= enemySize + bullet->GetRad()) {
				bullet->SetDead(); // 弾死亡
				enemy->SetDead();  // 敵死亡
			}
		}

		/// 敵とプレイヤーの当たり判定
		Vector2 playerPos = player_->GetSprite()->GetPosition();

		length = std::sqrtf(std::powf(enemyPos.x - playerPos.x, 2) + std::powf(enemyPos.y - playerPos.y, 2));

		// 衝突判定
		if (length <= enemySize + player_->GetRad()) {
		}


	}



}

void GamePlayScene::Pop()
{
#ifdef _DEBUG
	ImGui::Begin("popEnemy");
	ImGui::DragFloat2("popPos", &popPos_.x, 0.1f);
	if (ImGui::Button("pop"))
		enemyManager_->PopEnemy(popPos_);
	ImGui::End();
	if (input_->TriggerKey(DIK_E)) {
		enemyManager_->RondomPopEnemy();
	}
	if (input_->TriggerKey(DIK_R)) {
		enemyManager_->AllDeathEnemy();
	}

#endif // _DEBUG
}
