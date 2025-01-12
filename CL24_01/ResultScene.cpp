#include "ResultScene.h"
#include "Game.h"
#include <cmath>

ResultScene::ResultScene(int score) : score(score) {
	sound.Init();
	TextureManager* textureManager = new TextureManager(g_pDevice);

	result_bg = new Object;
	result_bg->Init(textureManager, L"asset/Result.png");
	result_bg->SetPos(0.0f, 0.0f, 0.0f);			//位置
	result_bg->SetSize(800.0f, 600.0f, 0.0f);		//大きさ
	result_bg->SetColor(0.8f, 0.8f, 0.8f, 1.0f);

	button = new Object;
	button->Init(textureManager, L"asset/Enter.png");
	button->SetPos(0.0f, -300.0f, 0.0f);			//位置
	button->SetSize(150.0f, 120.0f, 0.0f);		//大きさ

	score_bg = new Object;
	score_bg->Init(textureManager, L"asset/score.png");
	score_bg->SetPos(0.0f, 60.0f, 0.0f);			//位置
	score_bg->SetSize(500.0f, 500.0f, 0.0f);		//大きさ

	for (int i = 0; i < 5; i++) {
		// UIの生成
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

	// ==========ボタンアニメーション==========
	time += 0.016f;
	// cos波を計算
	float angle = offset + amplitude * std::cos(2.0f * 3.14159265358979f * frequency * time);
	// 角度を設定
	button->SetAngle(angle);

	// ==========スコア表示用==========
	int tempScore = score;
	for (int i = static_cast<int>(scoreNum.size()) - 1; i >= 0; i--) {
		int digit = tempScore % 10;  // 右端の桁を取得
		tempScore /= 10;            // スコアを10で割って次の桁へ進む

		// UVを桁の値に基づいて設定
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