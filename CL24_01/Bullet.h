#pragma once
#include "Object.h"

class Bullet : public Object
{
private:
	bool activeFlg = false;
	int bulletDamage = 1;
	float moveSpeed;
	int bulletType = 0;
	DirectX::SimpleMath::Vector3 direction;

	DirectX::SimpleMath::Vector3 velocity = { 0.0f,0.0f,0.0f };


public:

	Bullet(int setType);
	~Bullet();

	void Update();
	void move();
	bool CheckCollision(const DirectX::XMFLOAT3& objPos, float r);
	int GetBulletDamege();
};


