#include "GameScene.h"
#include "Game.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <sstream>

std::chrono::high_resolution_clock::time_point start;

GameScene::GameScene() {
	textureManager = new TextureManager(g_pDevice);

	// �v���C���[�̐���
	player = new Player;
	player->Init(textureManager, L"asset/player.png");
	player->SetPos(0.0f, -500.0f, 0.0f);
	player->SetSize(40.0f, 40.0f, 0.0f);

	// �w�i�̐���
	bg = new Object;
	bg->Init(textureManager, L"asset/Gamebg.png");
	bg->SetPos(0.0f, 0.0f, 0.0f);
	bg->SetSize(560.0f, 720.0f, 0.0f);
	bg->SetColor(1.0f, 0.0f, 0.0f, 0.0f);

	bulletManager = new BulletManager(this, enemies, player, textureManager);
}

GameScene::~GameScene() {
	// TextureManager�����
	delete textureManager;
	delete bulletManager;
	delete player;
	delete bg;
}

// �X�V
void GameScene::Update() {
	input.Update();
	//=====================�C���g���A�j���[�V����=====================
	if (state == 0) {
		Intro();
	}
	//=====================�Q�[���X�^�[�g=====================
	else if (state == 1) {
		// ���݂̎��Ԃ��擾
		auto now = std::chrono::high_resolution_clock::now();
		// �o�ߎ��Ԃ��v�Z
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
		// ========�e����========
		if (input.GetKeyPress(VK_SPACE)) {
			if (shootcount % shootInterval == 0) {
				bulletManager->ShootBullet();
				shootcount = 0;
			}
			shootcount++;
		}

		bulletManager->Update();
		// ========�e�͈̔͌��m========
		bulletManager->OutBullet();

		// ========�G����========
		spawnTimer += 1.0f / 60.0f;
		// ����̎��Ԃ̎���������ȓG�𐶐�
		if (elapsed.count() == 100) {
			enemyType = 1;
		}
		if (spawnTimer >= rand() % 5 + 1) {
			spawnTimer = 0.0f;
			float spawnX, spawnY;
			spawnX = rand() % MAP_WIDTH - (MAP_WIDTH / 2);  // -470 �` 390�͈̔͂�X�ʒu�������_������
			spawnY = (MAP_HEIGHT / 2);
			SpawnEnemy(spawnX, spawnY, enemyType);
			//���������G�̎�ނ��m�[�}���łȂ��Ȃ�
			if (enemyType != 0) {
				// �G�̎�ނ��m�[�}���ɐݒ�
				enemyType = 0;
			}
		}

		// ========�L�����N�^�[�X�V========
		player->Update(input);

		// �_���[�W�G�t�F�N�g��Ԃ��珙�X�ɓ����ɖ߂�
		if (bg->GetColor().w != 0.0f) {
			bg->SetColor(1.0f, 0.0f, 0.0f, bg->GetColor().w - 0.01f);
		}

		// ========�G�̍X�V========
		for (auto& enemy : enemies) {
			enemy->Update();
			int state = enemy->GetState();
			if (state == 1 && enemy->CanShoot()) {
				// �v���C���[�̍��W�ɐ���
				DirectX::XMFLOAT3 t_pos = enemy->GetPos();
				//�e�̔��˕��@���G�l�~�[�^�C�v�ɂ����
				switch (enemy->GetEnemyType()) {
				case 0:
					bulletManager->EnemyShootBullet(t_pos);
					break;
				case 1:
					break;
				}
				enemy->ResetCoolTime();
			}
		}

		// �폜�t���O�������Ă���G���폜
		enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const std::unique_ptr<Enemy>& enemy) {
			return enemy->GetDeadFlg();
			}),
			enemies.end());


		// ========���S========
		if (player->GetdeadFlg()) {
			SceneManager::ChangeScene(SceneManager::RESULT);
		}

		// �f�o�b�O
		if (input.GetKeyTrigger(VK_3)) {
			SceneManager::ChangeScene(SceneManager::RESULT);
		}
	}
	// ���׌y��
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}


void GameScene::Draw() {
	player->Draw();
	bulletManager->Draw();
	for (auto& obj : enemies) {
		obj->Draw();
	}
	for (auto& obj : health) {
		obj->Draw();
	}
	bg->Draw();
}

void GameScene::SpawnEnemy(float posX, float posY, int type) {
	// �G�̐���
	enemies.emplace_back(std::make_unique<Enemy>(type));
	// �G�̏�����
	AddEnemy(L"asset/enemy",type);
	// �w��̍��W�ɐ���
	enemies.back()->SetPos(posX, posY, 0.0f);
	enemies.back()->SetSize(enemies.back()->GetRadius() * 2, enemies.back()->GetRadius() * 2, 0.0f);
}

void GameScene::AddEnemy(const std::wstring& baseTexturePath, int enemyType) {
	// �e�N�X�`���p�X�𐶐�
	std::wstringstream texturePath;
	texturePath << baseTexturePath << enemyType << L".png";

	enemies.back()->Init(textureManager, texturePath.str().c_str());
}


void GameScene::RemoveEnemy(Enemy* enemy) {
	if (!enemy) {
		return;  // �����ȃ|�C���^�͖���
	}
	// �Ώۂ̓G��enemies����T���č폜
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[enemy](const std::unique_ptr<Enemy>& e) {
			return e.get() == enemy;
		}),
		enemies.end());
}

// �_���[�W���󂯂���
void GameScene::TakeDamege() {
	// �̗͌��炷
	health.erase(health.end() - 1);
	// �w�i�^���ԂɁi�_���[�W�G�t�F�N�g�j
	bg->SetColor(1.0f, 0.0f, 0.0f, 0.7f);
}

void GameScene::Intro() {
	// ���[�v�J�E���g
	static int animcount;
	// ���ݕ\�������̗�
	static int healthval;
	// �̗͂̍ő�l�i���̐��l�܂ő̗͐�������j
	int maxhealth = player->GetHealth();
	player->Intro();


	if (player->GetPos().y >= -100.0f) {
		if (animcount % 10 == 0 && healthval < maxhealth) {
			// UI�̐���
			health.emplace_back(std::make_unique<Object>());
			// UI�̏�����
			health.back()->Init(textureManager, L"asset/health.png");
			// �ʒu�ݒ�
			health.back()->SetPos(120.0f + healthval + (healthval % 10) * 15.0f, -300.0f - (healthval / 10) * 15.0f, 0.0f);
			health.back()->SetSize(15.0f, 15.0f, 0.0f);
			healthval++;
		}
		// �̗͂��ő�ɂȂ�����A�j���[�V�����I��
		else if (healthval == maxhealth) {
			state = 1;
			healthval = 0;
			animcount = 0;
			// �Q�[�����Ԃ̌v���J�n
			start = std::chrono::high_resolution_clock::now();
		}
	}
	animcount++;
}

Player* GameScene::GetPlayer() {
	return player;
}
