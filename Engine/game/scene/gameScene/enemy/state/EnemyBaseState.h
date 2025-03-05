#pragma once

class Enemy;

class EnemyBaseState
{
public:

	EnemyBaseState(Enemy* enemy);

	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Finalize() = 0;

protected:

	Enemy* enemy_ = nullptr;
	
};