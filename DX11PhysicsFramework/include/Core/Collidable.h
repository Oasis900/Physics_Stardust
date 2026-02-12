#pragma once
#include <Components/CTransform.h>
#include <cmath>
#include <Structures/Structures.h>
#include <Core/constants.h>

namespace Colliders
{
    class SphereCollider;

    class Collider abstract
    {
        CTransform* transform_ = nullptr;

        protected:
        float radius_ = 0.0f;
        
        public:
        Collider(CTransform* transform, const float& radius) : transform_(transform), radius_(radius) {}
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
        float GetRadius() const { return radius_; }
        //--------------------------------------------------//
        virtual ~Collider() = default;
    };

    class SphereCollider : public Collider
    {
        public:
        SphereCollider(CTransform* transform, const float& radius) : Collider(transform, radius) {}
        //--------------------------------------------------//
        bool CollidesWith(Collider& other) override { return other.CollidesWith(*this); }
        bool CollidesWith(SphereCollider& other) override; 
        //--------------------------------------------------//
    };


    inline bool SphereCollider::CollidesWith(SphereCollider& other)
    {
        float combined_radius = GetRadius() + other.GetRadius();
        float distance = abs((GetPosition() - other.GetPosition()).Magnitude());

        if (distance <= combined_radius)
        {
            return true;
        }

        return false;
    }
}
