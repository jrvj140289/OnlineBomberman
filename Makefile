SFILES = server.c
SDIR = server/
SSRC = ${addprefix ${SDIR}, ${SFILES}}

CFILES = client.c
CDIR = client/
CSRC = ${addprefix ${CDIR}, ${CFILES}}

INCS = includes/

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

CLIENT = client
SRVR = server

${SRVR}: ${SSRC}
	${CC} ${CFLAGS} ${SSRC} -I${INCS} -o ${SRVR}

${CLIENT}: ${CSRC}
	${CC} ${CFLAGS} ${CSRC} -I${INCS} -o ${CLIENT}

all: ${SRVR} ${CLIENT}

clean:
	${RM} ${SRVR}
	${RM} ${CLIENT}

runs: ${SRVR}
	${SRVR}

runc: ${CLIENT}
	${CLIENT}

re: clean all

.PHONY: all clean runs runc re
