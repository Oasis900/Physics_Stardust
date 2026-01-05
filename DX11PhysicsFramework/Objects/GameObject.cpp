#include "GameObject.h"

GameObject::GameObject(const std::string& type, const Geometry& geometry, const Material& material, const float& mass) : type_(type)
{
	transform_comp_ = new CTransform();
	render_comp_ = new CRender(geometry, material);
	physics_comp_ = new CPhysics(transform_comp_, mass);
}

GameObject::~GameObject()
{
	delete transform_comp_; transform_comp_ = nullptr;
	delete render_comp_; render_comp_ = nullptr;
	delete physics_comp_; physics_comp_ = nullptr;
}
