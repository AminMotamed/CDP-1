# Makefile for program source directory in GNU NLS utilities package.
# Copyright (C) 1995, 1996, 1997 by Ulrich Drepper <drepper@gnu.ai.mit.edu>
#
# This file file be copied and used freely without restrictions.  It can
# be used in projects which are not available under the GNU Public License
# but which still want to provide support for the GNU gettext functionality.
# Please note that the actual code is *not* freely available.
#
# - Modified by Owen Taylor <otaylor@redhat.com> to use GETTEXT_PACKAGE
#   instead of PACKAGE and to look for po2tbl in ./ not in intl/
#
# - Modified by jacob berkman <jacob@ximian.com> to install
#   Makefile.in.in and po2tbl.sed.in for use with glib-gettextize
#
# - Modified by Rodney Dawes <dobey@novell.com> for use with intltool
#
# We have the following line for use by intltoolize:
# INTLTOOL_MAKEFILE

GETTEXT_PACKAGE = gimp20
XGETTEXT_KEYWORDS=--keyword=_ --keyword=N_ --keyword=Q_:1g --keyword=C_:1c,2 --keyword=NC_:1c,2

PACKAGE = gimp
VERSION = 2.8.16

SHELL = /bin/sh

srcdir = .
top_srcdir = ..
top_builddir = ..


prefix = /usr/local
exec_prefix = ${prefix}
datadir = ${datarootdir}
datarootdir = ${prefix}/share
libdir = ${exec_prefix}/lib
DATADIRNAME = share
itlocaledir = $(prefix)/$(DATADIRNAME)/locale
subdir = po
install_sh = ${SHELL} /home/gaston/Downloads/gimp-2.8.16/install-sh
# Automake >= 1.8 provides $(MKDIR_P).
# Until it can be supposed, use the safe fallback:
mkdir_p = $(install_sh) -d

INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644

GMSGFMT = /usr/bin/msgfmt
MSGFMT = /usr/bin/msgfmt
XGETTEXT = /usr/bin/xgettext
INTLTOOL_UPDATE = /usr/bin/intltool-update
INTLTOOL_EXTRACT = /usr/bin/intltool-extract
MSGMERGE = INTLTOOL_EXTRACT=$(INTLTOOL_EXTRACT) srcdir=$(srcdir) $(INTLTOOL_UPDATE) --gettext-package $(GETTEXT_PACKAGE) --dist
GENPOT   = INTLTOOL_EXTRACT=$(INTLTOOL_EXTRACT) srcdir=$(srcdir) $(INTLTOOL_UPDATE) --gettext-package $(GETTEXT_PACKAGE) --pot

ALL_LINGUAS = 

PO_LINGUAS=$(shell if test -r $(srcdir)/LINGUAS; then grep -v "^\#" $(srcdir)/LINGUAS; fi)

USER_LINGUAS=$(shell if test -n "$(LINGUAS)"; then LLINGUAS="$(LINGUAS)"; ALINGUAS="$(ALL_LINGUAS)"; for lang in $$LLINGUAS; do if test -n "`grep ^$$lang$$ $(srcdir)/LINGUAS`" -o -n "`echo $$ALINGUAS|grep ' ?$$lang ?'`"; then printf "$$lang "; fi; done; fi)

USE_LINGUAS=$(shell if test -n "$(USER_LINGUAS)"; then LLINGUAS="$(USER_LINGUAS)"; else if test -n "$(PO_LINGUAS)"; then LLINGUAS="$(PO_LINGUAS)"; else LLINGUAS="$(ALL_LINGUAS)"; fi; fi; for lang in $$LLINGUAS; do printf "$$lang "; done)

POFILES=$(shell LINGUAS="$(USE_LINGUAS)"; for lang in $$LINGUAS; do printf "$$lang.po "; done)

DISTFILES = Makefile.in.in POTFILES.in $(POFILES)
EXTRA_DISTFILES = POTFILES.skip Makevars LINGUAS

POTFILES = \
	../app/about.h \
	../app/app.c \
	../app/batch.c \
	../app/language.c \
	../app/main.c \
	../app/sanity.c \
	../app/version.c \
	../app/actions/actions.c \
	../app/actions/brush-editor-actions.c \
	../app/actions/brushes-actions.c \
	../app/actions/buffers-actions.c \
	../app/actions/channels-actions.c \
	../app/actions/channels-commands.c \
	../app/actions/colormap-actions.c \
	../app/actions/colormap-commands.c \
	../app/actions/config-actions.c \
	../app/actions/context-actions.c \
	../app/actions/context-commands.c \
	../app/actions/cursor-info-actions.c \
	../app/actions/data-commands.c \
	../app/actions/debug-actions.c \
	../app/actions/dialogs-actions.c \
	../app/actions/dock-actions.c \
	../app/actions/dockable-actions.c \
	../app/actions/documents-actions.c \
	../app/actions/documents-commands.c \
	../app/actions/drawable-actions.c \
	../app/actions/drawable-commands.c \
	../app/actions/dynamics-actions.c \
	../app/actions/dynamics-editor-actions.c \
	../app/actions/edit-actions.c \
	../app/actions/edit-commands.c \
	../app/actions/error-console-actions.c \
	../app/actions/error-console-commands.c \
	../app/actions/file-actions.c \
	../app/actions/file-commands.c \
	../app/actions/fonts-actions.c \
	../app/actions/gradient-editor-actions.c \
	../app/actions/gradient-editor-commands.c \
	../app/actions/gradients-actions.c \
	../app/actions/gradients-commands.c \
	../app/actions/help-actions.c \
	../app/actions/image-actions.c \
	../app/actions/image-commands.c \
	../app/actions/images-actions.c \
	../app/actions/layers-actions.c \
	../app/actions/layers-commands.c \
	../app/actions/palette-editor-actions.c \
	../app/actions/palette-editor-commands.c \
	../app/actions/palettes-actions.c \
	../app/actions/palettes-commands.c \
	../app/actions/patterns-actions.c \
	../app/actions/plug-in-actions.c \
	../app/actions/plug-in-commands.c \
	../app/actions/quick-mask-actions.c \
	../app/actions/quick-mask-commands.c \
	../app/actions/sample-points-actions.c \
	../app/actions/select-actions.c \
	../app/actions/select-commands.c \
	../app/actions/templates-actions.c \
	../app/actions/templates-commands.c \
	../app/actions/text-editor-actions.c \
	../app/actions/text-editor-commands.c \
	../app/actions/text-tool-actions.c \
	../app/actions/text-tool-commands.c \
	../app/actions/tool-options-actions.c \
	../app/actions/tool-options-commands.c \
	../app/actions/tool-presets-actions.c \
	../app/actions/tool-preset-editor-actions.c \
	../app/actions/tools-actions.c \
	../app/actions/vectors-actions.c \
	../app/actions/vectors-commands.c \
	../app/actions/view-actions.c \
	../app/actions/view-commands.c \
	../app/actions/window-actions.c \
	../app/actions/windows-actions.c \
	../app/base/base-enums.c \
	../app/base/tile-swap.c \
	../app/config/config-enums.c \
	../app/config/gimpconfig-file.c \
	../app/config/gimpdisplayoptions.c \
	../app/config/gimprc.c \
	../app/config/gimprc-blurbs.h \
	../app/config/gimprc-deserialize.c \
	../app/core/core-enums.c \
	../app/core/gimp-contexts.c \
	../app/core/gimp-edit.c \
	../app/core/gimp-gradients.c \
	../app/core/gimp-gui.c \
	../app/core/gimp-modules.c \
	../app/core/gimp-tags.c \
	../app/core/gimp-units.c \
	../app/core/gimp-user-install.c \
	../app/core/gimp.c \
	../app/core/gimpbrush-load.c \
	../app/core/gimpbrush.c \
	../app/core/gimpbrushclipboard.c \
	../app/core/gimpbrushgenerated-load.c \
	../app/core/gimpbrushgenerated-save.c \
	../app/core/gimpbrushgenerated.c \
	../app/core/gimpbrushpipe-load.c \
	../app/core/gimpbrushpipe.c \
	../app/core/gimpchannel-select.c \
	../app/core/gimpchannel.c \
	../app/core/gimpcontext.c \
	../app/core/gimpcurve-load.c \
	../app/core/gimpcurve-save.c \
	../app/core/gimpdata.c \
	../app/core/gimpdatafactory.c \
	../app/core/gimpdrawable-blend.c \
	../app/core/gimpdrawable-brightness-contrast.c \
	../app/core/gimpdrawable-bucket-fill.c \
	../app/core/gimpdrawable-color-balance.c \
	../app/core/gimpdrawable-colorize.c \
	../app/core/gimpdrawable-curves.c \
	../app/core/gimpdrawable-desaturate.c \
	../app/core/gimpdrawable-equalize.c \
	../app/core/gimpdrawable-foreground-extract.c \
	../app/core/gimpdrawable-hue-saturation.c \
	../app/core/gimpdrawable-invert.c \
	../app/core/gimpdrawable-levels.c \
	../app/core/gimpdrawable-offset.c \
	../app/core/gimpdrawable-posterize.c \
	../app/core/gimpdrawable-stroke.c \
	../app/core/gimpdrawable-threshold.c \
	../app/core/gimpdrawable-transform.c \
	../app/core/gimpdrawable.c \
	../app/core/gimpdynamicsoutput.c \
	../app/core/gimpgradient-load.c \
	../app/core/gimpgradient-save.c \
	../app/core/gimpgrid.c \
	../app/core/gimpgrouplayer.c \
	../app/core/gimpimage-arrange.c \
	../app/core/gimpimage-colormap.c \
	../app/core/gimpimage-convert.c \
	../app/core/gimpimage-crop.c \
	../app/core/gimpimage-grid.c \
	../app/core/gimpimage-guides.c \
	../app/core/gimpimage-item-list.c \
	../app/core/gimpimage-merge.c \
	../app/core/gimpimage-new.c \
	../app/core/gimpimage-quick-mask.c \
	../app/core/gimpimage-resize.c \
	../app/core/gimpimage-sample-points.c \
	../app/core/gimpimage-scale.c \
	../app/core/gimpimage-undo-push.c \
	../app/core/gimpimage.c \
	../app/core/gimpimagefile.c \
	../app/core/gimpitem.c \
	../app/core/gimpitem-exclusive.c \
	../app/core/gimpitem-linked.c \
	../app/core/gimplayer-floating-sel.c \
	../app/core/gimplayer.c \
	../app/core/gimplayermask.c \
	../app/core/gimppalette-import.c \
	../app/core/gimppalette-load.c \
	../app/core/gimppalette-save.c \
	../app/core/gimppalette.c \
	../app/core/gimppattern-load.c \
	../app/core/gimppattern.c \
	../app/core/gimppatternclipboard.c \
	../app/core/gimppdbprogress.c \
	../app/core/gimpprogress.c \
	../app/core/gimpselection.c \
	../app/core/gimpstrokeoptions.c \
	../app/core/gimptoolpreset-load.c \
	../app/core/gimptemplate.c \
	../app/core/gimptooloptions.c \
	../app/core/gimpunit.c \
	../app/dialogs/about-dialog.c \
	../app/dialogs/channel-options-dialog.c \
	../app/dialogs/convert-dialog.c \
	../app/dialogs/data-delete-dialog.c \
	../app/dialogs/dialogs-constructors.c \
	../app/dialogs/dialogs.c \
	../app/dialogs/fade-dialog.c \
	../app/dialogs/file-open-dialog.c \
	../app/dialogs/file-open-location-dialog.c \
	../app/dialogs/file-save-dialog.c \
	../app/dialogs/grid-dialog.c \
	../app/dialogs/image-merge-layers-dialog.c \
	../app/dialogs/image-new-dialog.c \
	../app/dialogs/image-properties-dialog.c \
	../app/dialogs/image-scale-dialog.c \
	../app/dialogs/input-devices-dialog.c \
	../app/dialogs/keyboard-shortcuts-dialog.c \
	../app/dialogs/layer-add-mask-dialog.c \
	../app/dialogs/layer-options-dialog.c \
	../app/dialogs/module-dialog.c \
	../app/dialogs/offset-dialog.c \
	../app/dialogs/palette-import-dialog.c \
	../app/dialogs/preferences-dialog.c \
	../app/dialogs/print-size-dialog.c \
	../app/dialogs/quit-dialog.c \
	../app/dialogs/resize-dialog.c \
	../app/dialogs/resolution-calibrate-dialog.c \
	../app/dialogs/scale-dialog.c \
	../app/dialogs/stroke-dialog.c \
	../app/dialogs/template-options-dialog.c \
	../app/dialogs/tips-dialog.c \
	../app/dialogs/tips-parser.c \
	../app/dialogs/user-install-dialog.c \
	../app/dialogs/vectors-export-dialog.c \
	../app/dialogs/vectors-import-dialog.c \
	../app/dialogs/vectors-options-dialog.c \
	../app/display/display-enums.c \
	../app/display/gimpcursorview.c \
	../app/display/gimpdisplay.c \
	../app/display/gimpdisplay-handlers.c \
	../app/display/gimpdisplayshell.c \
	../app/display/gimpdisplayshell-callbacks.c \
	../app/display/gimpdisplayshell-close.c \
	../app/display/gimpdisplayshell-dnd.c \
	../app/display/gimpdisplayshell-filter-dialog.c \
	../app/display/gimpdisplayshell-handlers.c \
	../app/display/gimpdisplayshell-layer-select.c \
	../app/display/gimpdisplayshell-scale-dialog.c \
	../app/display/gimpdisplayshell-title.c \
	../app/display/gimpnavigationeditor.c \
	../app/display/gimpstatusbar.c \
	../app/file/file-open.c \
	../app/file/file-procedure.c \
	../app/file/file-save.c \
	../app/file/file-utils.c \
	../app/gegl/gimp-gegl-enums.c \
	../app/gegl/gimpcurvesconfig.c \
	../app/gegl/gimplevelsconfig.c \
	../app/gegl/gimpoperationcagecoefcalc.c \
	../app/gegl/gimpoperationcagetransform.c \
	../app/gui/gui.c \
	../app/gui/gui-message.c \
	../app/gui/session.c \
	../app/gui/splash.c \
	../app/gui/themes.c \
	../app/menus/menus.c \
	../app/paint/gimpairbrush.c \
	../app/paint/gimpbrushcore.c \
	../app/paint/gimpclone.c \
	../app/paint/gimpconvolve.c \
	../app/paint/gimpdodgeburn.c \
	../app/paint/gimperaser.c \
	../app/paint/gimpheal.c \
	../app/paint/gimpink.c \
	../app/paint/gimpinkoptions.c \
	../app/paint/gimppaintbrush.c \
	../app/paint/gimppaintcore-stroke.c \
	../app/paint/gimppaintcore.c \
	../app/paint/gimppaintoptions.c \
	../app/paint/gimppencil.c \
	../app/paint/gimpperspectiveclone.c \
	../app/paint/gimpsmudge.c \
	../app/paint/gimpsourcecore.c \
	../app/paint/paint-enums.c \
	../app/pdb/channel-cmds.c \
	../app/pdb/color-cmds.c \
	../app/pdb/convert-cmds.c \
	../app/pdb/drawable-cmds.c \
	../app/pdb/drawable-transform-cmds.c \
	../app/pdb/edit-cmds.c \
	../app/pdb/floating-sel-cmds.c \
	../app/pdb/gimppdb-query.c \
	../app/pdb/gimppdb-utils.c \
	../app/pdb/gimppdb.c \
	../app/pdb/gimppdbcontext.c \
	../app/pdb/gimpprocedure.c \
	../app/pdb/guides-cmds.c \
	../app/pdb/image-cmds.c \
	../app/pdb/image-select-cmds.c \
	../app/pdb/item-transform-cmds.c \
	../app/pdb/layer-cmds.c \
	../app/pdb/paths-cmds.c \
	../app/pdb/procedural-db-cmds.c \
	../app/pdb/selection-cmds.c \
	../app/pdb/selection-tools-cmds.c \
	../app/pdb/text-layer-cmds.c \
	../app/pdb/transform-tools-cmds.c \
	../app/pdb/undo-cmds.c \
	../app/pdb/vectors-cmds.c \
	../app/plug-in/gimpenvirontable.c \
	../app/plug-in/gimpinterpreterdb.c \
	../app/plug-in/gimpplugin-message.c \
	../app/plug-in/gimpplugin-progress.c \
	../app/plug-in/gimpplugin.c \
	../app/plug-in/gimppluginmanager-call.c \
	../app/plug-in/gimppluginmanager-restore.c \
	../app/plug-in/gimppluginmanager.c \
	../app/plug-in/gimppluginprocedure.c \
	../app/plug-in/gimppluginprocframe.c \
	../app/plug-in/gimptemporaryprocedure.c \
	../app/plug-in/plug-in-enums.c \
	../app/plug-in/plug-in-icc-profile.c \
	../app/plug-in/plug-in-rc.c \
	../app/text/gimpfont.c \
	../app/text/gimptext-compat.c \
	../app/text/gimptextlayer.c \
	../app/text/gimptextlayer-transform.c \
	../app/text/gimptextlayer-xcf.c \
	../app/text/gimptextlayout.c \
	../app/text/text-enums.c \
	../app/tools/gimp-tools.c \
	../app/tools/gimpairbrushtool.c \
	../app/tools/gimpalignoptions.c \
	../app/tools/gimpaligntool.c \
	../app/tools/gimpblendoptions.c \
	../app/tools/gimpblendtool.c \
	../app/tools/gimpbrightnesscontrasttool.c \
	../app/tools/gimpbucketfilloptions.c \
	../app/tools/gimpbucketfilltool.c \
	../app/tools/gimpbycolorselecttool.c \
	../app/tools/gimpcageoptions.c \
	../app/tools/gimpcagetool.c \
	../app/tools/gimpclonetool.c \
	../app/tools/gimpcolorbalancetool.c \
	../app/tools/gimpcolorizetool.c \
	../app/tools/gimpcoloroptions.c \
	../app/tools/gimpcolorpickeroptions.c \
	../app/tools/gimpcolorpickertool.c \
	../app/tools/gimpcolortool.c \
	../app/tools/gimpconvolvetool.c \
	../app/tools/gimpcropoptions.c \
	../app/tools/gimpcroptool.c \
	../app/tools/gimpcurvestool.c \
	../app/tools/gimpdesaturatetool.c \
	../app/tools/gimpdodgeburntool.c \
	../app/tools/gimpeditselectiontool.c \
	../app/tools/gimpellipseselecttool.c \
	../app/tools/gimperasertool.c \
	../app/tools/gimpflipoptions.c \
	../app/tools/gimpfliptool.c \
	../app/tools/gimpforegroundselectoptions.c \
	../app/tools/gimpforegroundselecttool.c \
	../app/tools/gimpfreeselecttool.c \
	../app/tools/gimpfuzzyselecttool.c \
	../app/tools/gimpgegltool.c \
	../app/tools/gimphealtool.c \
	../app/tools/gimphistogramoptions.c \
	../app/tools/gimphuesaturationtool.c \
	../app/tools/gimpimagemaptool-settings.c \
	../app/tools/gimpimagemaptool.c \
	../app/tools/gimpinkoptions-gui.c \
	../app/tools/gimpinktool.c \
	../app/tools/gimpiscissorsoptions.c \
	../app/tools/gimpiscissorstool.c \
	../app/tools/gimplevelstool.c \
	../app/tools/gimpmagnifyoptions.c \
	../app/tools/gimpmagnifytool.c \
	../app/tools/gimpmeasureoptions.c \
	../app/tools/gimpmeasuretool.c \
	../app/tools/gimpmoveoptions.c \
	../app/tools/gimpmovetool.c \
	../app/tools/gimppaintbrushtool.c \
	../app/tools/gimppaintoptions-gui.c \
	../app/tools/gimppainttool.c \
	../app/tools/gimppenciltool.c \
	../app/tools/gimpperspectiveclonetool.c \
	../app/tools/gimpperspectivetool.c \
	../app/tools/gimpposterizetool.c \
	../app/tools/gimprectangleoptions.c \
	../app/tools/gimprectangleselectoptions.c \
	../app/tools/gimprectangleselecttool.c \
	../app/tools/gimprectangletool.c \
	../app/tools/gimpregionselectoptions.c \
	../app/tools/gimpregionselecttool.c \
	../app/tools/gimprotatetool.c \
	../app/tools/gimpscaletool.c \
	../app/tools/gimpselectionoptions.c \
	../app/tools/gimpselectiontool.c \
	../app/tools/gimpsheartool.c \
	../app/tools/gimpsmudgetool.c \
	../app/tools/gimptextoptions.c \
	../app/tools/gimptexttool.c \
	../app/tools/gimptexttool-editor.c \
	../app/tools/gimpthresholdtool.c \
	../app/tools/gimptool.c \
	../app/tools/gimptransformoptions.c \
	../app/tools/gimptransformtool.c \
	../app/tools/gimpvectoroptions.c \
	../app/tools/gimpvectortool.c \
	../app/tools/tools-enums.c \
	../app/vectors/gimpvectors.c \
	../app/vectors/gimpvectors-export.c \
	../app/vectors/gimpvectors-import.c \
	../app/widgets/gimpactioneditor.c \
	../app/widgets/gimpactiongroup.c \
	../app/widgets/gimpactionview.c \
	../app/widgets/gimpbrusheditor.c \
	../app/widgets/gimpbrushfactoryview.c \
	../app/widgets/gimpbrushselect.c \
	../app/widgets/gimpbufferview.c \
	../app/widgets/gimpchanneltreeview.c \
	../app/widgets/gimpclipboard.c \
	../app/widgets/gimpcolordialog.c \
	../app/widgets/gimpcolordisplayeditor.c \
	../app/widgets/gimpcoloreditor.c \
	../app/widgets/gimpcolorframe.c \
	../app/widgets/gimpcolormapeditor.c \
	../app/widgets/gimpcolorselectorpalette.c \
	../app/widgets/gimpcontainergridview.c \
	../app/widgets/gimpcontainerpopup.c \
	../app/widgets/gimpcontrollereditor.c \
	../app/widgets/gimpcontrollerkeyboard.c \
	../app/widgets/gimpcontrollerlist.c \
	../app/widgets/gimpcontrollermouse.c \
	../app/widgets/gimpcontrollerwheel.c \
	../app/widgets/gimpdataeditor.c \
	../app/widgets/gimpdeviceeditor.c \
	../app/widgets/gimpdeviceinfoeditor.c \
	../app/widgets/gimpdevices.c \
	../app/widgets/gimpdevicestatus.c \
	../app/widgets/gimpdnd-xds.c \
	../app/widgets/gimpdnd.c \
	../app/widgets/gimpdock.c \
	../app/widgets/gimpdock.h \
	../app/widgets/gimpdockable.c \
	../app/widgets/gimpdockbook.c \
	../app/widgets/gimpdockwindow.c \
	../app/widgets/gimpdocumentview.c \
	../app/widgets/gimpdrawabletreeview.c \
	../app/widgets/gimpdynamicseditor.c \
	../app/widgets/gimpdynamicsoutputeditor.c \
	../app/widgets/gimpeditor.c \
	../app/widgets/gimperrorconsole.c \
	../app/widgets/gimperrordialog.c \
	../app/widgets/gimpfiledialog.c \
	../app/widgets/gimpfileprocview.c \
	../app/widgets/gimpfilleditor.c \
	../app/widgets/gimpgradienteditor.c \
	../app/widgets/gimpgrideditor.c \
	../app/widgets/gimphelp.c \
	../app/widgets/gimphistogrameditor.c \
	../app/widgets/gimpimagecommenteditor.c \
	../app/widgets/gimpimageprofileview.c \
	../app/widgets/gimpimagepropview.c \
	../app/widgets/gimpitemtreeview.c \
	../app/widgets/gimplayertreeview.c \
	../app/widgets/gimpmenudock.c \
	../app/widgets/gimpmessagebox.c \
	../app/widgets/gimppaletteeditor.c \
	../app/widgets/gimppanedbox.c \
	../app/widgets/gimppdbdialog.c \
	../app/widgets/gimpprofilechooserdialog.c \
	../app/widgets/gimpprogressdialog.c \
	../app/widgets/gimppropwidgets.c \
	../app/widgets/gimpselectiondata.c \
	../app/widgets/gimpselectioneditor.c \
	../app/widgets/gimpsettingsbox.c \
	../app/widgets/gimpsettingseditor.c \
	../app/widgets/gimpsizebox.c \
	../app/widgets/gimpstrokeeditor.c \
	../app/widgets/gimptagentry.c \
	../app/widgets/gimptemplateeditor.c \
	../app/widgets/gimptextbuffer-serialize.c \
	../app/widgets/gimptextbuffer.c \
	../app/widgets/gimptexteditor.c \
	../app/widgets/gimptextstyleeditor.c \
	../app/widgets/gimpthumbbox.c \
	../app/widgets/gimptoolbox-color-area.c \
	../app/widgets/gimptoolbox-dnd.c \
	../app/widgets/gimptoolbox-image-area.c \
	../app/widgets/gimptoolbox-indicator-area.c \
	../app/widgets/gimptoolbox.c \
	../app/widgets/gimptooleditor.c \
	../app/widgets/gimptooloptionseditor.c \
	../app/widgets/gimptoolpalette.c \
	../app/widgets/gimptoolpreseteditor.c \
	../app/widgets/gimptranslationstore.c \
	../app/widgets/gimpuimanager.c \
	../app/widgets/gimpundoeditor.c \
	../app/widgets/gimpvectorstreeview.c \
	../app/widgets/gimpviewablebox.c \
	../app/widgets/gimpwidgets-constructors.c \
	../app/widgets/gimpwidgets-utils.c \
	../app/widgets/widgets-enums.c \
	../app/xcf/xcf-load.c \
	../app/xcf/xcf-read.c \
	../app/xcf/xcf-save.c \
	../app/xcf/xcf-write.c \
	../app/xcf/xcf-seek.c \
	../app/xcf/xcf.c \
	../data/tags/gimp-tags-default.xml.in \
	../desktop/gimp.appdata.xml.in \
	../desktop/gimp.desktop.in.in

CATALOGS=$(shell LINGUAS="$(USE_LINGUAS)"; for lang in $$LINGUAS; do printf "$$lang.gmo "; done)

.SUFFIXES:
.SUFFIXES: .po .pox .gmo .mo .msg .cat

.po.pox:
	$(MAKE) $(GETTEXT_PACKAGE).pot
	$(MSGMERGE) $< $(GETTEXT_PACKAGE).pot -o $*.pox

.po.mo:
	$(MSGFMT) -o $@ $<

.po.gmo:
	file=`echo $* | sed 's,.*/,,'`.gmo \
	  && rm -f $$file && $(GMSGFMT) -o $$file $<

.po.cat:
	sed -f ../intl/po2msg.sed < $< > $*.msg \
	  && rm -f $@ && gencat $@ $*.msg


all: all-yes

all-yes: $(CATALOGS)
all-no:

$(GETTEXT_PACKAGE).pot: $(POTFILES)
	$(GENPOT)

install: install-data
install-data: install-data-yes
install-data-no: all
install-data-yes: all
	$(mkdir_p) $(DESTDIR)$(itlocaledir)
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  dir=$(DESTDIR)$(itlocaledir)/$$lang/LC_MESSAGES; \
	  $(mkdir_p) $$dir; \
	  if test -r $$lang.gmo; then \
	    $(INSTALL_DATA) $$lang.gmo $$dir/$(GETTEXT_PACKAGE).mo; \
	    echo "installing $$lang.gmo as $$dir/$(GETTEXT_PACKAGE).mo"; \
	  else \
	    $(INSTALL_DATA) $(srcdir)/$$lang.gmo $$dir/$(GETTEXT_PACKAGE).mo; \
	    echo "installing $(srcdir)/$$lang.gmo as" \
		 "$$dir/$(GETTEXT_PACKAGE).mo"; \
	  fi; \
	  if test -r $$lang.gmo.m; then \
	    $(INSTALL_DATA) $$lang.gmo.m $$dir/$(GETTEXT_PACKAGE).mo.m; \
	    echo "installing $$lang.gmo.m as $$dir/$(GETTEXT_PACKAGE).mo.m"; \
	  else \
	    if test -r $(srcdir)/$$lang.gmo.m ; then \
	      $(INSTALL_DATA) $(srcdir)/$$lang.gmo.m \
		$$dir/$(GETTEXT_PACKAGE).mo.m; \
	      echo "installing $(srcdir)/$$lang.gmo.m as" \
		   "$$dir/$(GETTEXT_PACKAGE).mo.m"; \
	    else \
	      true; \
	    fi; \
	  fi; \
	done

# Empty stubs to satisfy archaic automake needs
dvi info tags TAGS ID:

# Define this as empty until I found a useful application.
install-exec installcheck:

uninstall:
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  rm -f $(DESTDIR)$(itlocaledir)/$$lang/LC_MESSAGES/$(GETTEXT_PACKAGE).mo; \
	  rm -f $(DESTDIR)$(itlocaledir)/$$lang/LC_MESSAGES/$(GETTEXT_PACKAGE).mo.m; \
	done

check: all $(GETTEXT_PACKAGE).pot
	rm -f missing notexist
	srcdir=$(srcdir) $(INTLTOOL_UPDATE) -m
	if [ -r missing -o -r notexist ]; then \
	  exit 1; \
	fi

mostlyclean:
	rm -f *.pox $(GETTEXT_PACKAGE).pot *.old.po cat-id-tbl.tmp
	rm -f .intltool-merge-cache

clean: mostlyclean

distclean: clean
	rm -f Makefile Makefile.in POTFILES stamp-it
	rm -f *.mo *.msg *.cat *.cat.m *.gmo

maintainer-clean: distclean
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."
	rm -f Makefile.in.in

distdir = ../$(PACKAGE)-$(VERSION)/$(subdir)
dist distdir: $(DISTFILES)
	dists="$(DISTFILES)"; \
	extra_dists="$(EXTRA_DISTFILES)"; \
	for file in $$extra_dists; do \
	  test -f $(srcdir)/$$file && dists="$$dists $(srcdir)/$$file"; \
	done; \
	for file in $$dists; do \
	  test -f $$file || file="$(srcdir)/$$file"; \
	  ln $$file $(distdir) 2> /dev/null \
	    || cp -p $$file $(distdir); \
	done

update-po: Makefile
	$(MAKE) $(GETTEXT_PACKAGE).pot
	tmpdir=`pwd`; \
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  echo "$$lang:"; \
	  result="`$(MSGMERGE) -o $$tmpdir/$$lang.new.po $$lang`"; \
	  if $$result; then \
	    if cmp $(srcdir)/$$lang.po $$tmpdir/$$lang.new.po >/dev/null 2>&1; then \
	      rm -f $$tmpdir/$$lang.new.po; \
            else \
	      if mv -f $$tmpdir/$$lang.new.po $$lang.po; then \
	        :; \
	      else \
	        echo "msgmerge for $$lang.po failed: cannot move $$tmpdir/$$lang.new.po to $$lang.po" 1>&2; \
	        rm -f $$tmpdir/$$lang.new.po; \
	        exit 1; \
	      fi; \
	    fi; \
	  else \
	    echo "msgmerge for $$lang.gmo failed!"; \
	    rm -f $$tmpdir/$$lang.new.po; \
	  fi; \
	done

Makefile POTFILES: stamp-it
	@if test ! -f $@; then \
	  rm -f stamp-it; \
	  $(MAKE) stamp-it; \
	fi

stamp-it: Makefile.in.in $(top_builddir)/config.status POTFILES.in
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/Makefile.in CONFIG_HEADERS= CONFIG_LINKS= \
	       $(SHELL) ./config.status

# Tell versions [3.59,3.63) of GNU make not to export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
