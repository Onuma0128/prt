
#include "Sprite.h"
#include "memory"
#include "Input.h"
#include "playerBullet.h"
#include "list"
class Map;

class Player
{
public:
	
	void Init();

	void Update();

	void Draw();

	void SetMap(Map* map) { map_ = map; }

	std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	Sprite* GetSprite() { return sprite_.get(); }

	float GetRad() const { return kRad_; }
private:


	// 移動
	void Move();

	// 法線方向更新
	void UpdateNormal();

	void ShotBullet();

	// 弾の更新
	void BulletUpdate();

private:
	Input* input;

	// スプライト
	std::unique_ptr<Sprite> sprite_ = nullptr;

	// 弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	
	// マップ
	Map* map_ = nullptr;

	Vector2 position_ = { 640,160 };

	Vector2 normal_{};

	// スティック用
	float stickT_ = 0.0f;
	float stickLength_ = 0.0f;


	float theta = 0;
	//float thetaSpeed = 0.01f;
	float angle_ = 0.0f; // 角
	float rotateSpeed_ = 1.0f; // 角速度

	bool isClick = false;
	float clicktimer = 0.0f;
	const float shotInterval = 0.25f;

	const float kBulletSpeed = 2.0f;

	// 半径
	float kRad_ = 10.0f;
};

