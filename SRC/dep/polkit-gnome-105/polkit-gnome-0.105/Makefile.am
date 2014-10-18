SUBDIRS = src po

ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

EXTRA_DIST = \
	autogen.sh		\
	TODO			\
	HACKING

DISTCHECK_CONFIGURE_FLAGS="--disable-maintainer-mode"

clean-local :
	rm -f *~ po/*~
