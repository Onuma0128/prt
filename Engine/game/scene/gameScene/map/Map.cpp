#include "Map.h"

#include <numbers>

void Map::Init()
{
	input = Input::GetInstance();

	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize("texture/map.png");

	sprite_->SetPosition(Vector2{ 640.0f,360.0f });
	sprite_->SetAnchorPoint(Vector2{ 0.5f,0.5f });
	sprite_->SetSize(size_);


	global_->AddValue<float>("Map", "SpaceScele", 1.0f);
	global_->AddValue<float>("Map", "ConstantSpaceScele", 1.0f);
}

void Map::Update()
{
	// 大きく
	Scale();

	// 縮む
	Shrink();

	sprite_->SetSize(size_);
	sprite_->Update();
}

void Map::Draw()
{
	sprite_->Draw();
}

void Map::Scale()
{
	if (isMaxPoison_) {
		if (!isPushKey_) {
			thetaSize_ = 0.0f;
		}
		isPushKey_ = true;

		if (thetaSize_ < 1.0f) {
			thetaSize_ += 1.0f / 180.0f;
			if (thetaSize_ >= 1.0f) {
				thetaSize_ = 1.0f;
			}
		}
		if (size_.x > 250.0f) {
			size_.x = thetaSize_ * -150.0f + 400.0f;
			size_.y = thetaSize_ * -150.0f + 400.0f;
			if (size_.x <= 250.0f) {
				size_.x = 250.0f;
				size_.y = 250.0f;
			}
		} else {
			thetaSize_ += 1.0f / 120.0f;
			if (thetaSize_ >= 2.0f) {
				isMaxPoison_ = false;
			}
		}

	}else{
		if (isPushKey_) {
			if (size_.x > size_.y) {
				size_.x = size_.y;
			} else {
				size_.y = size_.x;
			}
			thetaSize_ = 0.0f;
		}

		isPushKey_ = false;

		if (thetaSize_ < std::numbers::pi * 2.0f) {
			thetaSize_ += std::numbers::pi * 2.0f / 10.0f;
			if (thetaSize_ > std::numbers::pi * 2.0f) {
				thetaSize_ = std::numbers::pi * 2.0f;
			}
		}
		size_.x = std::sin(thetaSize_) * 10.0f + 400.0f;
		size_.y = -std::sin(thetaSize_) * 10.0f + 400.0f;
	}
}

void Map::Shrink()
{
	if (!isPushKey_) {
		if (size_.x > minSize_ || size_.y > minSize_) {
			size_.x -= shrinkSpeed_;
			size_.y -= shrinkSpeed_;
		}	
	}
}
