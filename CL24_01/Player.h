#pragma once
#include "Object.h"
#include "Input.h"
#include "Bullet.h"

class Player : public Object {
private:
	int movementType = 0;	// 移動方法　0:すぐに止まる　1:滑る
	float moveSpeed = 1.0f;	// 移動速度
	int health;				// HP
	float radius = 10.0f;   // 当たり判定の半径
	bool deadFlg = false;	// 死亡しているかどうか

	DirectX::SimpleMath::Vector3 velocity = { 0.0f,0.0f,0.0f };

public:
	Player();  // コンストラクタ
	void Update(Input input);  // プレイヤーの更新
	void move(Input input);
	void Intro();

	float GetRadius() const;
	void DecreaseHealth(int);
	bool GetdeadFlg() const;
	int GetHealth() const;


};

