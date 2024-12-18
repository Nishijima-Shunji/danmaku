#include "Bullet.h"

Bullet::Bullet(int setType) : bulletType(setType) {
	moveSpeed = 0.3f;
}

Bullet::~Bullet() {

}

void Bullet::Update() {
	move();
}

void Bullet::move() {
	switch (bulletType) {
	case 0:
		direction = { 0.0f,1.0f,0.0f };
		break;
	case 1:
		direction = { 0.0f,-1.0f,0.0f };
		break;
	//case 2:

	//}
	}
	velocity += direction * moveSpeed;
		pos += velocity;
}

bool Bullet::CheckCollision(const DirectX::XMFLOAT3& objPos, float r) {
	DirectX::XMFLOAT3 circlePos = GetPos();
	float radius = 20.0f; // ���݂̉~�̔��a

	// ���S�Ԃ̋����̓����v�Z
	float dx = circlePos.x - objPos.x;
	float dy = circlePos.y - objPos.y;
	float distanceSquared = dx * dx + dy * dy;

	// ���a�̘a�̓��
	float radiusSum = radius + r;
	float radiusSumSquared = radiusSum * radiusSum;

	// �����̓�悪���a�̘a�̓��ȉ��ł���ΏՓ�
	return distanceSquared <= radiusSumSquared;
}

int Bullet::GetBulletDamege() {
	return bulletDamage;
}