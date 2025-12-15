#pragma once
#define SIMPLE_VERTEX_HPP
#include <cstring>
#include <DirectXMath.h>

struct SimpleVertex
{
    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT3 normal;
    DirectX::XMFLOAT2 tex_coord;

    bool operator<(const SimpleVertex other) const
    {
        return memcmp((void*)this, (void*)&other, sizeof(SimpleVertex)) > 0;
    };
};