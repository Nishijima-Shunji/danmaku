#include "TextureManager.h"
#include "WICTextureLoader.h" // CreateWICTextureFromFile ���g�����߂ɕK�v

TextureManager::TextureManager(ID3D11Device* device)
    : m_device(device)
{
    // �R���X�g���N�^
}

TextureManager::~TextureManager() {
    // �f�X�g���N�^�ŃL���b�V�����̑S�e�N�X�`�������
    ReleaseAllTextures();
}

ID3D11ShaderResourceView* TextureManager::GetTexture(const wchar_t* imgname) {
    // �t�@�C���p�X���΃p�X�ɕϊ�
    wchar_t fullPath[MAX_PATH];
    GetFullPathName(imgname, MAX_PATH, fullPath, NULL);

    std::wstring imgPath = fullPath;

    // �L���b�V�����m�F
    auto it = textureCache.find(imgPath);
    if (it != textureCache.end()) {
        // �L���b�V���ɑ��݂���ꍇ�A�Q�ƃJ�E���g�𑝂₵�ĕԂ�
        it->second->AddRef();
        printf("���݂���e�N�X�`��\n");
        return it->second;
    }

    // �V�����e�N�X�`����ǂݍ���
    ID3D11ShaderResourceView* textureView = nullptr;
    HRESULT hr = LoadTextureFromFile(fullPath, &textureView);
    if (FAILED(hr)) {
        MessageBoxA(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "�G���[", MB_ICONERROR | MB_OK);
        return nullptr;
    }

    // �L���b�V���ɒǉ�
    textureCache[imgPath] = textureView;
    printf("�V�����o�^\n");
    return textureView;
}

HRESULT TextureManager::LoadTextureFromFile(const wchar_t* imgname, ID3D11ShaderResourceView** textureView) {
    // �e�N�X�`�����t�@�C������ǂݍ���
    return DirectX::CreateWICTextureFromFile(m_device, imgname, NULL, textureView);
}

void TextureManager::ReleaseAllTextures() {
    // �L���b�V�����̑S�e�N�X�`�������
    for (auto& pair : textureCache) {
        if (pair.second) {
            pair.second->Release();
        }
    }
    textureCache.clear();
}
