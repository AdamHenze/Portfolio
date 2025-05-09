// ADAM HENZE
// project 3
// 4780 opsys
// Mark Hauschild
// 3/7/2024

#include<errno.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/time.h>

#define PERMS 0644
typedef struct msgbuffer {
	long mtype;
	int intData;
	int pData;
} msgbuffer;

//help function prototype
void help();
//help function
void help() {
	printf("-h Help\n");
	printf("USAGE: oss [-h] [-n #] [-s #] [-t #]\n");
	printf("[-h]: Throws help message: No execution.\n");
	printf("[-n]: expects integer value for max total children to launch\n");
	printf("[-s]: expects integer value for number of max simultaneous children\n");
	printf("[-t]: expects integer value for iterations in child loop\n");
}

struct PCB {
	int check;
	int pid;
	int secs;
	int nans;
};

static void myhandler(int s) {
	printf("TIME LIMIT EXIT\n");
	exit(1);
}
static int setupinterrupt(void) { /* set up myhandler for SIGPROF */
		struct sigaction act;
		act.sa_handler = myhandler;
		act.sa_flags = 0;
		return (sigemptyset(&act.sa_mask) || sigaction(SIGPROF, &act, NULL));
}
static int setupitimer(void) { /* set ITIMER_PROF for 2-second intervals */
		struct itimerval value;
		value.it_interval.tv_sec = 60;
		value.it_interval.tv_usec = 0;
		value.it_value = value.it_interval;
		return (setitimer(ITIMER_PROF, &value, NULL));
}

int main(int argc, char** argv) {

	int status;
	//variable declares
	int option; // arg options
	int i; //counter
	int s = 1; //max simultaneous children
	int n = 1; //total children to launch
	int m = 0; //total process so far
	int sc = 0; //current simultaneous children
	int t = 0;; //child iteration count 
	
	struct PCB processTable[20];

	int childInterval = 0;

	const int sh_key = 161803;

	char *fileName = "output.txt";

	int shm_id = shmget( sh_key , sizeof(int) * 2, IPC_CREAT|0666);

	if (setupinterrupt() == -1) {
			perror("Failed to set up handler for SIGPROF");
			return 1;
	}
	if (setupitimer() == -1) {
			perror("Failed to set up the ITIMER_PROF interval timer");
			return 1;
	}


	if( shm_id <= 0 ){
		printf("Shared Memory get failed\n");
		exit(1);
		}

	int *clockSecs = (int *)(shmat(shm_id,0,0));
	int *clockNans = clockSecs+1;

	*clockSecs = 0;
	*clockNans = 0;

	msgbuffer buf;
	int msqid;
	key_t key;
	system("touch msgq.txt");
	// get a key for our message queue
	if ((key = ftok("msgq.txt", 1)) == -1) {
		perror("ftok");
		exit(1);
	}
	// create our message queue
	if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {
		perror("msgget in parent");
		exit(1);
	}
//	printf("Message queue set up\n");

	//options switch to handle arguments
	while ((option = getopt(argc, argv, "hn:s:t:i:f:")) != -1) {
		
		
		
		//switch case assigns updated option arguments to params
		switch(option) {
			case 'h':
				//help
     				help();
     				return 0;
     				break;
    			case 'n':
				//max total
				//defaults to one
				n = atoi(optarg);
				continue;
			case 's':
				//max simul
				//defaults to one
				s = atoi(optarg);
     				continue;
			case 't':
				//child time init
				//defaults to one
				t = atoi(optarg);
				continue;
			case 'i':
				//millsec child interval
				childInterval = atoi(optarg);
				continue;
			case 'f':
				fileName = optarg;
				continue;
			default:
     				help();
     				return 0;
   		}
	}

        int pcbTimer = 0;
	int timeCheck = childInterval;

	// prime process table entries with 0 values, for some reason they would not always be 0 else
	for(i = 0; i < 20;i++){
                processTable[i].check = 0;
                processTable[i].pid = 0;
                processTable[i].secs = 0;
                processTable[i].nans = 0;
	}

	FILE *fp = fopen(fileName, "w");
	if (fp == NULL) 
    	{ 
        	printf("Could not open file"); 
        	return 0; 
     	}


	int pcbPos = 0;

	//main program while loop, checks total children <= total child limit
	while(m < n || sc > 0){

                //increment clock by adding to nanosecs of sim clock
		int clockInc;
		if(sc < 1){
			clockInc = 250000000;
		}else{
			clockInc = 250000000 / sc;
		}
		*clockNans += clockInc;
                timeCheck += clockInc;
                pcbTimer += clockInc;


                //Fisr check clock for nanosecs >= 1 sec
                if(*clockNans > 1000000000){
                        *clockNans -= 1000000000;
                        *clockSecs += 1;
                }

		//failsafe
		if(sc > 15){
			printf("TOO MANY KIDS BEING MADE\n");
			exit(1);
		};

		// check if child has terminated
		pid_t pid = waitpid(-1,&status,WNOHANG);	

		// if return pid clear entry in process table
		if(pid > 0){
			//printf("%d SC--\n", pid);
			for( i = 0 ; i < 20 ; i++){
				if(processTable[i].pid == pid){
			                processTable[i].check = 0;
			                processTable[i].pid = 0;
			                processTable[i].secs = 0;
			                processTable[i].nans = 0;
				}
			}
			sc--;
		}
		// possibly launch new children 
		//if total launched < max then launch new process
		int childPid = 0;
		if(m < n && sc < s && timeCheck >= childInterval){
                        timeCheck = 0;
			childPid = fork(); // This is where the child process splits from the parent
			if (childPid == 0) {
			        time_t getTime;
			        srand((unsigned) time(&getTime));

				//init child hang time based on args
				int childTimeSec = (rand() % (t + 1));
				int childTimeNan = (rand() % 1000000000);
				printf("WORKER PID: %d PPID: %d SYSCLOCK: %d SYSCLOCKNANO: %d TERMTIME: %d TERMTIMENANO: %d --STARTING\n", getpid(), getppid(), *clockSecs, *clockNans, *clockSecs + childTimeSec, *clockNans + childTimeNan );
				char* args[] = {"./worker"};
				asprintf(&args[1],"%d",childTimeSec);
				asprintf(&args[2],"%d",childTimeNan);
				args[3] = NULL;
				execvp(args[0], args);
				fprintf(stderr,"Exec failed ERRNO: %d\n", errno);
				exit(1);	
			} else { // else then parent process, update simul counter and total counter 
				sc++;
				m++;
                		for(i = 0;i < 20;i++){
				// FIXED!!! EXECVP NEEDS NULL AS THE FINAL ARG IN ITS ARG ARRAY
                        		if(processTable[i].check == 0 && childPid != 0){
                                		//printf("INSERT INTO PCB\n");
                                		processTable[i].check = 1;
                                		processTable[i].pid = childPid;
                                		processTable[i].secs = *clockSecs;
                                		processTable[i].nans = *clockNans;
                                		break;
                        		}
                		}
			}
		}
		//if no children running, and launched == max children, break loop end program
		if(sc == 0 && m == n){
			printf("CHILD CONDITIONS MET: BREAK\n");
			break;
		}

		//check pcb timer for half sec increments to print pcb
		if(pcbTimer >= 500000000){
			printf("Entry\tCheck\tPID\tStartSec\tStartNan\n");
                        fprintf(fp,"%d\n", pcbTimer);
                        fprintf(fp,"Entry\tCheck\tPID\tStartSec\tStartNan\n");
			for( i = 0 ; i < 20 ; i++){
                	printf("%d \t%d \t%d \t%d \t%d\n",
					i, 
					processTable[i].check,
					processTable[i].pid,
					processTable[i].secs,
					processTable[i].nans);
                        fprintf(fp,"%d \t%d \t%d \t%d \t%d\n",
                                        i,
                                        processTable[i].check,
                                        processTable[i].pid,
                                        processTable[i].secs,
                                        processTable[i].nans);
			}
			pcbTimer = 0;
		}

		//CALC NEXT CHILD
		//p3 walked the pcb as its rr queue
		//will need to impliment new design
		int childCheck = 0;

		for(i = pcbPos;i < 20;i++){
			//printf("%d\n", pcbPos);
			if(processTable[i].check > 0){
				pcbPos = i + 1;
				//SETS MTYPE TO NEXT CHILD TO MSG
				buf.mtype = processTable[i].pid;
				childCheck = 1;
				break;
			}
			pcbPos++;
			if(pcbPos > 19){
				pcbPos = 0;
			}
		}


		//MSG SELECETED CHILD		
		msgbuffer rcvbuf;
		if(childCheck > 0){
			// lets send a message only to child1, not child0
			buf.intData = 200;   // we will give it the pid we are sending to, so we know it received it
			fprintf(fp,"Parent sending message to %d @ %d:%d\n",buf.mtype,*clockSecs,*clockNans);
			if (msgsnd(msqid, &buf, sizeof(msgbuffer)-sizeof(long), 0) == -1) {
				perror("msgsnd to child 1 failed\n");
				exit(1);
			}
			// Then let me read a message, but only one meant for me
			// ie: the one the child just is sending back to me
			if (msgrcv(msqid, &rcvbuf,sizeof(msgbuffer), getpid(),0) == -1) {
				perror("failed to receive message in parent\n");
				exit(1);
			}	
			printf("Parent %d received message: data was %d %d @ %d:%d\n",
					getpid(),
					rcvbuf.intData,
					rcvbuf.pData,
					*clockSecs,
					*clockNans);
                        fprintf(fp,"Parent %d received message: data was %d %d @ %d:%d\n",
                                        getpid(),
                                        rcvbuf.intData,
                                        rcvbuf.pData,
                                        *clockSecs,
                                        *clockNans);

		}
		if(rcvbuf.intData == 0){
			printf("Process %d preparing to end @ %d:%d\n", rcvbuf.pData, *clockSecs,*clockNans);
			fprintf(fp,"Process %d preparing to end @ %d:%d\n", rcvbuf.pData, *clockSecs,*clockNans);
			sc--;	
			//REMOVE FROM PCB
                        for( i = 0 ; i < 20 ; i++){
                                if(processTable[i].pid == rcvbuf.pData){
					processTable[i].check = 0;
                                        processTable[i].pid = 0;
                                        processTable[i].secs = 0;
                                        processTable[i].nans = 0;
                                }
                        }
			wait(0);
			rcvbuf.intData = 1;
		}
		
	}//end of main loop

	// get rid of message queue
	if (msgctl(msqid, IPC_RMID, NULL) == -1) {
		perror("msgctl to get rid of queue in parent failed");
		exit(1);
	}

	// free and detach mem
	shmdt(clockSecs);
	shmdt(clockNans);
	shmctl(shm_id,IPC_RMID,NULL);

	fclose(fp);
	system("rm msgq.txt");

	//count final total children, end program
	printf("FINAL TOTAL CHILDREN %d\n", m);
	return 0;
}

