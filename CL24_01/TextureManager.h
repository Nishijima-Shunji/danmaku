#pragma once

#include <d3d11_1.h>
#include <string>
#include <map>

class TextureManager {
public:
    TextureManager(ID3D11Device* device);
    ~TextureManager();

    // �e�N�X�`�����擾����i�L���b�V���ɑ��݂���΂����Ԃ��j
    ID3D11ShaderResourceView* GetTexture(const wchar_t* imgname);

private:
    ID3D11Device* m_device;
    std::map<std::wstring, ID3D11ShaderResourceView*> textureCache;

    // �e�N�X�`�����L���b�V���ɒǉ���������֐�
    HRESULT LoadTextureFromFile(const wchar_t* imgname, ID3D11ShaderResourceView** textureView);

    // �L���b�V�����ꂽ�e�N�X�`�����������
    void ReleaseAllTextures();
};
