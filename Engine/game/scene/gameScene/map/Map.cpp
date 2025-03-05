#include "Map.h"

void Map::Init()
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize("texture/map.png");

	sprite_->SetPosition(Vector2{ 640.0f,360.0f });
	sprite_->SetAnchorPoint(Vector2{ 0.5f,0.5f });
	sprite_->SetSize(Vector2{ 400.0f,400.0f });
}

void Map::Update()
{
	sprite_->Update();
}

void Map::Draw()
{
	sprite_->Draw();
}
