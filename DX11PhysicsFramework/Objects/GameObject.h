#pragma once
#include <directxmath.h>
#include <d3d11_1.h>
#include <string>

#include "../Interface/IUpdateable.h"

#include "../Components/CPhysics.h"
#include "../Components/CRender.h"
#include "../Components/CTransform.h"

class GameObject
{
	CRender* render_comp_ = nullptr;
	CTransform* transform_comp_ = nullptr;
	CPhysics* physics_comp_ = nullptr;
	//--------------------------------------------------//
	std::string type_;
	
public:
	GameObject(const std::string& type, const Geometry& geometry, const Material& material, const float& mass);
	//--------------------------------------------------//
	CRender* GetRender() const { return render_comp_; }
	CTransform* GetTransform() const { return transform_comp_; }
	CPhysics* GetPhysics() const { return physics_comp_; }
	//--------------------------------------------------//
	std::string GetType() const { return type_; }
	//--------------------------------------------------//
	//void Render(const float& dt, ID3D11DeviceContext * pImmediateContext) const;
	//void Update(const float& dt) final;
	//--------------------------------------------------//
	~GameObject();
	
};

