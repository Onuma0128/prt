#pragma once
#include <memory>

#include "BaseScene.h"

#include "Object3d.h"
#include "WorldTransform.h"
#include "Sprite.h"
#include "ParticleEmitter.h"
#include "TrailEffect.h"

#include "gameScene/test/TestObject.h"
#include "Animation.h"

#include "map/Map.h"
#include "player/Player.h"
#include "enemy/EnemyManager.h"

class GamePlayScene : public BaseScene
{
public:

	void Initialize() override;

	void Finalize() override;

	void Update() override;

	void Draw() override;

private:

	std::unique_ptr<TestObject> testObj_ = nullptr;

	std::unique_ptr<Map> map_ = nullptr;

	std::unique_ptr<Player> player_ = nullptr;

	std::unique_ptr<EnemyManager> enemyManager_ = nullptr;

};

