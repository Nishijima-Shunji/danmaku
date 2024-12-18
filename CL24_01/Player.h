#pragma once
#include "Object.h"
#include "Input.h"
#include "Bullet.h"

class Player : public Object {
private:
	int movementType = 0;	// �ړ����@�@0:�����Ɏ~�܂�@1:����
	float moveSpeed = 1.0f;	// �ړ����x
	int health;				// HP
	float radius = 10.0f;   // �����蔻��̔��a
	bool deadFlg = false;	// ���S���Ă��邩�ǂ���

	DirectX::SimpleMath::Vector3 velocity = { 0.0f,0.0f,0.0f };

public:
	Player();  // �R���X�g���N�^
	void Update(Input input);  // �v���C���[�̍X�V
	void move(Input input);
	void Intro();

	float GetRadius() const;
	void DecreaseHealth(int);
	bool GetdeadFlg() const;
	int GetHealth() const;


};

