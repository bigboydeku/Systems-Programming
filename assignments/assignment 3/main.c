#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

/*
This program belongs to Denis Nadarevic (104445626) under the University of Windsor for educational purposes.
Do not use this without permission.
*/

int main(int argc, char * arg_v[]) {
	//open file with RD and WR permissions only
	int fd = open("storage", O_RDWR);
	int numberBuff;
	char buff[2], num[3];
	read(fd, buff, 2);
	numberBuff = atoi(buff);
	numberBuff -= 3;
	
	//sprint returns a string num that contains numberBuff
	sprintf(num, "%d", numberBuff);

	//set pointer to the beginning
	lseek(fd, 0, SEEK_SET);
	//write the number into the file
	write(fd, num, strlen(num)); //write the number into the file
	printf("From consumer: current total is %s\n", num);
	close(fd); //close file
	//execute producer file
	execl("./producer","./producer", (char *) 0); //call program
	printf("Error calling program."); //error message if execl does not work
	return 0;
}