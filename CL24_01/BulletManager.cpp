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
			switch (rand() % 4) {
			case 0: sound.Play(SOUND_LABEL_SEhit1); break;
			case 1: sound.Play(SOUND_LABEL_SEhit2); break;
			case 2: sound.Play(SOUND_LABEL_SEhit3); break;
			}
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
	bullet.back()->SetSize(30.0f, 30.0f, 0.0f);
}

void BulletManager::EnemyShootBullet(Enemy* enemy) {
	DirectX::XMFLOAT3 t_pos = enemy->GetPos();

	switch (enemy->GetEnemyType()) {
	case 0:
		// �e�̐���
		enemybullet.emplace_back(std::make_unique<Bullet>(1));
		// �e�̏�����
		enemybullet.back()->Init(textureManager, L"asset/enemybullet.png");
		enemybullet.back()->SetPos(t_pos.x, t_pos.y - 0.5f, t_pos.z);
		enemybullet.back()->SetSize(30.0f, 30.0f, 0.0f);

		break;
	case 1:
		int numBullets = rand() % 9 + 1; // �e�̐�
		float radius = 10.0f; // �~�̔��a
		const float pi = 3.14159265358979323846f;

		for (int i = 0; i < numBullets; ++i) {
			float angle = i * 2.0f * pi / numBullets; // ���Ԋu�̊p�x���v�Z

			// �i�s�����iunit vector�j�Ƃ��āA��]�Ɋ�Â��������v�Z
			float directionX = std::cos(angle); // x�����̐i�s����
			float directionY = std::sin(angle); // y�����̐i�s����

			// �e�𐶐�
			enemybullet.emplace_back(std::make_unique<Bullet>(2));

			// �e�̏�����
			enemybullet.back()->Init(textureManager, L"asset/enemybullet.png");

			// �e�̐i�s�����x�N�g���i���������ݒ�j
			enemybullet.back()->SetDirection(DirectX::SimpleMath::Vector3(directionX, directionY, 0.0f));

			// ������]������ݒ�
			enemybullet.back()->SetRotationOffset(angle); // ������]�p�x

			// �e�̈ʒu�𒆐S������˂����悤�ɐݒ�
			enemybullet.back()->SetPos(t_pos.x + radius * directionX, t_pos.y + radius * directionY, t_pos.z);

			// �e�̈ʒu�𒆐S������˂����悤�ɐݒ�
			enemybullet.back()->SetTargetPos(t_pos);

			enemybullet.back()->SetSize(30.0f, 30.0f, 0.0f);

		}

		break;
	}
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