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
	rm -f pg_tail

# 必须添加 -g -Wall 用于调试
pg_tail: pg_tail.c
	$(CC) $(CFLAGS) $(INC) $(LIB) -o pg_tail pg_tail.c $(LDFLAGS) -g -Wall

install: pg_tail
	cp pg_tail $(INSTALL)

uninstall:
	rm $(INSTALL)/pg_tail

homebrew: pg_tail
	cp pg_tail $(PREFIX)
