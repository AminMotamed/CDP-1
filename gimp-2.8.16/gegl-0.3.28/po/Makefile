# Makefile for PO directory in any package using GNU gettext.
# Copyright (C) 1995-1997, 2000-2007, 2009-2010 by Ulrich Drepper <drepper@gnu.ai.mit.edu>
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.
#
# Origin: gettext-0.19.8
GETTEXT_MACRO_VERSION = 0.19

PACKAGE = gegl
VERSION = 0.3.28
PACKAGE_BUGREPORT = 

SED = /bin/sed
SHELL = /bin/sh


srcdir = .
top_srcdir = ..


prefix = /usr/local
exec_prefix = ${prefix}
datarootdir = ${prefix}/share
datadir = ${datarootdir}
localedir = ${datarootdir}/locale
gettextsrcdir = $(datadir)/gettext/po

INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644

# We use $(mkdir_p).
# In automake <= 1.9.x, $(mkdir_p) is defined either as "mkdir -p --" or as
# "$(mkinstalldirs)" or as "$(install_sh) -d". For these automake versions,
# ${SHELL} /home/gaston/Downloads/gimp-2.8.16/gegl-0.3.28/install-sh does not start with $(SHELL), so we add it.
# In automake >= 1.10, $(MKDIR_P) is derived from ${MKDIR_P}, which is defined
# either as "/path/to/mkdir -p" or ".../install-sh -c -d". For these automake
# versions, $(mkinstalldirs) and $(install_sh) are unused.
mkinstalldirs = $(SHELL) ${SHELL} /home/gaston/Downloads/gimp-2.8.16/gegl-0.3.28/install-sh -d
install_sh = $(SHELL) ${SHELL} /home/gaston/Downloads/gimp-2.8.16/gegl-0.3.28/install-sh
MKDIR_P = /bin/mkdir -p
mkdir_p = $(MKDIR_P)

# When building gettext-tools, we prefer to use the built programs
# rather than installed programs.  However, we can't do that when we
# are cross compiling.
CROSS_COMPILING = @CROSS_COMPILING@

GMSGFMT_ = /usr/bin/msgfmt
GMSGFMT_no = /usr/bin/msgfmt
GMSGFMT_yes = /usr/bin/msgfmt
GMSGFMT = $(GMSGFMT_$(USE_MSGCTXT))
MSGFMT_ = /usr/bin/msgfmt
MSGFMT_no = /usr/bin/msgfmt
MSGFMT_yes = /usr/bin/msgfmt
MSGFMT = $(MSGFMT_$(USE_MSGCTXT))
XGETTEXT_ = /usr/bin/xgettext
XGETTEXT_no = /usr/bin/xgettext
XGETTEXT_yes = /usr/bin/xgettext
XGETTEXT = $(XGETTEXT_$(USE_MSGCTXT))
MSGMERGE = msgmerge
MSGMERGE_UPDATE = /usr/bin/msgmerge --update
MSGINIT = msginit
MSGCONV = msgconv
MSGFILTER = msgfilter

POFILES =  bs.po ca.po da.po de.po el.po en_GB.po eo.po es.po eu.po fr.po gl.po id.po is.po it.po ko.po lv.po nb.po oc.po pl.po pt.po pt_BR.po ru.po sk.po sl.po sr.po sv.po tr.po zh_CN.po
GMOFILES =  bs.gmo ca.gmo da.gmo de.gmo el.gmo en_GB.gmo eo.gmo es.gmo eu.gmo fr.gmo gl.gmo id.gmo is.gmo it.gmo ko.gmo lv.gmo nb.gmo oc.gmo pl.gmo pt.gmo pt_BR.gmo ru.gmo sk.gmo sl.gmo sr.gmo sv.gmo tr.gmo zh_CN.gmo
UPDATEPOFILES =  bs.po-update ca.po-update da.po-update de.po-update el.po-update en_GB.po-update eo.po-update es.po-update eu.po-update fr.po-update gl.po-update id.po-update is.po-update it.po-update ko.po-update lv.po-update nb.po-update oc.po-update pl.po-update pt.po-update pt_BR.po-update ru.po-update sk.po-update sl.po-update sr.po-update sv.po-update tr.po-update zh_CN.po-update
DUMMYPOFILES =  bs.nop ca.nop da.nop de.nop el.nop en_GB.nop eo.nop es.nop eu.nop fr.nop gl.nop id.nop is.nop it.nop ko.nop lv.nop nb.nop oc.nop pl.nop pt.nop pt_BR.nop ru.nop sk.nop sl.nop sr.nop sv.nop tr.nop zh_CN.nop
DISTFILES.common = Makefile.in.in remove-potcdate.sin \
$(DISTFILES.common.extra1) $(DISTFILES.common.extra2) $(DISTFILES.common.extra3)
DISTFILES = $(DISTFILES.common) Makevars POTFILES.in \
$(POFILES) $(GMOFILES) \
$(DISTFILES.extra1) $(DISTFILES.extra2) $(DISTFILES.extra3)

POTFILES = \
     ../bin/gegl.c \
     ../bin/gegl-options.c \
     ../gegl/gegl-enums.c \
     ../gegl/gegl-init.c \
     ../gegl/gegl-serialize.c \
     ../gegl/module/geglmodule.c \
     ../operations/common/alien-map.c \
     ../operations/common/bilateral-filter.c \
     ../operations/common/box-blur.c \
     ../operations/common/brightness-contrast.c \
     ../operations/common/buffer-sink.c \
     ../operations/common/buffer-source.c \
     ../operations/common/c2g.c \
     ../operations/common/checkerboard.c \
     ../operations/common/color.c \
     ../operations/common/color-enhance.c \
     ../operations/common/color-rotate.c \
     ../operations/common/color-temperature.c \
     ../operations/common/color-warp.c \
     ../operations/common/component-extract.c \
     ../operations/common/contrast-curve.c \
     ../operations/common/convolution-matrix.c \
     ../operations/common/copy-buffer.c \
     ../operations/common/difference-of-gaussians.c \
     ../operations/common/display.c \
     ../operations/common/distance-transform.c \
     ../operations/common/dither.c \
     ../operations/common/dropshadow.c \
     ../operations/common/edge-neon.c \
     ../operations/common/edge-sobel.c \
     ../operations/common/exp-combine.c \
     ../operations/common/exposure.c \
     ../operations/common/fattal02.c \
     ../operations/common/gaussian-blur.c \
     ../operations/common/gblur-1d.c \
     ../operations/common/gegl-buffer-load-op.c \
     ../operations/common/gegl-buffer-save-op.c \
     ../operations/common/gegl.c \
     ../operations/common/grey.c \
     ../operations/common/grid.c \
     ../operations/common/high-pass.c \
     ../operations/common/hue-chroma.c \
     ../operations/common/image-compare.c \
     ../operations/common/image-gradient.c \
     ../operations/common/introspect.c \
     ../operations/common/invert-gamma.c \
     ../operations/common/invert-linear.c \
     ../operations/common/layer.c \
     ../operations/common/levels.c \
     ../operations/common/linear-gradient.c \
     ../operations/common/magick-load.c \
     ../operations/common/mantiuk06.c \
     ../operations/common/map-absolute.c \
     ../operations/common/map-relative.c \
     ../operations/common/matting-global.c \
     ../operations/common/mblur.c \
     ../operations/common/median-blur.c \
     ../operations/common/mirrors.c \
     ../operations/common/mix.c \
     ../operations/common/mono-mixer.c \
     ../operations/common/motion-blur-linear.c \
     ../operations/common/newsprint.c \
     ../operations/common/noise-cell.c \
     ../operations/common/noise-cie-lch.c \
     ../operations/common/noise-hsv.c \
     ../operations/common/noise-hurl.c \
     ../operations/common/noise-perlin.c \
     ../operations/common/noise-pick.c \
     ../operations/common/noise-reduction.c \
     ../operations/common/noise-rgb.c \
     ../operations/common/noise-simplex.c \
     ../operations/common/noise-spread.c \
     ../operations/common/opacity.c \
     ../operations/common/open-buffer.c \
     ../operations/common/over.c \
     ../operations/common/panorama-projection.c \
     ../operations/common/pixelize.c \
     ../operations/common/posterize.c \
     ../operations/common/radial-gradient.c \
     ../operations/common/rectangle.c \
     ../operations/common/reinhard05.c \
     ../operations/common/remap.c \
     ../operations/common/rgb-clip.c \
     ../operations/common/saturation.c \
     ../operations/common/save.c \
     ../operations/common/sepia.c \
     ../operations/common/slic.c \
     ../operations/common/snn-mean.c \
     ../operations/common/stress.c \
     ../operations/common/stretch-contrast.c \
     ../operations/common/stretch-contrast-hsv.c \
     ../operations/common/svg-huerotate.c \
     ../operations/common/svg-luminancetoalpha.c \
     ../operations/common/svg-matrix.c \
     ../operations/common/svg-saturate.c \
     ../operations/common/threshold.c \
     ../operations/common/tile.c \
     ../operations/common/tile-seamless.c \
     ../operations/common/unpremultiply.c \
     ../operations/common/unsharp-mask.c \
     ../operations/common/value-invert.c \
     ../operations/common/vignette.c \
     ../operations/common/warp.c \
     ../operations/common/waterpixels.c \
     ../operations/common/watershed-transform.c \
     ../operations/common/wavelet-blur-1d.c \
     ../operations/common/wavelet-blur.c \
     ../operations/common/weighted-blend.c \
     ../operations/common/write-buffer.c \
     ../operations/common-gpl3+/antialias.c \
     ../operations/common-gpl3+/apply-lens.c \
     ../operations/common-gpl3+/bump-map.c \
     ../operations/common-gpl3+/cartoon.c \
     ../operations/common-gpl3+/channel-mixer.c \
     ../operations/common-gpl3+/color-exchange.c \
     ../operations/common-gpl3+/color-to-alpha.c \
     ../operations/common-gpl3+/cubism.c \
     ../operations/common-gpl3+/deinterlace.c \
     ../operations/common-gpl3+/diffraction-patterns.c \
     ../operations/common-gpl3+/displace.c \
     ../operations/common-gpl3+/edge.c \
     ../operations/common-gpl3+/edge-laplace.c \
     ../operations/common-gpl3+/emboss.c \
     ../operations/common-gpl3+/engrave.c \
     ../operations/common-gpl3+/fractal-explorer.c \
     ../operations/common-gpl3+/fractal-trace.c \
     ../operations/common-gpl3+/gaussian-blur-selective.c \
     ../operations/common-gpl3+/illusion.c \
     ../operations/common-gpl3+/lens-distortion.c \
     ../operations/common-gpl3+/lens-flare.c \
     ../operations/common-gpl3+/maze.c \
     ../operations/common-gpl3+/mosaic.c \
     ../operations/common-gpl3+/motion-blur-circular.c \
     ../operations/common-gpl3+/motion-blur-zoom.c \
     ../operations/common-gpl3+/noise-slur.c \
     ../operations/common-gpl3+/noise-solid.c \
     ../operations/common-gpl3+/oilify.c \
     ../operations/common-gpl3+/photocopy.c \
     ../operations/common-gpl3+/plasma.c \
     ../operations/common-gpl3+/polar-coordinates.c \
     ../operations/common-gpl3+/red-eye-removal.c \
     ../operations/common-gpl3+/ripple.c \
     ../operations/common-gpl3+/shadows-highlights.c \
     ../operations/common-gpl3+/shadows-highlights-correction.c \
     ../operations/common-gpl3+/shift.c \
     ../operations/common-gpl3+/sinus.c \
     ../operations/common-gpl3+/softglow.c \
     ../operations/common-gpl3+/spiral.c \
     ../operations/common-gpl3+/supernova.c \
     ../operations/common-gpl3+/texturize-canvas.c \
     ../operations/common-gpl3+/tile-glass.c \
     ../operations/common-gpl3+/tile-paper.c \
     ../operations/common-gpl3+/value-propagate.c \
     ../operations/common-gpl3+/video-degradation.c \
     ../operations/common-gpl3+/waves.c \
     ../operations/common-gpl3+/whirl-pinch.c \
     ../operations/common-gpl3+/wind.c \
     ../operations/core/cache.c \
     ../operations/core/cast-format.c \
     ../operations/core/clone.c \
     ../operations/core/convert-format.c \
     ../operations/core/crop.c \
     ../operations/core/load.c \
     ../operations/core/nop.c \
     ../operations/external/exr-save.cc \
     ../operations/external/ff-load.c \
     ../operations/external/ff-save.c \
     ../operations/external/jp2-load.c \
     ../operations/external/jpg-load.c \
     ../operations/external/jpg-save.c \
     ../operations/external/lcms-from-profile.c \
     ../operations/external/matting-levin.c \
     ../operations/external/npd.c \
     ../operations/external/npy-save.c \
     ../operations/external/path.c \
     ../operations/external/pixbuf.c \
     ../operations/external/png-load.c \
     ../operations/external/png-save.c \
     ../operations/external/ppm-load.c \
     ../operations/external/ppm-save.c \
     ../operations/external/raw-load.c \
     ../operations/external/rgbe-load.c \
     ../operations/external/rgbe-save.c \
     ../operations/external/save-pixbuf.c \
     ../operations/external/sdl-display.c \
     ../operations/external/svg-load.c \
     ../operations/external/text.c \
     ../operations/external/tiff-load.c \
     ../operations/external/tiff-save.c \
     ../operations/external/v4l.c \
     ../operations/external/vector-fill.c \
     ../operations/external/vector-stroke.c \
     ../operations/external/webp-load.c \
     ../operations/external/webp-save.c \
     ../operations/generated/add.c \
     ../operations/generated/clear.c \
     ../operations/generated/color-burn.c \
     ../operations/generated/color-dodge.c \
     ../operations/generated/darken.c \
     ../operations/generated/difference.c \
     ../operations/generated/divide.c \
     ../operations/generated/dst-atop.c \
     ../operations/generated/dst.c \
     ../operations/generated/dst-in.c \
     ../operations/generated/dst-out.c \
     ../operations/generated/dst-over.c \
     ../operations/generated/exclusion.c \
     ../operations/generated/gamma.c \
     ../operations/generated/hard-light.c \
     ../operations/generated/lighten.c \
     ../operations/generated/multiply.c \
     ../operations/generated/overlay.c \
     ../operations/generated/plus.c \
     ../operations/generated/screen.c \
     ../operations/generated/soft-light.c \
     ../operations/generated/src-atop.c \
     ../operations/generated/src.c \
     ../operations/generated/src-in.c \
     ../operations/generated/src-out.c \
     ../operations/generated/subtract.c \
     ../operations/generated/xor.c \
     ../operations/seamless-clone/seamless-clone.c \
     ../operations/seamless-clone/seamless-clone-compose.c \
     ../operations/transform/reflect.c \
     ../operations/transform/rotate.c \
     ../operations/transform/rotate-on-center.c \
     ../operations/transform/scale-ratio.c \
     ../operations/transform/scale-size.c \
     ../operations/transform/scale-size-keepaspect.c \
     ../operations/transform/shear.c \
     ../operations/transform/transform.c \
     ../operations/transform/transform-core.c \
     ../operations/transform/translate.c \
     ../operations/workshop/bayer-matrix.c \
     ../operations/workshop/bilateral-filter-fast.c \
     ../operations/workshop/color-to-alpha-plus.c \
     ../operations/workshop/demosaic-bimedian.c \
     ../operations/workshop/demosaic-simple.c \
     ../operations/workshop/ditto.c \
     ../operations/workshop/external/gluas.c \
     ../operations/workshop/external/lens-correct.c \
     ../operations/workshop/external/line-profile.c \
     ../operations/workshop/external/v4l2.c \
     ../operations/workshop/generated/average.c \
     ../operations/workshop/generated/blend-reflect.c \
     ../operations/workshop/generated/negation.c \
     ../operations/workshop/generated/soft-burn.c \
     ../operations/workshop/generated/soft-dodge.c \
     ../operations/workshop/generated/subtractive.c \
     ../operations/workshop/gradient-map.c \
     ../operations/workshop/hstack.c \
     ../operations/workshop/integral-image.c \
     ../operations/workshop/linear-sinusoid.c \
     ../operations/workshop/rawbayer-load.c \
     ../operations/workshop/segment-kmeans.c \
     ../operations/workshop/spherize.c

CATALOGS =  bs.gmo ca.gmo da.gmo de.gmo el.gmo en_GB.gmo eo.gmo es.gmo eu.gmo fr.gmo gl.gmo id.gmo is.gmo it.gmo ko.gmo lv.gmo nb.gmo oc.gmo pl.gmo pt.gmo pt_BR.gmo ru.gmo sk.gmo sl.gmo sr.gmo sv.gmo tr.gmo zh_CN.gmo

POFILESDEPS_ = $(srcdir)/$(DOMAIN).pot
POFILESDEPS_yes = $(POFILESDEPS_)
POFILESDEPS_no =
POFILESDEPS = $(POFILESDEPS_$(PO_DEPENDS_ON_POT))

DISTFILESDEPS_ = update-po
DISTFILESDEPS_yes = $(DISTFILESDEPS_)
DISTFILESDEPS_no =
DISTFILESDEPS = $(DISTFILESDEPS_$(DIST_DEPENDS_ON_UPDATE_PO))

# Makevars gets inserted here. (Don't remove this line!)
# Makefile variables for PO directory in any package using GNU gettext.

# Usually the message domain is the same as the package name.
DOMAIN = $(PACKAGE)-0.3

# These two variables depend on the location of this directory.
subdir = po
top_builddir = ..

# These options get passed to xgettext.
XGETTEXT_OPTIONS = --keyword=_ --keyword=N_ --keyword=Q_:1g --keyword=C_:1c,2 --keyword=NC_:1c,2 --from-code=UTF-8 --add-comments

# This is the copyright holder that gets inserted into the header of the
# $(DOMAIN).pot file.  Set this to the copyright holder of the surrounding
# package.  (Note that the msgstr strings, extracted from the package's
# sources, belong to the copyright holder of the package.)  Translators are
# expected to transfer the copyright for their translations to this person
# or entity, or to disclaim their copyright.  The empty string stands for
# the public domain; in this case the translators are expected to disclaim
# their copyright.
COPYRIGHT_HOLDER = (PACKAGE_STRING) authors

# This tells whether or not to prepend "GNU " prefix to the package
# name that gets inserted into the header of the $(DOMAIN).pot file.
# Possible values are "yes", "no", or empty.  If it is empty, try to
# detect it automatically by scanning the files in $(top_srcdir) for
# "GNU packagename" string.
PACKAGE_GNU = no

# This is the email address or URL to which the translators shall report
# bugs in the untranslated strings:
# - Strings which are not entire sentences, see the maintainer guidelines
#   in the GNU gettext documentation, section 'Preparing Strings'.
# - Strings which use unclear terms or require additional context to be
#   understood.
# - Strings which make invalid assumptions about notation of date, time or
#   money.
# - Pluralisation problems.
# - Incorrect English spelling.
# - Incorrect formatting.
# It can be your email address, or a mailing list address where translators
# can write to without being subscribed, or the URL of a web page through
# which the translators can contact you.
MSGID_BUGS_ADDRESS = https://bugzilla.gnome.org/enter_bug.cgi?product=GEGL&keywords=I18N+L10N&component=general

# This is the list of locale categories, beyond LC_MESSAGES, for which the
# message catalogs shall be used.  It is usually empty.
EXTRA_LOCALE_CATEGORIES =

# This tells whether the $(DOMAIN).pot file contains messages with an 'msgctxt'
# context.  Possible values are "yes" and "no".  Set this to yes if the
# package uses functions taking also a message context, like pgettext(), or
# if in $(XGETTEXT_OPTIONS) you define keywords with a context argument.
USE_MSGCTXT = yes

# These options get passed to msgmerge.
# Useful options are in particular:
#   --previous            to keep previous msgids of translated messages,
#   --quiet               to reduce the verbosity.
MSGMERGE_OPTIONS =

# These options get passed to msginit.
# If you want to disable line wrapping when writing PO files, add
# --no-wrap to MSGMERGE_OPTIONS, XGETTEXT_OPTIONS, and
# MSGINIT_OPTIONS.
MSGINIT_OPTIONS =

# This tells whether or not to regenerate a PO file when $(DOMAIN).pot
# has changed.  Possible values are "yes" and "no".  Set this to no if
# the POT file is checked in the repository and the version control
# program ignores timestamps.
PO_DEPENDS_ON_POT = no

# This tells whether or not to forcibly update $(DOMAIN).pot and
# regenerate PO files on "make dist".  Possible values are "yes" and
# "no".  Set this to no if the POT file and PO files are maintained
# externally.
DIST_DEPENDS_ON_UPDATE_PO = no

.SUFFIXES:
.SUFFIXES: .po .gmo .mo .sed .sin .nop .po-create .po-update

.po.mo:
	@echo "$(MSGFMT) -c -o $@ $<"; \
	$(MSGFMT) -c -o t-$@ $< && mv t-$@ $@

.po.gmo:
	@lang=`echo $* | sed -e 's,.*/,,'`; \
	test "$(srcdir)" = . && cdcmd="" || cdcmd="cd $(srcdir) && "; \
	echo "$${cdcmd}rm -f $${lang}.gmo && $(GMSGFMT) -c --statistics --verbose -o $${lang}.gmo $${lang}.po"; \
	cd $(srcdir) && rm -f $${lang}.gmo && $(GMSGFMT) -c --statistics --verbose -o t-$${lang}.gmo $${lang}.po && mv t-$${lang}.gmo $${lang}.gmo

.sin.sed:
	sed -e '/^#/d' $< > t-$@
	mv t-$@ $@


all: all-yes

all-yes: stamp-po
all-no:

# Ensure that the gettext macros and this Makefile.in.in are in sync.
CHECK_MACRO_VERSION = \
	test "$(GETTEXT_MACRO_VERSION)" = "0.19" \
	  || { echo "*** error: gettext infrastructure mismatch: using a Makefile.in.in from gettext version $(GETTEXT_MACRO_VERSION) but the autoconf macros are from gettext version 0.19" 1>&2; \
	       exit 1; \
	     }

# $(srcdir)/$(DOMAIN).pot is only created when needed. When xgettext finds no
# internationalized messages, no $(srcdir)/$(DOMAIN).pot is created (because
# we don't want to bother translators with empty POT files). We assume that
# LINGUAS is empty in this case, i.e. $(POFILES) and $(GMOFILES) are empty.
# In this case, stamp-po is a nop (i.e. a phony target).

# stamp-po is a timestamp denoting the last time at which the CATALOGS have
# been loosely updated. Its purpose is that when a developer or translator
# checks out the package via CVS, and the $(DOMAIN).pot file is not in CVS,
# "make" will update the $(DOMAIN).pot and the $(CATALOGS), but subsequent
# invocations of "make" will do nothing. This timestamp would not be necessary
# if updating the $(CATALOGS) would always touch them; however, the rule for
# $(POFILES) has been designed to not touch files that don't need to be
# changed.
stamp-po: $(srcdir)/$(DOMAIN).pot
	@$(CHECK_MACRO_VERSION)
	test ! -f $(srcdir)/$(DOMAIN).pot || \
	  test -z "$(GMOFILES)" || $(MAKE) $(GMOFILES)
	@test ! -f $(srcdir)/$(DOMAIN).pot || { \
	  echo "touch stamp-po" && \
	  echo timestamp > stamp-poT && \
	  mv stamp-poT stamp-po; \
	}

# Note: Target 'all' must not depend on target '$(DOMAIN).pot-update',
# otherwise packages like GCC can not be built if only parts of the source
# have been downloaded.

# This target rebuilds $(DOMAIN).pot; it is an expensive operation.
# Note that $(DOMAIN).pot is not touched if it doesn't need to be changed.
# The determination of whether the package xyz is a GNU one is based on the
# heuristic whether some file in the top level directory mentions "GNU xyz".
# If GNU 'find' is available, we avoid grepping through monster files.
$(DOMAIN).pot-update: $(POTFILES) $(srcdir)/POTFILES.in remove-potcdate.sed
	package_gnu="$(PACKAGE_GNU)"; \
	test -n "$$package_gnu" || { \
	  if { if (LC_ALL=C find --version) 2>/dev/null | grep GNU >/dev/null; then \
		 LC_ALL=C find -L $(top_srcdir) -maxdepth 1 -type f \
			       -size -10000000c -exec grep 'GNU gegl' \
			       /dev/null '{}' ';' 2>/dev/null; \
	       else \
		 LC_ALL=C grep 'GNU gegl' $(top_srcdir)/* 2>/dev/null; \
	       fi; \
	     } | grep -v 'libtool:' >/dev/null; then \
	     package_gnu=yes; \
	   else \
	     package_gnu=no; \
	   fi; \
	}; \
	if test "$$package_gnu" = "yes"; then \
	  package_prefix='GNU '; \
	else \
	  package_prefix=''; \
	fi; \
	if test -n '$(MSGID_BUGS_ADDRESS)' || test '$(PACKAGE_BUGREPORT)' = '@'PACKAGE_BUGREPORT'@'; then \
	  msgid_bugs_address='$(MSGID_BUGS_ADDRESS)'; \
	else \
	  msgid_bugs_address='$(PACKAGE_BUGREPORT)'; \
	fi; \
	case `$(XGETTEXT) --version | sed 1q | sed -e 's,^[^0-9]*,,'` in \
	  '' | 0.[0-9] | 0.[0-9].* | 0.1[0-5] | 0.1[0-5].* | 0.16 | 0.16.[0-1]*) \
	    $(XGETTEXT) --default-domain=$(DOMAIN) --directory=$(top_srcdir) \
	      --add-comments=TRANSLATORS: $(XGETTEXT_OPTIONS)  \
	      --files-from=$(srcdir)/POTFILES.in \
	      --copyright-holder='$(COPYRIGHT_HOLDER)' \
	      --msgid-bugs-address="$$msgid_bugs_address" \
	    ;; \
	  *) \
	    $(XGETTEXT) --default-domain=$(DOMAIN) --directory=$(top_srcdir) \
	      --add-comments=TRANSLATORS: $(XGETTEXT_OPTIONS)  \
	      --files-from=$(srcdir)/POTFILES.in \
	      --copyright-holder='$(COPYRIGHT_HOLDER)' \
	      --package-name="$${package_prefix}gegl" \
	      --package-version='0.3.28' \
	      --msgid-bugs-address="$$msgid_bugs_address" \
	    ;; \
	esac
	test ! -f $(DOMAIN).po || { \
	  if test -f $(srcdir)/$(DOMAIN).pot-header; then \
	    sed -e '1,/^#$$/d' < $(DOMAIN).po > $(DOMAIN).1po && \
	    cat $(srcdir)/$(DOMAIN).pot-header $(DOMAIN).1po > $(DOMAIN).po; \
	    rm -f $(DOMAIN).1po; \
	  fi; \
	  if test -f $(srcdir)/$(DOMAIN).pot; then \
	    sed -f remove-potcdate.sed < $(srcdir)/$(DOMAIN).pot > $(DOMAIN).1po && \
	    sed -f remove-potcdate.sed < $(DOMAIN).po > $(DOMAIN).2po && \
	    if cmp $(DOMAIN).1po $(DOMAIN).2po >/dev/null 2>&1; then \
	      rm -f $(DOMAIN).1po $(DOMAIN).2po $(DOMAIN).po; \
	    else \
	      rm -f $(DOMAIN).1po $(DOMAIN).2po $(srcdir)/$(DOMAIN).pot && \
	      mv $(DOMAIN).po $(srcdir)/$(DOMAIN).pot; \
	    fi; \
	  else \
	    mv $(DOMAIN).po $(srcdir)/$(DOMAIN).pot; \
	  fi; \
	}

# This rule has no dependencies: we don't need to update $(DOMAIN).pot at
# every "make" invocation, only create it when it is missing.
# Only "make $(DOMAIN).pot-update" or "make dist" will force an update.
$(srcdir)/$(DOMAIN).pot:
	$(MAKE) $(DOMAIN).pot-update

# This target rebuilds a PO file if $(DOMAIN).pot has changed.
# Note that a PO file is not touched if it doesn't need to be changed.
$(POFILES): $(POFILESDEPS)
	@lang=`echo $@ | sed -e 's,.*/,,' -e 's/\.po$$//'`; \
	if test -f "$(srcdir)/$${lang}.po"; then \
	  test -f $(srcdir)/$(DOMAIN).pot || $(MAKE) $(srcdir)/$(DOMAIN).pot; \
	  test "$(srcdir)" = . && cdcmd="" || cdcmd="cd $(srcdir) && "; \
	  echo "$${cdcmd}$(MSGMERGE_UPDATE) $(MSGMERGE_OPTIONS) --lang=$${lang} $${lang}.po $(DOMAIN).pot"; \
	  cd $(srcdir) \
	    && { case `$(MSGMERGE) --version | sed 1q | sed -e 's,^[^0-9]*,,'` in \
	           '' | 0.[0-9] | 0.[0-9].* | 0.1[0-7] | 0.1[0-7].*) \
	             $(MSGMERGE_UPDATE) $(MSGMERGE_OPTIONS) $${lang}.po $(DOMAIN).pot;; \
	           *) \
	             $(MSGMERGE_UPDATE) $(MSGMERGE_OPTIONS) --lang=$${lang} $${lang}.po $(DOMAIN).pot;; \
	         esac; \
	       }; \
	else \
	  $(MAKE) $${lang}.po-create; \
	fi


install: install-exec install-data
install-exec:
install-data: install-data-yes
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  $(mkdir_p) $(DESTDIR)$(gettextsrcdir); \
	  for file in $(DISTFILES.common) Makevars.template; do \
	    $(INSTALL_DATA) $(srcdir)/$$file \
			    $(DESTDIR)$(gettextsrcdir)/$$file; \
	  done; \
	  for file in Makevars; do \
	    rm -f $(DESTDIR)$(gettextsrcdir)/$$file; \
	  done; \
	else \
	  : ; \
	fi
install-data-no: all
install-data-yes: all
	@catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed -e 's/\.gmo$$//'`; \
	  dir=$(localedir)/$$lang/LC_MESSAGES; \
	  $(mkdir_p) $(DESTDIR)$$dir; \
	  if test -r $$cat; then realcat=$$cat; else realcat=$(srcdir)/$$cat; fi; \
	  $(INSTALL_DATA) $$realcat $(DESTDIR)$$dir/$(DOMAIN).mo; \
	  echo "installing $$realcat as $(DESTDIR)$$dir/$(DOMAIN).mo"; \
	  for lc in '' $(EXTRA_LOCALE_CATEGORIES); do \
	    if test -n "$$lc"; then \
	      if (cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc 2>/dev/null) | grep ' -> ' >/dev/null; then \
	        link=`cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc | sed -e 's/^.* -> //'`; \
	        mv $(DESTDIR)$(localedir)/$$lang/$$lc $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	        mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        (cd $(DESTDIR)$(localedir)/$$lang/$$lc.old && \
	         for file in *; do \
	           if test -f $$file; then \
	             ln -s ../$$link/$$file $(DESTDIR)$(localedir)/$$lang/$$lc/$$file; \
	           fi; \
	         done); \
	        rm -f $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	      else \
	        if test -d $(DESTDIR)$(localedir)/$$lang/$$lc; then \
	          :; \
	        else \
	          rm -f $(DESTDIR)$(localedir)/$$lang/$$lc; \
	          mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        fi; \
	      fi; \
	      rm -f $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo; \
	      ln -s ../LC_MESSAGES/$(DOMAIN).mo $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo 2>/dev/null || \
	      ln $(DESTDIR)$(localedir)/$$lang/LC_MESSAGES/$(DOMAIN).mo $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo 2>/dev/null || \
	      cp -p $(DESTDIR)$(localedir)/$$lang/LC_MESSAGES/$(DOMAIN).mo $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo; \
	      echo "installing $$realcat link as $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo"; \
	    fi; \
	  done; \
	done

install-strip: install

installdirs: installdirs-exec installdirs-data
installdirs-exec:
installdirs-data: installdirs-data-yes
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  $(mkdir_p) $(DESTDIR)$(gettextsrcdir); \
	else \
	  : ; \
	fi
installdirs-data-no:
installdirs-data-yes:
	@catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed -e 's/\.gmo$$//'`; \
	  dir=$(localedir)/$$lang/LC_MESSAGES; \
	  $(mkdir_p) $(DESTDIR)$$dir; \
	  for lc in '' $(EXTRA_LOCALE_CATEGORIES); do \
	    if test -n "$$lc"; then \
	      if (cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc 2>/dev/null) | grep ' -> ' >/dev/null; then \
	        link=`cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc | sed -e 's/^.* -> //'`; \
	        mv $(DESTDIR)$(localedir)/$$lang/$$lc $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	        mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        (cd $(DESTDIR)$(localedir)/$$lang/$$lc.old && \
	         for file in *; do \
	           if test -f $$file; then \
	             ln -s ../$$link/$$file $(DESTDIR)$(localedir)/$$lang/$$lc/$$file; \
	           fi; \
	         done); \
	        rm -f $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	      else \
	        if test -d $(DESTDIR)$(localedir)/$$lang/$$lc; then \
	          :; \
	        else \
	          rm -f $(DESTDIR)$(localedir)/$$lang/$$lc; \
	          mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        fi; \
	      fi; \
	    fi; \
	  done; \
	done

# Define this as empty until I found a useful application.
installcheck:

uninstall: uninstall-exec uninstall-data
uninstall-exec:
uninstall-data: uninstall-data-yes
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  for file in $(DISTFILES.common) Makevars.template; do \
	    rm -f $(DESTDIR)$(gettextsrcdir)/$$file; \
	  done; \
	else \
	  : ; \
	fi
uninstall-data-no:
uninstall-data-yes:
	catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed -e 's/\.gmo$$//'`; \
	  for lc in LC_MESSAGES $(EXTRA_LOCALE_CATEGORIES); do \
	    rm -f $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo; \
	  done; \
	done

check: all

info dvi ps pdf html tags TAGS ctags CTAGS ID:

mostlyclean:
	rm -f remove-potcdate.sed
	rm -f stamp-poT
	rm -f core core.* $(DOMAIN).po $(DOMAIN).1po $(DOMAIN).2po *.new.po
	rm -fr *.o

clean: mostlyclean

distclean: clean
	rm -f Makefile Makefile.in POTFILES *.mo

maintainer-clean: distclean
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."
	rm -f stamp-po $(GMOFILES)

distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)
dist distdir:
	test -z "$(DISTFILESDEPS)" || $(MAKE) $(DISTFILESDEPS)
	@$(MAKE) dist2
# This is a separate target because 'update-po' must be executed before.
dist2: stamp-po $(DISTFILES)
	dists="$(DISTFILES)"; \
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  dists="$$dists Makevars.template"; \
	fi; \
	if test -f $(srcdir)/$(DOMAIN).pot; then \
	  dists="$$dists $(DOMAIN).pot stamp-po"; \
	fi; \
	if test -f $(srcdir)/ChangeLog; then \
	  dists="$$dists ChangeLog"; \
	fi; \
	for i in 0 1 2 3 4 5 6 7 8 9; do \
	  if test -f $(srcdir)/ChangeLog.$$i; then \
	    dists="$$dists ChangeLog.$$i"; \
	  fi; \
	done; \
	if test -f $(srcdir)/LINGUAS; then dists="$$dists LINGUAS"; fi; \
	for file in $$dists; do \
	  if test -f $$file; then \
	    cp -p $$file $(distdir) || exit 1; \
	  else \
	    cp -p $(srcdir)/$$file $(distdir) || exit 1; \
	  fi; \
	done

update-po: Makefile
	$(MAKE) $(DOMAIN).pot-update
	test -z "$(UPDATEPOFILES)" || $(MAKE) $(UPDATEPOFILES)
	$(MAKE) update-gmo

# General rule for creating PO files.

.nop.po-create:
	@lang=`echo $@ | sed -e 's/\.po-create$$//'`; \
	echo "File $$lang.po does not exist. If you are a translator, you can create it through 'msginit'." 1>&2; \
	exit 1

# General rule for updating PO files.

.nop.po-update:
	@lang=`echo $@ | sed -e 's/\.po-update$$//'`; \
	if test "$(PACKAGE)" = "gettext-tools" && test "$(CROSS_COMPILING)" != "yes"; then PATH=`pwd`/../src:$$PATH; fi; \
	tmpdir=`pwd`; \
	echo "$$lang:"; \
	test "$(srcdir)" = . && cdcmd="" || cdcmd="cd $(srcdir) && "; \
	echo "$${cdcmd}$(MSGMERGE) $(MSGMERGE_OPTIONS) --lang=$$lang $$lang.po $(DOMAIN).pot -o $$lang.new.po"; \
	cd $(srcdir); \
	if { case `$(MSGMERGE) --version | sed 1q | sed -e 's,^[^0-9]*,,'` in \
	       '' | 0.[0-9] | 0.[0-9].* | 0.1[0-7] | 0.1[0-7].*) \
	         $(MSGMERGE) $(MSGMERGE_OPTIONS) -o $$tmpdir/$$lang.new.po $$lang.po $(DOMAIN).pot;; \
	       *) \
	         $(MSGMERGE) $(MSGMERGE_OPTIONS) --lang=$$lang -o $$tmpdir/$$lang.new.po $$lang.po $(DOMAIN).pot;; \
	     esac; \
	   }; then \
	  if cmp $$lang.po $$tmpdir/$$lang.new.po >/dev/null 2>&1; then \
	    rm -f $$tmpdir/$$lang.new.po; \
	  else \
	    if mv -f $$tmpdir/$$lang.new.po $$lang.po; then \
	      :; \
	    else \
	      echo "msgmerge for $$lang.po failed: cannot move $$tmpdir/$$lang.new.po to $$lang.po" 1>&2; \
	      exit 1; \
	    fi; \
	  fi; \
	else \
	  echo "msgmerge for $$lang.po failed!" 1>&2; \
	  rm -f $$tmpdir/$$lang.new.po; \
	fi

$(DUMMYPOFILES):

update-gmo: Makefile $(GMOFILES)
	@:

# Recreate Makefile by invoking config.status. Explicitly invoke the shell,
# because execution permission bits may not work on the current file system.
# Use /bin/bash, which is the shell determined by autoconf for the use by its
# scripts, not $(SHELL) which is hardwired to /bin/sh and may be deficient.
Makefile: Makefile.in.in Makevars $(top_builddir)/config.status POTFILES.in LINGUAS
	cd $(top_builddir) \
	  && /bin/bash ./config.status $(subdir)/$@.in po-directories

force:

# Tell versions [3.59,3.63) of GNU make not to export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
# This file, Rules-quot, can be copied and used freely without restrictions.
# Special Makefile rules for English message catalogs with quotation marks.

DISTFILES.common.extra1 = quot.sed boldquot.sed en@quot.header en@boldquot.header insert-header.sin Rules-quot

.SUFFIXES: .insert-header .po-update-en

en@quot.po-create:
	$(MAKE) en@quot.po-update
en@boldquot.po-create:
	$(MAKE) en@boldquot.po-update

en@quot.po-update: en@quot.po-update-en
en@boldquot.po-update: en@boldquot.po-update-en

.insert-header.po-update-en:
	@lang=`echo $@ | sed -e 's/\.po-update-en$$//'`; \
	if test "$(PACKAGE)" = "gettext-tools" && test "$(CROSS_COMPILING)" != "yes"; then PATH=`pwd`/../src:$$PATH; GETTEXTLIBDIR=`cd $(top_srcdir)/src && pwd`; export GETTEXTLIBDIR; fi; \
	tmpdir=`pwd`; \
	echo "$$lang:"; \
	ll=`echo $$lang | sed -e 's/@.*//'`; \
	LC_ALL=C; export LC_ALL; \
	cd $(srcdir); \
	if $(MSGINIT) $(MSGINIT_OPTIONS) -i $(DOMAIN).pot --no-translator -l $$lang -o - 2>/dev/null \
	   | $(SED) -f $$tmpdir/$$lang.insert-header | $(MSGCONV) -t UTF-8 | \
	   { case `$(MSGFILTER) --version | sed 1q | sed -e 's,^[^0-9]*,,'` in \
	     '' | 0.[0-9] | 0.[0-9].* | 0.1[0-8] | 0.1[0-8].*) \
	       $(MSGFILTER) $(SED) -f `echo $$lang | sed -e 's/.*@//'`.sed \
	       ;; \
	     *) \
	       $(MSGFILTER) `echo $$lang | sed -e 's/.*@//'` \
	       ;; \
	     esac } 2>/dev/null > $$tmpdir/$$lang.new.po \
	     ; then \
	  if cmp $$lang.po $$tmpdir/$$lang.new.po >/dev/null 2>&1; then \
	    rm -f $$tmpdir/$$lang.new.po; \
	  else \
	    if mv -f $$tmpdir/$$lang.new.po $$lang.po; then \
	      :; \
	    else \
	      echo "creation of $$lang.po failed: cannot move $$tmpdir/$$lang.new.po to $$lang.po" 1>&2; \
	      exit 1; \
	    fi; \
	  fi; \
	else \
	  echo "creation of $$lang.po failed!" 1>&2; \
	  rm -f $$tmpdir/$$lang.new.po; \
	fi

en@quot.insert-header: insert-header.sin
	sed -e '/^#/d' -e 's/HEADER/en@quot.header/g' $(srcdir)/insert-header.sin > en@quot.insert-header

en@boldquot.insert-header: insert-header.sin
	sed -e '/^#/d' -e 's/HEADER/en@boldquot.header/g' $(srcdir)/insert-header.sin > en@boldquot.insert-header

mostlyclean: mostlyclean-quot
mostlyclean-quot:
	rm -f *.insert-header
