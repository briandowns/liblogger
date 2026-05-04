CC = clang

CFLAGS  = -std=c99 -fPIC -O3 -Wall 
LDFLAGS = -ljansson

NAME = liblogger

UNAME_S := $(shell uname -s)

# respect traditional UNIX path usage
INCDIR := /usr/local/include
LIBDIR  = /usr/local/lib

ifeq ($(UNAME_S),Linux)
$(NAME).so: clean
endif
ifeq ($(UNAME_S),Darwin)
$(NAME).dylib: clean
	$(CC) $(CFLAGS) $(LDFLAGS) -c -dynamiclib -o $@ logger.c
else
	$(CC) -shared -o $@ logger.c $(CFLAGS) $(LDFLAGS)
endif

.PHONY: install
install: 
	cp logger.h $(INCDIR)
ifeq ($(UNAME_S),Darwin)
	cp $(NAME).dylib $(LIBDIR)
else
	cp $(NAME).so $(LIBDIR)
endif

.PHONY: uninstall
uninstall:
	rm -f $(INCDIR)/logger.h
ifeq ($(UNAME_S),Linux)
	rm -f $(INCDIR)/$(NAME).so
endif
ifeq ($(UNAME_S),Darwin)
	rm -f $(INCDIR)/$(NAME).dylib
endif

example: clean
	$(CC) -g -o $@ logger.c example.c $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(NAME).dylib
	rm -f $(NAME).so
	rm -f example
