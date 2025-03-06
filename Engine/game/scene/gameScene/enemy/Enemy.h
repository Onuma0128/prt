#pragma once

#include <memory>
#include <list>

#include "Sprite.h"

#include "state/EnemyBaseState.h"
#include "gameScene/map/Map.h"

class PlayerBullet;
class Enemy
{
public:

	void Init(const Vector2& position);

	void Update();

	void Draw();

	// マップとの当たり判定
	void Collision();

	// 状態チェンジ用
	void ChengeState(std::unique_ptr<EnemyBaseState> newState);

	Map* GetMap()const { return map_; }
	void SetMap(Map* map) { map_ = map; }

	Sprite* GetSprite() { return sprite_.get(); }

	bool GetIsFalling()const { return isFalling_; }

	//void SetPlayerBullet(std::list <PlayerBullet>* playerBullet) { playerBullet_ = *playerBullet; }

	void BulletCollision();

	bool IsDead() const { return isDead_; };

	void SetDead() { isDead_ = true; };

	float GetRad() const { return kRad_; }

private:

	Map* map_ = nullptr;

	//std::list <PlayerBullet> playerBullet_;

	// 敵のSprite
	std::unique_ptr<Sprite> sprite_ = nullptr;

	// 敵の状態(移動とか攻撃とか)
	std::unique_ptr<EnemyBaseState> state_ = nullptr;

	// 落下しているかどうか
	bool isFalling_ = false;

	float saveMapSize_ = 0.0f;

	float kRad_ = 20.0f;

	bool isDead_ = false;
};

