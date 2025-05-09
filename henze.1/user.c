// ADAM HENZE
// project 1
// 4780 opsys
// Mark Hauschild
// 2/6/2024

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>

//main for user
int main(int argc, char** argv) {
	//convert arg 1 to int
	int x = atoi(argv[1]);
	int i;
	//loop sleep iterations x # of times
	for(i = 0; i < x; i++){
		printf("USER PID: %d\t PPID: %d\t ITERATION %d BEFORE SLEEP\n",getpid(), getppid(), (i + 1));
		sleep(1);
                printf("USER PID: %d\t PPID: %d\t ITERATION %d AFTER SLEEP\n",getpid(), getppid(), (i + 1));
	}
	printf("EXIT PROCESS; USER %d\n", getpid());
	return 0;
}
