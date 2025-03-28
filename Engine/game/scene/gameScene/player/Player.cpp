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
	
	colliderSprite_ = std::make_unique<Sprite>();
	colliderSprite_->Initialize("texture/map.png");
	colliderSprite_->SetPosition(position_);
	colliderSprite_->SetAnchorPoint(Vector2{ 0.5f,0.5f });
	colliderSprite_->SetSize(Vector2{ 40.0f,40.0f });
	colliderSprite_->SetColor(Vector4{ 1.0f,0.0f,0.0f,0.5f });
}

void Player::Update()
{
	// 移動処理
	Move();

	Vector2 stick = { input->GetGamepadLeftStickX(),input->GetGamepadLeftStickY() };

	UpdateNormal();

	ImGui::Begin("player");
	ImGui::InputFloat2("normal", &normal_.x);
	ImGui::InputFloat("rotate", &angle_);
	ImGui::InputFloat2("left_stick", &stick.x);
	ImGui::End();

	// 弾
	BulletUpdate();
	
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

	colliderSprite_->SetPosition(sprite_->GetPosition());
	colliderSprite_->Update();
}

void Player::Draw()
{
	for (const auto& bullet : bullets_) {
		bullet->Draw();
	}


	sprite_->Draw();
	colliderSprite_->Draw();
}

/// <summary>
/// 移動処理
/// </summary>
void Player::Move()
{
	// マップの情報を取得
	Vector2 center = map_->GetSprite()->GetPosition();
	float radius = map_->GetSprite()->GetSize().x / 2.0f;

	// スティックを取得
	Vector2 stick = { input->GetGamepadLeftStickX(),input->GetGamepadLeftStickY() };

	// スティックが倒されているなら
	if (stick.Length() != 0.0f) {

		// スティックからthetaを計算してLerpさせる
		float stickTheta = std::atan2(-stick.y, stick.x);
		theta = theta + (stickTheta - theta) * stickT_;

		// スティックが押された瞬間
		if (stickT_ == 0.0f) {
			stickLength_ = Vector2{
				.x = std::cos(stickTheta) * radius + center.x,
				.y = std::sin(stickTheta) * radius + center.y
			}.Length();
		}

		// tを加算
		stickT_ += 1.0f / stickLength_;
		if (stickT_ > 1.0f) {
			stickT_ = 1.0f;
		}

	} else {
		stickT_ = 0.0f;

		float sizeX = map_->GetSprite()->GetSize().x;
		float thetaSpeed = 0.003f * sizeX + 0.1f;

		// 移動処理
		if (input->PushKey(DIK_A)) {
			theta += 1.0f / (100.0f * thetaSpeed);
		}
		if (input->PushKey(DIK_D)) {
			theta -= 1.0f / (100.0f * thetaSpeed);
		}
	}

	// 座標を更新
	Vector2 position{};
	position.x = center.x + radius * std::cos(theta);
	position.y = center.y + radius * std::sin(theta);

	sprite_->SetPosition(position);
}



void Player::UpdateNormal()
{
	normal_ = Normalize(sprite_->GetPosition() - map_->GetSprite()->GetPosition());
	angle_ = std::atan2(-normal_.x, normal_.y);
}

void Player::ShotBullet()
{
	if (input->PushMouseButton(0)) {
		isClick = true;
	}
	else {
		isClick = false;
	}


	if (isClick) {
		clicktimer -= 1.0f / 60.0f;
		if (clicktimer <= 0 && bulletCount_ > 0) {
			clicktimer = shotInterval;
			--bulletCount_;

			// 弾の速度
			Vector2 velocityB = Normalize(Vector2(static_cast<float>(input->GetMousePosX()), static_cast<float>(input->GetMousePosY())) - sprite_->GetPosition());

			velocityB = velocityB * kBulletSpeed;

			// 弾を生成し、初期化
			auto newBullet = std::make_unique<PlayerBullet>();
			newBullet->Initialize(sprite_->GetPosition(), velocityB);
			newBullet->SetMap(map_);

			// 弾を登録する
			bullets_.push_back(std::move(newBullet));
		}
	}
	else {
		clicktimer = 0;
	}

}

void Player::BulletUpdate()
{
	ShotBullet();

	// 弾の更新
	for (const auto& bullet : bullets_) {
		bullet->Update();
	}

	// デスフラグが立った弾を削除
	bullets_.remove_if([](const std::unique_ptr<PlayerBullet>& bullet) { 
		return bullet->IsDead(); 
		});
}


