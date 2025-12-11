#include "DX11PhysicsFramework.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

bool DX11PhysicsFramework::HandleKeyboard(const MSG& msg)
{
	XMFLOAT3 cameraPosition = camera_->GetPosition();

	switch (msg.wParam)
	{
		case VK_UP:
			cam_orbit_radius_ = max(cam_orbit_radius_min_, cam_orbit_radius_ - (cam_speed_ * 0.2f));
			return true;

		case VK_DOWN:
			cam_orbit_radius_ = min(cam_orbit_radius_max_, cam_orbit_radius_ + (cam_speed_ * 0.2f));
			return true;

		case VK_RIGHT:
			cam_orbit_angle_xz_ -= cam_speed_;
			return true;

		case VK_LEFT:
			cam_orbit_angle_xz_ += cam_speed_;
			return true;

		default:
		return false;
	}
}

HRESULT DX11PhysicsFramework::Initialise(HINSTANCE hInstance, int nShowCmd)
{
	HRESULT hr = S_OK;

	#pragma region Non-D3D11 Instantiation
	light_ = new Light();
	loading_ = new Loading();
	obj_mesh_ = new MeshData();
	#pragma endregion

	hr = CreateWindowHandle(hInstance, nShowCmd);
	if (FAILED(hr)) return E_FAIL;
	//--------------------------------------------------//
	hr = CreateD3DDevice();
	if (FAILED(hr)) return E_FAIL;
	//--------------------------------------------------//
	hr = CreateSwapChainAndFrameBuffer();
	if (FAILED(hr)) return E_FAIL;
	//--------------------------------------------------//
	hr = InitShadersAndInputLayout();
	if (FAILED(hr)) return E_FAIL;
	//--------------------------------------------------//
	hr = InitVertexIndexBuffers();
	if (FAILED(hr)) return E_FAIL;
	//--------------------------------------------------//
	hr = InitPipelineStates();
	if (FAILED(hr)) return E_FAIL;
	//--------------------------------------------------//
	hr = InitRunTimeData();
	if (FAILED(hr)) return E_FAIL;

	return hr;
}

DX11PhysicsFramework::~DX11PhysicsFramework()
{
	#pragma region Non-D3D11 Cleanup
	if (light_) light_ = nullptr;
	if (loading_) loading_ = nullptr;
	if (obj_mesh_) obj_mesh_->index_buffer->Release(); obj_mesh_->vertex_buffer->Release(); obj_mesh_ = nullptr;
	for each (GameObject * go in game_object_) {go = nullptr;}
	if (camera_) camera_ = nullptr;
	#pragma endregion

	if (immediate_context_)immediate_context_->Release();

	if (frame_buffer_view_)frame_buffer_view_->Release();
	if (depth_buffer_view_)depth_buffer_view_->Release();
	
	if (depth_stencil_buffer_)depth_stencil_buffer_->Release();
	
	if (swap_chain_)swap_chain_->Release();
	
	if (cw_cull_mode_)cw_cull_mode_->Release();
	if (ccw_cull_mode_)ccw_cull_mode_->Release();
	
	if (input_layout_)input_layout_->Release();
	
	if (vertex_shader_)vertex_shader_->Release();
	if (pixel_shader_)pixel_shader_->Release();
	
	if (constant_buffer_)constant_buffer_->Release();
	if (cube_vb_)cube_vb_->Release();
	if (plane_vb_)plane_vb_->Release();
	if (cube_ib_)cube_ib_->Release();
	if (plane_ib_)plane_ib_->Release();

	if (ds_less_equal_) ds_less_equal_->Release();
	if (rs_cull_none_) rs_cull_none_->Release();

	if (sampler_state_)sampler_state_->Release();
	if (stone_tex_rv_)stone_tex_rv_->Release();
	if (ground_tex_rv_)ground_tex_rv_->Release();
	if (hercules_tex_rv_)hercules_tex_rv_->Release();

	if (dxgi_device_)dxgi_device_->Release();
	if (dxgi_factory_)dxgi_factory_->Release();
	
	if (device_)device_->Release();
}

HRESULT DX11PhysicsFramework::CreateWindowHandle(HINSTANCE hInstance, int nCmdShow)
{
	const wchar_t* windowName = L"DX11 Physics Stardust";
	//--------------------------------------------------//
	WNDCLASSW wndClass;
	wndClass.style = 0;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = nullptr;
	wndClass.hIcon = nullptr;
	wndClass.hCursor = nullptr;
	wndClass.hbrBackground = nullptr;
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = windowName;
	//--------------------------------------------------//
	RegisterClassW(&wndClass);
	//--------------------------------------------------//
	window_handle_ = CreateWindowExW(0, windowName, windowName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
		nullptr, nullptr, hInstance, nullptr);

	return S_OK;
}

HRESULT DX11PhysicsFramework::CreateD3DDevice()
{
	HRESULT hr = S_OK;
	//--------------------------------------------------//
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
	};
	//--------------------------------------------------//
	ID3D11Device* baseDevice;
	ID3D11DeviceContext* baseDeviceContext;
	//--------------------------------------------------//
	DWORD createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT | createDeviceFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &baseDevice, nullptr, &baseDeviceContext);
	if (FAILED(hr)) return hr;

	///////////////////////////////////////////////////////////////////////////////////////////////

	hr = baseDevice->QueryInterface(__uuidof(ID3D11Device), reinterpret_cast<void**>(&device_));
	hr = baseDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext), reinterpret_cast<void**>(&immediate_context_));

	baseDevice->Release();
	baseDeviceContext->Release();

	///////////////////////////////////////////////////////////////////////////////////////////////

	hr = device_->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgi_device_));
	if (FAILED(hr)) return hr;

	IDXGIAdapter* dxgiAdapter;
	hr = dxgi_device_->GetAdapter(&dxgiAdapter);
	hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgi_factory_));
	dxgiAdapter->Release();

	return S_OK;
}

HRESULT DX11PhysicsFramework::CreateSwapChainAndFrameBuffer()
{
	HRESULT hr = S_OK;
	//--------------------------------------------------//
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
	swapChainDesc.Width = 0; // Defer to WindowWidth
	swapChainDesc.Height = 0; // Defer to WindowHeight
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //FLIP* modes don't support sRGB backbuffer
	swapChainDesc.Stereo = FALSE;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapChainDesc.Flags = 0;
	//--------------------------------------------------//
	hr = dxgi_factory_->CreateSwapChainForHwnd(device_, window_handle_, &swapChainDesc, nullptr, nullptr, &swap_chain_);
	if (FAILED(hr)) return hr;

	///////////////////////////////////////////////////////////////////////////////////////////////

	ID3D11Texture2D* frameBuffer = nullptr;
	//--------------------------------------------------//
	hr = swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&frameBuffer));
	if (FAILED(hr)) return hr;
	//--------------------------------------------------//
	D3D11_RENDER_TARGET_VIEW_DESC framebufferDesc = {};
	framebufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; //sRGB render target enables hardware gamma correction
	framebufferDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	//--------------------------------------------------//
	hr = device_->CreateRenderTargetView(frameBuffer, &framebufferDesc, &frame_buffer_view_);
	//--------------------------------------------------//
	frameBuffer->Release();
	//--------------------------------------------------//
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	frameBuffer->GetDesc(&depthBufferDesc); // copy from framebuffer properties
	//--------------------------------------------------//
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	//--------------------------------------------------//
	device_->CreateTexture2D(&depthBufferDesc, nullptr, &depth_stencil_buffer_);
	device_->CreateDepthStencilView(depth_stencil_buffer_, nullptr, &depth_buffer_view_);
	//--------------------------------------------------//
	return hr;
}

HRESULT DX11PhysicsFramework::InitShadersAndInputLayout()
{
	HRESULT hr = S_OK;
	ID3DBlob* errorBlob;
	//--------------------------------------------------//
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	#pragma region Compile & Create Vertex Shader
	ID3DBlob* vsBlob;
    hr = D3DCompileFromFile(L"Shaders/SimpleShaders.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS_main", "vs_5_0", dwShaderFlags, 0, &vsBlob, &errorBlob);
	if (FAILED(hr))
	{
		MessageBoxA(window_handle_, (char*)errorBlob->GetBufferPointer(), nullptr, ERROR);
		errorBlob->Release();
		return hr;
	}
	//--------------------------------------------------//
	hr = device_->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertex_shader_);
	if (FAILED(hr))
	{	
		vsBlob->Release();
        return hr;
	}
	#pragma endregion

	#pragma region Compile & Create Pixel Shader
	ID3DBlob* psBlob;
	hr = D3DCompileFromFile(L"Shaders/SimpleShaders.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS_main", "ps_5_0", dwShaderFlags, 0, &psBlob, &errorBlob);
	if (FAILED(hr))
	{
		MessageBoxA(window_handle_, (char*)errorBlob->GetBufferPointer(), nullptr, ERROR);
		errorBlob->Release();
		return hr;
	}

	// Create the pixel shader
	hr = device_->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pixel_shader_);

    if (FAILED(hr)) return hr;
	#pragma endregion
	
    #pragma region Define & Create Input Layout
    D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

    // Create the input layout
	hr = device_->CreateInputLayout(inputElementDesc, ARRAYSIZE(inputElementDesc), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &input_layout_);
	#pragma endregion
	
	vsBlob->Release();
	psBlob->Release();
	errorBlob->Release();

	return hr;
}

HRESULT DX11PhysicsFramework::InitVertexIndexBuffers()
{
	#pragma region Create & Bind Cube VB
    // Create vertex buffer
    SimpleVertex vertices[] =
    {
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0, 1.0f, 0), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0, 1.0f, 0), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0, 1.0f, 0), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0, 1.0f, 0), XMFLOAT2(1.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0, -1.0f, 0), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0, -1.0f, 0), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0, -1.0f, 0), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0, -1.0f, 0), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-1.0f, 0, 0), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, 0, 0), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-1.0f, 0, 0), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0, 0), XMFLOAT2(0.0f, 0.0f) },

		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(1.0f, 0, 0), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0, 0), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(1.0f, 0, 0), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0, 0), XMFLOAT2(1.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0, 0, -1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0, 0, -1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0, 0, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0, 0, -1.0f), XMFLOAT2(0.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0, 0, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0, 0, 1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0, 0, 1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0, 0, 1.0f), XMFLOAT2(1.0f, 0.0f) },
    };

    D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(SimpleVertex) * 24;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = vertices;

    HRESULT hr = device_->CreateBuffer(&bd, &InitData, &cube_vb_);
    if (FAILED(hr)) return hr;
	#pragma endregion

	#pragma region Create & Bind Cube IB
	// Create index buffer
	WORD indices[] =
	{
		3, 1, 0,
		2, 1, 3,

		6, 4, 5,
		7, 4, 6,

		11, 9, 8,
		10, 9, 11,

		14, 12, 13,
		15, 12, 14,

		19, 17, 16,
		18, 17, 19,

		22, 20, 21,
		23, 20, 22
	};

	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 36;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = indices;
	hr = device_->CreateBuffer(&bd, &InitData, &cube_ib_);
	if (FAILED(hr)) return hr;
	#pragma endregion

	#pragma region Create & Bind Plane VB
	SimpleVertex planeVertices[] =
	{
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 5.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(5.0f, 5.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(5.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
	};

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = planeVertices;

	hr = device_->CreateBuffer(&bd, &InitData, &plane_vb_);

	if (FAILED(hr)) return hr;
	#pragma endregion

	#pragma region Create & Bind Plane IB
	// Create plane index buffer
	WORD planeIndices[] =
	{
		0, 3, 1,
		3, 2, 1,
	};

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 6;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = planeIndices;
	hr = device_->CreateBuffer(&bd, &InitData, &plane_ib_);

	if (FAILED(hr)) return hr;
	#pragma endregion

	return S_OK;
}

HRESULT DX11PhysicsFramework::InitPipelineStates()
{
	immediate_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	immediate_context_->IASetInputLayout(input_layout_);

	#pragma region Create & Bind Rasterizer States
	// Rasterizer
	D3D11_RASTERIZER_DESC cmdesc;
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_NONE;
	HRESULT hr = device_->CreateRasterizerState(&cmdesc, &rs_cull_none_);

	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_BACK;
	cmdesc.FrontCounterClockwise = true;
	hr = device_->CreateRasterizerState(&cmdesc, &ccw_cull_mode_);

	cmdesc.FrontCounterClockwise = false;
	hr = device_->CreateRasterizerState(&cmdesc, &cw_cull_mode_);

	immediate_context_->RSSetState(cw_cull_mode_);
	#pragma endregion

	#pragma region Create & Bind Depth Stencil + Sampler
	D3D11_DEPTH_STENCIL_DESC dssDesc;
	ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dssDesc.DepthEnable = true;
	dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	device_->CreateDepthStencilState(&dssDesc, &ds_less_equal_);

	immediate_context_->OMSetDepthStencilState(ds_less_equal_, 0);

	D3D11_SAMPLER_DESC bilinearSamplerdesc = {};
	bilinearSamplerdesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	bilinearSamplerdesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	bilinearSamplerdesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	bilinearSamplerdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	bilinearSamplerdesc.MaxLOD = INT_MAX;
	bilinearSamplerdesc.MinLOD = 0;

	hr = device_->CreateSamplerState(&bilinearSamplerdesc, &sampler_state_);
	if (FAILED(hr)) return hr;
	#pragma endregion

    return S_OK;
}

HRESULT DX11PhysicsFramework::InitRunTimeData()
{
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	#pragma region Create & Bind Viewport
	viewport_ = { 0.0f, 0.0f, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), 0.0f, 1.0f };
	immediate_context_->RSSetViewports(1, &viewport_);
	#pragma endregion

	hr = device_->CreateBuffer(&constantBufferDesc, nullptr, &constant_buffer_);
	if (FAILED(hr)) { return hr; }

	#pragma region Load & Bind Stone + Floor texture
	stone_tex_rv_ = loading_->LoadTexture(device_, R"(Loaders\\Resources\\Textures\\stone.dds)");
	ground_tex_rv_ = loading_->LoadTexture(device_, R"(Loaders\\Resources\\Textures\\floor.dds)");
	#pragma endregion

	#pragma region Setup Camera
	XMFLOAT3 eye = XMFLOAT3(0.0f, 2.0f, -1.0f);
	XMFLOAT3 at = XMFLOAT3(0.0f, 2.0f, 0.0f);
	XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);

	camera_ = new Camera(eye, at, up, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), 0.01f, 200.0f);
	#pragma endregion

	#pragma region Setup Scene Light
	light_->ambient_light = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	light_->diffuse_light = XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f);
	light_->specular_light = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	light_->specular_power = 10.0f;
	light_->light_vec_w = XMFLOAT3(0.0f, 0.5f, -1.0f);
	#pragma endregion
	
	#pragma region Setup Hercules Geometry
	Geometry herculesGeometry;
	obj_mesh_ = loading_->LoadMesh(device_, R"(Loaders\\Resources\\OBJ\\donut.obj)");
	herculesGeometry.index_buffer = obj_mesh_->index_buffer;
	herculesGeometry.indices_num = static_cast<int>(obj_mesh_->index_count);
	herculesGeometry.vertex_buffer = obj_mesh_->vertex_buffer;
	herculesGeometry.vb_offset = obj_mesh_->vb_offset;
	herculesGeometry.vb_stride = obj_mesh_->vb_stride;
	#pragma endregion

	#pragma region Setup Cube Geometry
	Geometry cubeGeometry;
	cubeGeometry.index_buffer = cube_ib_;
	cubeGeometry.vertex_buffer = cube_vb_;
	cubeGeometry.indices_num = 36;
	cubeGeometry.vb_offset = 0;
	cubeGeometry.vb_stride = sizeof(SimpleVertex);
	#pragma endregion

	#pragma region Setup Plane Geometry
	Geometry planeGeometry;
	planeGeometry.index_buffer = plane_ib_;
	planeGeometry.vertex_buffer = plane_vb_;
	planeGeometry.indices_num = 6;
	planeGeometry.vb_offset = 0;
	planeGeometry.vb_stride = sizeof(SimpleVertex);
	#pragma endregion

	#pragma region Setup Shiny Material
	Material shinyMaterial;
	shinyMaterial.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	shinyMaterial.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	shinyMaterial.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	#pragma endregion

	#pragma region Setup Non-Shiny Material
	Material noSpecMaterial;
	noSpecMaterial.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	noSpecMaterial.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	noSpecMaterial.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	#pragma endregion

	#pragma region Initialise Floor Object
	GameObject* gameObject = new GameObject("Floor", planeGeometry, noSpecMaterial);
	gameObject->GetTransform()->SetPosition(0.0f, 0.0f, 0.0f);
	gameObject->SetScale(15.0f, 15.0f, 15.0f);
	gameObject->SetRotation(XMConvertToRadians(90.0f), 0.0f, 0.0f);
	gameObject->SetTextureRV(ground_tex_rv_);
	
	game_object_.push_back(gameObject);
	#pragma endregion

	#pragma region Intialise Cube Objects
	for (int i = 0; i < 4; i++)
	{
		gameObject = new GameObject("Cube " + i, cubeGeometry, shinyMaterial);
		gameObject->SetScale(1.0f, 1.0f, 1.0f);
		gameObject->GetTransform()->SetPosition(-2.0f + (static_cast<float>(i) * 2.5f), 1.0f, 10.0f);
		gameObject->SetTextureRV(stone_tex_rv_);

		game_object_.push_back(gameObject);
	}
	#pragma endregion

	#pragma region Intialise Donut Object
	gameObject = new GameObject("Donut", herculesGeometry, shinyMaterial);
	gameObject->SetScale(1.0f, 1.0f, 1.0f);
	gameObject->GetTransform()->SetPosition(-5.0f, 0.5f, 10.0f);
	gameObject->SetTextureRV(stone_tex_rv_);
	
	game_object_.push_back(gameObject);
	#pragma endregion
	
	return S_OK;
}

void DX11PhysicsFramework::Update()
{
	#pragma region TimeStep Calculations  
	static ULONGLONG frameStart = GetTickCount64();

	ULONGLONG frameNow = GetTickCount64();
	float deltaTime = static_cast<float>(frameNow - frameStart) / 1000.0f;
	frameStart = frameNow;

	static float simpleCount = 0.0f;
	simpleCount += deltaTime;
	#pragma endregion

	#pragma region Keyboard Input for Objects
	if (GetAsyncKeyState('1'))
	{
		game_object_.at(1)->GetTransform()->SetPosition(0, 0, -0.02f);
	}
	if (GetAsyncKeyState('2'))
	{
		game_object_.at(1)->GetTransform()->SetPosition(0, 0, 0.02f);
	}
	if (GetAsyncKeyState('3'))
	{
		game_object_.at(2)->GetTransform()->SetPosition(0, 0, -0.02f);
	}
	if (GetAsyncKeyState('4'))
	{
		game_object_.at(2)->GetTransform()->SetPosition(0, 0, 0.02f);
	}
	#pragma endregion
	
	#pragma region Camera Update
	float angleAroundZ = XMConvertToRadians(cam_orbit_angle_xz_);

	float x = cam_orbit_radius_ * cos(angleAroundZ);
	float z = cam_orbit_radius_ * sin(angleAroundZ);

	XMFLOAT3 cameraPos = camera_->GetPosition();
	cameraPos.x = x;
	cameraPos.z = z;

	camera_->SetPosition(cameraPos);
	camera_->Update();
	#pragma endregion
	
	for (auto gameObject : game_object_)
	{
		gameObject->Update(deltaTime);
	}
}

void DX11PhysicsFramework::Draw()
{
	#pragma region Clear Buffers
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // red,green,blue,alpha
	immediate_context_->OMSetRenderTargets(1, &frame_buffer_view_, depth_buffer_view_);
    immediate_context_->ClearRenderTargetView(frame_buffer_view_, ClearColor);
	immediate_context_->ClearDepthStencilView(depth_buffer_view_, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	#pragma endregion

	#pragma region Setup Buffers & Render scene
	immediate_context_->VSSetShader(vertex_shader_, nullptr, 0);
	immediate_context_->PSSetShader(pixel_shader_, nullptr, 0);

	immediate_context_->VSSetConstantBuffers(0, 1, &constant_buffer_);
	immediate_context_->PSSetConstantBuffers(0, 1, &constant_buffer_);
	immediate_context_->PSSetSamplers(0, 1, &sampler_state_);

	XMFLOAT4X4 tempView = camera_->GetView();
	XMFLOAT4X4 tempProjection = camera_->GetProjection();

	XMMATRIX view = XMLoadFloat4x4(&tempView);
	XMMATRIX projection = XMLoadFloat4x4(&tempProjection);

	cb_data_.SetViewMatrix(XMMatrixTranspose(view));
	cb_data_.SetProjectionMatrix(XMMatrixTranspose(projection));

	cb_data_.SetLight(*light_);
	cb_data_.SetEyePowW(camera_->GetPosition());
	#pragma endregion

	#pragma region Render Game Objects
	for (auto gameObject : game_object_)
	{
		// Get render material
		Material material = gameObject->GetMaterial();

		// Copy material to shader
		cb_data_.SetSurfaceInfo(material.ambient, material.diffuse, material.specular);

		// Set world matrix
		cb_data_.SetWorldMatrix(XMMatrixTranspose(gameObject->GetWorldMatrix()));

		// Set texture
		if (gameObject->HasTexture())
		{
			immediate_context_->PSSetShaderResources(0, 1, gameObject->GetTextureRV());
			cb_data_.SetHasTexture(true);
		}
		else
		{
			cb_data_.SetHasTexture(false);
		}

		//Write constant buffer data onto GPU
		D3D11_MAPPED_SUBRESOURCE mappedSubresource;
		immediate_context_->Map(constant_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
		memcpy(mappedSubresource.pData, &cb_data_, sizeof(cb_data_));
		immediate_context_->Unmap(constant_buffer_, 0);

		// Draw object
		gameObject->Draw(immediate_context_);
	}
	#pragma endregion

    //
    // Present our back buffer to our front buffer
    //
    swap_chain_->Present(0, 0);
}