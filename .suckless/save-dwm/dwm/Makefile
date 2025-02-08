include config/config.mk

SRC = src/drw.c src/dwm.c src/util.c
OBJ = ${SRC:.c=.o}
BIN_DIR = $(HOME)/.local/bin
BIN_DWM = $(BIN_DIR)/dwm
BIN_DWMBLOCKS = $(BIN_DIR)/dwmblocks
MAN = src/dwm.1

CFLAGS += -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os -I/usr/X11R6/include -I/usr/include/freetype2
LDFLAGS += -L/usr/X11R6/lib -lX11 -lXinerama -lfontconfig -lXft -lImlib2 -lXrender

all: dwm dwmblocks

.c.o:
	${CC} -c ${CFLAGS} $< -o $@

dwm: ${OBJ}
	mkdir -p ${BIN_DIR}
	${CC} -o ${BIN_DWM} ${OBJ} ${LDFLAGS}

dwmblocks:
	mkdir -p ${BIN_DIR}
	${CC} -o ${BIN_DWMBLOCKS} patches/dwmblocks.c ${CFLAGS} ${LDFLAGS}

clean:
	rm -f ${BIN_DWM} ${BIN_DWMBLOCKS} src/*.o

install: all
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	if [ -f ${MAN} ]; then \
		sed "s/VERSION/${VERSION}/g" < ${MAN} > ${DESTDIR}${MANPREFIX}/man1/dwm.1; \
		chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1; \
	fi

uninstall:
	rm -f ${BIN_DWM} ${BIN_DWMBLOCKS} \
		${DESTDIR}${MANPREFIX}/man1/dwm.1

.PHONY: all clean install uninstall

