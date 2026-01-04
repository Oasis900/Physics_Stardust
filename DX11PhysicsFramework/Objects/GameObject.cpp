#include "GameObject.h"
#pragma region DirectX Variables & Functions
using DirectX::XMMATRIX;
using DirectX::XMFLOAT3;
#pragma endregion

GameObject::GameObject(const std::string& type, const Geometry& geometry, const Material& material) : type_(type)
{
	transform_comp_ = new CTransform();
	render_comp_ = new CRender(geometry, material);
	transform_comp_->SetScale(1.0f, 1.0f, 1.0f);
	transform_comp_->SetRotation(XMFLOAT3());
	transform_comp_->SetWorldMatrix(XMMATRIX());
	physics_comp_ = new CPhysics();
}

GameObject::~GameObject()
{
	delete transform_comp_; transform_comp_ = nullptr;
	delete render_comp_; render_comp_ = nullptr;
	delete physics_comp_; physics_comp_ = nullptr;
}

/*void GameObject::Render(const float& dt, ID3D11DeviceContext * pImmediateContext) const
{
	render_comp_->Draw(pImmediateContext);
}*/
