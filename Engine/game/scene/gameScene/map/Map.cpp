#include "Map.h"

void Map::Init()
{
	input = Input::GetInstance();

	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize("texture/map.png");

	sprite_->SetPosition(Vector2{ 640.0f,360.0f });
	sprite_->SetAnchorPoint(Vector2{ 0.5f,0.5f });
	sprite_->SetSize(Vector2{ size_,size_ });
}

void Map::Update()
{
	// 大きく
	Scale();

	// 縮む
	Shrink();

	sprite_->SetSize(Vector2{ size_,size_ });
	sprite_->Update();
}

void Map::Draw()
{
	sprite_->Draw();
}

void Map::Scale()
{
	if (input->PushKey(DIK_SPACE)) {
		size_ += 1.0f;
		isPushKey_ = true;
	}else{
		isPushKey_ = false;
	}
}

void Map::Shrink()
{
	if (!isPushKey_) {
		if (size_ > minSize_) {
			size_ -= shrinkSpeed_;
		}
		
		
	}

	if (size_ > maxSize_) {
		size_ = maxSize_;
	}
	if (size_ < minSize_) {
		size_ = minSize_;
	}
}
