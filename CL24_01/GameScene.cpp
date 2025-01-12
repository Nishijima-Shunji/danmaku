#include "GameScene.h"
#include "Game.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <sstream>

std::chrono::high_resolution_clock::time_point start;

GameScene::GameScene(int maxhp){
	sound.Init();
	sound.Play(SOUND_LABEL_BGM001);

	textureManager = new TextureManager(g_pDevice);

	// �v���C���[�̐���
	player = new Player(maxhp);
	player->Init(textureManager, L"asset/player.png");
	player->SetPos(0.0f, -500.0f, 0.0f);
	player->SetSize(40.0f, 40.0f, 0.0f);

	// �w�i�̐���
	bg = new Object;
	bg->Init(textureManager, L"asset/Gamebg.png");
	bg->SetPos(0.0f, 0.0f, 0.0f);
	bg->SetSize(560.0f, 720.0f, 0.0f);
	bg->SetColor(1.0f, 0.0f, 0.0f, 0.0f);

	// �X�R�A�w�i�̐���
	score_bg = new Object;
	score_bg->Init(textureManager, L"asset/score_bg.png");
	score_bg->SetPos(-250.0f, -300.0f, 0.0f);
	score_bg->SetSize(50.0f, 50.0f, 0.0f);

	for (int i = 0; i < 5; i++) {
		// UI�̐���
		scoreNum.emplace_back(std::make_unique<Object>());
		scoreNum.back()->Init(textureManager, L"asset/num.png", 10, 1);
		scoreNum.back()->SetPos((i * 25.0f) - 215.0f, -300.0f, 0.0f);
		scoreNum.back()->SetSize(25.0f, 25.0f, 0.0f);
		scoreNum.back()->SetUV(0, 0);
	}
	bulletManager = new BulletManager(this, enemies, player, textureManager);
}

GameScene::~GameScene() {
	// TextureManager�����
	delete textureManager;
	delete bulletManager;
	delete player;
	delete bg;
	delete score_bg;
}

// �X�V
void GameScene::Update() {
	input.Update();

	// �_���[�W�G�t�F�N�g��Ԃ��珙�X�ɓ����ɖ߂�
	if (bg->GetColor().w != 0.0f) {
		bg->SetColor(1.0f, 0.0f, 0.0f, bg->GetColor().w - 0.01f);
	}


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
				if (score != 0) {
					score--;
				}
				bulletManager->ShootBullet();
				shootcount = 0;
				sound.Play(SOUND_LABEL_SEthrow);
			}
			shootcount++;
		}

		bulletManager->Update();

		// ========�e�̉�ʊO���m========
		bulletManager->OutBullet();

		// ========�G����========
		spawnTimer += 1.0f / 60.0f;
		// ����̎��Ԃ̎���������ȓG�𐶐�
		if (elapsed.count() > 10000) {
			enemyType = 1;
			// �^�C�}�[�����Z�b�g
			start = now;
		}
		if (spawnTimer >= rand() % 5 + 1) {
			spawnTimer = 0.0f;
			if (enemies.size() < 30) {
				SpawnEnemy(enemyType);
				//���������G�̎�ނ��m�[�}���łȂ��Ȃ�
				if (enemyType != 0) {
					// �G�̎�ނ��m�[�}���ɐݒ�
					enemyType = 0;
				}
			}
		}

		// ========�L�����N�^�[�X�V========
		player->Update(input);

		// ========�G�̍X�V========
		for (auto it = enemies.begin(); it != enemies.end();) {
			auto& enemy = *it;
			enemy->Update();
			int state = enemy->GetState();

			// �G�̒e����
			if (state == 1 && enemy->CanShoot()) {
				bulletManager->EnemyShootBullet(enemy.get());
				enemy->ResetCoolTime();
			}

			// �͈͊O�֍s�����̗͂��Ȃ��Ȃ�Ə���
			if (enemy->GetDeadFlg() == true || enemy->GetPos().y > 500.0f) {
				// �X�R�A����
				score += (enemy->GetEnemyType() * 5 + 5) * 5;
				// �G�����S���Ă���ꍇ�폜
				it = enemies.erase(it);
				std::cout << score << std::endl;
			}
			else {
				// ����ȊO�͎��̗v�f�ɐi��
				++it;
			}
		}

		// ========���S========
		if (player->GetdeadFlg()) {
			player->SetVelocity(DirectX::SimpleMath::Vector3(0.0f,20.0f,0.0f));
			state = 2;
			sound.Play(SOUND_LABEL_SE002);
		}

		// ========�X�R�A�\���p========
		int tempScore = score;
		for (int i = static_cast<int>(scoreNum.size()) - 1; i >= 0; i--) {
			int digit = tempScore % 10;  // �E�[�̌����擾
			tempScore /= 10;			 // �X�R�A��10�Ŋ����Ď��̌��֐i��

			// UV�����̒l�Ɋ�Â��Đݒ�
			scoreNum[i]->SetUV(digit, 0);
		}
	}

	// =====================���S�A�j���[�V����=====================
	else if (state == 2) {
		Outro();
		if (player->GetPos().y < -400.0f) {
			sound.Stop(SOUND_LABEL_BGM001);
			SceneManager::ChangeScene(SceneManager::RESULT, score);
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
	score_bg->Draw();
	for (auto& obj : scoreNum) {
		obj->Draw();
	}
	bg->Draw();
}

void GameScene::SpawnEnemy(int type) {
	// �G�̐���
	enemies.emplace_back(std::make_unique<Enemy>(type));
	// �G�̏�����
	AddEnemy(L"asset/enemy", type);
	// �w��̍��W�ɐ���
	//enemies.back()->SetPos(posX, posY, 0.0f);
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
		return;
	}
	// �Ώۂ̓G��T���č폜
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[enemy](const std::unique_ptr<Enemy>& e) {
			return e.get() == enemy;
		}),
		enemies.end());
}

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
			health.back()->SetPos(120.0f + healthval + (healthval % 10) * 14.0f, -280.0f - (healthval / 10) * 15.0f, 0.0f);
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

void GameScene::Outro() {
	player->Outro();
}
