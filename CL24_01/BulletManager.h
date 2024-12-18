#pragma once
#include "GameScene.h"
#include "Bullet.h"

class GameScene;
class Player;
class Enemy;

class BulletManager
{
private:
    TextureManager* textureManager;
    // ‰¼Ši”[
    std::vector<std::unique_ptr<Enemy>>& enemies;
    Player* player;
    GameScene* gamescene;
    //’eŠÖŒW
    std::vector<std::unique_ptr<Bullet>> bullet;        // ’e‚ÌƒŠƒXƒg
    std::vector<std::unique_ptr<Bullet>> enemybullet;   // ’e‚ÌƒŠƒXƒg
public:
    BulletManager(GameScene* gamescene ,std::vector<std::unique_ptr<Enemy>>& enemies, Player*& player, TextureManager* texturemanager);
    ~BulletManager();

    void Init();
    void Update();
    void Draw();

    void ShootBullet();
    void EnemyShootBullet(DirectX::XMFLOAT3 t_pos);
    void OutBullet();
};

