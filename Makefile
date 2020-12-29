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
	mkdir -p ${DESTDIR}${PREFIX}/share/man/man1
	cp vuim.1 ${DESTDIR}${PREFIX}/share/man/man1/vuim.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/vuim
	rm -f ${DESTDIR}${PREFIX}/share/man/man1/vuim.1

.PHONY: all clean install uninstall
