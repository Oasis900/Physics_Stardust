#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>

#include "../Components/CTransform.h"
#pragma region DX Math Variables
using DirectX::XMMATRIX;
using DirectX::XMFLOAT4X4;
using DirectX::XMFLOAT4;
using DirectX::XMFLOAT3;
#pragma endregion

#pragma region DX Matrix Functions
using DirectX::XMMatrixTranslation;
using DirectX::XMMatrixRotationX;
using DirectX::XMMatrixRotationY;
using DirectX::XMMatrixRotationZ;
using DirectX::XMMatrixScaling;
#pragma endregion

using std::string;


struct Geometry
{
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int numberOfIndices;

	UINT vertexBufferStride;
	UINT vertexBufferOffset;
};

struct Material
{
	XMFLOAT4 diffuse;
	XMFLOAT4 ambient;
	XMFLOAT4 specular;
};

class GameObject
{
	// TODO (Game Object) : Extract all transform & render variables and logic to relevant components.
	
	GameObject* parent_ = nullptr;
	CTransform* transform_comp_ = nullptr;

	XMFLOAT3 _rotation;
	XMFLOAT3 _scale;

	string type_;
	XMFLOAT4X4 _world;

	Geometry _geometry;
	Material _material;

	ID3D11ShaderResourceView* _textureRV = nullptr;
	
public:
	GameObject(string type, Geometry geometry, Material material);
	~GameObject();
	
	CTransform* GetTransform() const { return transform_comp_; }

	string GetType() const { return type_; }

	void SetParent(GameObject * parent) { parent_ = parent; }
	
	void SetScale(XMFLOAT3 scale) { _scale = scale; }
	void SetScale(float x, float y, float z) { _scale.x = x; _scale.y = y; _scale.z = z; }

	XMFLOAT3 GetScale() const { return _scale; }

	void SetRotation(XMFLOAT3 rotation) { _rotation = rotation; }
	void SetRotation(float x, float y, float z) { _rotation.x = x; _rotation.y = y; _rotation.z = z; }

	XMFLOAT3 GetRotation() const { return _rotation; }
	
	// Rendering information
	Geometry GetGeometryData() const { return _geometry; }
	Material GetMaterial() const { return _material; }
	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }

	void SetTextureRV(ID3D11ShaderResourceView * textureRV) { _textureRV = textureRV; }
	ID3D11ShaderResourceView* const* GetTextureRV() { return &_textureRV; }
	bool HasTexture() const { return _textureRV ? true : false; }

	void Update(const float& dt);
	void Draw(ID3D11DeviceContext * pImmediateContext);
	
};

