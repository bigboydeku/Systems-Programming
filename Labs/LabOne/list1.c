#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(void)
{
	int image = open("list1.txt", O_CREAT | O_RDWR, 0777);
	write(image, "101   GM\tBuick\t2010\n",20);
	write(image, "102   Ford\tLincoln\t2005",23);
	close(image);
	return 0;
}