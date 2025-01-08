#include "Bullet.h"
#include <cmath>

Bullet::Bullet(int setType) : bulletType(setType), rotationOffset(0.0f), initRadius(10.0f) {
	if (setType == 2) {
		moveSpeed = 0.0001f;
	}
	else {
		moveSpeed = 0.3f;
	}
}

Bullet::~Bullet() {

}

void Bullet::Update() {
	move();
}

void Bullet::move() {
	switch (bulletType) {
	// �����̒e
	case 0:	
		direction = { 0.0f,1.0f,0.0f };
		break;

	// �ʏ�G�̒e
	case 1:
		direction = { 0.0f,-1.0f,0.0f };
		break;

	// ����G�̒e
	case 2:
		// ��]�̍X�V�i�e�e���ƂɈقȂ�p�x���g�p�j
		rotationOffset += rotationSpeed; // �p�x��i�߂ĉ�]

		// ���a�𑝉������āA�e���L����
		initRadius += expansionSpeed; // �ȑO�� initialRadius �� initRadius �ɕύX

		// �e�̈ʒu���X�V���邽�߂ɁA�G�̈ʒu����Ɍv�Z
		float offsetX = initRadius * std::cos(rotationOffset); // ��]��� x ���W
		float offsetY = initRadius * std::sin(rotationOffset); // ��]��� y ���W

		// �e�̐i�s�����x�N�g�����X�V�i��]��̕����j
		direction = DirectX::SimpleMath::Vector3(offsetX, offsetY, 0.0f);

		// �V�����ʒu���v�Z�i�G�̈ʒu����ɂ��ĉ�]������j
		pos = DirectX::SimpleMath::Vector3(t_pos.x + offsetX, t_pos.y + offsetY, t_pos.z);

		break;
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

void Bullet::SetVelocity(float x, float y, float z) {
	velocity = DirectX::SimpleMath::Vector3(x, y, z);
}

void Bullet::SetDirection(const DirectX::SimpleMath::Vector3& dir) {
	direction = dir;
}

void Bullet::SetRotationOffset(float angle) {
	rotationOffset = angle; // ��]�p�x��ݒ�
}

void Bullet::SetTargetPos(DirectX::SimpleMath::Vector3 pos) {
	t_pos = pos;
}