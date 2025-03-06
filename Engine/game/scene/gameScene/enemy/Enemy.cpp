#include "Enemy.h"

#include "state/EnemyMoveState.h"
#include "gameScene/player/playerBullet.h"

void Enemy::Init(const Vector2& position)
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize("texture/enemy.png");

	sprite_->SetAnchorPoint(Vector2{ 0.5f,1.0f });
	sprite_->SetPosition(position);
	sprite_->SetSize(Vector2{ 64.0f,64.0f });

	state_ = std::make_unique<EnemyMoveState>(this);
	state_->Initialize();

	isFalling_ = true;
}

void Enemy::Update()
{
	Collision();

	state_->Update();

	sprite_->Update();
}

void Enemy::Draw()
{
	state_->Draw();

	sprite_->Draw();
}

void Enemy::Collision()
{
	// マップとの当たり判定
	Vector2 mapCenter = map_->GetSprite()->GetPosition();
	Vector2 enemyPos = sprite_->GetPosition();

	float length = std::sqrtf(std::powf(enemyPos.x - mapCenter.x, 2) + std::powf(enemyPos.y - mapCenter.y, 2));

	// length以下なら当たっている
	if (length <= (map_->GetSprite()->GetSize().x / 2.0f)) {
		Vector2 velocity = Normalize(enemyPos - mapCenter);
		enemyPos += velocity;
		sprite_->SetPosition(enemyPos);
		isFalling_ = true;
	}
	else {
		isFalling_ = false;
		if (saveMapSize_ < map_->GetSprite()->GetSize().x / 2.0f) {
			isFalling_ = true;
		}
		saveMapSize_ = map_->GetSprite()->GetSize().x / 2.0f;
	}
}

void Enemy::ChengeState(std::unique_ptr<EnemyBaseState> newState)
{
	state_->Finalize();
	state_ = std::move(newState);
	state_->Initialize();
}

void Enemy::BulletCollision()
{
	/*for (int i = 0; i < playerBullet_->size(); i++) {
		playerBullet_[i]
	}*/


	//for (auto& bullet : playerBullet_) {
	//	// マップとの当たり判定
	//	Vector2 bulletPos = bullet.GetSprite()->GetPosition();
	//	Vector2 enemyPos = sprite_->GetPosition();
	//	float enemySize = sprite_->GetSize().x;


	//	float length = std::sqrtf(std::powf(enemyPos.x - bulletPos.x, 2) + std::powf(enemyPos.y - bulletPos.y, 2));
	//	
	//	if (length <= enemySize + bullet.GetRad()) {
	//		isDead_ = true;
	//	}
	//}
}
