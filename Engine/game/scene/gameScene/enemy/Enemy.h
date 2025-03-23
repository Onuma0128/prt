#pragma once

#include <memory>
#include <list>

#include "Sprite.h"

#include "state/EnemyBaseState.h"
#include "gameScene/map/Map.h"

class PlayerBullet;
class Player;

enum class EnemyIsAlive {
	Active = 0,			// 生きている
	OnThePlayer = 1,	// プレイヤーの上にいる
	Bullet = 2,			// 弾になった
	Dead = 3,			// 死んでいる
};

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

	// ポインタ

	Map* GetMap()const { return map_; }
	void SetMap(Map* map) { map_ = map; }

	Player* GetPlayer()const { return player_; }
	void SetPlayer(Player* player) { player_ = player; }

	Sprite* GetSprite() { return sprite_.get(); }
	Sprite* GetColliderSprite() { return colliderSprite_.get(); }

	// フラグ

	bool GetIsFalling()const { return isFalling_; }

	bool IsDead() const { return isDead_; };

	void SetDead() { isDead_ = true; };

	float GetRad() const { return kRad_; }

	EnemyIsAlive GetIsAlive() const { return isAlive_; }
	void SetIsAlive(EnemyIsAlive isAlive) { isAlive_ = isAlive; }

private:

	void OnThePlayerVelocity();

private:

	Map* map_ = nullptr;
	Player* player_ = nullptr;
	
	// 敵のSprite
	std::unique_ptr<Sprite> sprite_ = nullptr;
	std::unique_ptr<Sprite> colliderSprite_ = nullptr;
	std::unique_ptr<Sprite> velocitySprite_ = nullptr;

	// 敵の状態(移動とか攻撃とか)
	std::unique_ptr<EnemyBaseState> state_ = nullptr;

	// 落下しているかどうか
	bool isFalling_ = false;

	float saveMapSize_ = 0.0f;

	float kRad_ = 20.0f;

	// 敵が死んでいるか
	EnemyIsAlive isAlive_ = EnemyIsAlive::Active;
	Vector2 bulletVelocity_{};

	bool isDead_ = false;
};

