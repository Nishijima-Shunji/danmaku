#include "ResultScene.h"
#include "Game.h"
#include <cmath>

ResultScene::ResultScene(int score) : score(score) {
	sound.Init();
	TextureManager* textureManager = new TextureManager(g_pDevice);

	result_bg = new Object;
	result_bg->Init(textureManager, L"asset/Result.png");
	result_bg->SetPos(0.0f, 0.0f, 0.0f);			//�ʒu
	result_bg->SetSize(800.0f, 600.0f, 0.0f);		//�傫��
	result_bg->SetColor(0.8f, 0.8f, 0.8f, 1.0f);

	button = new Object;
	button->Init(textureManager, L"asset/Enter.png");
	button->SetPos(0.0f, -300.0f, 0.0f);			//�ʒu
	button->SetSize(150.0f, 120.0f, 0.0f);		//�傫��

	score_bg = new Object;
	score_bg->Init(textureManager, L"asset/score.png");
	score_bg->SetPos(0.0f, 60.0f, 0.0f);			//�ʒu
	score_bg->SetSize(500.0f, 500.0f, 0.0f);		//�傫��

	for (int i = 0; i < 5; i++) {
		// UI�̐���
		scoreNum.emplace_back(std::make_unique<Object>());
		scoreNum.back()->Init(textureManager, L"asset/num.png", 10, 1);
		scoreNum.back()->SetPos((i * 60.0f) - 125.0f, 0.0f, 0.0f);
		scoreNum.back()->SetSize(60.0f, 60.0f, 0.0f);
		scoreNum.back()->SetUV(0, 0);
	}
}

ResultScene::~ResultScene() {
	delete result_bg;
	delete button;
	delete score_bg;
}

void ResultScene::Update() {
	input.Update();

	// ==========�{�^���A�j���[�V����==========
	time += 0.016f;
	// cos�g���v�Z
	float angle = offset + amplitude * std::cos(2.0f * 3.14159265358979f * frequency * time);
	// �p�x��ݒ�
	button->SetAngle(angle);

	// ==========�X�R�A�\���p==========
	int tempScore = score;
	for (int i = static_cast<int>(scoreNum.size()) - 1; i >= 0; i--) {
		int digit = tempScore % 10;  // �E�[�̌����擾
		tempScore /= 10;            // �X�R�A��10�Ŋ����Ď��̌��֐i��

		// UV�����̒l�Ɋ�Â��Đݒ�
		scoreNum[i]->SetUV(digit, 0);
	}

	if (input.GetKeyRelease(VK_RETURN)) {
		SceneManager::ChangeScene(SceneManager::TITLE);
	}
}

void ResultScene::Draw() {
	result_bg->Draw();
	button->Draw();
	score_bg->Draw();
	for (auto& obj : scoreNum) {
		obj->Draw();
	}
}