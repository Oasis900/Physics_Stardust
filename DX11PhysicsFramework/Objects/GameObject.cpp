#include "GameObject.h"

GameObject::GameObject(string type, Geometry geometry, Material material) : _geometry(geometry), type_(type), _material(material)
{
	parent_ = nullptr;
	transform_comp_ = new CTransform();
	_rotation = XMFLOAT3();
	_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	_world = XMFLOAT4X4();
	_textureRV = nullptr;
}

GameObject::~GameObject()
{
	if (parent_) parent_ = nullptr;
	if (transform_comp_) transform_comp_ = nullptr;
	if (_textureRV) _textureRV = nullptr;
	if (_geometry.indexBuffer) _geometry.indexBuffer = nullptr;
	if (_geometry.vertexBuffer) _geometry.vertexBuffer = nullptr;
}

void GameObject::Update(const float& dt)
{
	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	XMMATRIX rotation = XMMatrixRotationX(_rotation.x) * XMMatrixRotationY(_rotation.y) * XMMatrixRotationZ(_rotation.z);
	XMMATRIX translation = XMMatrixTranslation(transform_comp_->GetPosition().x, transform_comp_->GetPosition().y, transform_comp_->GetPosition().z);

	XMStoreFloat4x4(&_world, scale * rotation * translation);

	if (parent_ != nullptr)
	{
		XMStoreFloat4x4(&_world, this->GetWorldMatrix() * parent_->GetWorldMatrix());
	}
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// We are assuming that the constant buffers and all other draw setup has already taken place

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &_geometry.vertexBuffer, &_geometry.vertexBufferStride, &_geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}
