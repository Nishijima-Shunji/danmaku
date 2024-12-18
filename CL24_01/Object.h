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
		{-0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},  // ０番目の頂点座標　{ x, y, z }
		{ 0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},  // １番目の頂点座標
		{-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},  // ２番目の頂点座標
		{ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},  // ３番目の頂点座標
	};

	////座標
	DirectX::SimpleMath::Vector3 pos = { 0.0f, 0.0f, 0.0f };
	//大きさ
	DirectX::XMFLOAT3 size = { 100.0f, 100.0f, 0.0f };
	//色
	DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
	//角度
	float angle = 0.0f;

	// 頂点バッファ
	ID3D11Buffer* m_pVertexBuffer = nullptr;

	ID3D11ShaderResourceView* m_pTextureView = nullptr;


	//テクスチャが縦横に何分割されているか
	int splitX = 1;
	int splitY = 1;
public:

	virtual ~Object();

	DirectX::XMFLOAT3 GetPos(void);
	DirectX::XMFLOAT3 GetSize(void);
	float GetAngle(void);
	DirectX::XMFLOAT4 GetColor(void);

	//右上から何個目を切り抜いて表示するか
	float numU = 0;
	float numV = 0;

	virtual void Init(TextureManager* textureManager, const wchar_t* imgname);
	virtual void Draw();
	virtual void Uninit();

	virtual void SetPos(float x, float y, float z);		//座標をセット
	virtual void SetSize(float x, float y, float z);	//大きさをセット
	virtual void SetAngle(float a);						//角度をセット
	virtual void SetColor(float r, float g, float b, float a);	//色をセット

	virtual void SetTexture(TextureManager* textureManager, const wchar_t* imgname);
};

