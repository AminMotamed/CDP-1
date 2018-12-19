#include "config.h"
#include <gegl-plugin.h>
void gegl_op_cache_register_type(GTypeModule *module);
void gegl_op_load_register_type(GTypeModule *module);
void gegl_op_clone_register_type(GTypeModule *module);
void gegl_op_cast_format_register_type(GTypeModule *module);
void gegl_op_convert_format_register_type(GTypeModule *module);
void gegl_op_crop_register_type(GTypeModule *module);
void gegl_op_json_register_type(GTypeModule *module);
void gegl_op_nop_register_type(GTypeModule *module);
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
  gegl_op_cache_register_type(module);
  gegl_op_load_register_type(module);
  gegl_op_clone_register_type(module);
  gegl_op_cast_format_register_type(module);
  gegl_op_convert_format_register_type(module);
  gegl_op_crop_register_type(module);
  gegl_op_json_register_type(module);
  gegl_op_nop_register_type(module);
 return TRUE;
}
