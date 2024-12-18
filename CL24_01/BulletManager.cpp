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
	// ========�e�̍X�V========
	for (auto bulletIt = bullet.begin(); bulletIt != bullet.end();) {
		(*bulletIt)->Update();

		bool hit = false;
		
		for (auto& e_obj : enemies) {
			if ((*bulletIt)->CheckCollision(e_obj->GetPos(), e_obj->GetRadius())) {
				hit = true;
				e_obj->DecreaseHealth((*bulletIt)->GetBulletDamege());
				break; // ���[�v�𔲂���
			}
		}

		if (hit) {
			// �e���폜
			bulletIt = bullet.erase(bulletIt);
		}
		else {
			++bulletIt;
		}
	}
	for (auto enemybulletIt = enemybullet.begin(); enemybulletIt != enemybullet.end();) {
		(*enemybulletIt)->Update();

		bool hit = false;
		// �_���[�W�󂯂�
		if ((*enemybulletIt)->CheckCollision(player->GetPos(), player->GetRadius())) {
			hit = true;
			player->DecreaseHealth((*enemybulletIt)->GetBulletDamege());
			// �_���[�W�G�t�F�N�g
			gamescene->TakeDamege();
		}
		if (hit) {
			// �e���폜
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
	// �e�̐���
	bullet.emplace_back(std::make_unique<Bullet>(0));
	// �e�̏�����
	bullet.back()->Init(textureManager, L"asset/bullet.png");
	// �v���C���[�̍��W�ɐ���
	DirectX::XMFLOAT3 t_pos = player->GetPos();
	bullet.back()->SetPos(t_pos.x, t_pos.y + 50.0f, t_pos.z);
}

void BulletManager::EnemyShootBullet(DirectX::XMFLOAT3 t_pos) {
	// �e�̐���
	enemybullet.emplace_back(std::make_unique<Bullet>(1));
	// �e�̏�����
	enemybullet.back()->Init(textureManager, L"asset/enemybullet.png");
	enemybullet.back()->SetPos(t_pos.x, t_pos.y - 0.5f, t_pos.z);
}

// �e���͈͊O�ɍs���ƍ폜
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