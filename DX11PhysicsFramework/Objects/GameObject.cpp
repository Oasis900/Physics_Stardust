#include "GameObject.h"

GameObject::GameObject(const string& type, const Geometry& geometry, const Material& material) : type_(type)
{
	transform_comp_ = new CTransform();
	render_comp_ = new CRender(geometry, material);
	transform_comp_->SetScale(1.0f, 1.0f, 1.0f);
	transform_comp_->SetRotation(XMFLOAT3());
	transform_comp_->SetWorldMatrix(XMMATRIX());
}

GameObject::~GameObject()
{
	if (transform_comp_) transform_comp_ = nullptr;
	if (render_comp_) render_comp_ = nullptr;
}

void GameObject::Update(const float& dt)
{
	transform_comp_->Update(dt);
	
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext) const
{
	render_comp_->Draw(pImmediateContext);
}
