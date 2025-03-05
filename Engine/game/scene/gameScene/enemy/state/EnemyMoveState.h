#pragma once

#include "EnemyBaseState.h"

#include "GlobalVariables.h"

class EnemyMoveState :public EnemyBaseState
{
public:

	EnemyMoveState(Enemy* enemy);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:

	// 円を回る移動処理
	void Move();

	// マップの中心からのVelocityを取った回転の更新処理
	void VelocityRotate();

private:

	GlobalVariables* global_ = GlobalVariables::GetInstance();

	// 敵の回転アングル
	float angle_ = 0.0f;

	// 敵の移動回転
	float theta_ = 0.0f;

};

