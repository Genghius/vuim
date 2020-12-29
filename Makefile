.POSIX:

PREFIX = /usr/local

MYLIBS = ${LIBS} -l curses
MYCPPFLAGS = ${CPPFLAGS} -D _POSIX_C_SOURCE=200809L

all: vuim

vuim: vuim.c
	${CC} -o $@ ${MYCPPFLAGS} ${CFLAGS} ${LDFLAGS} vuim.c ${MYLIBS}

clean:
	rm -f vuim

install: vuim
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp vuim ${DESTDIR}${PREFIX}/bin/vuim

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/vuim

.PHONY: all clean install uninstall
