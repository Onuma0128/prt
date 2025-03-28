#pragma once

#include <memory>
#include <vector>
#include <list>

#include "Enemy.h"

#include "GlobalVariables.h"


class PlayerBullet;
class Map;
class Player;

class EnemyManager
{
public:

	void Init();

	void Update();

	void Draw();

	void SetMap(Map* map) { map_ = map; }
	void SetPlayer(Player* player) { player_ = player; }

	std::list<std::unique_ptr<Enemy>>& GetEnemys() { return enemys_; }


	void PopEnemy(Vector2 popPos);
	
	void RondomPopEnemy();
	
	void AllDeathEnemy();

private:

	GlobalVariables* global_ = GlobalVariables::GetInstance();

	Map* map_ = nullptr;
	Player* player_ = nullptr;


	// 敵を管理する配列
	std::list<std::unique_ptr<Enemy>> enemys_;

};