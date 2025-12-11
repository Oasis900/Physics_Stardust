#pragma once
#ifndef COMP_RENDER_HPP
#define COMP_RENDER_HPP
#include <d3d11.h>
#include <directxmath.h>
using DirectX::XMFLOAT4;

// TODO (Render Component) : Complete extraction of variables and logic responsiblity from game object

struct Geometry
{
    ID3D11Buffer* vertex_buffer;
    ID3D11Buffer* index_buffer;
    int indices_num;

    UINT vb_stride;
    UINT vb_offset;
};

struct Material
{
    XMFLOAT4 diffuse;
    XMFLOAT4 ambient;
    XMFLOAT4 specular;
};

class CRender
{
    Geometry geometry_;
    Material material_;
    //--------------------------------------------------//
    ID3D11ShaderResourceView* texture_rv_ = nullptr;
    //--------------------------------------------------//
    ~CRender();
    
public:
    CRender(const Geometry& geometry, const Material& material);
    //--------------------------------------------------//
    Geometry GetGeometryData() const { return geometry_; }
    Material GetMaterial() const { return material_; }
    //--------------------------------------------------//
    void SetTextureRV(ID3D11ShaderResourceView * textureRV) { texture_rv_ = textureRV; }
    ID3D11ShaderResourceView* const* GetTextureRV() { return &texture_rv_; }
    bool HasTexture() const { return texture_rv_ ? true : false; }
    //--------------------------------------------------//
    void Draw(ID3D11DeviceContext * pImmediateContext) const;
};
#endif