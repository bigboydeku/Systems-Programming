#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *arg_v[]) 
{
    int pidOne = fork();

    if (pidOne == 0)
    {
      int pidFour = fork();
      if (pidFour == 0)
      {
        int sleepingTime = atoi(arg_v[4]);
        sleep(sleepingTime);
        printf("Process Four ID: %d\n", getpid());
      }
      else {
        int pidFive = fork();
        if (pidFive == 0)
        {
          int time = atoi(arg_v[5]);
          sleep(time);
          printf("Process Five ID: %d\n", getpid());  
        }
        else {
          int time = atoi(arg_v[2]);
        sleep(time);
        printf("Process Two ID: %d\n", getpid());
        }
      }
    }
  else {
    int pidThree = fork();
    if (pidThree == 0)
    {
      int pidSix = fork();
      if (pidSix == 0)
      {
        int time = atoi(arg_v[6]);
        sleep(time);
        printf("Process Six ID: %d\n", getpid()); 
      }
      else {
      	int time = aotoi(arg_v[7]);
      	sleep(time);
      	printf("Process Seven ID: %d\n", getpid());
      }
    }
    else {
      else {
      int time = aotoi(arg_v[3]);
      sleep(time);
      printf("Process Three ID: %d\n", getpid());
    }
    }
  }
		
    sleep(5);
    return 0;
}