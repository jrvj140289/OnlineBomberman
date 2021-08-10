#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <SDL2/SDL.h>

#define LENGTH 2048

int running = 1;
int sockfd = 0;
char name[32];

void str_trim_lf (char* arr, int length) {
  int i;
  for (i = 0; i < length; i++) { // trim \n
    if (arr[i] == '\n') {
      arr[i] = '\0';
      break;
    }
  }
}

void send_msg_handler()
{
	char message[LENGTH] = {};
	char buffer[LENGTH + 32] = {};
	
	while(1) {
    	fgets(message, LENGTH, stdin);
    	str_trim_lf(message, LENGTH);

    	if (strcmp(message, "exit") == 0)
			break;
		else 
		{
			//sprintf(buffer, "%s: %s\n", name, message);
      		sprintf(buffer, "%s\n", message);
      		send(sockfd, buffer, strlen(buffer), 0);
    	}
		bzero(message, LENGTH);
    	bzero(buffer, LENGTH + 32);
	}
	running = 0;
}

void recv_msg_handler()
{
	char message[LENGTH] = {};
	while (1)
	{
		if (recv(sockfd, message, LENGTH, 0) > 0)
			printf("%s", message);
		memset(message, 0, sizeof(message));
	}
}

int error(char *str)
{
	return (printf("%s\n", str));
}

int main()
{
	int port = 6000;
	char *ip = "127.0.0.1";
	int sleeping = 60;
	pthread_t send_msg_thread;
	pthread_t recv_msg_thread;
	struct sockaddr_in server_addr;
	
	fgets(name, 32, stdin);
  	//str_trim_lf(name, strlen(name));

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_port = htons(port);

	if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		return (error("ERROR: connect"));
	if(pthread_create(&send_msg_thread, NULL, (void *) send_msg_handler, NULL) != 0)
    	return (error("ERROR: pthread"));
	if(pthread_create(&recv_msg_thread, NULL, (void *) recv_msg_handler, NULL) != 0)
		return (error("ERROR: pthread"));

	while (running)
		sleep(sleeping);
	close(sockfd);
	return (0);
}