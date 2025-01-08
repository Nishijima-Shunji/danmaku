#include "Player.h"

// �X�e�[�^�X�̏����ݒ�
Player::Player() {
	// �v���C���[�̈ړ����x
	if (movementType == 0) {
		moveSpeed = 3.0f;
	}
	else if (movementType == 1) {
		moveSpeed = 0.1f;
	}


	// �v���C���[��HP
	health = 1;
	deadFlg = false;
}

void Player::Update(Input input) {

	move(input);    //�ړ�
	if (health <= 0) {
		deadFlg = true;
	}

}

void Player::move(Input input) {
	// �ړ����t���O
	bool moveFlg = false;
	DirectX::SimpleMath::Vector3 oldPos = pos;

	if (movementType == 0) {
		// �L�����N�^�[�ړ�
		velocity = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	}
	if (input.GetKeyPress(VK_A)) {
		velocity.x -= moveSpeed;
		moveFlg = true;
	}
	if (input.GetKeyPress(VK_D)) {
		velocity.x += moveSpeed;
		moveFlg = true;
	}
	if (input.GetKeyPress(VK_W)) {
		velocity.y += moveSpeed;
		moveFlg = true;
	}
	if (input.GetKeyPress(VK_S)) {
		velocity.y -= moveSpeed;
		moveFlg = true;
	}
	if (movementType == 1) {
		// moveFlg��false�Ȃ�ړ���~
		if (!moveFlg) {
			velocity = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
		}
	}
	// ���W�X�V
	pos += velocity;

	// �͈͊O�Ȃ猳�ɖ߂��i�ړ��o���Ȃ��j
	if (pos.x > MAP_WIDTH / 2 || pos.x < -(MAP_WIDTH / 2) ||
		pos.y > MAP_HEIGHT / 2 || pos.y < -(MAP_HEIGHT / 2)) {
		pos = oldPos;
	}
}

void Player::Intro() {
	if (pos.y < -100.0f) {
		velocity.y = 5.0f;
		pos += velocity;
	}
}

float Player::GetRadius() const {
	return radius;
}

void Player::DecreaseHealth(int damage) {
	health -= damage;
}

bool Player::GetdeadFlg() const {
	return deadFlg;
}

int Player::GetHealth() const {
	return health;
}
