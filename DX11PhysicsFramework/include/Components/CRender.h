#pragma once
#define COMP_RENDER_HPP
#include <d3d11.h>
#include <directxmath.h>

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
    DirectX::XMFLOAT4 diffuse;
    DirectX::XMFLOAT4 ambient;
    DirectX::XMFLOAT4 specular;
};

class CRender
{
    Geometry* geometry_ = nullptr;
    Material* material_ = nullptr;
    //--------------------------------------------------//
    ID3D11ShaderResourceView* texture_rv_ = nullptr;
    //--------------------------------------------------//
    
public:
    CRender(const Geometry& geometry, const Material& material);
    //--------------------------------------------------//
    Geometry GetGeometryData() const { return *geometry_; }
    Material GetMaterialData() const { return *material_; }
    //--------------------------------------------------//
    void SetTextureRV(ID3D11ShaderResourceView * textureRV) { texture_rv_ = textureRV; }
    ID3D11ShaderResourceView* const* GetTextureRV() const { return &texture_rv_; }
    bool HasTexture() const { return texture_rv_ ? true : false; }
    //--------------------------------------------------//
    void Draw(ID3D11DeviceContext * pImmediateContext) const;
    //--------------------------------------------------//
    ~CRender();
};