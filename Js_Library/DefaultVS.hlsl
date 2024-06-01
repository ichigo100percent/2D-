//float4 main( float4 pos : POSITION ) : SV_POSITION
//{
//	return pos;
//}

float4 VS(float4 p : POSITION) : SV_POSITION
{
    return float4(p.x, p.y, 0.5f, 1.0f);
}