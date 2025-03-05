#include "playerBullet.h"
#include "gameScene/map/Map.h"

void PlayerBullet::Initialize(const Vector2& position, const Vector2& Velocity)
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize("texture/bullet.png");
	position_ = position;
	sprite_->SetPosition(position_);
	sprite_->SetAnchorPoint(Vector2{ 0.5f,0.5f });
	sprite_->SetSize(Vector2{ 20.0f,20.0f });
	velocity_ = Velocity;
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
	if (length <= ((map_->GetSprite()->GetSize().x / 2.0f))) {
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
}

void PlayerBullet::Draw()
{
	sprite_->Draw();
}
