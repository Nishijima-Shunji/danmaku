#include "SceneManager.h"
#include "BaseScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"

BaseScene* SceneManager::m_pScene = nullptr; // nullptr �ŏ�����

void SceneManager::ChangeScene(SCENE scene , int score) {
    if (m_pScene != nullptr) {
        delete m_pScene;
    }

    switch (scene) {
    case SCENE::TITLE:
        m_pScene = new TitleScene(); // �^�C�g���V�[����ݒ�
        break;
    case SCENE::GAME:
        m_pScene = new GameScene(score);  // �Q�[���V�[����ݒ�
        break;
    case SCENE::RESULT:
        m_pScene = new ResultScene(score); // ���U���g�V�[����ݒ�
        break;
    default:
        break;
    }
}

void SceneManager::Update() {
    if (m_pScene) {
        m_pScene->Update(); // ���݂̃V�[���̍X�V
    }
}

void SceneManager::Render() {
    if (m_pScene) {
        m_pScene->Draw(); // ���݂̃V�[���̕`��
    }
}
