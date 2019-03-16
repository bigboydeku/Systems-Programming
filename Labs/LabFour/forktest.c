#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int isPrime(int n);

int main(void)
{
	int userInput;
	int fd;
	char arr[2];
	char buff;
	int a,b;
	int pid;
	pid = fork();
	if (pid == 0)
	{
		sleep(2);
		fd = open("data.txt", O_RDONLY, 0777);
		if (fd == 0) {
			printf("Error, empty file.\n");
			return 0;
		}
		else {
			while((read(fd, &buff, 1)) > 0)
			{
				a *= 10;
				b = buff - '0';				
				a += b;
			}
			if (isPrime(a) == 1){
				printf("Prime number!\n");
				exit(0);
			}
			else {
				printf("Not prime!\n");
				exit(0);
			}
		}
		return 0;
	}
	else
	{
		fd = open("data.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
		printf("Enter an integer from 1 to 15 (inclusive)>> ");
		scanf("%s", &arr);
		userInput = atoi(arr);
	
		if (userInput <= 15 && userInput >= 1)
			write(fd, arr, sizeof(arr));
		else
			printf("Error, not in range.\n");
		close(fd);
		return 0;
	}
	close(fd);
	return 0;
}


int isPrime(int n) {
    int i;
    if (n <= 1) return 0;

    for (i=2; i*i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}