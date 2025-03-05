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

class GamePlayScene : public BaseScene
{
public:

	void Initialize() override;

	void Finalize() override;

	void Update() override;

	void Draw() override;

private:

	std::unique_ptr<TestObject> testObj_ = nullptr;

};

