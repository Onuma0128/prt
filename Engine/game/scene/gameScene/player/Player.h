
#include "Sprite.h"
#include "memory"
#include "Input.h"

class Map;

class Player
{
public:
	
	void Init();

	void Update();

	void Draw();

	void SetMap(Map* map) { map_ = map; }
private:

	void Move();


	void UpdateNormal();



private:
	Input* input;


	std::unique_ptr<Sprite> sprite_ = nullptr;



	Map* map_ = nullptr;

	Vector2 gravityVelo_{};

	Vector2 position_ = { 640,160 };

	Vector2 normal_{};


	float theta = 0;
	float thetaSpeed = 0.01f;
	float angle_ = 0.0f; // 角
	float rotateSpeed_ = 1.0f; // 角速度
};

