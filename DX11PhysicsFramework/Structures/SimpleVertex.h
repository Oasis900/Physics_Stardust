#pragma once
#ifndef SIMPLE_VERTEX_HPP
#define SIMPLE_VERTEX_HPP
#include <cstring>
#include <DirectXMath.h>
using DirectX::XMFLOAT3;
using DirectX::XMFLOAT2;

struct SimpleVertex
{
    XMFLOAT3 pos;
    XMFLOAT3 normal;
    XMFLOAT2 tex_coord;

    bool operator<(const SimpleVertex other) const
    {
        return memcmp((void*)this, (void*)&other, sizeof(SimpleVertex)) > 0;
    };
};
#endif