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
	if (input->PushKey(DIK_SPACE)) {
		if (!isPushKey_) {
			size_.x += global_->GetValue<float>("Map", "SpaceScele");
			size_.y += global_->GetValue<float>("Map", "SpaceScele");
		}
		size_.x += global_->GetValue<float>("Map", "ConstantSpaceScele");
		size_.y += global_->GetValue<float>("Map", "ConstantSpaceScele");
		isPushKey_ = true;

		if (thetaSize_ < std::numbers::pi * 2.0f) {
			thetaSize_ += std::numbers::pi * 2.0f / 10.0f;
			if (thetaSize_ > std::numbers::pi * 2.0f) {
				thetaSize_ = std::numbers::pi * 2.0f;
			}
		}
		size_.x += std::sin(thetaSize_) * 10.0f;
		size_.y += -std::sin(thetaSize_) * 10.0f;

	}else{
		if (isPushKey_) {
			if (size_.x > size_.y) {
				size_.x = size_.y;
			} else {
				size_.y = size_.x;
			}
		}

		isPushKey_ = false;
		thetaSize_ = 0.0f;
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

	if (size_.x >= maxSize_ || size_.y >= maxSize_) {
		size_.x = maxSize_;
		size_.y = maxSize_;
	}
	if (size_.x <= minSize_ || size_.y <= minSize_) {
		size_.x = minSize_;
		size_.y = minSize_;
	}
}
