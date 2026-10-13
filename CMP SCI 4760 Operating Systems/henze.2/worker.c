// ADAM HENZE
// project 2
// 4780 opsys
// Mark Hauschild
// 2/22/2024

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>

//main for user
int main(int argc, char** argv) {
	//convert arg 1 to int
	int secs = atoi(argv[1]);
	int nans = atoi(argv[2]);

	int secsGoal;
	int nansGoal;


	int i;

	int sh_key = 161803;

	int shm_id = shmget(sh_key,sizeof(int)*2,0666);

	if(shm_id == -1 ){
		printf("ERROR IN CHILD SHMGET\n");
	}

	int *clockSecs = (int*)(shmat(shm_id,0,0));
	int *clockNans = clockSecs+1;

	secsGoal = secs + *clockSecs;
	nansGoal = nans + *clockNans;

	//printf("%d + %d\n", secs, *clockSecs);
        //printf("%d + %d\n", nans, *clockNans);

	//printf("SEC GOAL: \t%d\n",secsGoal);
	//printf("NANO GOAL: \t%d\n",nansGoal);


	//*clockSecs += 1;
	//*clockNans += 2;
        //printf("XXX\n");
	int checksecs = *clockSecs;
	int current = 0;
	//loop sleep iterations x # of times
	while(1){

		if(*clockSecs > checksecs){
			checksecs = *clockSecs;
			current++;	
			printf("WORKER PID: %d PPID: %d SYSCLOCK: %d SYSCLOCKNANO: %d TERMTIME: %d TERMTIMENANO: %d \n", getpid(), getppid(), *clockSecs, *clockNans, secsGoal, nansGoal );
			printf("--%d secs since starting\n", current);
		}
		//printf("XXX\n");
		//sleep(1);
        	//clockSecs = (int*)(shmat(shm_id,0,0));
        	//clockNans = clockSecs+1;
	        //printf("%d, %d\n", *clockSecs, *clockNans);
		//looping checking clock
		if(*clockSecs > secsGoal){
                        printf("WORKER PID: %d PPID: %d SYSCLOCK: %d SYSCLOCKNANO: %d TERMTIME: %d TERMTIMENANO: %d --ENDING\n", getpid(), getppid(), *clockSecs, *clockNans, secsGoal, nansGoal );
			break;
		}else if (*clockSecs >= secsGoal && *clockNans >= nansGoal){
                        printf("WORKER PID: %d PPID: %d SYSCLOCK: %d SYSCLOCKNANO: %d TERMTIME: %d TERMTIMENANO: %d --ENDING\n", getpid(), getppid(), *clockSecs, *clockNans, secsGoal, nansGoal );
                        break;
		}
		
	
		//printf("USER PID: %d\t PPID: %d\t ITERATION %d BEFORE SLEEP\n",getpid(), getppid(), (i + 1));
		//sleep(1);
                //printf("USER PID: %d\t PPID: %d\t ITERATION %d AFTER SLEEP\n",getpid(), getppid(), (i + 1));
	}

	//printf("%d ... %d\n", *clockSecs, *clockNans);
	//printf("EXIT PROCESS; USER %d\n", getpid());

        shmdt(clockSecs);
        shmdt(clockNans);

	return 0;
}
