#pragma once

#include <memory>

#include "Sprite.h"
#include "Input.h"


class Map
{
public:

	void Init();

	void Update();

	void Draw();

	Sprite* GetSprite() { return sprite_.get(); }

private:

	void Scale();

	void Shrink();

private:
	Input* input;

	std::unique_ptr<Sprite> sprite_ = nullptr;

	// スペースキーを押しているのか
	bool isPushKey_ = false;

	
	// 縮む速度
	float shrinkSpeed_ = 1.0f;

	// サイズ
	const float maxSize_ = 400;
	const float minSize_ = 200;
	float size_ = 400;



};