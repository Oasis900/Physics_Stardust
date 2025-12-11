#include "GameObject.h"

GameObject::GameObject(const string& type, const Geometry& geometry, const Material& material) : type_(type), geometry_(geometry), material_(material)
{
	parent_ = nullptr;
	transform_comp_ = new CTransform();
	rotation_ = XMFLOAT3();
	scale_ = XMFLOAT3(1.0f, 1.0f, 1.0f);
	world_ = XMFLOAT4X4();
	texture_rv_ = nullptr;
}

GameObject::~GameObject()
{
	if (parent_) parent_ = nullptr;
	if (transform_comp_) transform_comp_ = nullptr;
	if (texture_rv_) texture_rv_ = nullptr;
	if (geometry_.index_buffer) geometry_.index_buffer->Release();
	if (geometry_.vertex_buffer) geometry_.vertex_buffer->Release();
}

void GameObject::Update(const float& dt)
{
	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	XMMATRIX rotation = XMMatrixRotationX(rotation_.x) * XMMatrixRotationY(rotation_.y) * XMMatrixRotationZ(rotation_.z);
	XMMATRIX translation = XMMatrixTranslation(transform_comp_->GetPosition().x, transform_comp_->GetPosition().y, transform_comp_->GetPosition().z);

	XMStoreFloat4x4(&world_, scale * rotation * translation);

	if (parent_ != nullptr)
	{
		XMStoreFloat4x4(&world_, this->GetWorldMatrix() * parent_->GetWorldMatrix());
	}
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// We are assuming that the constant buffers and all other draw setup has already taken place

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &geometry_.vertex_buffer, &geometry_.vb_stride, &geometry_.vb_offset);
	pImmediateContext->IASetIndexBuffer(geometry_.index_buffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(geometry_.indices_num, 0, 0);
}
