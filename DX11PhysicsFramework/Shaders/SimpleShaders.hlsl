//--------------------------------------------------------------------------------------
// File: DX11 Framework.hlsl
//--------------------------------------------------------------------------------------

Texture2D txDiffuse : register(t0);

SamplerState samLinear : register(s0);

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

struct SurfaceInfo
{
	float4 amb_mat;
	float4 diff_mat;
	float4 spec_mat;
};

struct Light
{
	float4 amb_light;
	float4 diff_light;
	float4 spec_light;

	float spec_power;
	float3 light_vec_w;
};

cbuffer ConstantBuffer_ : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;

	SurfaceInfo surface;
	Light light;

	float3 EyePosW;
	float HasTexture;
}

struct VS_INPUT
{
	float4 PosL : POSITION;
	float3 NormL : NORMAL;
	float2 Tex : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 PosH : SV_POSITION;
	float3 NormW : NORMAL;

	float3 PosW : POSITION;
	float2 Tex : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS_main(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;

	float4 posW = mul(input.PosL, World);
	output.PosW = posW.xyz;

	output.PosH = mul(posW, View);
	output.PosH = mul(output.PosH, Projection);
	output.Tex = input.Tex;

	float3 normalW = mul(float4(input.NormL, 0.0f), World).xyz;
	output.NormW = normalize(normalW);

    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS_main(VS_OUTPUT input) : SV_Target
{
	float3 normalW = normalize(input.NormW);

	float3 toEye = normalize(EyePosW - input.PosW);

	// Get texture data from file
	float4 textureColour = txDiffuse.Sample(samLinear, input.Tex);

	float4 ambient = float4(0.0f, 0.0f, 0.0f,0.0f);
    float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightLecNorm = normalize(light.light_vec_w);
	// Compute Colour

	// Compute the reflection vector.
	float3 r = reflect(-lightLecNorm, normalW);

	// Determine how much specular light makes it into the eye.
	float specularAmount = pow(saturate(dot(r, toEye)), light.spec_power);

	// Determine the diffuse light intensity that strikes the vertex.
    float diffuseAmount = saturate(dot(lightLecNorm, normalW));

	// Only display specular when there is diffuse
	if (diffuseAmount <= 0.0f)
	{
		specularAmount = 0.0f;
	}

	// Sum all the terms together and copy over the diffuse alpha.
	float4 finalColour;

	if (HasTexture == 1.0f)
	{
        specular += specularAmount * (surface.spec_mat * light.spec_light);
        diffuse += diffuseAmount * (textureColour * light.diff_light);
        ambient += (textureColour * light.amb_light);
		
		finalColour = ambient + diffuse + specular;
    }
	else
	{
        specular += specularAmount * (surface.spec_mat * light.spec_light);
        diffuse += diffuseAmount * (surface.diff_mat * light.diff_light);
        ambient += (surface.amb_mat * light.amb_light);
		
		finalColour.rgb = ambient + diffuse + specular;
	}

	finalColour.a = surface.diff_mat.a;

	return finalColour;
}