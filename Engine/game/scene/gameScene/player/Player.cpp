#include "Player.h"
#include "gameScene/map/Map.h"
#include "imgui.h"


void Player::Init()
{
	input = Input::GetInstance();


	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize("texture/player.png");

	sprite_->SetPosition(position_);
	sprite_->SetAnchorPoint(Vector2{ 0.5f,1.0f });
	sprite_->SetSize(Vector2{ 40.0f,40.0f });
	

}

void Player::Update()
{
	// 移動処理
	Move();


	UpdateNormal();

	ImGui::Begin("player");
	ImGui::InputFloat2("normal", &normal_.x);
	ImGui::InputFloat("rotate", &angle_);
	ImGui::End();

	
	
	// マップとの当たり判定
	Vector2 mapCenter = map_->GetSprite()->GetPosition();
	Vector2 enemyPos = sprite_->GetPosition();

	float length = std::sqrt(std::powf(enemyPos.x - mapCenter.x, 2) + std::powf(enemyPos.y - mapCenter.y, 2));
	// マップの円の半径
	float mapRadius = map_->GetSprite()->GetSize().x / 2.0f;

	// length以下なら当たっている
	if (length < ((map_->GetSprite()->GetSize().x / 2.0f))) {
		Vector2 velocity = Normalize(enemyPos - mapCenter);
		enemyPos += velocity;
		sprite_->SetPosition(enemyPos);
	}
	else {
		// 円の外に出た場合、境界上に補正
		Vector2 pushBackPos = mapCenter + Normalize(enemyPos - mapCenter) * mapRadius;
		sprite_->SetPosition(pushBackPos);
	}


	// 最後にセットして更新
	sprite_->SetRotation(angle_);
	sprite_->Update();
}

void Player::Draw()
{
	sprite_->Draw();
}

/// <summary>
/// 移動処理
/// </summary>
void Player::Move()
{
	

	// 移動処理
	if (input->PushKey(DIK_A)) {
		theta += thetaSpeed;
	}
	if (input->PushKey(DIK_D)) {
		theta -= thetaSpeed;
	}
	
	//theta += 1.0f / 180.0f;

	Vector2 position{};
	Vector2 center = map_->GetSprite()->GetPosition();
	float radius = map_->GetSprite()->GetSize().x / 2.0f;
	position.x = center.x + radius * std::cos(theta);
	position.y = center.y + radius * std::sin(theta);

	sprite_->SetPosition(position);
}



void Player::UpdateNormal()
{
	normal_ = Normalize(sprite_->GetPosition() - map_->GetSprite()->GetPosition());
	angle_ = std::atan2(-normal_.x, normal_.y);
}


