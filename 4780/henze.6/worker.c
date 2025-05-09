// ADAM HENZE
// project 5
// 4780 opsys
// Mark Hauschild
// 4/19/2024

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
	int request;
	int resources[10];
} msgbuffer;

//sets up chance limits for child
const int chanceResource = 750, chanceTerminate = 950;

//main for user
int main(int argc, char** argv) {

	srand(getpid);

	int i;
	int current = 0;
	int resources[10] = {0,0,0,0,0,0,0,0,0,0};

	//shmem
	int sh_key = 161803;
	int shm_id = shmget(sh_key,sizeof(int)*2,0666);
	if(shm_id == -1 ){
		printf("ERROR IN CHILD SHMGET\n");
	}

	int *clockSecs = (int*)(shmat(shm_id,0,0));
        int *clockNans = clockSecs+1;
	int checkSecs = *clockSecs;
	int checkNans = *clockNans;

	//msg buf
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

	//loop
	while(1){
		//randoms
		//srand((getpid() + current) * 3);
		int randCheck = (rand() % 64);
		int randRead = (rand() % 1000) + 1;
		int randInc = (rand() % 10) + 1;
		int randTerm = (rand() % 1000) + 1;
	

		checkNans = *clockNans;
		checkSecs = *clockSecs;
		current++;
	        printf("Worker PID: %d PPID: %d SysClock(secs): %d SysClock(Nans): %d",getpid(),getppid(),*clockSecs,*clockNans);
		printf(" --%d : CURRENT ITERATION\n", current);
		//TERMINATE ROLL
		if(randTerm >= 990){
                        buf.intData = -1;
                        buf.mtype = getppid();
                        buf.pData = getpid();
                        if (msgsnd(msqid,&buf,sizeof(msgbuffer)-sizeof(long),0) == -1) {
                                perror("msgsnd to parent failed\n");
                                exit(1);
                        }
			break;
		}

		buf.intData = (randCheck * 1024) + 1023;

		if(randRead < 750){
			buf.request = 0;// read
		}else{
                        buf.request = 1;// write
		}

                buf.mtype = getppid();
                buf.pData = getpid();
		//buf.request = 1;
		//buf.intData = randInc;
		//resources[randInc]++;
		if (msgsnd(msqid,&buf,sizeof(msgbuffer)-sizeof(long),0) == -1) {
	        	perror("msgsnd to parent failed\n");
	                exit(1);
	        }
                //rcv msg
                if ( msgrcv(msqid, &buf, sizeof(msgbuffer), getpid(), 0) == -1) {
                	perror("failed to receive message from parent\n");
                        exit(1);
		}
	}// end loop

        //printf("Worker PID: %d PPID: %d SysClock(secs): %d SysClock(Nans): %d", getpid(), getppid(), *clockSecs, *clockNans);
        //printf("after %d iterations --TERMINATING\n", current);

        shmdt(clockSecs);
        shmdt(clockNans);

	return 0;
}
