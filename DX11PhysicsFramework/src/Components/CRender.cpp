#include <Components/CRender.h>

CRender::~CRender()
{
    if (geometry_) {delete geometry_; geometry_ = nullptr;}
    if (material_) {delete material_; material_ = nullptr;}
}

void CRender::Draw(ID3D11DeviceContext* pImmediateContext) const
{
    pImmediateContext->IASetVertexBuffers(0, 1, &geometry_->vertex_buffer, &geometry_->vb_stride, &geometry_->vb_offset);
    pImmediateContext->IASetIndexBuffer(geometry_->index_buffer, DXGI_FORMAT_R16_UINT, 0);
    pImmediateContext->DrawIndexed(geometry_->indices_num, 0, 0);
}


