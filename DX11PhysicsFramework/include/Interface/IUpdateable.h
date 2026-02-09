#pragma once
#define INTERFACE_UPDATE_HPP

class IUpdateable
{
public:
    IUpdateable() = default;
    //--------------------------------------------------//
    IUpdateable(const IUpdateable& other) = delete;
    IUpdateable& operator=(const IUpdateable&) = delete;
    IUpdateable(IUpdateable&&) = delete;
    IUpdateable& operator=(const IUpdateable&&) = delete;
    //--------------------------------------------------//
    virtual void Update(const float& dt) = 0;
    //--------------------------------------------------//
    virtual ~IUpdateable() = default;
};