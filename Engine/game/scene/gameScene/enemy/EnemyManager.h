#pragma once

#include <memory>
#include <vector>
#include <list>

#include "Enemy.h"

#include "GlobalVariables.h"


class PlayerBullet;
class Map;

class EnemyManager
{
public:

	void Init();

	void Update();

	void Draw();

	void SetMap(Map* map) { map_ = map; }

	std::list<std::unique_ptr<Enemy>>& GetEnemys() { return enemys_; }


private:

	GlobalVariables* global_ = GlobalVariables::GetInstance();

	Map* map_ = nullptr;


	// 敵を管理する配列
	std::list<std::unique_ptr<Enemy>> enemys_;

};