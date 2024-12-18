#include "Game.h"
#include <time.h>
#include <vector>
#include <iostream>

void Game::Init(HWND hWnd) {
	srand((unsigned)time(NULL));

	D3D_Create(hWnd);

	//sound.Init();	//サウンドを初期化
	//sound.Play(SOUND_LABEL_BGM000);	//BGMを再生

	//初期シーンをタイトルにする
	sm.ChangeScene(sm.TITLE);

}

void Game::Draw() {
	// ゲーム処理実行
	D3D_StartRender();
	sm.Render();
	D3D_FinishRender();
}

void Game::Uninit() {
	//sound.Uninit();			//サウンドを終了
	// 
	// DirectXの解放処理
	D3D_Release();
}

void Game::Update() {
	sm.Update();	//現在シーンのアップデートを実行
}
