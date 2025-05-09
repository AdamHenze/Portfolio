// ADAM HENZE
// project 4
// 4780 opsys
// Mark Hauschild
// 3/22/2024

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

//sets up chance limits for child
const int chanceIO = 50, chanceTerminate = 990;

//main for user
int main(int argc, char** argv) {
	//convert arg 1 to int
	int secs = atoi(argv[1]);
	int nans = atoi(argv[2]);
	int secsGoal;
	int nansGoal;
	int i;
	int current = 0;

	//shmem
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

	//loop sleep iterations x # of times
	while(1){
		//randoms
		srand((getpid() + current) * 3);
		int randCheck = (rand() % 1000);
		int randInc = (rand() % 10000000) / 2;
		current++;

		//rcv msg
		if ( msgrcv(msqid, &buf, sizeof(msgbuffer), getpid(), 0) == -1) {
	                perror("failed to receive message from parent\n");
	                exit(1);
	        } else {
	        	// output message from parent
	        	printf("Child %d received message: data was %d\n",getpid(), buf.intData);
		}

		printf("Worker PID: %d PPID: %d SysClock(secs): %d SysClock(Nans): %d Termination(Secs): %d Termination(Nans): %d", 
				getpid(), 
				getppid(), 
				*clockSecs, 
				*clockNans, 
				secsGoal, 
				nansGoal );
		printf(" --%d Iterations since starting\n", current);

		//looping checking clock
		//checks clock and random chances
		//returns negative on terminate, positive for full time and IO block
		if(*clockSecs > secsGoal){
			buf.intData *= -1;
		}else if (*clockSecs >= secsGoal && *clockNans >= nansGoal){
			buf.intData *= -1;
		}else if(randCheck > chanceTerminate){
			buf.intData = -1 * (randInc);
		}else if(randCheck < chanceIO){
			buf.intData = randInc;
		}
		//note; if buf unchanged we reutrn full quantum positive, indicating full use without break

                // now send a message back to our parent
                buf.mtype = getppid();
                buf.pData = getpid();
                if (msgsnd(msqid,&buf,sizeof(msgbuffer)-sizeof(long),0) == -1) {
                        perror("msgsnd to parent failed\n");
                        exit(1);
                }

		if(buf.intData <= 0){
			break;
		}
	}// end loop

        printf("Worker PID: %d PPID: %d SysClock(secs): %d SysClock(Nans): %d Termination(Secs): %d Termination(Nans): %d", 
			getpid(), 
			getppid(), 
			*clockSecs, 
			*clockNans, 
			secsGoal, 
			nansGoal );
        printf(" --Terminating after %d iterations\n", current);

        shmdt(clockSecs);
        shmdt(clockNans);

//	printf("exit\n");
	return 0;
}
