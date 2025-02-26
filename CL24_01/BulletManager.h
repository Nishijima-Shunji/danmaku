#pragma once
#include "GameScene.h"
#include "Bullet.h"
#include "sound.h"

class GameScene;
class Player;
class Enemy;

class BulletManager
{
private:
    Sound sound;
    TextureManager* textureManager;
    // ���i�[
    std::vector<std::unique_ptr<Enemy>>& enemies;
    Player* player;
    GameScene* gamescene;
    //�e�֌W
    std::vector<std::unique_ptr<Bullet>> bullet;        // �e�̃��X�g
    std::vector<std::unique_ptr<Bullet>> enemybullet;   // �e�̃��X�g



public:
    BulletManager(GameScene* gamescene ,std::vector<std::unique_ptr<Enemy>>& enemies, Player*& player, TextureManager* texturemanager);
    ~BulletManager();

    void Init();
    void Update();
    void Draw();

    void ShootBullet();
    void EnemyShootBullet(Enemy* enemy);
    void OutBullet();
};

