#include "Enemy.h"
#include <cmath>

// �R���X�g���N�^�@�G�����ŏ��ɓ����
Enemy::Enemy(int enemyType) : enemyType(enemyType) {
	targetPos.x = rand() % MAP_WIDTH - (MAP_WIDTH / 2);
	switch (enemyType) {
	case 0:
		targetPos.y = rand() % (MAP_HEIGHT / 2) - 10.0f;
		moveSpeed = 2.0f;
		break;
	case 1:
		moveSpeed = 1.0f;
		state = 1;
		break;
	}
}

void Enemy::Update() {
	if (health <= 0) {
		deadFlg = true;
	}

	shotTime++;

	move();
}

void Enemy::move() {
	//�����Ƌ������v�Z����
	DirectX::SimpleMath::Vector3 direction = targetPos - pos;
	float distance = direction.Length();

	//targetpos�ɓ������Ă��邩
	if (distance > 0.1f && state == 0) {
		// ���K�����Ĉړ������x�N�g�����擾
		direction.Normalize();

		// �ړ��ʂ��v�Z �����~���x
		velocity = direction * moveSpeed;
		pos += velocity;

		if ((targetPos - pos).LengthSquared() < velocity.LengthSquared()) {
			pos = targetPos; // �ړI�n�ɓ��B�����Ƃ݂Ȃ�
			state = 1;		 //������ԂɕύX
		}
	}

	if (enemyType == 1) {
		// ������ֈړ�
		velocity = DirectX::SimpleMath::Vector3{0.0f,1.0f,0.0f} * moveSpeed;
		pos += velocity;
	}
}

float Enemy::GetRadius() const {
	return radius;
}

int Enemy::GetHealth() const {
	return health;
}

bool Enemy::GetDeadFlg() const {
	return deadFlg;
}

int Enemy::GetState() const {
	return state;
}

int Enemy::GetEnemyType() const {
	return enemyType;
}

void Enemy::DecreaseHealth(int damage) {
	health -= damage;
}

bool Enemy::CanShoot() const {
	return shotTime >= shootCooltime;
}

void Enemy::ResetCoolTime() {
	shotTime = 0;
}