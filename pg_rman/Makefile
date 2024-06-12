#
# pg_rman: Makefile
#
#  Portions Copyright (c) 2008-2021, NIPPON TELEGRAPH AND TELEPHONE CORPORATION
#
PROGRAM = pg_rman
SRCS = \
	backup.c \
	catalog.c \
	data.c \
	delete.c \
	dir.c \
	init.c \
	parray.c \
	pg_rman.c \
	restore.c \
	show.c \
	util.c \
	validate.c \
	xlog.c \
	pgsql_src/pg_ctl.c \
	pgut/pgut.c \
	pgut/pgut-port.c
OBJS = $(SRCS:.c=.o)
# pg_crc.c and are copied from PostgreSQL source tree.

# XXX for debug, add -g and disable optimization

# flags = `pkg-config`
# glas = $(shell $(pkg-config)  --cflags --libs glib-2.0)
PG_CPPFLAGS = -I$(libpq_srcdir) -lm -g -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include  -lglib-2.0
PG_LIBS = $(libpq_pgport)

REGRESS = init option show delete purge backup backup_management restore restore_checksum backup_from_standby arc_srv_log_management

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

# remove dependency to libxml2 and libxslt
LIBS := $(filter-out -lxml2, $(LIBS))
LIBS := $(filter-out -lxslt, $(LIBS))

$(OBJS): pg_rman.h
