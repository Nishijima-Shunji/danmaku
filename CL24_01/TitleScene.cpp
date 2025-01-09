#include "TitleScene.h"
#include "Game.h"
#include <cmath>

TitleScene::TitleScene() {
	TextureManager* textureManager = new TextureManager(g_pDevice);

	title_bg = new Object;  // オブジェクト生成
	title_bg->Init(textureManager, L"asset/Gamebg.png");
	title_bg->SetPos(0.0f, 0.0f, 0.0f);	//位置を設定
	title_bg->SetSize(1280.0f, 720.0f, 0.0f);	//大きさを設定
	title_bg->SetColor(0.0f, 0.0f, 0.0f, 1.0f);	//色を設定

	button = new Object;
	button->Init(textureManager, L"asset/Enter.png");
	button->SetPos(0.0f, -200.0f, 0.0f);			//位置
	button->SetSize(300.0f, 240.0f, 0.0f);			//大きさ

	health = new Object;
	health->Init(textureManager, L"asset/health_nobg.png");
	health->SetPos(80.0f, 300.0f, 0.0f);			//位置
	health->SetSize(40.0f, 40.0f, 0.0f);			//大きさ

	for (int i = 0; i < 2; i++) {
		// UIの生成
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

//シーンのアップデート
void TitleScene::Update() {
	if (state == 0) {
		input.Update();	//キー入力の判定
		// 角度を設定
		// ==========ボタンアニメーション==========
		time += 0.016f;
		// cos波を計算
		float angle = offset + amplitude * std::cos(2.0f * 3.14159265358979f * frequency * time);
		button->SetAngle(angle);

		// ==========HP表示用==========
		int tempScore = maxhp;
		for (int i = static_cast<int>(scoreNum.size()) - 1; i >= 0; i--) {
			int digit = tempScore % 10;  // 右端の桁を取得
			tempScore /= 10;            // スコアを10で割って次の桁へ進む

			// UVを桁の値に基づいて設定
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
			SceneManager::ChangeScene(SceneManager::GAME, maxhp);	//シーンをGAMEへ移行
		}
	}
}

//各シーンの描画
void TitleScene::Draw() {
	title_bg->Draw();
	button->Draw();
	health->Draw();
	for (auto& obj : scoreNum) {
		obj->Draw();
	}
}