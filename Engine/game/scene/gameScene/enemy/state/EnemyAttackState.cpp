#include "EnemyAttackState.h"

#include <numbers>

#include "gameScene/map/Map.h"
#include "gameScene/enemy/Enemy.h"
#include "EnemyMoveState.h"

#include "Vector2.h"

EnemyAttackState::EnemyAttackState(Enemy* enemy) :EnemyBaseState(enemy) {}

void EnemyAttackState::Initialize()
{
	Vector2 mapCenter = enemy_->GetMap()->GetSprite()->GetPosition();
	Vector2 enemyPos = enemy_->GetSprite()->GetPosition();
	Vector2 velocity = enemyPos - mapCenter;
	float angle = std::atan2(-velocity.x, velocity.y);
	originallyTheta_ = (std::numbers::pi / 2.0f) + angle;
}

void EnemyAttackState::Update()
{
	if (theta_ > std::numbers::pi * 2.0f) {
		enemy_->ChengeState(std::make_unique<EnemyMoveState>(enemy_));
		return;
	}

	Vector2 mapCenter = enemy_->GetMap()->GetSprite()->GetPosition();
	Vector2 enemyPos = enemy_->GetSprite()->GetPosition();
	radius_ = std::sqrtf(std::powf(enemyPos.x - mapCenter.x, 2) + std::powf(enemyPos.y - mapCenter.y, 2));

	if (attackStand_ByTime_ < 1.0f) {

		attackStand_ByTime_ += 1.0f / 90.0f;

		// サイズを大きくしたり、小さくしたり
		float size = (std::sinf(attackStand_ByTime_ * 19.0f) * 10.0f) + 64.0f;
		enemy_->GetSprite()->SetSize(Vector2{ size,size });

		// 赤く点滅させる
		float color = std::sin(attackStand_ByTime_ * 19.0f);
		enemy_->GetSprite()->SetColor(Vector4{ 1.0f,color ,color ,1.0f });

		if (attackStand_ByTime_ >= 1.0f) {
			enemy_->GetSprite()->SetSize(Vector2{ 64.0f,64.0f });
			enemy_->GetSprite()->SetColor(Vector4{ 1.0f,1.0f ,1.0f ,1.0f });
		}

	} else {
		Attack();
		VelocityRotate();
	}
}

void EnemyAttackState::Draw()
{
}

void EnemyAttackState::Finalize()
{
	enemy_->SetIsAttackTime(0.0f);
}

void EnemyAttackState::Attack()
{
	theta_ += 1.0f / 5.0f;

	Vector2 position{};
	Vector2 center = enemy_->GetMap()->GetSprite()->GetPosition();
	position.x = center.x + radius_ * std::cosf(theta_ + originallyTheta_);
	position.y = center.y + radius_ * std::sinf(theta_ + originallyTheta_);

	enemy_->GetSprite()->SetPosition(position);
}

void EnemyAttackState::VelocityRotate()
{
	Vector2 mapCenter = enemy_->GetMap()->GetSprite()->GetPosition();
	Vector2 enemyPos = enemy_->GetSprite()->GetPosition();
	Vector2 velocity = enemyPos - mapCenter;
	angle_ = std::atan2(-velocity.x, velocity.y);

	enemy_->GetSprite()->SetRotation(angle_);
}
