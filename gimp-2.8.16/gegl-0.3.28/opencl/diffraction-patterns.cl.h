static const char* diffraction_patterns_cl_source =
"float3                                                                        \n"
"diff_intensity (const float x,                                                \n"
"                const float y,                                                \n"
"                const float3 lam,                                             \n"
"                const float polarization,                                     \n"
"                const float scattering,                                       \n"
"                const int   iterations,                                       \n"
"                const float weird_factor)                                     \n"
"{                                                                             \n"
"  float3 cxy = (float3)0.0f;                                                  \n"
"  float3 sxy = (float3)0.0f;                                                  \n"
"                                                                              \n"
"  for (int i = 0; i <= iterations; i++)                                       \n"
"    {                                                                         \n"
"      const float a = -M_PI_F + i * (2.0f * M_PI_F / iterations);             \n"
"      float sina, cosa;                                                       \n"
"      sina = sincos (a, &cosa);                                               \n"
"                                                                              \n"
"      const float v0 = cosa;                                                  \n"
"      const float v1 = 0.75f * sina;                                          \n"
"      const float v2 = 0.5f * (4.0f * cosa * cosa + sina * sina);             \n"
"      const float3 p = 4.0f * lam * (v0 * x + v1 * y - v2);                   \n"
"                                                                              \n"
"      float3 sinp, cosp;                                                      \n"
"      sinp = sincos (p, &cosp);                                               \n"
"      cxy += cosp;                                                            \n"
"      sxy += sinp;                                                            \n"
"    }                                                                         \n"
"                                                                              \n"
"  cxy *= weird_factor;                                                        \n"
"  sxy *= weird_factor;                                                        \n"
"                                                                              \n"
"  const float polpi2 = polarization * (M_PI_F / 2.0f);                        \n"
"  float sinpolpi2, cospolpi2;                                                 \n"
"  sinpolpi2 = sincos (polpi2, &cospolpi2);                                    \n"
"                                                                              \n"
"  return scattering * ((cospolpi2 + sinpolpi2) * cxy * cxy +                  \n"
"                       (cospolpi2 - sinpolpi2) * sxy * sxy);                  \n"
"}                                                                             \n"
"                                                                              \n"
"__kernel void                                                                 \n"
"cl_diffraction_patterns (__global       float *out,                           \n"
"                                  const int    offset_x,                      \n"
"                                  const int    offset_y,                      \n"
"                                  const int    width,                         \n"
"                                  const int    height,                        \n"
"                                  const float3 sedges,                        \n"
"                                  const float3 contours,                      \n"
"                                  const float3 frequency,                     \n"
"                                  const float  brightness,                    \n"
"                                  const float  polarization,                  \n"
"                                  const float  scattering,                    \n"
"                                  const int    iterations,                    \n"
"                                  const float  weird_factor)                  \n"
"{                                                                             \n"
"  const int gidx = get_global_id (0);                                         \n"
"  const int gidy = get_global_id (1);                                         \n"
"                                                                              \n"
"  const int x = gidx + offset_x;                                              \n"
"  const int y = gidy + offset_y;                                              \n"
"                                                                              \n"
"  const float dh = +10.0f / (width - 1);                                      \n"
"  const float dv = -10.0f / (height - 1);                                     \n"
"                                                                              \n"
"  const float px = dh * x - 5.0f;                                             \n"
"  const float py = dv * y + 5.0f;                                             \n"
"                                                                              \n"
"  const float3 di = diff_intensity (px, py, frequency, polarization, scattering,\n"
"                                    iterations, weird_factor);                \n"
"  const float3 out_v = fabs (sedges * sin (contours * atan (brightness * di)));\n"
"                                                                              \n"
"  const int gid = gidy * get_global_size (0) + gidx;                          \n"
"  out[gid * 3 + 0] = out_v.x;                                                 \n"
"  out[gid * 3 + 1] = out_v.y;                                                 \n"
"  out[gid * 3 + 2] = out_v.z;                                                 \n"
"}                                                                             \n"
;
