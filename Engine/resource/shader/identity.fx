float4x4 matrix_world_view_proj;

texture tex0;
sampler2D sampler0 = sampler_state
{
  texture = tex0;
  MinFilter = Linear;
  MagFilter = Linear;
  MipFilter = Linear;
};

void vsmain(float3 pos : POSITION,
      float2 tex_cords : TEXCOORD0,
      out float4 out_position : POSITION,
      out float2 oTexc : TEXCOORD0)
{
  out_position = mul(float4(pos,1), matrix_world_view_proj);
  oTexc = tex_cords;
}

float4 psmain(float2 tex_cords : TEXCOORD0) : COLOR
{
  return tex2D(sampler0, tex_cords);
}

technique std
{
  pass
  {
    VertexShader = compile vs_2_0 vsmain();
    PixelShader = compile ps_2_0 psmain();
  }
}