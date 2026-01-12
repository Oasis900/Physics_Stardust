#pragma once
#define STRUCTURES_HPP
#include <directxmath.h>

enum ObjectType
{
	FLOOR,
	CUBE,
	DONUT,
	SPHERE
};

struct SurfaceInfo
{
	DirectX::XMFLOAT4 ambient_mat;
	DirectX::XMFLOAT4 diffuse_mat;
	DirectX::XMFLOAT4 specular_mat;
};

struct Light
{
	DirectX::XMFLOAT4 ambient_light;
	DirectX::XMFLOAT4 diffuse_light;
	DirectX::XMFLOAT4 specular_light;
	//--------------------------------------------------//
	float specular_power;
	DirectX::XMFLOAT3 light_vec_w;
};

// TODO (Constant Buffer Data) : Has been set as a singleton. 11/12/25 (00:50)
class ConstantBuffer
{
	ConstantBuffer() = default;
	//--------------------------------------------------//
	DirectX::XMMATRIX world_;
	DirectX::XMMATRIX view_;
	DirectX::XMMATRIX projection_;
	//--------------------------------------------------//
	SurfaceInfo surface_;
	//--------------------------------------------------//
	Light light_;
	//--------------------------------------------------//
	DirectX::XMFLOAT3 eye_pow_w_;
	float has_texture_;

public:
	static ConstantBuffer& GetInstance()
	{
		static ConstantBuffer instance;
		return instance;
	};
	//--------------------------------------------------//
	ConstantBuffer(const ConstantBuffer&) = delete;
	ConstantBuffer(ConstantBuffer&&) = delete;
	ConstantBuffer& operator=(const ConstantBuffer&) = delete;
	ConstantBuffer& operator=(ConstantBuffer&&) = delete;
	//--------------------------------------------------//
	DirectX::XMMATRIX GetWorldMatrix() const { return world_; }
	void SetWorldMatrix(const DirectX::XMMATRIX& value) { world_ = value; }
	//--------------------------------------------------//
	DirectX::XMMATRIX GetViewMatrix() const { return view_; }
	void SetViewMatrix(const DirectX::XMMATRIX& view) { view_ = view; }
	//--------------------------------------------------//
	DirectX::XMMATRIX GetProjectionMatrix() const { return projection_; }
	void SetProjectionMatrix(const DirectX::XMMATRIX& projection) { projection_ = projection; }
	//--------------------------------------------------//
	SurfaceInfo GetSurfaceInfo() const { return surface_; }
	void SetSurfaceInfo(const SurfaceInfo& surface) { surface_ = surface; }
	void SetSurfaceInfo(const DirectX::XMFLOAT4& ambient, const DirectX::XMFLOAT4& diffuse, const DirectX::XMFLOAT4& specular) { surface_.ambient_mat = ambient; surface_.diffuse_mat = diffuse; surface_.specular_mat = specular; }
	//--------------------------------------------------//
	Light GetLight() const { return light_; }
	void SetLight(const Light& light) { light_ = light; }
	//--------------------------------------------------//
	DirectX::XMFLOAT3 GetEyePowW() const { return eye_pow_w_; }
	void SetEyePowW(const DirectX::XMFLOAT3& pow) { eye_pow_w_ = pow; }
	//--------------------------------------------------//
	float GetHasTexture() const { return has_texture_; }
	void SetHasTexture(const bool& has_texture) { has_texture_ = has_texture; }
};