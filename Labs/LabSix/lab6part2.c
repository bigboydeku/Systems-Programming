#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


int main(int arg_c, char * arg_v[])
{
	for (int i = 1 ; i < arg_c ; i+=2)
	{
		if (fork() == 0)
		{
			execlp(arg_v[i], arg_v[i], arg_v[i+1],0);
			printf("Error!!!!");
		}
	}
	return 0;
}
	