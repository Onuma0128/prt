#include "EnemyMoveState.h"

#include <numbers>

#include "Input.h"

#include "gameScene/map/Map.h"
#include "gameScene/enemy/Enemy.h"
#include "EnemyAttackState.h"

#include "Vector2.h"

EnemyMoveState::EnemyMoveState(Enemy* enemy) :EnemyBaseState(enemy) {}

void EnemyMoveState::Initialize()
{
	Vector2 mapCenter = enemy_->GetMap()->GetSprite()->GetPosition();
	Vector2 enemyPos = enemy_->GetSprite()->GetPosition();
	Vector2 velocity = enemyPos - mapCenter;
	float angle = std::atan2(-velocity.x, velocity.y);
	theta_ = (static_cast<float>(std::numbers::pi) / 2.0f) + angle;
}

void EnemyMoveState::Update()
{
	if (!enemy_->GetIsFalling()) {
		Move();
		ColliderMove();
	}

	VelocityRotate();
}

void EnemyMoveState::Draw()
{
}

void EnemyMoveState::Finalize()
{
}

void EnemyMoveState::VelocityRotate()
{
	Vector2 mapCenter = enemy_->GetMap()->GetSprite()->GetPosition();
	Vector2 enemyPos = enemy_->GetSprite()->GetPosition();
	Vector2 velocity = enemyPos - mapCenter;
	angle_ = std::atan2(-velocity.x, velocity.y);

	enemy_->GetSprite()->SetRotation(angle_);
}

void EnemyMoveState::Move()
{
	float sizeX = enemy_->GetMap()->GetSprite()->GetSize().x;
	float thetaSpeed = 0.003f * sizeX + 0.1f;

	// 生きているなら
	if (enemy_->GetIsAlive() == EnemyIsAlive::Active || enemy_->GetIsAlive() == EnemyIsAlive::OnThePlayer) {
		theta_ += 1.0f / (global_->GetValue<float>("Enemy", "thetaSpeed") * thetaSpeed);
	} else { // 弾になっている、もしくは死んでいるなら
		Vector2 mapCenter = enemy_->GetMap()->GetSprite()->GetPosition();
		Vector2 enemyPos = enemy_->GetSprite()->GetPosition();
		Vector2 velocity = enemyPos - mapCenter;
		float angle = std::atan2(-velocity.x, velocity.y);
		theta_ = (static_cast<float>(std::numbers::pi) / 2.0f) + angle;
	} // 弾になっていなければ
	if (enemy_->GetIsAlive() != EnemyIsAlive::Bullet) {
		Vector2 position{};
		Vector2 center = enemy_->GetMap()->GetSprite()->GetPosition();
		float radius = enemy_->GetMap()->GetSprite()->GetSize().x / 2.0f;
		position.x = center.x + radius * std::cosf(theta_);
		position.y = center.y + radius * std::sinf(theta_);

		enemy_->GetSprite()->SetPosition(position);

		radius -= 10.0f;
		position.x = center.x + radius * std::cosf(theta_);
		position.y = center.y + radius * std::sinf(theta_);

		enemy_->GetColliderSprite()->SetPosition(position);
	}
}

void EnemyMoveState::ColliderMove()
{
	Vector2 mapCenter = enemy_->GetMap()->GetSprite()->GetPosition();
	Vector2 enemyPos = enemy_->GetSprite()->GetPosition();
	Vector2 velocity = mapCenter - enemyPos;
	Vector2 colliderPosition = enemyPos + (Normalize(velocity) * 10.0f);

	enemy_->GetColliderSprite()->SetPosition(colliderPosition);
}
