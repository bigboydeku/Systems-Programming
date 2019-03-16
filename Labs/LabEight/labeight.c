
/*
Name: Denis Nadarevic
ID: 104445626
Date: March 13th 2019

*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	int fd[2];
	pipe(fd);
	
	//child process
	if (fork() == 0) {
		close(fd[0]); //close reading end of the pipe
		dup2(fd[1], STDOUT_FILENO); //output from the terminal/kernel new refers to the same file as fd[1]
		execlp(argv[1], argv[1], (char *) 0); //piping response to parent
	}
	
	//parent process
	else {
		int buff = 0;
	
		char output[1000]; //1000 = extra room


		close(fd[1]); //close writing end of the pipe, for reading
    
		int final = open("result.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777); //opens file
	
		buff = read(fd[0], output, sizeof(output));  //read the information from the descriptor into output
		
		write(final, output, buff); //writes the output of the command into the file

		printf("The result of %s is written into result.txt with total %d bytes\n", argv[1], buff); //writes into the terminal

		close(final); //close file
		close(fd[0]); //close reading end of the pipe
		}
	
	return 0;
}











