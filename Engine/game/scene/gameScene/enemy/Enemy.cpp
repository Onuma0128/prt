#include "Enemy.h"

#include <numbers>

#include "gameScene/player/Player.h"

#include "state/EnemyMoveState.h"
#include "state/EnemyAttackState.h"

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

	colliderSprite_ = std::make_unique<Sprite>();
	colliderSprite_->Initialize("texture/map.png");
	colliderSprite_->SetAnchorPoint(Vector2{ 0.5f,0.5f });
	colliderSprite_->SetSize(Vector2{ 64.0f,64.0f });
	colliderSprite_->SetColor(Vector4{ 1.0f,0.0f,0.0f,0.5f });

	Vector2 center = map_->GetSprite()->GetPosition();
	Vector2 enemyPos = sprite_->GetPosition();
	Vector2 velocity = center - enemyPos;
	Vector2 colliderPosition = enemyPos + (Normalize(velocity) * 10.0f);

	colliderSprite_->SetPosition(colliderPosition);


	velocitySprite_ = std::make_unique<Sprite>();
	velocitySprite_->Initialize("white1x1.png");
	velocitySprite_->SetAnchorPoint(Vector2{ 0.5f,1.0f });
	velocitySprite_->SetSize(Vector2{ 1.0f,100.0f });
}

void Enemy::Update()
{
	if (isAlive_ == EnemyIsAlive::Bullet) {
		Vector2 position = sprite_->GetPosition() + (bulletVelocity_ * -3.0f);
		sprite_->SetPosition(position);
		Vector2 mapCenter = map_->GetSprite()->GetPosition();
		Vector2 velocity = mapCenter - position;
		Vector2 colliderPosition = position + (Normalize(velocity) * 10.0f);
		colliderSprite_->SetPosition(colliderPosition);
	}

	Collision();

	state_->Update();

	if (isAlive_ == EnemyIsAlive::Active || isAlive_ == EnemyIsAlive::OnThePlayer) {
		OnThePlayerVelocity();
	}

	// 敵が弾になり再度ステージに着いたら
	if (isAlive_ == EnemyIsAlive::Bullet) {
		if (bulletVelocity_.Length() != 0.0f && !isFalling_) {
			isAlive_ = EnemyIsAlive::Dead;
			bulletVelocity_ = {};
			sprite_->SetSize(Vector2{ 96.0f,16.0f });
		}
	}

	sprite_->Update();
	colliderSprite_->Update();
	velocitySprite_->Update();
}

void Enemy::Draw()
{
	state_->Draw();

	if (isAlive_ == EnemyIsAlive::OnThePlayer) {
		velocitySprite_->Draw();
	}

	sprite_->Draw();
	colliderSprite_->Draw();
}

void Enemy::Collision()
{
	// マップとの当たり判定
	Vector2 mapCenter = map_->GetSprite()->GetPosition();
	Vector2 enemyPos = sprite_->GetPosition();
	Vector2 enemyColliderPos = colliderSprite_->GetPosition();

	Vector2 velocity = Normalize(enemyPos - mapCenter);
	Vector2 colliderVelocity = Normalize(enemyColliderPos - mapCenter);

	float length = std::sqrtf(std::powf(enemyPos.x - mapCenter.x, 2) + std::powf(enemyPos.y - mapCenter.y, 2));

	// length以下なら当たっている
	// 落下処理
	if (length <= (map_->GetSprite()->GetSize().x / 2.0f)) {
		enemyPos += velocity * 0.3f;
     		sprite_->SetPosition(enemyPos);
		enemyColliderPos += colliderVelocity * 0.3f;
		colliderSprite_->SetPosition(enemyColliderPos);
		isFalling_ = true;
	} else { // 押し出し処理
		isFalling_ = false;

		if (saveMapSize_ < map_->GetSprite()->GetSize().x / 2.0f) {
			isFalling_ = true;
		}

		enemyPos -= velocity * 2.0f;
		sprite_->SetPosition(enemyPos);
		enemyColliderPos -= colliderVelocity * 2.0f;
		colliderSprite_->SetPosition(enemyColliderPos);

		saveMapSize_ = map_->GetSprite()->GetSize().x / 2.0f;
	}
}

void Enemy::ChengeState(std::unique_ptr<EnemyBaseState> newState)
{
	state_->Finalize();
	state_ = std::move(newState);
	state_->Initialize();
}

void Enemy::OnThePlayerVelocity()
{
	Vector2 enemyPos = colliderSprite_->GetPosition();
	Vector2 playerPos = player_->GetSprite()->GetPosition();
	bulletVelocity_ = playerPos - enemyPos;
	float angle_ = std::atan2(-bulletVelocity_.x, bulletVelocity_.y);

	velocitySprite_->SetRotation(angle_);
	velocitySprite_->SetPosition(sprite_->GetPosition());
}


