/*
Name: Denis Nadarevic
ID: 104445626
This program applies sockets to perform the basic functionality of a secure shell. You can input simple one-argument commands to the server.
This program is not to be used for commercial use and should not be used for another's benefit in any form without permission. This program is under the name Denis Nadarevic,
as a student of the University of Windsor.
*/

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>

int main(int argc, char * arg_v[]) {
	
	char buf[100];
	char ch;
	char buftwo[100]; //temp array to display stuff
	pid_t pid;
	int client;
	
	
	socklen_t len;
	
	//socket address structure information
	struct sockaddr_in servAdd; //used to organize information of server to connect to
	int server = socket(AF_INET, SOCK_STREAM, 0); //create endpoint for communication
	servAdd.sin_family = AF_INET; //domain- address family/format
	servAdd.sin_addr.s_addr = inet_addr(arg_v[1]); //IP address
	servAdd.sin_port = 45565; //port

	connect(server, (struct sockaddr*)&servAdd, sizeof(servAdd)); //connects to server
	
	if ((pid = fork() == 0)) { //child
		while(read(server, &ch, 1)) {
			write(1, &ch, 1);
		}
		kill(getppid(), SIGTERM);
	}
	else { //parent
		
		while(1) {
			sleep(1);
			printf("\nenter shell command: ");
			scanf("%s", buf);
			write (server, buf, strlen(buf) + 1); //write into the server socket 
			read(server, buftwo, 100); //read from the socket
			printf("%s", buftwo); //this is just to print the command inputted, not really necessary
			memset(buftwo, 0, 100);
		}
	}
	exit(0);
}