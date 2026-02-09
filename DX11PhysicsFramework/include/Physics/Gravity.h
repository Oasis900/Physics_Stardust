#pragma once
#include <Physics/Force.h>

// TODO (Gravity) [12/01/26] : Review class when attempting General Relativity

class Gravity : public Force
{
    GameObject* object_ = nullptr;
public:
    explicit Gravity(CTransform* transform) : Force(transform) {}
    //--------------------------------------------------//
    Gravity(const Gravity& other) = delete;
    Gravity& operator=(const Gravity&) = delete;
    Gravity(Gravity&&) = delete;
    Gravity& operator=(const Gravity&&) = delete;
    //--------------------------------------------------//
    void AddGameObject(GameObject* game_object) { object_ = game_object; }
    //--------------------------------------------------//
    Vector3 CalculateGravity();
    //--------------------------------------------------//
    ~Gravity() override {object_ = nullptr;}
};
