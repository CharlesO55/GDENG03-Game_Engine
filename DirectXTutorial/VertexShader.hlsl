
struct VS_INPUT
{
    float4 position : POSITION;
    //float4 position1 : POSITION1;
    float3 color : COLOR;
    float3 color1 : COLOR1;
    //row_major float4x4 transform : TRANSFORM;
    //float4 transform : TRANSFORM;
    //float4 transform1 : TRANSFORM1;
    //float4 transform2 : TRANSFORM2;
    //float4 transform3 : TRANSFORM3;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};


cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    float m_time;
};



VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
	
//	output.position = lerp(input.position, input.position1, (float)((sin((float)(m_time / (float)1000.0f)) + 1.0f) / 2.0f));
    //float4x4 mat_transform = float4x4(input.transform, input.transform1, input.transform2, input.transform3);
    
    output.position = mul(input.position, m_world);
    output.position = mul(output.position, m_world);
    output.position = mul(output.position, m_view);
    output.position = mul(output.position, m_proj);


    output.color = input.color;
    output.color1 = input.color1;
    
    //if (input.transform.r > 0)
    //    output.color1 = input.color;
       
    return output;
}