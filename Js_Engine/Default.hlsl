
struct VS_INPUT
{
    float4 position : POSITION;
    float4 color : COLOR;
    float2 uv : TEXTURE;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};

// IA - VS - RS - PS - OM
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = input.position;
    output.color = input.color;
    output.uv = input.uv;
    
    return output;
}


// PS
texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

struct PS_INPUT
{
    float4 position : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};

struct PS_OUTPUT
{
    float4 c : SV_Target;
};

PS_OUTPUT PS(PS_INPUT input)
{
    PS_OUTPUT output;
    float4 pixel = texture0.Sample(sampler0, input.uv);
    output.c = pixel;
    
    return output;
}