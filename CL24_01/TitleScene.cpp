#include "TitleScene.h"
#include "Game.h"

TitleScene::TitleScene() {
	TextureManager* textureManager = new TextureManager(g_pDevice);

	title_bg = new Object;  // �I�u�W�F�N�g����
	title_bg->Init(textureManager, L"asset/Gamebg.png");
	title_bg->SetPos(0.0f, 0.0f, 0.0f);	//�ʒu��ݒ�
	title_bg->SetSize(1280.0f, 720.0f, 0.0f);	//�傫����ݒ�
	title_bg->SetAngle(0.0f);	//�p�x��ݒ�
	title_bg->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	//�F��ݒ�
}
TitleScene::~TitleScene() {
	delete title_bg;
}

//�V�[���̃A�b�v�f�[�g
void TitleScene::Update() {
	input.Update();	//�L�[���͂̔���
	if (input.GetKeyTrigger(VK_RETURN)) {
		SceneManager::ChangeScene(SceneManager::GAME);	//�V�[����GAME�ֈڍs
	}
}

//�e�V�[���̕`��
void TitleScene::Draw() {
	title_bg->Draw();
}