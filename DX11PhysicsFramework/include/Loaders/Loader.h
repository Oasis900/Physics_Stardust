#pragma once
#define DX11_LOADING_HPP
#include <DirectXMath.h>
#include <d3d11_1.h>
#include <Loaders/DDSTextureLoader.h>
#include <Loaders/OBJLoader.h>

typedef ID3D11ShaderResourceView Texture;

class Loader
{
    MeshData* mesh_ = nullptr;
    Texture* texture_ = nullptr;
    
public:
    Loader();
    MeshData* LoadMesh(ID3D11Device* device, const std::string& path) const;
    Texture* LoadTexture(ID3D11Device* device, const std::string& path);
    ~Loader();
};
