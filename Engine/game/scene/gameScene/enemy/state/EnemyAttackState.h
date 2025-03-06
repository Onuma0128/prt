#pragma once

#include "EnemyBaseState.h"

#include "GlobalVariables.h"

class EnemyAttackState :public EnemyBaseState
{
public:

	EnemyAttackState(Enemy* enemy);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:

	// 円を回る移動処理
	void Attack();

	// マップの中心からのVelocityを取った回転の更新処理
	void VelocityRotate();

private:

	GlobalVariables* global_ = GlobalVariables::GetInstance();

	// 攻撃開始までの待機時間
	float attackStand_ByTime_ = 0.0f;

	// 敵の回転アングル
	float angle_ = 0.0f;

	// 攻撃の瞬間の半径
	float radius_ = 0.0f;

	// 敵の移動回転
	float theta_ = 0.0f;
	float originallyTheta_ = 0.0f;

};

