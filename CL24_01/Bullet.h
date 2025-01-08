#pragma once
#include "Object.h"

class Bullet : public Object
{
private:
	bool activeFlg = false;
	int bulletDamage = 1;
	float moveSpeed;
	int bulletType = 0;

	float angleOffset = 0.0f;
	float expansionSpeed = 1.0f; // îºåaÇÃçLÇ™ÇËë¨ìx
	float rotationSpeed = 0.01f; // âÒì]ÇÃë¨ìx
	float rotationOffset;
	float initRadius;
	float radius = 10.0f;		// â~ÇÃîºåa
	const float pi = 3.14159265358979323846f;


	DirectX::SimpleMath::Vector3 direction;
	DirectX::SimpleMath::Vector3 velocity = { 0.0f,0.0f,0.0f };
	DirectX::SimpleMath::Vector3 t_pos = { 0.0f,0.0f,0.0f };


public:

	Bullet(int setType);
	~Bullet();

	void Update();
	void move();
	bool CheckCollision(const DirectX::XMFLOAT3& objPos, float r);
	int GetBulletDamege();

	void SetVelocity(float,float,float);
	void SetDirection(const DirectX::SimpleMath::Vector3& dir);
	void SetRotationOffset(float angle);
	void SetTargetPos(DirectX::SimpleMath::Vector3 pos);
};


