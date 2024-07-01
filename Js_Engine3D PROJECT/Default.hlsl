
struct VS_INPUT
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

cbuffer CameraData : register(b0)
{
    row_major matrix ViewMatrix;
    row_major matrix ProjectionMatrix;
}

cbuffer TransformData : register(b1)
{
    row_major matrix WorldMatrix;
}

cbuffer AnimationData : register(b2)
{
    float2 spriteOffset;
    float2 spriteSize;
    float2 textureSize;
    float useAnimation;
}
    
// IA - VS - RS - PS - OM
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    
    float4 position = mul(input.position, WorldMatrix); // W
    position = mul(position, ViewMatrix); // V
    position = mul(position, ProjectionMatrix); // P
    
    output.position = position;
    output.uv = input.uv;
    
    if (useAnimation == 1.0f)
    {
        output.uv *= spriteSize / textureSize;
        output.uv += spriteOffset  / textureSize;
    }

    return output;
}


struct PS_INPUT
{
    float4 position : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};

Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 color = texture0.Sample(sampler0, input.uv);
	
    color.r = dot(color.rgb, float3(1.1f, 0.0f, 0.0f));
    color.g = dot(color.rgb, float3(0.0f, 1.1f, 0.0f));
    color.b = dot(color.rgb, float3(0.0f, 0.0f, 1.1f));

    float gamma = 2.2;
    color.rgb = pow(color.rgb, 1.0 / gamma);

    
    //// 제거하려는 색상 (147, 187, 236)
    //float3 removeColor = float3(147.0 / 255.0, 187.0 / 255.0, 236.0 / 255.0);

    //// 색상이 제거하려는 색상과 일치하는지 확인
    //if (all(abs(color.rgb - removeColor) < 0.01))
    //{
    //    // 색상이 일치하면 알파 값을 0으로 설정하여 투명하게 만듦
    //    color.a = 0.0;
    //}
   
    return color;
}