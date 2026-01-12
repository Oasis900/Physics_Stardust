#include <Objects/GameObject.h>

GameObject::GameObject(const ObjectType& type, const Geometry& geometry, const Material& material, const float& mass)
{
	transform_comp_ = new CTransform(type);
	render_comp_ = new CRender(geometry, material);

	if (type == FLOOR)
	{
		physics_comp_ = new CPhysics(transform_comp_, mass);
	}

	if (type == CUBE || type == SPHERE)
	{
		physics_comp_ = new CPhysics(transform_comp_, 1.0f/mass); // Divide 1.0 by mass to prevent calculations using 0.0
	}

	if (type == DONUT)
	{
		physics_comp_ = new CPhysics(transform_comp_, 1.0f/mass); // Divide 1.0 by mass to prevent calculations using 0.0
	}
}

GameObject::~GameObject()
{
	if (transform_comp_) {delete transform_comp_; transform_comp_ = nullptr;}
	if (render_comp_) {delete render_comp_; render_comp_ = nullptr;}
	if (physics_comp_) {delete physics_comp_; physics_comp_ = nullptr;}
	
}
