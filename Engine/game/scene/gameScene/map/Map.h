#pragma once

#include <memory>

#include "Sprite.h"

class Map
{
public:

	void Init();

	void Update();

	void Draw();

private:

	std::unique_ptr<Sprite> sprite_ = nullptr;

};