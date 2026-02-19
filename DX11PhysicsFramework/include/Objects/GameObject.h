#pragma once
#include <Components/CPhysics.h>
#include <Components/CParticle.h>
#include <Components/CRigidBody.h>
#include <Components/CRender.h>
#include <Components/CTransform.h>


class GameObject
{
	CTransform* transform_comp_ = nullptr;
	CRender* render_comp_ = nullptr;
	CPhysics* physics_comp_ = nullptr;
	
public:
	GameObject(const ObjectType& type, const Geometry& geometry, const Material& material) : transform_comp_(new CTransform()), render_comp_(new CRender(geometry, material))
	{
		switch (type)
		{
			case PLANET:
			physics_comp_ = new CRigidBody(transform_comp_);
			physics_comp_->SetCollider(new Colliders::SphereCollider(transform_comp_, static_cast<float>(K_Planet_Radius)));
			break;

			case SUN:
			physics_comp_ = new CRigidBody(transform_comp_);
			physics_comp_->SetCollider(new Colliders::SphereCollider(transform_comp_, static_cast<float>(k_Solar_Radius)));
			break;

			default:
			physics_comp_ = new CParticle(transform_comp_);
			break;
		}
	} 
	//--------------------------------------------------//
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	GameObject(GameObject&&) = delete;
	GameObject& operator=(const GameObject&&) = delete;
	//--------------------------------------------------//
	CRender* GetRender() const { return render_comp_; }
	CTransform* GetTransform() const { return transform_comp_; }
	CPhysics* GetPhysics() const { return physics_comp_; }
	//--------------------------------------------------//
	~GameObject();
};

