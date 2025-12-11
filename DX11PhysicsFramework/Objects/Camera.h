#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>

using namespace DirectX;

class Camera
{
	XMFLOAT3 eye_; 
	XMFLOAT3 at_;
	XMFLOAT3 up_;

	FLOAT window_width_;
	FLOAT window_height_;
	FLOAT near_depth_;
	FLOAT far_depth_;

	XMFLOAT4X4 view_;
	XMFLOAT4X4 projection_;

public:
	Camera(XMFLOAT3 position, XMFLOAT3 at, XMFLOAT3 up, FLOAT window_width, FLOAT window_height, FLOAT near_depth, FLOAT far_depth);
	~Camera();

	void Update();

	XMFLOAT4X4 GetView() const { return view_; }
	XMFLOAT4X4 GetProjection() const { return projection_; }

	XMFLOAT4X4 GetViewProjection() const;

	XMFLOAT3 GetPosition() const { return eye_; }
	XMFLOAT3 GetLookAt() const { return at_; }
	XMFLOAT3 GetUp() const { return up_; }

	void SetPosition(XMFLOAT3 position) { eye_ = position; }
	void SetLookAt(XMFLOAT3 look_at) { at_ = look_at; }
	void SetUp(XMFLOAT3 up) { up_ = up; }

	void Reshape(const FLOAT& window_width, const FLOAT& window_height, const FLOAT& near_depth, const FLOAT& far_depth);
};

