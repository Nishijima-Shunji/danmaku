#pragma once
#include "Object.h"
#include "Input.h"
#include "Bullet.h"

#define MAP_WIDTH (560)	// �E�C���h�E�̕�
#define MAP_HEIGHT (720)	// �E�C���h�E�̍���

class Player : public Object {
private:
	int movementType = 0;	// �ړ����@�@0:�����Ɏ~�܂�@1:����
	float moveSpeed = 1.0f;	// �ړ����x
	int health;				// HP
	float radius = 8.0f;   // �����蔻��̔��a
	bool deadFlg = false;	// ���S���Ă��邩�ǂ���

	DirectX::SimpleMath::Vector3 velocity = { 0.0f,0.0f,0.0f };

public:
	Player(int maxhp);  // �R���X�g���N�^
	void Update(Input input);  // �v���C���[�̍X�V
	void move(Input input);
	void Intro();
	void Outro();

	float GetRadius() const;
	void DecreaseHealth(int);
	bool GetdeadFlg() const;
	int GetHealth() const;

	void SetVelocity(DirectX::SimpleMath::Vector3 velo);
};

