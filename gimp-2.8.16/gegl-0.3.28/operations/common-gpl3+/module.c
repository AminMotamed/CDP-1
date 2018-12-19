#include "config.h"
#include <gegl-plugin.h>
void gegl_op_antialias_register_type(GTypeModule *module);
void gegl_op_apply_lens_register_type(GTypeModule *module);
void gegl_op_bump_map_register_type(GTypeModule *module);
void gegl_op_cartoon_register_type(GTypeModule *module);
void gegl_op_channel_mixer_register_type(GTypeModule *module);
void gegl_op_color_exchange_register_type(GTypeModule *module);
void gegl_op_color_to_alpha_register_type(GTypeModule *module);
void gegl_op_cubism_register_type(GTypeModule *module);
void gegl_op_deinterlace_register_type(GTypeModule *module);
void gegl_op_diffraction_patterns_register_type(GTypeModule *module);
void gegl_op_displace_register_type(GTypeModule *module);
void gegl_op_edge_laplace_register_type(GTypeModule *module);
void gegl_op_edge_register_type(GTypeModule *module);
void gegl_op_emboss_register_type(GTypeModule *module);
void gegl_op_engrave_register_type(GTypeModule *module);
void gegl_op_fractal_explorer_register_type(GTypeModule *module);
void gegl_op_fractal_trace_register_type(GTypeModule *module);
void gegl_op_gaussian_blur_selective_register_type(GTypeModule *module);
void gegl_op_illusion_register_type(GTypeModule *module);
void gegl_op_lens_distortion_register_type(GTypeModule *module);
void gegl_op_lens_flare_register_type(GTypeModule *module);
void gegl_op_maze_register_type(GTypeModule *module);
void gegl_op_mosaic_register_type(GTypeModule *module);
void gegl_op_motion_blur_circular_register_type(GTypeModule *module);
void gegl_op_motion_blur_zoom_register_type(GTypeModule *module);
void gegl_op_noise_slur_register_type(GTypeModule *module);
void gegl_op_noise_solid_register_type(GTypeModule *module);
void gegl_op_oilify_register_type(GTypeModule *module);
void gegl_op_photocopy_register_type(GTypeModule *module);
void gegl_op_plasma_register_type(GTypeModule *module);
void gegl_op_polar_coordinates_register_type(GTypeModule *module);
void gegl_op_red_eye_removal_register_type(GTypeModule *module);
void gegl_op_ripple_register_type(GTypeModule *module);
void gegl_op_shadows_highlights_register_type(GTypeModule *module);
void gegl_op_shadows_highlights_correction_register_type(GTypeModule *module);
void gegl_op_shift_register_type(GTypeModule *module);
void gegl_op_sinus_register_type(GTypeModule *module);
void gegl_op_softglow_register_type(GTypeModule *module);
void gegl_op_spiral_register_type(GTypeModule *module);
void gegl_op_supernova_register_type(GTypeModule *module);
void gegl_op_texturize_canvas_register_type(GTypeModule *module);
void gegl_op_tile_glass_register_type(GTypeModule *module);
void gegl_op_tile_paper_register_type(GTypeModule *module);
void gegl_op_value_propagate_register_type(GTypeModule *module);
void gegl_op_video_degradation_register_type(GTypeModule *module);
void gegl_op_waves_register_type(GTypeModule *module);
void gegl_op_whirl_pinch_register_type(GTypeModule *module);
void gegl_op_wind_register_type(GTypeModule *module);
static const GeglModuleInfo modinfo = {
GEGL_MODULE_ABI_VERSION
};

const GeglModuleInfo * gegl_module_query (GTypeModule *module);
gboolean gegl_module_register (GTypeModule *module);

G_MODULE_EXPORT const GeglModuleInfo *
gegl_module_query (GTypeModule *module)
{
  return &modinfo;
}

G_MODULE_EXPORT gboolean
gegl_module_register (GTypeModule *module)
{
  gegl_op_antialias_register_type(module);
  gegl_op_apply_lens_register_type(module);
  gegl_op_bump_map_register_type(module);
  gegl_op_cartoon_register_type(module);
  gegl_op_channel_mixer_register_type(module);
  gegl_op_color_exchange_register_type(module);
  gegl_op_color_to_alpha_register_type(module);
  gegl_op_cubism_register_type(module);
  gegl_op_deinterlace_register_type(module);
  gegl_op_diffraction_patterns_register_type(module);
  gegl_op_displace_register_type(module);
  gegl_op_edge_laplace_register_type(module);
  gegl_op_edge_register_type(module);
  gegl_op_emboss_register_type(module);
  gegl_op_engrave_register_type(module);
  gegl_op_fractal_explorer_register_type(module);
  gegl_op_fractal_trace_register_type(module);
  gegl_op_gaussian_blur_selective_register_type(module);
  gegl_op_illusion_register_type(module);
  gegl_op_lens_distortion_register_type(module);
  gegl_op_lens_flare_register_type(module);
  gegl_op_maze_register_type(module);
  gegl_op_mosaic_register_type(module);
  gegl_op_motion_blur_circular_register_type(module);
  gegl_op_motion_blur_zoom_register_type(module);
  gegl_op_noise_slur_register_type(module);
  gegl_op_noise_solid_register_type(module);
  gegl_op_oilify_register_type(module);
  gegl_op_photocopy_register_type(module);
  gegl_op_plasma_register_type(module);
  gegl_op_polar_coordinates_register_type(module);
  gegl_op_red_eye_removal_register_type(module);
  gegl_op_ripple_register_type(module);
  gegl_op_shadows_highlights_register_type(module);
  gegl_op_shadows_highlights_correction_register_type(module);
  gegl_op_shift_register_type(module);
  gegl_op_sinus_register_type(module);
  gegl_op_softglow_register_type(module);
  gegl_op_spiral_register_type(module);
  gegl_op_supernova_register_type(module);
  gegl_op_texturize_canvas_register_type(module);
  gegl_op_tile_glass_register_type(module);
  gegl_op_tile_paper_register_type(module);
  gegl_op_value_propagate_register_type(module);
  gegl_op_video_degradation_register_type(module);
  gegl_op_waves_register_type(module);
  gegl_op_whirl_pinch_register_type(module);
  gegl_op_wind_register_type(module);
 return TRUE;
}
