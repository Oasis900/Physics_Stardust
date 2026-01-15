#include <Loaders/Loader.h>

Loader::Loader()
{
    mesh_ = new MeshData();
}

MeshData* Loader::LoadMesh(ID3D11Device* device, const std::string& path) const
{
    *mesh_ = OBJLoader::Load(path, device, true);

    if (mesh_->index_count == 0)
    {
        throw std::runtime_error("File path for mesh potentially incorrect\n");
    }

    return mesh_;
}

Texture* Loader::LoadTexture(ID3D11Device* device, const std::string& path)
{
    std::wstring ws_path = std::wstring(path.begin(), path.end());

    const wchar_t* wc_path = ws_path.c_str(); 

    DirectX::CreateDDSTextureFromFile(device, wc_path, nullptr, &texture_);

    if (texture_ == nullptr)
    {
        throw std::runtime_error("Loading texture is not initialized\n");
    }

    return texture_;
}

Loader::~Loader()
{
    if (mesh_)
    {
        mesh_->vertex_buffer->Release();
        mesh_->index_buffer->Release();
        delete mesh_;
        mesh_ = nullptr;
    }
    
    if (texture_) {texture_->Release(); texture_ = nullptr;}
}
