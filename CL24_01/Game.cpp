#include "Game.h"
#include <time.h>
#include <vector>
#include <iostream>

void Game::Init(HWND hWnd) {
	srand((unsigned)time(NULL));

	D3D_Create(hWnd);
	sound.Init();	//�T�E���h��������


	//�����V�[�����^�C�g���ɂ���
	sm.ChangeScene(sm.TITLE);

}

void Game::Draw() {
	// �Q�[���������s
	D3D_StartRender();
	sm.Render();
	D3D_FinishRender();
}

void Game::Uninit() {
	
	sound.Uninit();
	// DirectX�̉������
	D3D_Release();
}

void Game::Update() {
	sm.Update();	//���݃V�[���̃A�b�v�f�[�g�����s
}
