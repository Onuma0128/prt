#pragma once

#include <memory>
#include <vector>

#include "Enemy.h"

class Map;

class EnemyManager
{
public:

	void Init();

	void Update();

	void Draw();

	void SetMap(Map* map) { map_ = map; }

private:

	Map* map_ = nullptr;

	// 敵を管理する配列
	std::vector<std::unique_ptr<Enemy>> enemys_;

};