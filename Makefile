.POSIX:

PREFIX = /usr/local
CC = gcc


CCFLAGS = -c

debug: CCFLAGS += -g

debug: dwmblocks

dwmblocks: dwmblocks.o
	$(CC) dwmblocks.o -lX11 -o dwmblocks
dwmblocks.o: dwmblocks.c blocks.h funcs.h
	$(CC) $(CCFLAGS) dwmblocks.c
clean:
	rm -f *.o *.gch dwmblocks

install: dwmblocks
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f dwmblocks $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/dwmblocks
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/dwmblocks

.PHONY: clean debug install uninstall
