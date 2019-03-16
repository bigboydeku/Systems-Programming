#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int pid = fork();
	if (pid == 0) {
		execl("./mybash","./mybash", (char *)0);
		printf("Error.");
	}
	else {
		sleep(1);
		printf("\nSTUDY!STUDY!STUDY!\n");
		
	}
}