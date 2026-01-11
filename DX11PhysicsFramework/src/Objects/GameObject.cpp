#include <Objects/GameObject.h>

GameObject::GameObject(const std::string& type, const Geometry& geometry, const Material& material, const float& mass) : type_(type)
{
	transform_comp_ = new CTransform(type);
	render_comp_ = new CRender(geometry, material);
	physics_comp_ = new CPhysics(transform_comp_, mass);
}

GameObject::~GameObject()
{
	if (transform_comp_) {delete transform_comp_; transform_comp_ = nullptr;}
	if (render_comp_) {delete render_comp_; render_comp_ = nullptr;}
	if (physics_comp_) {delete physics_comp_; physics_comp_ = nullptr;}
	
}
