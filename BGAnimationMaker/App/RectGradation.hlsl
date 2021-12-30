//	Based on Siv3D v0.6.3 default 2D shader

//
//	Textures
//
Texture2D		g_texture0 : register(t0);
SamplerState	g_sampler0 : register(s0);

namespace s3d
{
	//
	//	VS Output / PS Input
	//
	struct PSInput
	{
		float4 position	: SV_POSITION;
		float4 color	: COLOR0;
		float2 uv		: TEXCOORD0;
	};
}

//
//	Constant Buffer
//
cbuffer PSConstants2D : register(b0)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
	float4 g_sdfOutlineColor;
	float4 g_sdfShadowColor;
	float4 g_internal;
}

cbuffer Color4 : register(b1)
{
	float4 c0, c1, c2, c3;
}

//
//	Functions
//

float4 PS(s3d::PSInput input) : SV_TARGET
{
	//bi-linear
	const float4 c = lerp(
		lerp(c0, c1, input.uv.x),
		lerp(c3, c2, input.uv.x),
		input.uv.y
	);

	return c;
}
