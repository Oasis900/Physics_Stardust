#pragma once
#define PHYSICS_FRAMEWORK_HPP

#include <windows.h>
#include <d3d11_1.h>

#include <Core/Timer.h>
#include <Core/Debug.h>
#include <Objects/DebugCamera.h>
#include <Objects/GameObject.h>
#include <Loaders/Loader.h>
#include <Structures/Structures.h>

static constexpr int WINDOW_WIDTH = 1280;
static constexpr int WINDOW_HEIGHT = 720;
static constexpr float FPS60 = 1.0f/60.0f;
static constexpr float SPEED = 100.0f;

class DX11PhysicsFramework
{
	HWND window_handle_;
	//--------------------------------------------------//
	ID3D11DeviceContext* immediate_context_ = nullptr;
	ID3D11Device* device_ = nullptr;
	IDXGIDevice* dxgi_device_ = nullptr;
	IDXGIFactory2* dxgi_factory_ = nullptr;
	ID3D11RenderTargetView* frame_buffer_view_ = nullptr;
	IDXGISwapChain1* swap_chain_ = nullptr;
	D3D11_VIEWPORT viewport_;
	//--------------------------------------------------//
	ID3D11VertexShader* vertex_shader_ = nullptr;
	ID3D11PixelShader* pixel_shader_ = nullptr;
	ID3D11InputLayout* input_layout_ = nullptr;
	ID3D11Buffer* constant_buffer_ = nullptr;
	ID3D11Buffer* cube_vb_ = nullptr;
	ID3D11Buffer* cube_ib_ = nullptr;
	//--------------------------------------------------//
	ID3D11Buffer* plane_vb_ = nullptr;
	ID3D11Buffer* plane_ib_ = nullptr;
	//--------------------------------------------------//
	ID3D11DepthStencilView* depth_buffer_view_ = nullptr;
	ID3D11Texture2D* depth_stencil_buffer_ = nullptr;
	//--------------------------------------------------//
	ID3D11ShaderResourceView* stone_tex_rv_ = nullptr;
	ID3D11ShaderResourceView* ground_tex_rv_ = nullptr;
	ID3D11ShaderResourceView* sun_tex_rv = nullptr;
	//--------------------------------------------------//
	ID3D11SamplerState* sampler_state_ = nullptr;
	//--------------------------------------------------//
	std::vector<GameObject*> game_object_;
	DebugCamera* b_camera_ = nullptr;
	Loader* load_ = nullptr;
	LightInfo* light_ = nullptr;
	MeshData* obj_mesh_ = nullptr;
	Timer* timer_ = nullptr;
	//--------------------------------------------------//
	const float cam_speed_ = 0.6f * 0.2f;
	//--------------------------------------------------//
	ID3D11DepthStencilState* ds_less_equal_ = nullptr;
	ID3D11RasterizerState* rs_cull_none_ = nullptr;
	//--------------------------------------------------//
	ID3D11RasterizerState* ccw_cull_mode_ = nullptr; // Counter Clockwise
	ID3D11RasterizerState* cw_cull_mode_ = nullptr; // Clockwise
	//--------------------------------------------------//
	HRESULT CreateWindowHandle(HINSTANCE hInstance, int nCmdShow);
	HRESULT CreateD3DDevice();
	HRESULT CreateSwapChainAndFrameBuffer();
	//--------------------------------------------------//
	HRESULT InitShadersAndInputLayout();
	HRESULT InitVertexIndexBuffers();
	HRESULT InitPipelineStates();
	HRESULT InitRunTimeData();

public:
	~DX11PhysicsFramework();
	//--------------------------------------------------//
	HRESULT Initialise(HINSTANCE hInstance, int nShowCmd);
	//--------------------------------------------------//
	bool HandleKeyboard(const MSG& msg);
	void Update();
	void Draw();
	void KeyInput();
};

