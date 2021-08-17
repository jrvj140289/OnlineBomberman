# Server info
SRVR_FS = server.c
SRVR_DIR = server
SRVR_SRC := $(SRVR_FS:%=SRVR_DIR/src/%)
SRVR_BD := $(SRVR_FS:%.c=SRVR_DIR/obj/%.o)

# Client info
CLNT_FS = client.c
CLNT_DIR = client
CLNT_SRC := $(CLNT_FS:%=$(CLNT_DIR)/src/%)
CLNT_BD := $(CLNT_FS:%.c=$(CLNT_DIR)/obj/%.o)

# General info
INC = includes/

# Compiler info
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Programs names
CLIENT = bbman
SERVER = host_bbman

# Build step for client
$(CLNT_BD): $(CLNT_SRC)
	$(CC) $(CFLAGS) -I$(INC) -I$(CLNT_DIR)/$(INC) -c $< -o $@

$(CLIENT): $(CLNT_BD)
	$(CC) $(CFLAGS) $(CLNT_BD) $(CLNT_DIR)/main.c -I$(INC) -I$(CLNT_DIR)/$(INC)

# Build step for server
$(SRVR_BD): $(SRVR_SRC)
	$(CC) $(CFLAGS) -I$(INC) -I$(CLNT_DIR)/$(INC) -c $< -o $@

$(SERVER): $(SRVR_BD)
	$(CC) $(CFLAGS) $(SRVR_BD) $(SRVR_DIR)/main.c -I$(INC) -I$(SRVR_DIR)/$(INC)

all: ${SRVR} ${CLIENT}

clean:
	${RM} ${CLNT_BD}
	${RM} ${SRVR_BD}

fclean: clean
	${RM} ${CLIENT}
	${RM} ${SERVER}

runc: ${CLIENT}
	./${CLIENT}

runs: ${SRVR}
	./${SRVR}

re: fclean all

.PHONY: all clean fclean runs runc re
