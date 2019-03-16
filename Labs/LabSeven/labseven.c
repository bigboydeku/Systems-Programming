#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>

static void sig_user(int dummy) {}

int main(int argc, char * arg_v[]) {
	char * buf[3];
	buf[0] = "EXAM! EXAM! EXAM!\n";
	buf[1] = "HELP! HELP! HELP!\n";
	buf[2] = "STUDY! STUDY! STUDY!\n";
	
	signal(SIGUSR1, sig_user);
	
	//create file and open it
	int fd = open(arg_v[1], O_CREAT | O_RDWR | O_TRUNC, 0755);
	printf("Parent opened file: %s\n", arg_v[1]);
	
	pid_t pid = fork();
	
	//first child
	if (pid == 0) {
		sleep(1);
		printf("Parent created first child process: %d\n", getpid());
		kill(getppid(), SIGUSR1);
		pause();
		write(fd, buf[0], strlen(buf[0]));
		printf("%d has written to file: %s\n", getpid(), buf[0]);
		sleep(5);
		kill(getppid(), SIGUSR1);
		exit(0);
	}
	//parent
	else {
		pid_t pidtwo = fork();
		//second child
		if (pidtwo == 0) {
			pause();
			printf("Parent created second child process: %d\n", getpid());
			kill(pid, SIGUSR1);
			pause();
			write(fd, buf[1], strlen(buf[1]));
			printf("%d has written to file: %s\n", getpid(), buf[1]);
			sleep(5);
			kill(getppid(), SIGUSR1);
		}
		//parent
		else {
			pause();
			kill(pidtwo, SIGUSR1);
			pause();
			kill(pidtwo, SIGUSR1);
			pause();
			write(fd, buf[2], strlen(buf[2]));
			printf("Parent has written to file: %s\n", buf[2]);
			sleep(5);
			close(fd);
			signal(SIGUSR1, sig_user);
			printf("Parent has closed the file\n");
		}
	}
}

