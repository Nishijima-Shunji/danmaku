#include "ResultScene.h"
#include "Game.h"

ResultScene::ResultScene() {
	TextureManager* textureManager = new TextureManager(g_pDevice);

	result_bg = new Object;
	result_bg->Init(textureManager, L"asset/Result.png");
	result_bg->SetPos(0.0f, 0.0f, 0.0f);			//ˆÊ’u
	result_bg->SetSize(1280.0f, 720.0f, 0.0f);		//‘å‚«‚³
	result_bg->SetAngle(0.0f);						//Šp“x
	result_bg->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	//F
}

ResultScene::~ResultScene() {
	delete result_bg;
}

void ResultScene::Update() {
	input.Update();
	if (input.GetKeyRelease(VK_RETURN)) {
		SceneManager::ChangeScene(SceneManager::TITLE);
	}
}

void ResultScene::Draw() {
	result_bg->Draw();
}