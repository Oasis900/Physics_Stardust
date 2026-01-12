#pragma once
#include <Components/CTransform.h>

// TODO (ICollidable) [12/01/26] : Review implementation of this interface, may want to reconsider implementation

namespace ICollidable
{
    class SphereCollider;

    class Collider abstract
    {
        CTransform* transform_ = nullptr;
        
        public:
        Collider(CTransform* transform) : transform_(transform) {}
        //--------------------------------------------------//
        Collider(const Collider& other) = default;
        Collider& operator=(const Collider&) = default;
        Collider(Collider&&) = default;
        Collider& operator=(Collider&&) = default;
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
        float radius_ = 1.0f;
        
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

        if (other.GetPosition().Magnitude() < combined_radius)
        {
            return other.CollidesWith(*this);
        }

        return false;
    }
}
