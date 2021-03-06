include common.mk

all: vex

##
## Step 1: A bunch of defines
##

#ifeq ($(MULTIARCH),1)
LIB_OBJS = $(NORMAL_OBJS) $(MULTIARCH_OBJS)
#else
#LIB_OBJS = $(NORMAL_OBJS) $(SINGLEARCH_OBJS)
#endif

# NOTE: GNU make will automatically set CC and AR, so these conditional
# assignments will never do anything. just here for posterity.
# https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html
CC ?= cc
CC_NATIVE ?= cc
AR ?= ar
RM ?= rm -f

STATIC_LIBRARY_FILE = libvex.a
DYNAMIC_LIBRARY_FILE = libvex.so
EXTRA_CLEAN_FILES = TAG-* auxprogs/genoffsets

CFLAGS := -g -Ipub -Ipriv \
	-Wall -Wmissing-prototypes -Wstrict-prototypes -Wshadow \
	-Wpointer-arith -Wbad-function-cast -Wcast-qual \
	-Wcast-align -Wmissing-declarations \
	-Wwrite-strings -Wformat -Wformat-security \
	-std=gnu99 -fstrict-aliasing -fPIC \
	$(EXTRA_CFLAGS)

# If not debugging, put -g -O2 after any flags we inherit from our invoker
# -O2 vs -O makes a significant difference, at least with gcc4
ifeq ($(DEBUG),1)
CFLAGS += -g
else
CFLAGS += -O0
endif

# gcc requires -malign-double to compile consistently
# old versions of clang error when given this flag
ifneq ($(shell $(CC) 2>&1 | grep -o clang),clang)
CFLAGS += -malign-double
endif

# These are a separate set of defines that compile for parallel environments
#CC = icc
#CFLAGS = -g -Wall -wd981 -wd279 -wd1287 -wd869 -wd111 -wd188 -wd186
# 981: operands are evaluated in unspecified order
# 279: controlling expression is constant
# 1287: invalid attribute for parameter
# 869: parameter "..." was never referenced
# 111: statement is unreachable
# 188: enumerated type mixed with another type
# (the above are for icc 8.0 -- 8.0.0.55 I think)
# 186: pointless comparison of unsigned integer with zero

# kludge: stops V biarch builds screwing up at -j 2 or above
# The Right fix is to autoconf/automake-ise vex.
.NOTPARALLEL:



##
## Step 2: Define some build rules
##

pub/libvex_guest_offsets.h: $(PUB_HEADERS) auxprogs/genoffsets.c
	$(CC_NATIVE) $(CFLAGS) -o auxprogs/genoffsets auxprogs/genoffsets.c
	auxprogs/genoffsets > pub/libvex_guest_offsets.h

%.o: %.c $(ALL_HEADERS)
	$(CC) -c -o $@ $(CFLAGS) $<

$(STATIC_LIBRARY_FILE): $(LIB_OBJS)
	$(RM) $@
	$(AR) -crs $@ $^

$(DYNAMIC_LIBRARY_FILE): $(LIB_OBJS)
	$(CC) -o $@ -shared $(CFLAGS) $^



##
## Step 3: a bunch of extra build rules that valgrind would like to use
##

minidist:
	rm -f vex--minidist-2005MMDD.tar
	tar cf vex--minidist-2005MMDD.tar $(PUB_HEADERS) $(PRIV_HEADERS) \
		Makefile-gcc Makefile conf_unix.mk			\
		`echo $(LIB_OBJS) | sed "s/\.o/\.c/g"`
	@echo 
	@echo minidist done, size follows:
	@ls -l vex--minidist-2005MMDD.tar
	@echo

# The idea with these TAG-s is to mark the flavour of libvex.a 
# most recently built, so if the same target is re-requested, we
# don't rebuild everything, but if a different one is requested
# then we scrub everything and start over.

libvex-x86-linux.a: TAG-x86-linux libvex.a
	mv -f libvex.a libvex-x86-linux.a
TAG-x86-linux:
	if [ ! -f TAG-x86-linux ] ; then rm -f $(LIB_OBJS) TAG-* libvex.a ; fi
	touch TAG-x86-linux

libvex-amd64-linux.a: TAG-amd64-linux libvex.a
	mv -f libvex.a libvex-amd64-linux.a
TAG-amd64-linux:
	if [ ! -f TAG-amd64-linux ] ; then rm -f $(LIB_OBJS) TAG-* libvex.a ; fi
	touch TAG-amd64-linux

libvex-ppc32-linux.a: TAG-ppc32-linux libvex.a
	mv -f libvex.a libvex-ppc32-linux.a
TAG-ppc32-linux:
	if [ ! -f TAG-ppc32-linux ] ; then rm -f $(LIB_OBJS) TAG-* libvex.a ; fi
	touch TAG-ppc32-linux

libvex-ppc64-linux.a: TAG-ppc64-linux libvex.a
	mv -f libvex.a libvex-ppc64-linux.a
TAG-ppc64-linux:
	if [ ! -f TAG-ppc64-linux ] ; then rm -f $(LIB_OBJS) TAG-* libvex.a ; fi
	touch TAG-ppc64-linux

libvex-mips-linux.a: TAG-mips32-linux libvex.a
	mv -f libvex.a libvex-mips32-linux.a
TAG-mips-linux:
	if [ ! -f TAG-mips32-linux ] ; then rm -f $(LIB_OBJS) TAG-* libvex.a ; fi
	touch TAG-mips32-linux

libvex-ppc32-aix5.a: TAG-ppc32-aix5 libvex.a
	mv -f libvex.a libvex-ppc32-aix5.a
TAG-ppc32-aix5:
	if [ ! -f TAG-ppc32-aix5 ] ; then rm -f $(LIB_OBJS) TAG-* libvex.a ; fi
	touch TAG-ppc32-aix5

libvex-ppc64-aix5.a: TAG-ppc64-aix5 libvex.a
	mv -f libvex.a libvex-ppc64-aix5.a
TAG-ppc64-aix5:
	if [ ! -f TAG-ppc64-aix5 ] ; then rm -f $(LIB_OBJS) TAG-* libvex.a ; fi
	touch TAG-ppc64-aix5

libvex-x86-darwin.a: TAG-x86-darwin libvex.a
	mv -f libvex.a libvex-x86-darwin.a
TAG-x86-darwin:
	if [ ! -f TAG-x86-darwin ] ; then rm -f $(LIB_OBJS) TAG-* libvex.a ; fi
	touch TAG-x86-darwin

libvex-amd64-darwin.a: TAG-amd64-darwin libvex.a
	mv -f libvex.a libvex-amd64-darwin.a
TAG-amd64-darwin:
	if [ ! -f TAG-amd64-darwin ] ; then rm -f $(LIB_OBJS) TAG-* libvex.a ; fi
	touch TAG-amd64-darwin

libvex-arm64-linux.a: TAG-arm64-linux libvex.a
	mv -f libvex.a libvex-arm64-linux.a
TAG-arm64-linux:
	if [ ! -f TAG-arm64-linux ] ; then rm -f $(LIB_OBJS) TAG-* libvex.a ; fi
	touch TAG-arm64-linux

# Empty, needed for Valgrind
install:

scratch: clean all

vex: $(STATIC_LIBRARY_FILE) $(DYNAMIC_LIBRARY_FILE)

clean:
	$(RM) $(GEN_HEADERS) $(NORMAL_OBJS) $(SINGLEARCH_OBJS) $(MULTIARCH_OBJS) \
		$(STATIC_LIBRARY_FILE) $(DYNAMIC_LIBRARY_FILE) \
		$(EXTRA_CLEAN_FILES)
