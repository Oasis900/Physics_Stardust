#pragma once
#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP
#include <directxmath.h>
using DirectX::XMMATRIX;
using DirectX::XMFLOAT4;
using DirectX::XMFLOAT3;
using DirectX::XMFLOAT2;

struct SurfaceInfo
{
	XMFLOAT4 ambient_mat;
	XMFLOAT4 diffuse_mat;
	XMFLOAT4 specular_mat;
};

struct Light
{
	XMFLOAT4 ambient_light;
	XMFLOAT4 diffuse_light;
	XMFLOAT4 specular_light;
	//--------------------------------------------------//
	float specular_power;
	XMFLOAT3 light_vec_w;
};

// TODO (Constant Buffer Data) : Has been set as a singleton. 11/12/25 (00:50)
class ConstantBuffer
{
	ConstantBuffer() = default;
	//--------------------------------------------------//
	XMMATRIX world_;
	XMMATRIX view_;
	XMMATRIX projection_;
	//--------------------------------------------------//
	SurfaceInfo surface_;
	//--------------------------------------------------//
	Light light_;
	//--------------------------------------------------//
	XMFLOAT3 eye_pow_w_;
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
	XMMATRIX GetWorldMatrix() const { return world_; }
	void SetWorldMatrix(const XMMATRIX& value) { world_ = value; }
	//--------------------------------------------------//
	XMMATRIX GetViewMatrix() const { return view_; }
	void SetViewMatrix(const XMMATRIX& view) { view_ = view; }
	//--------------------------------------------------//
	XMMATRIX GetProjectionMatrix() const { return projection_; }
	void SetProjectionMatrix(const XMMATRIX& projection) { projection_ = projection; }
	//--------------------------------------------------//
	SurfaceInfo GetSurfaceInfo() const { return surface_; }
	void SetSurfaceInfo(const SurfaceInfo& surface) { surface_ = surface; }
	void SetSurfaceInfo(const XMFLOAT4& ambient, const XMFLOAT4& diffuse, const XMFLOAT4& specular) { surface_.ambient_mat = ambient; surface_.diffuse_mat = diffuse; surface_.specular_mat = specular; }
	//--------------------------------------------------//
	Light GetLight() const { return light_; }
	void SetLight(const Light& light) { light_ = light; }
	//--------------------------------------------------//
	XMFLOAT3 GetEyePowW() const { return eye_pow_w_; }
	void SetEyePowW(const XMFLOAT3& pow) { eye_pow_w_ = pow; }
	//--------------------------------------------------//
	float GetHasTexture() const { return has_texture_; }
	void SetHasTexture(const bool& has_texture) { has_texture_ = has_texture; }
};
#endif