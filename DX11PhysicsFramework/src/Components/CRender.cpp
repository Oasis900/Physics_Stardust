#include <Components/CRender.h>

CRender::CRender(const Geometry& geometry, const Material& material)
{
    geometry_ = new Geometry();
    material_ = new Material();
    
    *geometry_ = geometry;
    *material_ = material;
}

CRender::~CRender()
{
    delete geometry_; geometry_ = nullptr;
    delete material_; material_ = nullptr;
}

void CRender::Draw(ID3D11DeviceContext* pImmediateContext) const
{
    pImmediateContext->IASetVertexBuffers(0, 1, &geometry_->vertex_buffer, &geometry_->vb_stride, &geometry_->vb_offset);
    pImmediateContext->IASetIndexBuffer(geometry_->index_buffer, DXGI_FORMAT_R16_UINT, 0);

    pImmediateContext->DrawIndexed(geometry_->indices_num, 0, 0);
}


