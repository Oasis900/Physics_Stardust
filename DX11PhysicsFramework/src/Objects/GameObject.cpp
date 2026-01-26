#include <Objects/GameObject.h>

GameObject::~GameObject()
{
	if (transform_comp_) {delete transform_comp_; transform_comp_ = nullptr;}
	if (render_comp_) {delete render_comp_; render_comp_ = nullptr;}
	if (physics_comp_) {delete physics_comp_; physics_comp_ = nullptr;}
}
