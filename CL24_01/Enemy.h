#pragma once
#include "Object.h"
#include <DirectXMath.h>
#include "TextureManager.h"
#include "GameScene.h"

//前方宣言
class GameScene;

class Enemy : public Object {
private:
    GameScene* gameScene;

    DirectX::SimpleMath::Vector3 targetPos;
    DirectX::SimpleMath::Vector3 velocity;


    int enemyType;
    float moveSpeed;                // 速度
    int health = 3;			    // HP
    float radius = 20.0f;       // 当たり判定の半径

    bool deadFlg = false;       //死亡済みかどうかのフラグ
    int state = 0;

    int shootCooltime = 100;        // 弾のクールタイム
    int shotTime;    // 弾を撃ってからの経過時間

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
    bool CanShoot() const; // 弾を撃てるかどうか判定
    void ResetCoolTime(); // クールダウンをリセット
};