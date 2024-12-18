#pragma once
#include "Object.h"
#include <DirectXMath.h>
#include "TextureManager.h"
#include "GameScene.h"

//�O���錾
class GameScene;

class Enemy : public Object {
private:
    GameScene* gameScene;

    DirectX::SimpleMath::Vector3 targetPos;
    DirectX::SimpleMath::Vector3 velocity;


    int enemyType;
    float moveSpeed;                // ���x
    int health = 3;			    // HP
    float radius = 20.0f;       // �����蔻��̔��a

    bool deadFlg = false;       //���S�ς݂��ǂ����̃t���O
    int state = 0;

    int shootCooltime = 100;        // �e�̃N�[���^�C��
    int shotTime;    // �e�������Ă���̌o�ߎ���

public:
    Enemy(int enemyType);

    void Update(); 

    void move();

    float GetRadius() const;
    int GetHealth() const;
    bool GetDeadFlg() const;
    int GetState() const;
    int GetEnemyType() const;

    void DecreaseHealth(int);
    bool CanShoot() const; // �e�����Ă邩�ǂ�������
    void ResetCoolTime(); // �N�[���_�E�������Z�b�g
};