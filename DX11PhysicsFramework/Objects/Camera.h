#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>

class Camera
{
	DirectX::XMFLOAT3 eye_; 
	DirectX::XMFLOAT3 at_;
	DirectX::XMFLOAT3 up_;

	FLOAT window_width_;
	FLOAT window_height_;
	FLOAT near_depth_;
	FLOAT far_depth_;

	DirectX::XMFLOAT4X4 view_;
	DirectX::XMFLOAT4X4 projection_;

public:
	Camera(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 at, DirectX::XMFLOAT3 up, FLOAT window_width, FLOAT window_height, FLOAT near_depth, FLOAT far_depth);
	~Camera();

	void Update();

	DirectX::XMFLOAT4X4 GetView() const { return view_; }
	DirectX::XMFLOAT4X4 GetProjection() const { return projection_; }

	DirectX::XMFLOAT4X4 GetViewProjection() const;

	DirectX::XMFLOAT3 GetPosition() const { return eye_; }
	DirectX::XMFLOAT3 GetLookAt() const { return at_; }
	DirectX::XMFLOAT3 GetUp() const { return up_; }

	void SetPosition(DirectX::XMFLOAT3 position) { eye_ = position; }
	void SetLookAt(DirectX::XMFLOAT3 look_at) { at_ = look_at; }
	void SetUp(DirectX::XMFLOAT3 up) { up_ = up; }

	void Reshape(const FLOAT& window_width, const FLOAT& window_height, const FLOAT& near_depth, const FLOAT& far_depth);
};

