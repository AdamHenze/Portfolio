// ADAM HENZE
// project 2
// 4780 opsys
// Mark Hauschild
// 3/7/2024

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>

#define PERMS 0644
typedef struct msgbuffer {
	long mtype;
	int intData;
	int pData;
} msgbuffer;

//main for user
int main(int argc, char** argv) {
	//convert arg 1 to int
	int secs = atoi(argv[1]);
	int nans = atoi(argv[2]);

	int secsGoal;
	int nansGoal;

	int i;

	int current = 0;
	int sh_key = 161803;
	int shm_id = shmget(sh_key,sizeof(int)*2,0666);
	if(shm_id == -1 ){
		printf("ERROR IN CHILD SHMGET\n");
	}

	int checksecs;
        int *clockSecs = (int*)(shmat(shm_id,0,0));
        int *clockNans = clockSecs+1;

        secsGoal = secs + *clockSecs;
        nansGoal = nans + *clockNans;

	msgbuffer buf;
	buf.mtype = 1;
	int msqid = 0;
	key_t key;

	// get a key for our message queue
	if ((key = ftok("msgq.txt", 1)) == -1) {
		perror("ftok");
		exit(1);
	}

	// create our message queue
	if ((msqid = msgget(key, PERMS)) == -1) {
		perror("msgget in child");
		exit(1);
	}

	//loop sleep iterations x # of times
	while(1){
		current++;
		if ( msgrcv(msqid, &buf, sizeof(msgbuffer), getpid(), 0) == -1) {
	                perror("failed to receive message from parent\n");
	                exit(1);
	        } else {
	        	// output message from parent
	        	//printf("Child %d received message: data was %d\n",getpid(), buf.intData);
		}

			printf("WORKER PID: %d PPID: %d SYSCLOCK: %d SYSCLOCKNANO: %d TERMTIME: %d TERMTIMENANO: %d \n", getpid(), getppid(), *clockSecs, *clockNans, secsGoal, nansGoal );
			printf("--%d Iterations since starting\n", current);

		//looping checking clock
		if(*clockSecs > secsGoal){
			buf.intData = 0;
			//break;
		}else if (*clockSecs >= secsGoal && *clockNans >= nansGoal){
			buf.intData = 0;
			//break;
		}else{
			buf.intData = 1;
		}

                // now send a message back to our parent
                buf.mtype = getppid();
                buf.pData = getpid();

                if (msgsnd(msqid,&buf,sizeof(msgbuffer)-sizeof(long),0) == -1) {
                        perror("msgsnd to parent failed\n");
                        exit(1);
                }

		if(buf.intData == 0){
			break;
		}
	}// end loop

        printf("WORKER PID: %d PPID: %d SYSCLOCK: %d SYSCLOCKNANO: %d TERMTIME: %d TERMTIMENANO: %d ", getpid(), getppid(), *clockSecs, *clockNans, secsGoal, nansGoal );
        printf("--Terminationg after %d iterations\n", current);

        shmdt(clockSecs);
        shmdt(clockNans);

//	printf("exit\n");
	return 0;
}
