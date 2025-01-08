#pragma once
#include <memory>
#include "BaseScene.h"
#include "BulletManager.h"
#include "Player.h"
#include "Enemy.h"

#define MAP_WIDTH (560)	// �E�C���h�E�̕�
#define MAP_HEIGHT (720)	// �E�C���h�E�̍���

// �O���錾
class BulletManager;
class Enemy;

class GameScene : public BaseScene
{
private:
    TextureManager* textureManager;     // �e�N�X�`���Ǘ��̌Ăяo��
    BulletManager* bulletManager;       // �e�̊Ǘ��̌Ăяo��

    Player* player;         // �v���C���[
    Object* bg;             // �w�i

    int state = 0;
   
    std::vector<std::unique_ptr<Object>> health;        // �̗͂̃��X�g
    //std::vector<Bullet*> bullet;    // �e�̃��X�g
    int shootcount = 0; // �e�̐����p
    int shootInterval = 5;  //�e�̊Ԋu

    //�G�֌W
    std::vector<std::unique_ptr<Enemy>> enemies;    // �G�̃��X�g
    float spawnTimer =  0.0f;
    int enemyType = 0;



public:


    GameScene();
    ~GameScene();

    void Update() override;
    void Draw() override;

    void SpawnEnemy(int type);
    void AddEnemy(const std::wstring& baseTexturePath, int enemyType);
    void RemoveEnemy(Enemy* enemy);
    void TakeDamege();

    void Intro();

    Player* GetPlayer();
};

