#pragma once

#include <SimpleMath.h>
#include <vector>
#include <memory>

#include "direct3d.h"
#include "WICTextureLoader.h"
#include "TextureManager.h"

class Object
{
protected:
	Vertex vertexList[4] =
	{
		//=============TRIANGLESTRIP===============
		//	x      y     z     r     g     b     a     u     v
		{-0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},  // �O�Ԗڂ̒��_���W�@{ x, y, z }
		{ 0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},  // �P�Ԗڂ̒��_���W
		{-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},  // �Q�Ԗڂ̒��_���W
		{ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},  // �R�Ԗڂ̒��_���W
	};

	////���W
	DirectX::SimpleMath::Vector3 pos = { 0.0f, 0.0f, 0.0f };
	//�傫��
	DirectX::XMFLOAT3 size = { 100.0f, 100.0f, 0.0f };
	//�F
	DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
	//�p�x
	float angle = 0.0f;

	// ���_�o�b�t�@
	ID3D11Buffer* m_pVertexBuffer = nullptr;

	ID3D11ShaderResourceView* m_pTextureView = nullptr;


	//�e�N�X�`�����c���ɉ���������Ă��邩
	int splitX = 1;
	int splitY = 1;
public:

	virtual ~Object();

	DirectX::XMFLOAT3 GetPos(void);
	DirectX::XMFLOAT3 GetSize(void);
	float GetAngle(void);
	DirectX::XMFLOAT4 GetColor(void);

	//�E�ォ�牽�ڂ�؂蔲���ĕ\�����邩
	float numU = 0;
	float numV = 0;

	virtual void Init(TextureManager* textureManager, const wchar_t* imgname);
	virtual void Draw();
	virtual void Uninit();

	virtual void SetPos(float x, float y, float z);		//���W���Z�b�g
	virtual void SetSize(float x, float y, float z);	//�傫�����Z�b�g
	virtual void SetAngle(float a);						//�p�x���Z�b�g
	virtual void SetColor(float r, float g, float b, float a);	//�F���Z�b�g

	virtual void SetTexture(TextureManager* textureManager, const wchar_t* imgname);
};

