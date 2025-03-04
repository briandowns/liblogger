CC = cc

CFLAGS  = -std=c99 -O3 -Wall 
LDFLAGS = -ljansson

NAME = liblogger

UNAME_S := $(shell uname -s)

# respect traditional UNIX path usage
INCDIR := /usr/local/include
LIBDIR  = /usr/local/lib

ifeq ($(UNAME_S),Linux)
$(NAME).so:
	$(CC) -shared -o $@ $(CFLAGS) $(LDFLAGS)
endif
ifeq ($(UNAME_S),Darwin)
$(NAME).dylib:
	$(CC) $(CFLAGS) $(LDFLAGS) -c -dynamiclib -o $@ 
endif

.PHONY: install
install: 
	cp logger.h $(INCDIR)
ifeq ($(UNAME_S),Linux)
	cp logger.h $(INCDIR)
	cp $(NAME).so $(LIBDIR)
endif
ifeq ($(UNAME_S),Darwin)
	cp logger.h $(INCDIR)
	cp $(NAME).dylib $(LIBDIR)
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
