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
		int randCheck = (rand() % 1000);
		int randInc = (rand() % 10) + 1;

		//++ rand terminate check
		if(*clockNans >= checkNans + 250000000 || *clockSecs > checkSecs){
			checkNans = *clockNans;
			checkSecs = *clockSecs;
			current++;
	                printf("Worker PID: %d PPID: %d SysClock(secs): %d SysClock(Nans): %d",getpid(),getppid(),*clockSecs,*clockNans);
	                printf(" --%d : CURRENT ITERATION\n", current);
			//TERMINATE ROLL
			if(randCheck >= chanceTerminate){
	                        buf.intData = -1;
	                        buf.mtype = getppid();
	                        buf.pData = getpid();
	                        if (msgsnd(msqid,&buf,sizeof(msgbuffer)-sizeof(long),0) == -1) {
	                                perror("msgsnd to parent failed\n");
	                                exit(1);
	                        }
				break;
			}

			//RESOURCE ROLL
			buf.intData = 0;
                        buf.request = 0;
                        buf.mtype = getppid();
                        buf.pData = getpid();
			if(randCheck <= chanceResource){//PASS PERFORM RESOURCE ACTION
				if(randCheck < 600){//60% CHANCE TO GET 15% CHANCE to RLEASE
					if(resources[randInc] < 20){
						buf.request = 1;
						buf.intData = randInc;
						resources[randInc]++;
						if (msgsnd(msqid,&buf,sizeof(msgbuffer)-sizeof(long),0) == -1) {
	                                                perror("msgsnd to parent failed\n");
	                                                exit(1);
	                                        }
                                        	//rcv msg
                                        	if ( msgrcv(msqid, &buf, sizeof(msgbuffer), getpid(), 0) == -1) {
                                        	        perror("failed to receive message from parent\n");
                                        	        exit(1);
                                        	}
					}
				}else{
					for(i=0;i<10;i++){
						if(resources[i] > 0){
							buf.request = 2;
							buf.intData = i;
							resources[i]--;
	                                	        if (msgsnd(msqid,&buf,sizeof(msgbuffer)-sizeof(long),0) == -1) {
	                                	                perror("msgsnd to parent failed\n");
	                                	                exit(1);
	                                	        }
						}
					}
				}
			}		
		}
	}// end loop

        //printf("Worker PID: %d PPID: %d SysClock(secs): %d SysClock(Nans): %d", getpid(), getppid(), *clockSecs, *clockNans);
        //printf("after %d iterations --TERMINATING\n", current);

        shmdt(clockSecs);
        shmdt(clockNans);

	return 0;
}
