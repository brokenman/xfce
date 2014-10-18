#!/bin/bash
# Porteus-xfce strip script
# After installing packages to a directory
# copy the TREE here and run this script

if [ `uname -m|grep -o 64` ]; then
  LIB="usr/lib64"
  SHARCH=64
  LIBSUFFIX=64
  SUFFIX=64
else
  LIB="usr/lib"
  SHARCH=32
  LIBSUFFIX=""
  SUFFIX=32
fi

CWD=`pwd`
exp=../export${SUFFIX}

echo "Size BEFORE stripping: `du -sh`"

########### CUSTOM PORTEUS STUFF #############
rm -rf install
rm -rf usr/var/lib/scrollkeeper
rm -rf usr/share/swat/*
rm -rf usr/share/devhelp/*
rm -rf usr/share/gnome/help/*
rm -rf usr/share/help/*
rm -rf var/lib/scrollkeeper/*
rm -rf var/scrollkeeper/*
rm -f usr/share/applications/gksu.desktop
rm -f usr/share/applications/uxterm.desktop
rm -f usr/share/applications/xhtml2ps.desktop
rm etc/xdg/autostart/polkit-gnome-authentication-agent-1.desktop


## Create symlinks
ln -sf /etc/X11/xinit/xinitrc.xfce etc/X11/xinit/xinitrc
ln -sf /usr/sbin/lxdm usr/bin/lxdm
ln -sf /usr/bin/gnsu usr/bin/gksu
ln -sf /usr/bin/gnsu usr/bin/gnsudo
ln -sf /usr/bin/gnsu usr/bin/ktsuss
[ ! -d opt/porteus-scripts/xorg ] && mkdir -p opt/porteus-scripts/xorg
ln -sf /usr/bin/gnsu opt/porteus-scripts/xorg/psu
ln -sf /usr/bin/thunar opt/porteus-scripts/xorg/fmanager
if [ "$SHARCH" = "64" ]; then
	[ ! -e usr/lib64/libudev.so.1 ] && ln -sf /lib64/libudev.so.0.13.1 usr/lib64/libudev.so.1
fi
mv usr/bin/slock usr/bin/slock-binary
ln -sf /opt/porteus-scripts/xfce/start-slock usr/bin/slock
chmod u+s usr/bin/slock-binary
for a in `find usr/share/icons/hicolor -type f -name "xfce4-panel.png"|egrep -v "16x16|22x22"` \
`find usr/share/icons/hicolor -type f -name "xfce4-panel-menu.png"|egrep -v "16x16|22x22"`; do
	b=${a%/*}
	c=/$b/porteus-button.png
	rm $a
	ln -sf $c $a
done

ln -sf /usr/share/icons/hicolor/48x48/apps/porteus-button.png usr/share/pixmaps/xfce4_xicon.png
ln -sf /usr/share/icons/hicolor/48x48/apps/porteus-button.png usr/share/pixmaps/xfce4_xicon1.png
ln -sf /usr/share/icons/hicolor/48x48/apps/porteus-button.png usr/share/pixmaps/xfce4_xicon2.png
ln -sf /usr/share/icons/hicolor/48x48/apps/porteus-button.png usr/share/pixmaps/xfce4_xicon3.png
ln -sf /usr/share/icons/hicolor/48x48/apps/porteus-button.png usr/share/pixmaps/xfce4_xicon4.png
rm usr/share/pixmaps/gcolor2/icon.png
ln -sf /usr/share/icons/Faenza/apps/48/gcolor2.png usr/share/pixmaps/gcolor2/icon.png

## Fix/remove some icons
ln -sf /usr/share/icons/Faenza/mimetypes/48/encrypted.png usr/share/pixmaps/porteus/binary.png
ln -sf /usr/share/icons/Faenza/apps/48/help-browser.png usr/share/pixmaps/help-hint.png
# Clipman panel icon for dark background
for a in `find usr/share/icons/ -name "edit-paste*" | grep Faenza-Dark | egrep "/32/|/24/|/22/"`; do
	rm $a
	ln -sf /usr/share/icons/Faenza-Dark/status/24/gtg-panel.png $a
done
find usr/share/icons/hicolor/256x256/ -type f|xargs rm
find usr/share/icons/hicolor/128x128/ -type f|xargs rm
find usr/share/icons/hicolor/scalable/ -type f|xargs rm

## Remove misc gtk3 stuff
#rm -rf usr/share/gtk-3.0/demo/*
#rm usr/bin/gtk3-demo-application
#rm usr/bin/gtk3-demo
#rm usr/bin/gtk3-widget-factory

[ "$SUFFIX" == "32" ] && rm -r usr/lib64

## Theme changes
rm -rf usr/share/themes/{Xfce-*,Daloa,Kokodi,Moheli,ZOMG*}
rm -rf usr/share/themes/MediterraneanDarkest/gtk-3.0
rm -rf usr/share/themes/Zukitwo/gtk-3.0
rm -rf usr/share/themes/MediterraneanGrayDark/gtk-3.0

## Remove broken links
icons=usr/share/icons
find -L $icons -type l -delete

## Remove xbit from icon theme.
find usr/share/icons -type f|xargs chmod -x 2>/dev/null

# Apply porteus patches:
for x in `find xfce-patches -type f`; do patch -p1 < $x; done
rm -rf xfce-patches

## Fix some menu items
sed -i 's/Exec=.*/Exec=gnsu gparted/g' usr/share/applications/gparted.desktop
sed -i 's/Utility;/Graphics;/g' usr/share/applications/gcolor2.desktop

## suid slock
chmod u+s usr/bin/slock
########### END OF CUSTOM PORTEUS STUFF ##########

# Remove unnecessary stuff:
find . -type f -name "*~"|xargs rm -f
rm -rf usr/info/*
rm -rf usr/doc/*
rm -rf usr/man/man2/*
rm -rf usr/man/man3/*
rm -rf usr/man/man4/*
rm -rf usr/man/man6/*
rm -rf usr/man/man9/*
rm -rf usr/share/gtk-2.0/demo
rm -rf usr/share/gtk-doc/*
rm -rf usr/share/doc
rm -rf var/log/scripts/*
rm -rf var/log/setup/*
rm -rf var/log/removed*
rm etc/xfce/xdg/autostart/xscreensaver.desktop
#rm usr/lib64/libgcr-ui*
#rm usr/bin/gcr-viewer
rm usr/share/backgrounds/xfce/xfce-blue.jpg
rm -rf usr/share/themes/{Xfce-*,Daloa,Kokodi,Moheli,ZOMG*}
rm -rf usr/src/*

# Strip icons
rm xfce-icon-remove.txt

# Setup export directory for 05-devel and language-selection-tool
[ ! -d $exp/include ] && mkdir -p $exp/include
[ ! -d $exp/togo/locale ] && mkdir -p $exp/togo/locale
echo "Removing old local headers and locales"
rm -rf $exp/include/* 2>/dev/null
rm -rf $exp/togo/locale/* 2>/dev/null

# Set default perms, extract compressed files, strip debugging symbols:
echo "Changing permissions..."
find ./ -type d | xargs chmod -v 755 >/dev/null 2>&1
echo "Extracting All manpages..."
find . | grep .gz | xargs gunzip >/dev/null 2>&1
echo "stripping Unneeded Symbols..."
find . | xargs file | grep ELF | cut -f 1 -d : | xargs strip --strip-unneeded >/dev/null 2>&1

# Move headers, .gir/.cmake files:
find -type f -name "*.h" | xargs -n1 -i cp -a --parents {} $exp/include
rm -rf usr/include/*
cp -a --parents $LIB/girepository-1.0 usr/share/gir-1.0 $exp/include
rm -rf $LIB/girepository-1.0 usr/share/gir-1.0

# Remove static headers
find . -name "*.a" | xargs -n1 -i cp -a --parents {} $exp/include
find . -name "*.a" | xargs rm -f
find . -name "*.la" | xargs -n1 -i cp -a --parents {} $exp/include
find . -name "*.la" | xargs rm -f

# Move translations/localized man pages:
echo "moving locales"
cp -a usr/share/locale/* $exp/togo/locale/
rm -rf usr/share/locale/*


for x in `ls usr/man | grep -v man`; do
    rm -r usr/man/$x
done

echo "COMPLETE!"
echo "Size AFTER stripping: `du -sh`"
