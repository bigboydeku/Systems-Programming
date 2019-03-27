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
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <signal.h>
#include <sys/stat.h>

int main(int argc, char * arg_v[]) {
	
	char buffer[100];
	int fd[2]; //for piping
	pid_t pid;
	int client;
	socklen_t len;
	struct sockaddr_in servAdd;
	struct sockaddr_in cliAdd;
	
	
	int sd = socket(AF_INET, SOCK_STREAM, 0); //create endpoint for communication
	servAdd.sin_family = AF_INET;
	servAdd.sin_addr.s_addr =  INADDR_ANY;
	servAdd.sin_port = 45565; //port
	
	
	bind(sd, (struct sockaddr*)&servAdd, sizeof(servAdd));  //assign local protocol address to socket
	listen(sd, 5); //server is willing to accept connections now
	
	while(1) {
		
		printf("Waiting for connection...\n");
		
		len = sizeof(cliAdd);
		client = accept(sd, (struct sockaddr*)&cliAdd, &len); //gets first connection in queue of pending connections
		printf("Connected!\n");
		
		
		memset(buffer, 0, 100);
		while(read(client, buffer, 100) > 0) { //while theres something to still read
			printf("received command: %s\n", buffer);
			pipe(fd); //create pipe
			
			if ((pid = fork()) == 0) { //child - writes command 
				close(fd[0]); //close reading end of the pipe for writing
				dup2(fd[1], STDOUT_FILENO);
				execlp(buffer, buffer,(char*)0);
				printf("error!");
				close(fd[1]);
			}
			else {
				char temporary[500]; //holds the command temporarily
				close(fd[1]); //close writing end of the pipe for reading
				int hold = read(fd[0], temporary, sizeof(temporary)); //read returns the number of bytes 
				write(client, temporary, hold); //write the command into the client
			
			}
			memset(buffer, 0, 100);
		}
	}
}