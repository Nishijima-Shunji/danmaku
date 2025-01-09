#include "TitleScene.h"
#include "Game.h"
#include <cmath>

TitleScene::TitleScene() {
	TextureManager* textureManager = new TextureManager(g_pDevice);

	title_bg = new Object;  // �I�u�W�F�N�g����
	title_bg->Init(textureManager, L"asset/Gamebg.png");
	title_bg->SetPos(0.0f, 0.0f, 0.0f);	//�ʒu��ݒ�
	title_bg->SetSize(1280.0f, 720.0f, 0.0f);	//�傫����ݒ�
	title_bg->SetColor(0.0f, 0.0f, 0.0f, 1.0f);	//�F��ݒ�

	button = new Object;
	button->Init(textureManager, L"asset/Enter.png");
	button->SetPos(0.0f, -200.0f, 0.0f);			//�ʒu
	button->SetSize(300.0f, 240.0f, 0.0f);			//�傫��

	health = new Object;
	health->Init(textureManager, L"asset/health_nobg.png");
	health->SetPos(80.0f, 300.0f, 0.0f);			//�ʒu
	health->SetSize(40.0f, 40.0f, 0.0f);			//�傫��

	for (int i = 0; i < 2; i++) {
		// UI�̐���
		scoreNum.emplace_back(std::make_unique<Object>());
		scoreNum.back()->Init(textureManager, L"asset/num.png", 10, 1);
		scoreNum.back()->SetPos((i * 40.0f) + 125.0f, 300.0f, 0.0f);
		scoreNum.back()->SetSize(40.0f, 40.0f, 0.0f);
		scoreNum.back()->SetUV(0, 0);
	}
}
TitleScene::~TitleScene() {
	delete title_bg;
	delete button;
	delete health;
}

//�V�[���̃A�b�v�f�[�g
void TitleScene::Update() {
	if (state == 0) {
		input.Update();	//�L�[���͂̔���
		// �p�x��ݒ�
		// ==========�{�^���A�j���[�V����==========
		time += 0.016f;
		// cos�g���v�Z
		float angle = offset + amplitude * std::cos(2.0f * 3.14159265358979f * frequency * time);
		button->SetAngle(angle);

		// ==========HP�\���p==========
		int tempScore = maxhp;
		for (int i = static_cast<int>(scoreNum.size()) - 1; i >= 0; i--) {
			int digit = tempScore % 10;  // �E�[�̌����擾
			tempScore /= 10;            // �X�R�A��10�Ŋ����Ď��̌��֐i��

			// UV�����̒l�Ɋ�Â��Đݒ�
			scoreNum[i]->SetUV(digit, 0);
		}


		if (input.GetKeyTrigger(VK_UP)) {
			if (maxhp < max) {
				maxhp++;
			}
		}
		else if (input.GetKeyTrigger(VK_DOWN)) {
			if (maxhp > 1) {
				maxhp--;
			}
		}
		if (input.GetKeyTrigger(VK_RETURN)) {
			state = 1;
		}
	}
	if (state == 1) {
		title_bg->SetColor(1.0f, 1.0f, 1.0f, title_bg->GetColor().w - 0.01f);
		button->SetColor(1.0f, 1.0f, 1.0f, button->GetColor().w - 0.01f);

		if (title_bg->GetColor().w <= 0.0f) {
			SceneManager::ChangeScene(SceneManager::GAME, maxhp);	//�V�[����GAME�ֈڍs
		}
	}
}

//�e�V�[���̕`��
void TitleScene::Draw() {
	title_bg->Draw();
	button->Draw();
	health->Draw();
	for (auto& obj : scoreNum) {
		obj->Draw();
	}
}