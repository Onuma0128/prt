#include "playerBullet.h"

#include <numbers>

#include "gameScene/map/Map.h"

void PlayerBullet::Initialize(const Vector2& position, const Vector2& Velocity)
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize("texture/enemy.png");
	position_ = position;
	sprite_->SetPosition(position_);
	sprite_->SetAnchorPoint(Vector2{ 0.5f,0.5f });
	sprite_->SetSize(Vector2{ 96.0f,16.0f });
	velocity_ = Velocity;

	float angle = std::atan2(-velocity_.x, velocity_.y);
	sprite_->SetRotation(angle);

	colliderSprite_ = std::make_unique<Sprite>();
	colliderSprite_->Initialize("texture/map.png");
	colliderSprite_->SetPosition(position_);
	colliderSprite_->SetAnchorPoint(Vector2{ 0.5f,0.5f });
	colliderSprite_->SetSize(Vector2{ 64.0f,64.0f });
	colliderSprite_->SetColor(Vector4{ 1.0f,0.0f,0.0f,0.5f });
}

void PlayerBullet::Update()
{

	
	// マップとの当たり判定
	Vector2 mapCenter = map_->GetSprite()->GetPosition();
	Vector2 enemyPos = sprite_->GetPosition();

	float length = std::sqrt(std::powf(enemyPos.x - mapCenter.x, 2) + std::powf(enemyPos.y - mapCenter.y, 2));
	// マップの円の半径
	float mapRadius = map_->GetSprite()->GetSize().x / 2.0f;

	// length以下なら当たっている
	if (length <= (mapRadius + 10)) {
	}
	else {
		isDead_ = true;
	}


	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	// 座標を移動させる
	position_ += velocity_;

	sprite_->SetPosition(position_);
	sprite_->Update();

	colliderSprite_->SetPosition(sprite_->GetPosition());
	colliderSprite_->Update();
}

void PlayerBullet::Draw()
{
	sprite_->Draw();

	colliderSprite_->Draw();
}
