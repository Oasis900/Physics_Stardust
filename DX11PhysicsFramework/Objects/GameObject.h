#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>

#include "../Interface/IUpdateable.h"
#include "../Components/CRender.h"
#include "../Components/CTransform.h"
using std::string;

class GameObject : public IUpdateable
{
	// TODO (Game Object) : Improve performance of logic, increase abstraction | 11/12/25 | 12:35
	
	CTransform* transform_comp_ = nullptr;
	CRender* render_comp_ = nullptr;
	//--------------------------------------------------//
	string type_;
	
public:
	GameObject(const string& type, const Geometry& geometry, const Material& material);
	~GameObject();
	//--------------------------------------------------//
	CTransform* GetTransform() const { return transform_comp_; }
	//--------------------------------------------------//
	CRender* GetRender() const { return render_comp_; }
	//--------------------------------------------------//
	string GetType() const { return type_; }
	//--------------------------------------------------//
	void Draw(ID3D11DeviceContext * pImmediateContext) const;
	void Update(const float& dt) final;
	
};

