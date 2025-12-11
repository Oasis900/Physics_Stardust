#pragma once
#ifndef DX11_LOADING_HPP
#define DX11_LOADING_HPP
#include <DirectXMath.h>
#include <d3d11_1.h>
#include "OBJLoader.h"
#include "DDSTextureLoader.h"

typedef ID3D11ShaderResourceView Texture;

class Loading
{
    MeshData* mesh_ = nullptr;
    Texture* texture_ = nullptr;
    
public:
    MeshData* LoadMesh(ID3D11Device* device, const std::string& path);
    Texture* LoadTexture(ID3D11Device* device, const std::string& path);
    ~Loading();
};
#endif
