#pragma once
#ifndef COMP_RENDER_HPP
#define COMP_RENDER_HPP
#include <d3d11.h>

// TODO (Render Component) : Complete extraction of variables and logic responsiblity from game object

class CRender
{
    
public:
    void Draw(ID3D11DeviceContext * pImmediateContext);
};
#endif