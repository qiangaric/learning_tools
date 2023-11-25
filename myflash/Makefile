SHELL=/bin/sh

# pgc := $(shell which pg_config)
pgc := "/pgdata/pg15_3/src/bin/pg_config/pg_config"
inc := $(shell $(pgc) --includedir)
lib := $(shell $(pgc) --libdir)

INSTALL=/usr/local/bin
INC=-I$(inc) 
LIB=-L$(lib)
CFLAGS=-Wall -O2
LDFLAGS=-lpq

all: pg_tail

clean:
	rm -f /pgdata/projetcs/cJSON/myflash/binary/flashback

# 必须添加 -g -Wall 用于调试
pg_tail: source/binlogParseGlib.c 
	gcc -g3 -w  `pkg-config --cflags --libs glib-2.0` source/binlogParseGlib.c  -o binary/flashback
#	$(CC) $(CFLAGS) $(INC) $(LIB) --std=c99  -o pg_tail pg_tail01.c $(LDFLAGS)

# 必须添加 -g -Wall 用于调试
# pg_tail: pg_tail.c
# 	$(CC)   -o pg_tail pg_tail01.c 

install: pg_tail
	cp pg_tail $(INSTALL)

uninstall:
	rm $(INSTALL)/pg_tail

homebrew: pg_tail
	cp pg_tail $(PREFIX)