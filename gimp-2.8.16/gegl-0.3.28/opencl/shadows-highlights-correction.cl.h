static const char* shadows_highlights_correction_cl_source =
"float3 overlay(const float3 in_a,                                             \n"
"               const float3 in_b,                                             \n"
"               const float  opacity,                                          \n"
"               const float  transform,                                        \n"
"               const float  ccorrect,                                         \n"
"               const float  low_approximation)                                \n"
"{                                                                             \n"
"  /* a contains underlying image; b contains mask */                          \n"
"                                                                              \n"
"  const float3 scale = (float3)(100.0f, 128.0f, 128.0f);                      \n"
"  float3 a = in_a / scale;                                                    \n"
"  float3 b = in_b / scale;                                                    \n"
"                                                                              \n"
"                                                                              \n"
"  float opacity2 = opacity*opacity;                                           \n"
"                                                                              \n"
"  while(opacity2 > 0.0f)                                                      \n"
"  {                                                                           \n"
"    float la = a.x;                                                           \n"
"    float lb = (b.x - 0.5f) * sign(opacity)*sign(1.0f - la) + 0.5f;           \n"
"    float lref = copysign(fabs(la) > low_approximation ? 1.0f/fabs(la) : 1.0f/low_approximation, la);\n"
"    float href = copysign(fabs(1.0f - la) > low_approximation ? 1.0f/fabs(1.0f - la) : 1.0f/low_approximation, 1.0f - la);\n"
"                                                                              \n"
"    float chunk = opacity2 > 1.0f ? 1.0f : opacity2;                          \n"
"    float optrans = chunk * transform;                                        \n"
"    opacity2 -= 1.0f;                                                         \n"
"                                                                              \n"
"    a.x = la * (1.0f - optrans) + (la > 0.5f ? 1.0f - (1.0f - 2.0f * (la - 0.5f)) * (1.0f-lb) : 2.0f * la * lb) * optrans;\n"
"    a.y = a.y * (1.0f - optrans) + (a.y + b.y) * (a.x*lref * ccorrect + (1.0f - a.x)*href * (1.0f - ccorrect)) * optrans;\n"
"    a.z = a.z * (1.0f - optrans) + (a.z + b.z) * (a.x*lref * ccorrect + (1.0f - a.x)*href * (1.0f - ccorrect)) * optrans;\n"
"  }                                                                           \n"
"  /* output scaled back pixel */                                              \n"
"  return a * scale;                                                           \n"
"}                                                                             \n"
"                                                                              \n"
"                                                                              \n"
"__kernel void shadows_highlights(__global const float4  *in,                  \n"
"                                 __global const float   *aux,                 \n"
"                                 __global       float4  *out,                 \n"
"                                          const float    shadows,             \n"
"                                          const float    highlights,          \n"
"                                          const float    compress,            \n"
"                                          const float    shadows_ccorrect,    \n"
"                                          const float    highlights_ccorrect, \n"
"                                          const float    whitepoint)          \n"
"{                                                                             \n"
"  int gid = get_global_id(0);                                                 \n"
"  const float low_approximation = 0.01f;                                      \n"
"                                                                              \n"
"  float4 io = in[gid];                                                        \n"
"  float3 m = (float3)0.0f;                                                    \n"
"  float xform;                                                                \n"
"                                                                              \n"
"  if (! aux)                                                                  \n"
"    {                                                                         \n"
"      out[gid] = io;                                                          \n"
"      return;                                                                 \n"
"    }                                                                         \n"
"                                                                              \n"
"  /* blurred, inverted and desaturaed mask in m */                            \n"
"  m.x = 100.0f - aux[gid];                                                    \n"
"                                                                              \n"
"  /* white point adjustment */                                                \n"
"  io.x = io.x > 0.0f ? io.x/whitepoint : io.x;                                \n"
"  m.x = m.x > 0.0f ? m.x/whitepoint : m.x;                                    \n"
"                                                                              \n"
"  /* overlay highlights */                                                    \n"
"  xform = clamp(1.0f - 0.01f * m.x/(1.0f-compress), 0.0f, 1.0f);              \n"
"  io.xyz = overlay(io.xyz, m, -highlights, xform, 1.0f - highlights_ccorrect, low_approximation);\n"
"                                                                              \n"
"  /* overlay shadows */                                                       \n"
"  xform = clamp(0.01f * m.x/(1.0f-compress) - compress/(1.0f-compress), 0.0f, 1.0f);\n"
"  io.xyz = overlay(io.xyz, m, shadows, xform, shadows_ccorrect, low_approximation);\n"
"                                                                              \n"
"  out[gid] = io;                                                              \n"
"}                                                                             \n"
;
