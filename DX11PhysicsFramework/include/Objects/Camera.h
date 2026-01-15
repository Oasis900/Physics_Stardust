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

	float window_width_;
	float window_height_;
	float near_depth_;
	float far_depth_;

	DirectX::XMFLOAT4X4 view_;
	DirectX::XMFLOAT4X4 projection_;

public:
	Camera(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 at, DirectX::XMFLOAT3 up, float window_width, float window_height, float near_depth, float far_depth);
	~Camera();
	//--------------------------------------------------//
	void Update();
	//--------------------------------------------------//
	DirectX::XMFLOAT4X4 GetView() const { return view_; }
	DirectX::XMFLOAT4X4 GetProjection() const { return projection_; }
	DirectX::XMFLOAT4X4 GetViewProjection() const;
	//--------------------------------------------------//
	DirectX::XMFLOAT3 GetPosition() const { return eye_; }
	DirectX::XMFLOAT3 GetLookAt() const { return at_; }
	DirectX::XMFLOAT3 GetUp() const { return up_; }
	//--------------------------------------------------//
	void SetPosition(const DirectX::XMFLOAT3 position) { eye_ = position; }
	void SetLookAt(const DirectX::XMFLOAT3 look_at) { at_ = look_at; }
	void SetUp(const DirectX::XMFLOAT3 up) { up_ = up; }
	//--------------------------------------------------//
	void Reshape(const float& window_width, const float& window_height, const float& near_depth, const float& far_depth);
};

