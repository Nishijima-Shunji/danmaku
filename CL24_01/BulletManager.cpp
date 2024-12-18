#include "BulletManager.h"
#include <vector>

BulletManager::BulletManager(GameScene* gamescene ,std::vector<std::unique_ptr<Enemy>>& enemies, Player*& player, TextureManager* texturemanager)
	: gamescene(gamescene), enemies(enemies), player(player), textureManager(texturemanager) {

}

BulletManager::~BulletManager() {

}

void BulletManager::Init() {

}

void BulletManager::Update() {
	// ========弾の更新========
	for (auto bulletIt = bullet.begin(); bulletIt != bullet.end();) {
		(*bulletIt)->Update();

		bool hit = false;
		
		for (auto& e_obj : enemies) {
			if ((*bulletIt)->CheckCollision(e_obj->GetPos(), e_obj->GetRadius())) {
				hit = true;
				e_obj->DecreaseHealth((*bulletIt)->GetBulletDamege());
				break; // ループを抜ける
			}
		}

		if (hit) {
			// 弾を削除
			bulletIt = bullet.erase(bulletIt);
		}
		else {
			++bulletIt;
		}
	}
	for (auto enemybulletIt = enemybullet.begin(); enemybulletIt != enemybullet.end();) {
		(*enemybulletIt)->Update();

		bool hit = false;
		// ダメージ受ける
		if ((*enemybulletIt)->CheckCollision(player->GetPos(), player->GetRadius())) {
			hit = true;
			player->DecreaseHealth((*enemybulletIt)->GetBulletDamege());
			// ダメージエフェクト
			gamescene->TakeDamege();
		}
		if (hit) {
			// 弾を削除
			enemybulletIt = enemybullet.erase(enemybulletIt);
		}
		else {
			++enemybulletIt;
		}
	}
}

void BulletManager::Draw() {
	for (auto& obj : bullet) {
		obj->Draw();
	}
	for (auto& obj : enemybullet) {
		obj->Draw();
	}
}

void BulletManager::ShootBullet() {
	// 弾の生成
	bullet.emplace_back(std::make_unique<Bullet>(0));
	// 弾の初期化
	bullet.back()->Init(textureManager, L"asset/bullet.png");
	// プレイヤーの座標に生成
	DirectX::XMFLOAT3 t_pos = player->GetPos();
	bullet.back()->SetPos(t_pos.x, t_pos.y + 50.0f, t_pos.z);
}

void BulletManager::EnemyShootBullet(DirectX::XMFLOAT3 t_pos) {
	// 弾の生成
	enemybullet.emplace_back(std::make_unique<Bullet>(1));
	// 弾の初期化
	enemybullet.back()->Init(textureManager, L"asset/enemybullet.png");
	enemybullet.back()->SetPos(t_pos.x, t_pos.y - 0.5f, t_pos.z);
}

// 弾が範囲外に行くと削除
void BulletManager::OutBullet() {
	for (size_t i = 0; i < bullet.size();) {
		DirectX::XMFLOAT3 t_pos = bullet[i]->GetPos();
		if (-(MAP_WIDTH / 2) > t_pos.x || (MAP_WIDTH / 2) < t_pos.x ||
			-(MAP_HEIGHT / 2) > t_pos.y || (MAP_HEIGHT / 2) < t_pos.y) {
			bullet.erase(bullet.begin() + i);
		}
		else {
			++i;
		}
	}
}