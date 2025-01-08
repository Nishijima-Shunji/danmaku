#pragma once
#include <memory>
#include "BaseScene.h"
#include "BulletManager.h"
#include "Player.h"
#include "Enemy.h"

#define MAP_WIDTH (560)	// ウインドウの幅
#define MAP_HEIGHT (720)	// ウインドウの高さ

// 前方宣言
class BulletManager;
class Enemy;

class GameScene : public BaseScene
{
private:
    TextureManager* textureManager;     // テクスチャ管理の呼び出し
    BulletManager* bulletManager;       // 弾の管理の呼び出し

    Player* player;         // プレイヤー
    Object* bg;             // 背景

    int state = 0;
   
    std::vector<std::unique_ptr<Object>> health;        // 体力のリスト
    //std::vector<Bullet*> bullet;    // 弾のリスト
    int shootcount = 0; // 弾の制限用
    int shootInterval = 5;  //弾の間隔

    //敵関係
    std::vector<std::unique_ptr<Enemy>> enemies;    // 敵のリスト
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

