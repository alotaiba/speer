AUTOMAKE_OPTIONS = subdir-objects foreign
CFLAGS = -g -Iinclude -Wall -Wextra -std=gnu99

bin_PROGRAMS = speer
speer_SOURCES = src/core.c src/speer.c

distclean-local::
	-$(RM) -R autom4te*.cache
	-find . \( -name SCCS -o -name BitKeeper -o -name .svn -o -name CVS \
		-o -name .pc -o -name .hg -o -name .git \) -prune -o \
		\( -name '*.orig' -o -name '*.rej' -o -name '*~' -o -name '*.status' \
		-o -name '*.bak' -o -name '.*.orig' -o -name '*.DS_Store' -o -name '*.log' \
		-o -name '.script-config' -o -size 0 -o -name 'install-sh' \
		-o -name '.*.cmd' -o -name 'aclocal.m4' -o -name 'configure' -o -name 'missing' \
		-o -name 'Makefile' -o -name 'compile' -o -name 'depcomp' -o -name 'Makefile.in' \) \
		-type f -print | xargs $(RM)