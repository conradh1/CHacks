CC = cc
BARE_DAEMON_BIN = bared
BARE_DAEMON_SRC = bare_daemon_01.c

all: bared

bared:
    ${CC} ${BARE_DAEMON_SRC} -o ${BARE_DAEMON_BIN}

clean:
    rm -f a.out *.core ${BARE_DAEMON_BIN}
