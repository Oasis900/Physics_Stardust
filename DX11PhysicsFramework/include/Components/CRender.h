#pragma once
#define COMP_RENDER_HPP
#include <d3d11.h>
#include <directxmath.h>

struct Geometry
{
    ID3D11Buffer* vertex_buffer;
    ID3D11Buffer* index_buffer;
    int indices_num = 0;

    UINT vb_stride = 0;
    UINT vb_offset = 0;
};

struct Material
{
    DirectX::XMFLOAT4 diffuse = DirectX::XMFLOAT4();
    DirectX::XMFLOAT4 ambient = DirectX::XMFLOAT4();
    DirectX::XMFLOAT4 specular = DirectX::XMFLOAT4();
};

class CRender
{
    Geometry* geometry_ = nullptr;
    Material* material_ = nullptr;
    //--------------------------------------------------//
    ID3D11ShaderResourceView* texture_rv_ = nullptr;
    //--------------------------------------------------//
    
public:
    CRender(const Geometry& geometry, const Material& material) : geometry_(new Geometry(geometry)), material_(new Material(material)) {}
    //--------------------------------------------------//
    CRender(const CRender& other) = delete;
    CRender& operator=(const CRender&) = delete;
    CRender(CRender&&) = delete;
    CRender& operator=(const CRender&&) = delete;
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