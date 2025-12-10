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

	float specular_power;
	XMFLOAT3 light_vec_w;
};

struct ConstantBuffer
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;

	SurfaceInfo surface;

	Light light;

	XMFLOAT3 eye_pow_w;
	float has_texture;
};
#endif