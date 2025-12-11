#include "Camera.h"

Camera::Camera(XMFLOAT3 position, XMFLOAT3 at, XMFLOAT3 up, FLOAT window_width, FLOAT window_height, FLOAT near_depth, FLOAT far_depth)
	: eye_(position), at_(at), up_(up), window_width_(window_width), window_height_(window_height), near_depth_(near_depth), far_depth_(far_depth)
{
	Update();
}

Camera::~Camera()
{
}

void Camera::Update()
{
    // Initialize the view matrix

	XMFLOAT4 eye = XMFLOAT4(eye_.x, eye_.y, eye_.z, 1.0f);
	XMFLOAT4 at = XMFLOAT4(at_.x, at_.y, at_.z, 1.0f);
	XMFLOAT4 up = XMFLOAT4(up_.x, up_.y, up_.z, 0.0f);

	XMVECTOR eye_vec = XMLoadFloat4(&eye);
	XMVECTOR at_vec = XMLoadFloat4(&at);
	XMVECTOR up_vec = XMLoadFloat4(&up);

	XMStoreFloat4x4(&view_, XMMatrixLookAtLH(eye_vec, at_vec, up_vec));

    // Initialize the projection matrix
	XMStoreFloat4x4(&projection_, XMMatrixPerspectiveFovLH(0.25f * XM_PI, window_width_ / window_height_, near_depth_, far_depth_));
}

void Camera::Reshape(const FLOAT& window_width, const FLOAT& window_height, const FLOAT& near_depth, const FLOAT& far_depth)
{
	window_width_ = window_width;
	window_height_ = window_height;
	near_depth_ = near_depth;
	far_depth_ = far_depth;
}

XMFLOAT4X4 Camera::GetViewProjection() const 
{ 
	XMMATRIX view = XMLoadFloat4x4(&view_);
	XMMATRIX projection = XMLoadFloat4x4(&projection_);

	XMFLOAT4X4 view_proj;

	XMStoreFloat4x4(&view_proj, view * projection);

	return view_proj;
}