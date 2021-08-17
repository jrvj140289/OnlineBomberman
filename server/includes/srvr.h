#ifndef SRVR_H
#define SRVR_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/times.h>
#include <sys/select.h>
#include <unistd.h>

#define SERVER_BUSY "Sorry. The server is busy. bye\n"

#define MAX_USERS 20
#define MSG_LEN 4096

#endif
