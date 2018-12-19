#include "config.h"
#include <gegl-plugin.h>
void gegl_op_add_register_type(GTypeModule *module);
void gegl_op_clear_register_type(GTypeModule *module);
void gegl_op_color_burn_register_type(GTypeModule *module);
void gegl_op_color_dodge_register_type(GTypeModule *module);
void gegl_op_darken_register_type(GTypeModule *module);
void gegl_op_difference_register_type(GTypeModule *module);
void gegl_op_divide_register_type(GTypeModule *module);
void gegl_op_dst_atop_register_type(GTypeModule *module);
void gegl_op_dst_in_register_type(GTypeModule *module);
void gegl_op_dst_out_register_type(GTypeModule *module);
void gegl_op_dst_over_register_type(GTypeModule *module);
void gegl_op_dst_register_type(GTypeModule *module);
void gegl_op_exclusion_register_type(GTypeModule *module);
void gegl_op_gamma_register_type(GTypeModule *module);
void gegl_op_hard_light_register_type(GTypeModule *module);
void gegl_op_lighten_register_type(GTypeModule *module);
void gegl_op_multiply_register_type(GTypeModule *module);
void gegl_op_overlay_register_type(GTypeModule *module);
void gegl_op_plus_register_type(GTypeModule *module);
void gegl_op_screen_register_type(GTypeModule *module);
void gegl_op_soft_light_register_type(GTypeModule *module);
void gegl_op_src_atop_register_type(GTypeModule *module);
void gegl_op_src_in_register_type(GTypeModule *module);
void gegl_op_src_out_register_type(GTypeModule *module);
void gegl_op_src_register_type(GTypeModule *module);
void gegl_op_subtract_register_type(GTypeModule *module);
void gegl_op_xor_register_type(GTypeModule *module);
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
  gegl_op_add_register_type(module);
  gegl_op_clear_register_type(module);
  gegl_op_color_burn_register_type(module);
  gegl_op_color_dodge_register_type(module);
  gegl_op_darken_register_type(module);
  gegl_op_difference_register_type(module);
  gegl_op_divide_register_type(module);
  gegl_op_dst_atop_register_type(module);
  gegl_op_dst_in_register_type(module);
  gegl_op_dst_out_register_type(module);
  gegl_op_dst_over_register_type(module);
  gegl_op_dst_register_type(module);
  gegl_op_exclusion_register_type(module);
  gegl_op_gamma_register_type(module);
  gegl_op_hard_light_register_type(module);
  gegl_op_lighten_register_type(module);
  gegl_op_multiply_register_type(module);
  gegl_op_overlay_register_type(module);
  gegl_op_plus_register_type(module);
  gegl_op_screen_register_type(module);
  gegl_op_soft_light_register_type(module);
  gegl_op_src_atop_register_type(module);
  gegl_op_src_in_register_type(module);
  gegl_op_src_out_register_type(module);
  gegl_op_src_register_type(module);
  gegl_op_subtract_register_type(module);
  gegl_op_xor_register_type(module);
 return TRUE;
}
