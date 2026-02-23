#pragma once
#define STRUCTURES_HPP
#include <directxmath.h>

enum ObjectType
{
	SUN,
	PLANET,
	PARABOLOID
};

struct SurfaceInfo
{
	DirectX::XMFLOAT4 ambient_mat;
	DirectX::XMFLOAT4 diffuse_mat;
	DirectX::XMFLOAT4 specular_mat;
};

struct LightInfo
{
	DirectX::XMFLOAT4 ambient_light;
	DirectX::XMFLOAT4 diffuse_light;
	DirectX::XMFLOAT4 specular_light;
	//--------------------------------------------------//
	float specular_power;
	DirectX::XMFLOAT3 light_vec_w;
};

class ConstantBuffer
{
	ConstantBuffer() = default;
	~ConstantBuffer() = default;
	//--------------------------------------------------//
	DirectX::XMMATRIX world_;
	DirectX::XMMATRIX view_;
	DirectX::XMMATRIX projection_;
	//--------------------------------------------------//
	SurfaceInfo surface_;
	//--------------------------------------------------//
	LightInfo light_;
	//--------------------------------------------------//
	DirectX::XMFLOAT3 eye_pos_w_;
	float has_texture_;

public:
	static ConstantBuffer& GetInstance()
	{
		static ConstantBuffer instance;
		return instance;
	};
	//--------------------------------------------------//
	ConstantBuffer(const ConstantBuffer&) = delete;
	ConstantBuffer& operator=(const ConstantBuffer&) = delete;
	ConstantBuffer(ConstantBuffer&&) = delete;
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
	void SetSurfaceInfo(const DirectX::XMFLOAT4& ambient, const DirectX::XMFLOAT4& diffuse, const DirectX::XMFLOAT4& specular) { surface_.ambient_mat = ambient; surface_.diffuse_mat = diffuse; surface_.specular_mat = specular; }
	//--------------------------------------------------//
	LightInfo GetLightInfo() const { return light_; }
	void SetLightInfo(const LightInfo& light) { light_ = light; }
	//--------------------------------------------------//
	DirectX::XMFLOAT3 GetEyePosW() const { return eye_pos_w_; }
	void SetEyePosW(const DirectX::XMFLOAT3& pos) { eye_pos_w_ = pos; }
	//--------------------------------------------------//
	float GetHasTexture() const { return has_texture_; }
	void SetHasTexture(const bool& has_texture) { has_texture_ = has_texture; }
	//--------------------------------------------------//
	
};