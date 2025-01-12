#pragma once
#include "Object.h"
#include "Input.h"
#include "Bullet.h"

#define MAP_WIDTH (560)	// ウインドウの幅
#define MAP_HEIGHT (720)	// ウインドウの高さ

class Player : public Object {
private:
	int movementType = 0;	// 移動方法　0:すぐに止まる　1:滑る
	float moveSpeed = 1.0f;	// 移動速度
	int health;				// HP
	float radius = 8.0f;   // 当たり判定の半径
	bool deadFlg = false;	// 死亡しているかどうか

	DirectX::SimpleMath::Vector3 velocity = { 0.0f,0.0f,0.0f };

public:
	Player(int maxhp);  // コンストラクタ
	void Update(Input input);  // プレイヤーの更新
	void move(Input input);
	void Intro();
	void Outro();

	float GetRadius() const;
	void DecreaseHealth(int);
	bool GetdeadFlg() const;
	int GetHealth() const;

	void SetVelocity(DirectX::SimpleMath::Vector3 velo);
};

