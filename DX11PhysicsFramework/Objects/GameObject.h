#pragma once
#include <directxmath.h>
#include <d3d11_1.h>
#include <string>
#include "../Interface/IUpdateable.h"
#include "../Components/CRender.h"
#include "../Components/CTransform.h"

class GameObject : public IUpdateable
{
	CTransform* transform_comp_ = nullptr;
	CRender* render_comp_ = nullptr;
	//--------------------------------------------------//
	std::string type_;
	
public:
	GameObject(const std::string& type, const Geometry& geometry, const Material& material);
	~GameObject();
	//--------------------------------------------------//
	CTransform* GetTransform() const { return transform_comp_; }
	//--------------------------------------------------//
	CRender* GetRender() const { return render_comp_; }
	//--------------------------------------------------//
	std::string GetType() const { return type_; }
	//--------------------------------------------------//
	void Draw(ID3D11DeviceContext * pImmediateContext) const;
	void Update(const float& dt) final;
	
};

