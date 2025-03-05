#pragma once
#include "Sprite.h"
#include "memory"

class Map;

class PlayerBullet
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Vector2& position, const Vector2& Velocity);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool IsDead() const { return isDead_; };

	void SetMap(Map* map) { map_ = map; }
private:
	std::unique_ptr<Sprite> sprite_ = nullptr;

	//
	Map* map_;

	// 速度
	Vector2 velocity_;

	// 寿命<frm>
	static const int32_t kLifeTime = 60 * 2;

	// デスタイマー
	int32_t deathTimer_ = kLifeTime;

	// デスフラグ
	bool isDead_ = false;

	// 半径
	const float kRad = 1.0f;

	Vector2 position_;
};

