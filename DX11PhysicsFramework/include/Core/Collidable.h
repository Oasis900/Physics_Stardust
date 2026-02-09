#pragma once
#include <Components/CTransform.h>
#include <cmath>

namespace Colliders
{
    class SphereCollider;

    class Collider abstract
    {
        CTransform* transform_ = nullptr;
        
        public:
        Collider(CTransform* transform) : transform_(transform) {}
        //--------------------------------------------------//
        Collider(const Collider& other) = delete;
        Collider& operator=(const Collider&) = delete;
        Collider(Collider&&) = delete;
        Collider& operator=(Collider&&) = delete;
        //--------------------------------------------------//
        virtual bool CollidesWith (Collider& other) = 0;
        virtual bool CollidesWith (SphereCollider& other) = 0;
        //--------------------------------------------------//
        Vector3 GetPosition () const { return transform_->GetPosition(); }
        //--------------------------------------------------//
        virtual ~Collider() = default;
    };

    class SphereCollider : public Collider
    {
        float radius_ = 0.0f;
        
        public:
        SphereCollider(CTransform* transform, const float& radius) : Collider(transform), radius_(radius) {}
        //--------------------------------------------------//
        bool CollidesWith(Collider& other) override { return other.CollidesWith(*this); }
        bool CollidesWith(SphereCollider& other) override; 
        //--------------------------------------------------//
        float GetRadius() const { return radius_; }
    };

    inline bool SphereCollider::CollidesWith(SphereCollider& other)
    {
        float combined_radius = other.GetRadius() + GetRadius();
        float distance = abs(other.GetPosition().Magnitude() - GetPosition().Magnitude());

        if (distance <= combined_radius) { return true; }

        return false;
    }
}
