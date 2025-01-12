#include "BulletManager.h"
#include <vector>
#include <cmath>

BulletManager::BulletManager(GameScene* gamescene, std::vector<std::unique_ptr<Enemy>>& enemies, Player*& player, TextureManager* texturemanager)
	: gamescene(gamescene), enemies(enemies), player(player), textureManager(texturemanager) {
	sound.Init();
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
			switch (rand() % 4) {
			case 0: sound.Play(SOUND_LABEL_SEhit1); break;
			case 1: sound.Play(SOUND_LABEL_SEhit2); break;
			case 2: sound.Play(SOUND_LABEL_SEhit3); break;
			}
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
	bullet.back()->SetSize(30.0f, 30.0f, 0.0f);
}

void BulletManager::EnemyShootBullet(Enemy* enemy) {
	DirectX::XMFLOAT3 t_pos = enemy->GetPos();

	switch (enemy->GetEnemyType()) {
	case 0:
		// 弾の生成
		enemybullet.emplace_back(std::make_unique<Bullet>(1));
		// 弾の初期化
		enemybullet.back()->Init(textureManager, L"asset/enemybullet.png");
		enemybullet.back()->SetPos(t_pos.x, t_pos.y - 0.5f, t_pos.z);
		enemybullet.back()->SetSize(30.0f, 30.0f, 0.0f);

		break;
	case 1:
		int numBullets = rand() % 9 + 1; // 弾の数
		float radius = 10.0f; // 円の半径
		const float pi = 3.14159265358979323846f;

		for (int i = 0; i < numBullets; ++i) {
			float angle = i * 2.0f * pi / numBullets; // 等間隔の角度を計算

			// 進行方向（unit vector）として、回転に基づく方向を計算
			float directionX = std::cos(angle); // x方向の進行方向
			float directionY = std::sin(angle); // y方向の進行方向

			// 弾を生成
			enemybullet.emplace_back(std::make_unique<Bullet>(2));

			// 弾の初期化
			enemybullet.back()->Init(textureManager, L"asset/enemybullet.png");

			// 弾の進行方向ベクトル（方向だけ設定）
			enemybullet.back()->SetDirection(DirectX::SimpleMath::Vector3(directionX, directionY, 0.0f));

			// 初期回転方向を設定
			enemybullet.back()->SetRotationOffset(angle); // 初期回転角度

			// 弾の位置を中心から放射されるように設定
			enemybullet.back()->SetPos(t_pos.x + radius * directionX, t_pos.y + radius * directionY, t_pos.z);

			// 弾の位置を中心から放射されるように設定
			enemybullet.back()->SetTargetPos(t_pos);

			enemybullet.back()->SetSize(30.0f, 30.0f, 0.0f);

		}

		break;
	}
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