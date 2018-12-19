/* Plug-in to load and save .gih (GIMP Brush Pipe) files.
 *
 * Copyright (C) 1999 Tor Lillqvist
 * Copyright (C) 2000 Jens Lautenbacher, Sven Neumann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

  /* Example of how to call file_gih_save from script-fu:

  (let ((ranks (cons-array 1 'byte)))
    (aset ranks 0 12)
    (file-gih-save 1
                   img
                   drawable
                   "foo.gih"
                   "foo.gih"
                   100
                   "test brush"
                   125
                   125
                   3
                   4
                   1
                   ranks
                   1
                   '("random")))
  */


#include "config.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <glib/gstdio.h>

#include <glib.h>

#ifdef G_OS_WIN32
#include <io.h>
#endif

#ifndef _O_BINARY
#define _O_BINARY 0
#endif

#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>
#include <libgimpbase/gimpparasiteio.h>

#include "app/core/gimpbrush-header.h"
#include "app/core/gimppattern-header.h"

#include "libgimp/stdplugins-intl.h"


#define LOAD_PROC          "file-gih-load"
#define SAVE_PROC          "file-gih-save"
#define PLUG_IN_BINARY     "file-gih"
#define PLUG_IN_ROLE       "gimp-file-gih"
#define DUMMY_PATTERN_NAME "x"
#define MAXDESCLEN         256

/* Parameters applicable each time we save a gih, saved in the
 * main gimp application between invocations of this plug-in.
 */
static struct
{
  guint  spacing;
  gchar  description[MAXDESCLEN+1];
} info =
/* Initialize to this, change if non-interactive later */
{
  20,
  "GIMP Brush Pipe"
};


static gint num_layers = 0;

static const gchar *selection_modes[] = { "incremental",
                                          "angular",
                                          "random",
                                          "velocity",
                                          "pressure",
                                          "xtilt",
                                          "ytilt" };

static GimpPixPipeParams gihparams;

typedef struct
{
  GimpOrientationType orientation;
  gint32     image;
  gint32     toplayer;
  gint       nguides;
  gint32    *guides;
  gint      *value;
  GtkWidget *count_label;       /* Corresponding count adjustment, */
  gint      *count;             /* cols or rows                    */
  gint      *other_count;       /* and the other one               */
  GtkObject *ncells;
  GtkObject *rank0;
  GtkWidget *warning_label;
  GtkWidget *rank_entry[GIMP_PIXPIPE_MAXDIM];
  GtkWidget *mode_entry[GIMP_PIXPIPE_MAXDIM];
} SizeAdjustmentData;

/* static gint32 *vguides, *hguides;       */
/* static gint nvguides = 0, nhguides = 0; */

/* Declare some local functions.
 */
static void   query    (void);
static void   run      (const gchar      *name,
                        gint              nparams,
                        const GimpParam  *param,
                        gint             *nreturn_vals,
                        GimpParam       **return_vals);

static gint32    gih_load_image      (const gchar   *filename,
                                      GError       **error);
static gboolean  gih_load_one_brush  (gint           fd,
                                      gint32         image_ID);

static gboolean  gih_save_dialog     (gint32         image_ID);
static gboolean  gih_save_one_brush  (gint           fd,
                                      GimpPixelRgn  *pixel_rgn,
                                      const gchar   *name);
static gboolean  gih_save_image      (const gchar   *filename,
                                      gint32         image_ID,
                                      gint32         orig_image_ID,
                                      gint32         drawable_ID,
                                      GError       **error);


const GimpPlugInInfo PLUG_IN_INFO =
{
  NULL,  /* init_proc  */
  NULL,  /* quit_proc  */
  query, /* query_proc */
  run,   /* run_proc   */
};

MAIN ()

static void
query (void)
{
  static const GimpParamDef gih_save_args[] =
  {
    { GIMP_PDB_INT32,       "run-mode",     "The run mode { RUN-INTERACTIVE (0), RUN-NONINTERACTIVE (1) }" },
    { GIMP_PDB_IMAGE,       "image",        "Input image" },
    { GIMP_PDB_DRAWABLE,    "drawable",     "Drawable to save" },
    { GIMP_PDB_STRING,      "filename",     "The name of the file to save the brush pipe in" },
    { GIMP_PDB_STRING,      "raw-filename", "The name of the file to save the brush pipe in" },
    { GIMP_PDB_INT32,       "spacing",      "Spacing of the brush" },
    { GIMP_PDB_STRING,      "description",  "Short description of the brush pipe" },
    { GIMP_PDB_INT32,       "cell-width",   "Width of the brush cells" },
    { GIMP_PDB_INT32,       "cell-height",  "Width of the brush cells" },
    { GIMP_PDB_INT8,        "display-cols", "Display column number" },
    { GIMP_PDB_INT8,        "display-rows", "Display row number" },
    { GIMP_PDB_INT32,       "dimension",    "Dimension of the brush pipe" },
    /* The number of rank and sel args depend on the dimension */
    { GIMP_PDB_INT8ARRAY,   "rank",         "Ranks of the dimensions" },
    { GIMP_PDB_INT32,       "dimension",    "Dimension (again)" },
    { GIMP_PDB_STRINGARRAY, "sel",          "Selection modes" }
  };

  static const GimpParamDef gih_load_args[] =
  {
    { GIMP_PDB_INT32,  "run-mode",     "The run mode { RUN-INTERACTIVE (0), RUN-NONINTERACTIVE (1) }" },
    { GIMP_PDB_STRING, "filename",     "The name of the file to load" },
    { GIMP_PDB_STRING, "raw-filename", "The name of the file to load" }
  };
  static const GimpParamDef gih_load_return_vals[] =
  {
    { GIMP_PDB_IMAGE,  "image",        "Output image" }
  };


  gimp_install_procedure (LOAD_PROC,
                          "loads images in GIMP brush pipe format",
                          "This plug-in loads a GIMP brush pipe as an image.",
                          "Jens Lautenbacher, Sven Neumann",
                          "Jens Lautenbacher, Sven Neumann",
                          "2000",
                          N_("GIMP brush (animated)"),
                          NULL,
                          GIMP_PLUGIN,
                          G_N_ELEMENTS (gih_load_args),
                          G_N_ELEMENTS (gih_load_return_vals),
                          gih_load_args, gih_load_return_vals);

  gimp_plugin_icon_register (LOAD_PROC, GIMP_ICON_TYPE_STOCK_ID,
                             (const guint8 *) GIMP_STOCK_BRUSH);
  gimp_register_file_handler_mime (LOAD_PROC, "image/x-gimp-gih");
  gimp_register_magic_load_handler (LOAD_PROC,
                                    "gih",
                                    "",
                                    "");

  gimp_install_procedure (SAVE_PROC,
                          "saves images in GIMP brush pipe format",
                          "This plug-in saves an image in the GIMP brush pipe format. For a colored brush pipe, RGBA layers are used, otherwise the layers should be grayscale masks. The image can be multi-layered, and additionally the layers can be divided into a rectangular array of brushes.",
                          "Tor Lillqvist",
                          "Tor Lillqvist",
                          "1999",
                          N_("GIMP brush (animated)"),
                          "RGB*, GRAY*",
                          GIMP_PLUGIN,
                          G_N_ELEMENTS (gih_save_args), 0,
                          gih_save_args, NULL);

  gimp_plugin_icon_register (SAVE_PROC, GIMP_ICON_TYPE_STOCK_ID,
                             (const guint8 *) GIMP_STOCK_BRUSH);
  gimp_register_file_handler_mime ("file_gih_save", "image/x-gimp-gih");
  gimp_register_save_handler (SAVE_PROC,
                              "gih",
                              "");
}

static void
run (const gchar      *name,
     gint              nparams,
     const GimpParam  *param,
     gint             *nreturn_vals,
     GimpParam       **return_vals)
{
  static GimpParam   values[2];
  GimpRunMode        run_mode;
  GimpPDBStatusType  status = GIMP_PDB_SUCCESS;
  GimpParasite      *pipe_parasite;
  gint32             image_ID;
  gint32             orig_image_ID;
  gint32             drawable_ID;
  gint               i;
  GimpExportReturn   export = GIMP_EXPORT_CANCEL;
  GError            *error  = NULL;

  run_mode = param[0].data.d_int32;

  *return_vals  = values;
  *nreturn_vals = 1;

  values[0].type          = GIMP_PDB_STATUS;
  values[0].data.d_status = GIMP_PDB_EXECUTION_ERROR;

  INIT_I18N();

  if (strcmp (name, LOAD_PROC) == 0)
    {
      image_ID = gih_load_image (param[1].data.d_string, &error);

      if (image_ID != -1)
        {
          *nreturn_vals = 2;
          values[1].type         = GIMP_PDB_IMAGE;
          values[1].data.d_image = image_ID;
        }
      else
        {
          status = GIMP_PDB_EXECUTION_ERROR;
        }
    }
  else if (strcmp (name, SAVE_PROC) == 0)
    {
      image_ID = orig_image_ID = param[1].data.d_int32;
      drawable_ID = param[2].data.d_int32;

      /*  eventually export the image */
      switch (run_mode)
        {
        case GIMP_RUN_INTERACTIVE:
        case GIMP_RUN_WITH_LAST_VALS:
          gimp_ui_init (PLUG_IN_BINARY, FALSE);

          export = gimp_export_image (&image_ID, &drawable_ID, "GIH",
                                      GIMP_EXPORT_CAN_HANDLE_RGB   |
                                      GIMP_EXPORT_CAN_HANDLE_GRAY  |
                                      GIMP_EXPORT_CAN_HANDLE_ALPHA |
                                      GIMP_EXPORT_CAN_HANDLE_LAYERS);

          if (export == GIMP_EXPORT_CANCEL)
            {
              values[0].data.d_status = GIMP_PDB_CANCEL;
              return;
            }
          break;
        default:
          break;
        }

      g_free (gimp_image_get_layers (image_ID, &num_layers));

      switch (run_mode)
        {
        case GIMP_RUN_INTERACTIVE:
          /*  Possibly retrieve data  */
          gimp_get_data (SAVE_PROC, &info);

          gimp_pixpipe_params_init (&gihparams);

          /* Setup default values */
          if (gihparams.rows < 1) gihparams.rows = 1;
          if (gihparams.cols < 1) gihparams.cols = 1;

          gihparams.ncells = (num_layers * gihparams.rows * gihparams.cols);

          if (gihparams.cellwidth == 1 && gihparams.cellheight == 1)
            {
              gihparams.cellwidth  =
                gimp_image_width (image_ID)  / gihparams.cols;
              gihparams.cellheight =
                gimp_image_height (image_ID) / gihparams.rows;
            }

          pipe_parasite =
            gimp_image_get_parasite (orig_image_ID,
                                     "gimp-brush-pipe-parameters");
          if (pipe_parasite)
            gimp_pixpipe_params_parse (gimp_parasite_data (pipe_parasite),
                                       &gihparams);

          if (!gih_save_dialog (image_ID))
            status = GIMP_PDB_CANCEL;
          break;

        case GIMP_RUN_NONINTERACTIVE:
          if (nparams != 15)
            {
              status = GIMP_PDB_CALLING_ERROR;
            }
          else
            {
              info.spacing = param[5].data.d_int32;
              strncpy (info.description, param[6].data.d_string, MAXDESCLEN);
              info.description[MAXDESCLEN] = 0;

              gimp_pixpipe_params_init (&gihparams);

              gihparams.cellwidth  = param[7].data.d_int32;
              gihparams.cellheight = param[8].data.d_int32;
              gihparams.cols       = param[9].data.d_int8;
              gihparams.rows       = param[10].data.d_int8;
              gihparams.dim        = param[11].data.d_int32;
              gihparams.ncells     = 1;

              if (param[13].data.d_int32 != gihparams.dim)
                {
                  status = GIMP_PDB_CALLING_ERROR;
                }
              else
                {
                  for (i = 0; i < gihparams.dim; i++)
                    {
                      gihparams.rank[i]      = param[12].data.d_int8array[i];
                      gihparams.selection[i] = g_strdup (param[14].data.d_stringarray[i]);
                      gihparams.ncells       *= gihparams.rank[i];
                    }
                }
            }
          break;

        case GIMP_RUN_WITH_LAST_VALS:
          gimp_get_data (SAVE_PROC, &info);
          pipe_parasite =
            gimp_image_get_parasite (orig_image_ID,
                                     "gimp-brush-pipe-parameters");
          gimp_pixpipe_params_init (&gihparams);
          if (pipe_parasite)
            gimp_pixpipe_params_parse (gimp_parasite_data (pipe_parasite),
                                       &gihparams);
          break;
        }

      if (status == GIMP_PDB_SUCCESS)
        {
          if (gih_save_image (param[3].data.d_string,
                              image_ID, orig_image_ID, drawable_ID, &error))
            {
              gimp_set_data (SAVE_PROC, &info, sizeof (info));
            }
          else
            {
              status = GIMP_PDB_EXECUTION_ERROR;
            }
        }

      if (export == GIMP_EXPORT_EXPORT)
        gimp_image_delete (image_ID);
    }
  else
    {
      status = GIMP_PDB_CALLING_ERROR;
    }

  if (status != GIMP_PDB_SUCCESS && error)
    {
      *nreturn_vals = 2;
      values[1].type          = GIMP_PDB_STRING;
      values[1].data.d_string = error->message;
    }

  values[0].data.d_status = status;
}


/*  load routines  */

static gboolean
gih_load_one_brush (gint   fd,
                    gint32 image_ID)
{
  gchar         *name       = NULL;
  BrushHeader    bh;
  guchar        *brush_buf  = NULL;
  gint32         layer_ID;
  GimpDrawable  *drawable;
  GimpPixelRgn   pixel_rgn;
  gint           bn_size;
  GimpImageType  image_type;
  gint           width, height;
  gint           new_width, new_height;

  g_return_val_if_fail (fd != -1, FALSE);
  g_return_val_if_fail (image_ID != -1, FALSE);

  if (read (fd, &bh, sizeof (bh)) != sizeof (bh))
    return FALSE;

  /*  rearrange the bytes in each unsigned int  */
  bh.header_size  = g_ntohl (bh.header_size);
  bh.version      = g_ntohl (bh.version);
  bh.width        = g_ntohl (bh.width);
  bh.height       = g_ntohl (bh.height);
  bh.bytes        = g_ntohl (bh.bytes);
  bh.magic_number = g_ntohl (bh.magic_number);
  bh.spacing      = g_ntohl (bh.spacing);

  if (bh.version == 1)
    {
      /* Version 1 didn't know about spacing */
      bh.spacing = 25;
      /* And we need to rewind the handle a bit too */
      lseek (fd, -8, SEEK_CUR);
    }
  /* Version 1 didn't know about magic either */
  if ((bh.version != 1 &&
       (bh.magic_number != GBRUSH_MAGIC || bh.version != 2)) ||
      bh.header_size <= sizeof (bh))
    {
      return FALSE;
    }

  if ((bn_size = (bh.header_size - sizeof (bh))) > 0)
    {
      name = g_new (gchar, bn_size);
      if ((read (fd, name, bn_size)) < bn_size)
        {
          g_message (_("Error in GIMP brush pipe file."));
          g_free (name);
          return FALSE;
        }
    }
  else
    {
      name = g_strdup (_("Unnamed"));
    }

  /* Now there's just raw data left. */

  brush_buf = g_malloc (bh.width * bh.height * bh.bytes);

  if (read (fd, brush_buf,
            bh.width * bh.height * bh.bytes) != bh.width * bh.height * bh.bytes)
    {
      g_free (brush_buf);
      g_free (name);
      return FALSE;
    }


  if (bh.bytes == 1)
    {
      PatternHeader ph;

      /*  For backwards-compatibility, check if a pattern follows.
          The obsolete .gpb format did it this way.  */

      if (read (fd, &ph, sizeof(ph)) == sizeof(ph))
        {
          /*  rearrange the bytes in each unsigned int  */
          ph.header_size  = g_ntohl (ph.header_size);
          ph.version      = g_ntohl (ph.version);
          ph.width        = g_ntohl (ph.width);
          ph.height       = g_ntohl (ph.height);
          ph.bytes        = g_ntohl (ph.bytes);
          ph.magic_number = g_ntohl (ph.magic_number);

          if (ph.magic_number == GPATTERN_MAGIC && ph.version == 1 &&
              ph.header_size > sizeof (ph) &&
              ph.bytes == 3 && ph.width == bh.width && ph.height == bh.height &&
              lseek (fd, ph.header_size - sizeof (ph), SEEK_CUR) > 0)
            {
              guchar *plain_brush = brush_buf;
              gint    i;

              bh.bytes = 4;
              brush_buf = g_malloc (4 * bh.width * bh.height);

              for (i = 0; i < ph.width * ph.height; i++)
                {
                  if (read (fd, brush_buf + i * 4, 3) != 3)
                    {
                      g_free (name);
                      g_free (plain_brush);
                      g_free (brush_buf);
                      return FALSE;
                    }
                  brush_buf[i * 4 + 3] = plain_brush[i];
                }
              g_free (plain_brush);
            }
          else if (lseek (fd, - ((off_t) sizeof (PatternHeader)), SEEK_CUR) < 0)
            {
              g_message (_("GIMP brush file appears to be corrupted."));
              g_free (name);
              g_free (brush_buf);
              return FALSE;
            }
        }
    }

  /*
   * Create a new layer of the proper size.
   */

  switch (bh.bytes)
    {
    case 1:
      image_type = GIMP_GRAY_IMAGE;
      break;

    case 4:
      image_type = GIMP_RGBA_IMAGE;
      if (gimp_image_base_type (image_ID) == GIMP_GRAY)
        gimp_image_convert_rgb (image_ID);
      break;

    default:
      g_message ("Unsupported brush depth: %d\n"
                 "GIMP Brushes must be GRAY or RGBA\n",
                 bh.bytes);
      g_free (name);
      return FALSE;
    }

  new_width  = width  = gimp_image_width (image_ID);
  new_height = height = gimp_image_height (image_ID);

  if (bh.width > width || bh.height > height)
    {
      new_width  = MAX (width, bh.width);
      new_height = MAX (height, bh.height);
      gimp_image_resize (image_ID,
                         new_width, new_height,
                         (width - new_width) / 2, (height - new_height) / 2);
    }

  layer_ID = gimp_layer_new (image_ID, name,
                             bh.width, bh.height,
                             image_type, 100, GIMP_NORMAL_MODE);
  g_free (name);

  if (layer_ID != -1)
    {
      gimp_image_insert_layer (image_ID, layer_ID, -1, num_layers++);
      gimp_layer_set_offsets (layer_ID,
                              (new_width - bh.width)   / 2,
                              (new_height - bh.height) / 2);

      drawable = gimp_drawable_get (layer_ID);
      gimp_pixel_rgn_init (&pixel_rgn, drawable,
                           0, 0, drawable->width, drawable->height,
                           TRUE, FALSE);

      gimp_pixel_rgn_set_rect (&pixel_rgn,
                               brush_buf, 0, 0, bh.width, bh.height);

      if (image_type == GIMP_GRAY_IMAGE)
        {
          gimp_invert (layer_ID);
        }
    }

  g_free (brush_buf);

  return TRUE;
}

static gint32
gih_load_image (const gchar  *filename,
                GError      **error)
{
  gint     fd;
  gint     i;
  gint32   image_ID;
  GString *buffer;
  gchar    c;
  gchar   *name = NULL;
  gint     num_of_brushes = 0;
  gchar   *paramstring;
  GimpParasite *pipe_parasite;

  fd = g_open (filename, O_RDONLY | _O_BINARY, 0);

  if (fd == -1)
    {
      g_set_error (error, G_FILE_ERROR, g_file_error_from_errno (errno),
                   _("Could not open '%s' for reading: %s"),
                   gimp_filename_to_utf8 (filename), g_strerror (errno));
      return -1;
    }

  gimp_progress_init_printf (_("Opening '%s'"),
                             gimp_filename_to_utf8 (filename));

  /* The file format starts with a painfully simple text header */

  /*  get the name  */
  buffer = g_string_new (NULL);
  while (read (fd, &c, 1) == 1 && c != '\n' && buffer->len < 1024)
    g_string_append_c (buffer, c);

  if (buffer->len > 0 && buffer->len < 1024)
    name = buffer->str;

  g_string_free (buffer, FALSE);

  if (!name)
    {
      g_message ("Couldn't read name for brush pipe from '%s'",
                 gimp_filename_to_utf8 (filename));
      close (fd);
      return -1;
    }

  /*  get the number of brushes  */
  buffer = g_string_new (NULL);
  while (read (fd, &c, 1) == 1 && c != '\n' && buffer->len < 1024)
    g_string_append_c (buffer, c);

  if (buffer->len > 0 && buffer->len < 1024)
    {
      num_of_brushes = strtol (buffer->str, &paramstring, 10);
    }

  if (num_of_brushes < 1)
    {
      g_message ("Brush pipes should have at least one brush.");
      close (fd);
      g_free (name);
      g_string_free (buffer, TRUE);
      return -1;
    }

  image_ID = gimp_image_new (1, 1, GIMP_GRAY);
  gimp_image_set_filename (image_ID, filename);

  for (i = 0; i < num_of_brushes; i++)
    {
      if (! gih_load_one_brush (fd, image_ID))
        {
          g_set_error (error, G_FILE_ERROR, G_FILE_ERROR_FAILED,
                       "%s",
                       _("Couldn't load one brush in the pipe, giving up."));
          close (fd);
          g_free (name);
          g_string_free (buffer, TRUE);
          return -1;
        }

      gimp_progress_update ((gdouble) i / (gdouble) num_of_brushes);
    }

  while (*paramstring && g_ascii_isspace (*paramstring))
    paramstring++;

  /*  Since we do not (yet) load the pipe as described in the header,
      but use one layer per brush, we have to alter the paramstring
      before attaching it as a parasite.
   */

  if (*paramstring)
    {
      gimp_pixpipe_params_parse (paramstring, &gihparams);

      gihparams.cellwidth  = gimp_image_width  (image_ID);
      gihparams.cellheight = gimp_image_height (image_ID);
      gihparams.cols       = 1;
      gihparams.rows       = 1;

      paramstring = gimp_pixpipe_params_build (&gihparams);
      if (paramstring)
        {
          pipe_parasite = gimp_parasite_new ("gimp-brush-pipe-parameters",
                                             GIMP_PARASITE_PERSISTENT,
                                             strlen (paramstring) + 1,
                                             paramstring);
          gimp_image_attach_parasite (image_ID, pipe_parasite);
          gimp_parasite_free (pipe_parasite);
          g_free (paramstring);
        }
    }

  g_string_free (buffer, TRUE);

  return image_ID;
}

/*  save routines */

static void
size_adjustment_callback (GtkWidget *widget,
                          gpointer   data)
{
  gint  i;
  gint  size;
  gint  newn;
  gchar buf[10];
  SizeAdjustmentData *adj = (SizeAdjustmentData *) data;

  for (i = 0; i < adj->nguides; i++)
    gimp_image_delete_guide (adj->image, adj->guides[i]);

  g_free (adj->guides);
  adj->guides = NULL;
  gimp_displays_flush ();

  *(adj->value) = gtk_adjustment_get_value (GTK_ADJUSTMENT (widget));

  if (adj->orientation == GIMP_ORIENTATION_VERTICAL)
    {
      size = gimp_image_width (adj->image);
      newn = size / *(adj->value);
      adj->nguides = newn - 1;
      adj->guides = g_new (gint32, adj->nguides);
      for (i = 0; i < adj->nguides; i++)
        adj->guides[i] = gimp_image_add_vguide (adj->image,
                                                *(adj->value) * (i+1));
    }
  else
    {
      size = gimp_image_height (adj->image);
      newn = size / *(adj->value);
      adj->nguides = newn - 1;
      adj->guides = g_new (gint32, adj->nguides);
      for (i = 0; i < adj->nguides; i++)
        adj->guides[i] = gimp_image_add_hguide (adj->image,
                                                *(adj->value) * (i+1));
    }
  gimp_displays_flush ();
  sprintf (buf, "%2d", newn);
  gtk_label_set_text (GTK_LABEL (adj->count_label), buf);

  *(adj->count) = newn;

  gtk_widget_set_visible (GTK_WIDGET (adj->warning_label),
                          newn * *(adj->value) != size);

  if (adj->ncells != NULL)
    gtk_adjustment_set_value (GTK_ADJUSTMENT (adj->ncells),
                              *(adj->other_count) * *(adj->count));
  if (adj->rank0 != NULL)
    gtk_adjustment_set_value (GTK_ADJUSTMENT (adj->rank0),
                              *(adj->other_count) * *(adj->count));
}

static void
entry_callback (GtkWidget *widget,
                gpointer   data)
{
  if (data == info.description)
    {
      strncpy (info.description,
               gtk_entry_get_text (GTK_ENTRY (widget)), MAXDESCLEN);
      info.description[MAXDESCLEN]  = 0;
    }
}

static void
cb_callback (GtkWidget *widget,
             gpointer   data)
{
  gint index;

  index = gtk_combo_box_get_active (GTK_COMBO_BOX (widget));

  *((const gchar **) data) = selection_modes [index];
}

static void
dim_callback (GtkAdjustment *adjustment,
              SizeAdjustmentData *data)
{
  gint i;

  gihparams.dim = RINT (gtk_adjustment_get_value (adjustment));

  for (i = 0; i < GIMP_PIXPIPE_MAXDIM; i++)
    {
      gtk_widget_set_sensitive (data->rank_entry[i], i < gihparams.dim);
      gtk_widget_set_sensitive (data->mode_entry[i], i < gihparams.dim);
    }
}

static gboolean
gih_save_dialog (gint32 image_ID)
{
  GtkWidget *dialog;
  GtkWidget *table;
  GtkWidget *dimtable;
  GtkWidget *label;
  GtkObject *adjustment;
  GtkWidget *spinbutton;
  GtkWidget *entry;
  GtkWidget *box;
  GtkWidget *cb;
  gint       i;
  gchar      buffer[100];
  SizeAdjustmentData cellw_adjust;
  SizeAdjustmentData cellh_adjust;
  gint32    *layer_ID;
  gint32     nlayers;
  gboolean   run;

  dialog = gimp_export_dialog_new (_("Brush Pipe"), PLUG_IN_BINARY, SAVE_PROC);

  /* The main table */
  table = gtk_table_new (8, 2, FALSE);
  gtk_table_set_row_spacings (GTK_TABLE (table), 6);
  gtk_table_set_col_spacings (GTK_TABLE (table), 6);
  gtk_container_set_border_width (GTK_CONTAINER (table), 12);
  gtk_box_pack_start (GTK_BOX (gimp_export_dialog_get_content_area (dialog)),
                      table, TRUE, TRUE, 0);
  gtk_widget_show (table);

  /*
   * Spacing: __
   */
  spinbutton = gimp_spin_button_new (&adjustment, info.spacing,
                                     1, 1000, 1, 10, 0, 1, 0);
  gimp_table_attach_aligned (GTK_TABLE (table), 0, 0,
                             _("Spacing (percent):"), 0.0, 0.5,
                             spinbutton, 1, TRUE);

  g_signal_connect (adjustment, "value-changed",
                    G_CALLBACK (gimp_int_adjustment_update),
                    &info.spacing);

  /*
   * Description: ___________
   */
  entry = gtk_entry_new ();
  gtk_widget_set_size_request (entry, 200, -1);
  gtk_entry_set_text (GTK_ENTRY (entry), info.description);
  gimp_table_attach_aligned (GTK_TABLE (table), 0, 1,
                             _("Description:"), 0.0, 0.5,
                             entry, 1, FALSE);

  g_signal_connect (entry, "changed",
                    G_CALLBACK (entry_callback),
                    info.description);

  /*
   * Cell size: __ x __ pixels
   */
  box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 4);

  spinbutton = gimp_spin_button_new (&adjustment,
                                     gihparams.cellwidth,
                                     2, gimp_image_width (image_ID), 1, 10, 0,
                                     1, 0);
  gtk_box_pack_start (GTK_BOX (box), spinbutton, FALSE, FALSE, 0);
  gtk_widget_show (spinbutton);

  layer_ID = gimp_image_get_layers (image_ID, &nlayers);
  cellw_adjust.orientation = GIMP_ORIENTATION_VERTICAL;
  cellw_adjust.image       = image_ID;
  cellw_adjust.toplayer    = layer_ID[nlayers-1];
  cellw_adjust.nguides     = 0;
  cellw_adjust.guides      = NULL;
  cellw_adjust.value       = &gihparams.cellwidth;

  g_signal_connect (adjustment, "value-changed",
                    G_CALLBACK (size_adjustment_callback),
                    &cellw_adjust);

  label = gtk_label_new ("x");
  gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);
  gtk_widget_show (label);

  spinbutton = gimp_spin_button_new (&adjustment,
                                     gihparams.cellheight,
                                     2, gimp_image_height (image_ID), 1, 10, 0,
                                     1, 0);
  gtk_box_pack_start (GTK_BOX (box), spinbutton, FALSE, FALSE, 0);
  gtk_widget_show (spinbutton);

  cellh_adjust.orientation = GIMP_ORIENTATION_HORIZONTAL;
  cellh_adjust.image       = image_ID;
  cellh_adjust.toplayer    = layer_ID[nlayers-1];
  cellh_adjust.nguides     = 0;
  cellh_adjust.guides      = NULL;
  cellh_adjust.value       = &gihparams.cellheight;

  g_signal_connect (adjustment, "value-changed",
                    G_CALLBACK (size_adjustment_callback),
                    &cellh_adjust);

  label = gtk_label_new ( _("Pixels"));
  gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);
  gtk_widget_show (label);

  gimp_table_attach_aligned (GTK_TABLE (table), 0, 2,
                             _("Cell size:"), 0.0, 0.5,
                             box, 1, FALSE);

  g_free (layer_ID);

  /*
   * Number of cells: ___
   */
  spinbutton = gimp_spin_button_new (&adjustment,
                                     gihparams.ncells, 1, 1000, 1, 10, 0,
                                     1, 0);
  gimp_table_attach_aligned (GTK_TABLE (table), 0, 3,
                             _("Number of cells:"), 0.0, 0.5,
                             spinbutton, 1, TRUE);

  g_signal_connect (adjustment, "value-changed",
                    G_CALLBACK (gimp_int_adjustment_update),
                    &gihparams.ncells);

  if (gihparams.dim == 1)
    cellw_adjust.ncells = cellh_adjust.ncells = adjustment;
  else
    cellw_adjust.ncells = cellh_adjust.ncells = NULL;

  /*
   * Display as: __ rows x __ cols
   */
  box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);

  g_snprintf (buffer, sizeof (buffer), "%2d", gihparams.rows);
  label = gtk_label_new (buffer);
  gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);
  cellh_adjust.count_label = label;
  cellh_adjust.count       = &gihparams.rows;
  cellh_adjust.other_count = &gihparams.cols;
  gtk_widget_show (label);

  label = gtk_label_new (_(" Rows of "));
  gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);
  gtk_widget_show (label);

  g_snprintf (buffer, sizeof (buffer), "%2d", gihparams.cols);
  label = gtk_label_new (buffer);
  gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);
  cellw_adjust.count_label = label;
  cellw_adjust.count       = &gihparams.cols;
  cellw_adjust.other_count = &gihparams.rows;
  gtk_widget_show (label);

  label = gtk_label_new (_(" Columns on each layer"));
  gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);
  gtk_widget_show (label);

  label = gtk_label_new (_(" (Width Mismatch!) "));
  gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);
  cellw_adjust.warning_label = label;

  label = gtk_label_new (_(" (Height Mismatch!) "));
  gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);
  cellh_adjust.warning_label = label;

  gimp_table_attach_aligned (GTK_TABLE (table), 0, 4,
                             _("Display as:"), 0.0, 0.5,
                             box, 1, FALSE);

  /*
   * Dimension: ___
   */
  spinbutton = gimp_spin_button_new (&adjustment, gihparams.dim,
                                     1, GIMP_PIXPIPE_MAXDIM, 1, 1, 0, 1, 0);
  gimp_table_attach_aligned (GTK_TABLE (table), 0, 5,
                             _("Dimension:"), 0.0, 0.5,
                             spinbutton, 1, TRUE);

  g_signal_connect (adjustment, "value-changed",
                    G_CALLBACK (dim_callback),
                    &cellw_adjust);

  /*
   * Ranks / Selection: ______ ______ ______ ______ ______
   */

  dimtable = gtk_table_new (2, GIMP_PIXPIPE_MAXDIM, FALSE);
  gtk_table_set_col_spacings (GTK_TABLE (dimtable), 4);
  for (i = 0; i < GIMP_PIXPIPE_MAXDIM; i++)
    {
      gint j;

      spinbutton = gimp_spin_button_new (&adjustment,
                                         gihparams.rank[i], 1, 100, 1, 1, 0,
                                         1, 0);
      gtk_table_attach (GTK_TABLE (dimtable), spinbutton, 0, 1, i, i + 1,
                        GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);

      gtk_widget_show (spinbutton);

      if (i >= gihparams.dim)
        gtk_widget_set_sensitive (spinbutton, FALSE);

      g_signal_connect (adjustment, "value-changed",
                        G_CALLBACK (gimp_int_adjustment_update),
                        &gihparams.rank[i]);

      cellw_adjust.rank_entry[i] = cellh_adjust.rank_entry[i] = spinbutton;

      if (i == 0)
        {
          if (gihparams.dim == 1)
            cellw_adjust.rank0 = cellh_adjust.rank0 = adjustment;
          else
            cellw_adjust.rank0 = cellh_adjust.rank0 = NULL;
        }

      cb = gtk_combo_box_text_new ();

      for (j = 0; j < G_N_ELEMENTS (selection_modes); j++)
        gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (cb),
                                        selection_modes[j]);
      gtk_combo_box_set_active (GTK_COMBO_BOX (cb), 2);  /* random */

      if (gihparams.selection[i])
        for (j = 0; j < G_N_ELEMENTS (selection_modes); j++)
          if (!strcmp (gihparams.selection[i], selection_modes[j]))
            {
              gtk_combo_box_set_active (GTK_COMBO_BOX (cb), j);
              break;
            }

      gtk_table_attach (GTK_TABLE (dimtable), cb, 1, 2, i, i + 1,
                        GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);

      gtk_widget_show (cb);

      if (i >= gihparams.dim)
        gtk_widget_set_sensitive (cb, FALSE);

      g_signal_connect (GTK_COMBO_BOX (cb), "changed",
                        G_CALLBACK (cb_callback),
                        &gihparams.selection[i]);

      cellw_adjust.mode_entry[i] = cellh_adjust.mode_entry[i] = cb;


    }

  gimp_table_attach_aligned (GTK_TABLE (table), 0, 6,
                             _("Ranks:"), 0.0, 0.0,
                             dimtable, 1, FALSE);

  gtk_widget_show (dialog);

  run = (gimp_dialog_run (GIMP_DIALOG (dialog)) == GTK_RESPONSE_OK);

  if (run)
    {
      gint i;

      for (i = 0; i < GIMP_PIXPIPE_MAXDIM; i++)
        gihparams.selection[i] = g_strdup (gihparams.selection[i]);

      /* Fix up bogus values */
      gihparams.ncells = MIN (gihparams.ncells,
                              num_layers * gihparams.rows * gihparams.cols);
    }

  gtk_widget_destroy (dialog);

  for (i = 0; i < cellw_adjust.nguides; i++)
    gimp_image_delete_guide (image_ID, cellw_adjust.guides[i]);
  for (i = 0; i < cellh_adjust.nguides; i++)
    gimp_image_delete_guide (image_ID, cellh_adjust.guides[i]);

  return run;
}

static gboolean
gih_save_one_brush (gint          fd,
                    GimpPixelRgn *pixel_rgn,
                    const gchar  *name)
{
  BrushHeader  header;
  guchar      *buffer;
  guint        y;

  g_return_val_if_fail (fd != -1, FALSE);
  g_return_val_if_fail (pixel_rgn != NULL, FALSE);

  if (pixel_rgn->w < 1 || pixel_rgn->h < 1)
    return FALSE;

  if (! name)
    name = _("Unnamed");

  header.header_size  = g_htonl (sizeof (header) + strlen (name) + 1);
  header.version      = g_htonl (2);
  header.width        = g_htonl (pixel_rgn->w);
  header.height       = g_htonl (pixel_rgn->h);
  header.bytes        = g_htonl (pixel_rgn->bpp > 2 ? 4 : 1);
  header.magic_number = g_htonl (GBRUSH_MAGIC);
  header.spacing      = g_htonl (info.spacing);

  if (write (fd, &header, sizeof (header)) != sizeof (header))
    return FALSE;

  if (write (fd, name, strlen (name) + 1) != strlen (name) + 1)
    return FALSE;

  buffer = g_malloc (pixel_rgn->w * pixel_rgn->bpp);

  for (y = 0; y < pixel_rgn->h; y++)
    {
      guint x;

      gimp_pixel_rgn_get_row (pixel_rgn, buffer,
                              0 + pixel_rgn->x, y + pixel_rgn->y, pixel_rgn->w);

      switch (pixel_rgn->bpp)
        {
        case 1: /* GRAY */
          for (x = 0; x < pixel_rgn->w; x++)
            {
              const guchar value = 255 - buffer[x];

              if (write (fd, &value, 1) != 1)
                {
                  g_free (buffer);
                  return FALSE;
                }
            }
          break;

        case 2: /* GRAYA, alpha channel is ignored */
          for (x = 0; x < pixel_rgn->w; x++)
            {
              const guchar value = 255 - buffer[2 * x];

              if (write (fd, &value, 1) != 1)
                {
                  g_free (buffer);
                  return FALSE;
                }
            }
          break;

        case 3: /* RGB, alpha channel is added */
          for (x = 0; x < pixel_rgn->w; x++)
            {
              guchar value[4];

              value[0] = buffer[3 * x + 0];
              value[1] = buffer[3 * x + 1];
              value[2] = buffer[3 * x + 2];
              value[3] = 255;

              if (write (fd, value, 4) != 4)
                {
                  g_free (buffer);
                  return FALSE;
                }
            }
          break;

        case 4: /* RGBA */
          if (write (fd, buffer, pixel_rgn->w * pixel_rgn->bpp) !=
              pixel_rgn->w * pixel_rgn->bpp)
            {
              g_free (buffer);
              return FALSE;
            }
          break;

        default:
          g_assert_not_reached ();
          break;
        }
    }

  g_free (buffer);

  return TRUE;
}

static gboolean
gih_save_image (const gchar  *filename,
                gint32        image_ID,
                gint32        orig_image_ID,
                gint32        drawable_ID,
                GError      **error)
{
  GimpParasite *pipe_parasite;
  gchar        *header;
  gchar        *parstring;
  gint32       *layer_ID;
  gint          fd;
  gint          nlayers, layer;
  gint          row, col;
  gint          imagew, imageh;
  gint          offsetx, offsety;
  gint          k;

  if (gihparams.ncells < 1)
    return FALSE;

  imagew = gimp_image_width (image_ID);
  imageh = gimp_image_height (image_ID);
  gimp_tile_cache_size (gimp_tile_height () * imagew * 4);

  fd = g_open (filename, O_CREAT | O_TRUNC | O_WRONLY | _O_BINARY, 0666);

  if (fd == -1)
    {
      g_set_error (error, G_FILE_ERROR, g_file_error_from_errno (errno),
                   _("Could not open '%s' for writing: %s"),
                   gimp_filename_to_utf8 (filename), g_strerror (errno));
      return FALSE;
    }

  gimp_progress_init_printf (_("Saving '%s'"),
                             gimp_filename_to_utf8 (filename));

  parstring = gimp_pixpipe_params_build (&gihparams);

  header = g_strdup_printf ("%s\n%d %s\n",
                            info.description, gihparams.ncells, parstring);

  if (write (fd, header, strlen (header)) != strlen (header))
    {
      g_free (parstring);
      g_free (header);
      close (fd);
      return FALSE;
    }

  g_free (header);

  pipe_parasite = gimp_parasite_new ("gimp-brush-pipe-parameters",
                                     GIMP_PARASITE_PERSISTENT,
                                     strlen (parstring) + 1, parstring);
  gimp_image_attach_parasite (orig_image_ID, pipe_parasite);
  gimp_parasite_free (pipe_parasite);

  g_free (parstring);

  layer_ID = gimp_image_get_layers (image_ID, &nlayers);

  for (layer = 0, k = 0; layer < nlayers; layer++)
    {
      GimpDrawable *drawable = gimp_drawable_get (layer_ID[layer]);
      gchar        *name     = gimp_item_get_name (drawable->drawable_id);

      gimp_drawable_offsets (drawable->drawable_id, &offsetx, &offsety);

      for (row = 0; row < gihparams.rows; row++)
        {
          gint y, ynext;
          gint thisy, thish;

          y = (row * imageh) / gihparams.rows;
          ynext = ((row + 1) * imageh / gihparams.rows);

          /* Assume layer is offset to positive direction in x and y.
           * That's reasonable, as otherwise all of the layer
           * won't be visible.
           * thisy and thisx are in the drawable's coordinate space.
           */
          thisy = MAX (0, y - offsety);
          thish = (ynext - offsety) - thisy;
          thish = MIN (thish, drawable->height - thisy);

          for (col = 0; col < gihparams.cols; col++)
            {
              GimpPixelRgn  pixel_rgn;
              gint          x, xnext;
              gint          thisx, thisw;

              x = (col * imagew / gihparams.cols);
              xnext = ((col + 1) * imagew / gihparams.cols);
              thisx = MAX (0, x - offsetx);
              thisw = (xnext - offsetx) - thisx;
              thisw = MIN (thisw, drawable->width - thisx);

              gimp_pixel_rgn_init (&pixel_rgn, drawable, thisx, thisy,
                                   thisw, thish, FALSE, FALSE);

              if (! gih_save_one_brush (fd, &pixel_rgn, name))
                {
                  close (fd);
                  return FALSE;
                }

              k++;
              gimp_progress_update ((gdouble) k / gihparams.ncells);
            }
        }

      g_free (name);
      gimp_drawable_detach (drawable);
    }

  gimp_progress_update (1.0);

  g_free (layer_ID);

  close (fd);

  return TRUE;
}
