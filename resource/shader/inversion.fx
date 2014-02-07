void vsmain(float4 pos : POSITION,
			float4 color : COLOR,
			out float4 oPos : POSITION,
			out float4 oColor : COLOR)
{
	oPos = pos;
	oColor = color;
}

float4 psmain(float4 color : COLOR) : COLOR
{
	return 1.0f-color;
}

technique std
{
	pass
	{
		VertexShader = compile vs_2_0 vsmain();
		PixelShader = compile ps_2_0 psmain();
	}
}