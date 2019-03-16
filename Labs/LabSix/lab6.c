#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


int main(int arg_c, char * arg_v[])
{
	
	if (fork() == 0)
	{
		execl("./mybash", "./mybash", (char*) 0);
		printf("Error!!!");
	} else {
		sleep(1);
		for (int i = 0  ; i < 3 ; i++)
		{
			write(1, "STUDY!", 6);
		}
	}
}