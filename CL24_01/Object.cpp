#include "Object.h"
#include <iostream>

Object::~Object() {

}


void Object::Init(TextureManager* textureManager, const wchar_t* imgname) {
	// ���_�o�b�t�@���쐬����
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexList);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = g_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);

	//�e�N�X�`�����Z�b�g
	SetTexture(textureManager, imgname);
}

	void Object::Draw() {
		UINT strides = sizeof(Vertex);
		UINT offsets = 0;
		g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);

		//�e�N�X�`�����s�N�Z���V�F�[�_�[�ɓn��
		g_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureView);

		//�萔�o�b�t�@���X�V
		ConstBuffer cb;

		//�v���W�F�N�V�����ϊ��s����쐬
		cb.matrixProj = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
		cb.matrixProj - DirectX::XMMatrixTranspose(cb.matrixProj);

		//���[���h�ϊ��s��̍쐬
		//���I�u�W�F�N�g�̈ʒu�E�傫���E�������w��
		cb.matrixWorld = DirectX::XMMatrixScaling(size.x, size.y, size.z);
		cb.matrixWorld *= DirectX::XMMatrixRotationZ(angle * 3.14f / 180);
		cb.matrixWorld *= DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
		cb.matrixWorld = DirectX::XMMatrixTranspose(cb.matrixWorld);

		//UV�A�j���[�V�����̍s��쐬
		float u = (float)numU / splitX;
		float v = (float)numV / splitY;
		cb.matrixTex = DirectX::XMMatrixTranslation(u, v, 0.0f);
		cb.matrixTex = DirectX::XMMatrixTranspose(cb.matrixTex);

		//���_�J���[�̃f�[�^���쐬
		cb.color = color;

		//�s����V�F�[�_�[�ɓn��
		g_pDeviceContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

		g_pDeviceContext->Draw(4, 0); // �`�施��
	}

void Object::Uninit() {
	SAFE_RELEASE(m_pTextureView);
	SAFE_RELEASE(m_pVertexBuffer);
}

	//���W���Z�b�g����
void Object::SetPos(float x, float y, float z) {
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

	//�傫�����Z�b�g����
void Object::SetSize(float x, float y, float z) {
	size.x = x;
	size.y = y;
	size.z = z;
}

	//�p�x���Z�b�g����
void Object::SetAngle(float a) {
	angle = a;
}

	//�F���Z�b�g����
void Object::SetColor(float r, float g, float b, float a) {
	color.x = r;
	color.y = g;
	color.z = b;
	color.w = a;
}
	//�ʒu���擾
DirectX::XMFLOAT3 Object::GetPos(void) {
	return pos;
}
	//�ʒu���Z�b�g
DirectX::XMFLOAT3 Object::GetSize(void) {
	return size;
}
	//�p�x���擾
float Object::GetAngle(void) {
	return angle;
}
	//
DirectX::XMFLOAT4 Object::GetColor(void) {
	return color;
}

	//�ʂɃe�N�X�`�����Z�b�g
void Object::SetTexture(TextureManager* textureManager, const wchar_t* imgname) {
	// ���݂̃e�N�X�`���r���[�����
	if (m_pTextureView) {
		m_pTextureView->Release();
		m_pTextureView = nullptr;
	}

	// TextureManager��ʂ��ĐV�����e�N�X�`�����擾
	m_pTextureView = textureManager->GetTexture(imgname);
	if (!m_pTextureView) {
		MessageBoxA(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "�G���[", MB_ICONERROR | MB_OK);
		return;
	}
}
