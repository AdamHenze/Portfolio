// ADAM HENZE
// project 5
// 4780 opsys
// Mark Hauschild
// 4/19/2024

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
#include "stdarg.h"


#define PERMS 0644
//structs------------------------------------------
typedef struct msgbuffer {
	long mtype;
	int intData;
	int pData;
	int request;
	int resources[10];
} msgbuffer;

struct FrameTable {
        int page;
        int secondChance;
        int dirtyBit;
} frameTable[256];

struct PCB {
	int check;
	int pid;
	int secs;
	int nans;
	int blocked;
	int blockedSecs;
	int blockedNans;
	int queue;
	int resource;
	int pageTable[64];
} processTable[20];

struct resource {
	int check;
        int pid;
} r1[20],r2[20],r3[20],r4[20],r5[20],r6[20],r7[20],r8[20],r9[20],r10[20];

struct queue {
	int resource;
	int pid;
} q0[20],q1[20],q2[20],blocked[1000];
//protos-------------------------------------------------
void enqueue(struct queue[], int, int);
void help();
int lfprintf(FILE *,const char *, ... );
//funcs------------------------------------------------
void help() {
        printf("-h Help\n");
        printf("USAGE: oss [-h] [-n #] [-s #] [-t #]\n");
        printf("[-h]: Throws help message: No execution.\n");
        printf("[-n]: expects integer value for max total children to launch\n");
        printf("[-s]: expects integer value for number of max simultaneous children\n");
        printf("[-t]: expects integer value for iterations in child loop\n");
}

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
	int option; // arg options
	int i,j; //counter
	int s = 1; //max simultaneous children
	int n = 1; //total children to launch
	int m = 0; //total process so far
	int sc = 0; //current simultaneous children
	int t = 0;; //child iteration count 
	int childInterval = 100;
	const int sh_key = 161803;
	char *fileName = "log.txt";
	int shm_id = shmget( sh_key , sizeof(int) * 2, IPC_CREAT|0666);
        int pcbTimer;
        int timeCheck;
	int qNum;
	int checkSecs = 0;

	//Resources, first array is counter, pointer array points to the 10 resource arrays
	int resources[10] = {0,0,0,0,0,0,0,0,0,0};
	struct resource* resourcesP[10] = {r1,r2,r3,r4,r5,r6,r7,r8,r9,r10};

	//interupt timer
	if (setupinterrupt() == -1) {
			perror("Failed to set up handler for SIGPROF");
			return 1;
	}
	if (setupitimer() == -1) {
			perror("Failed to set up the ITIMER_PROF interval timer");
			return 1;
	}

	//attach to shmem
	if( shm_id <= 0 ){
		printf("Shared Memory get failed\n");
		exit(1);
		}
	int *clockSecs = (int *)(shmat(shm_id,0,0));
	int *clockNans = clockSecs+1;
	*clockSecs = 0;
	*clockNans = 0;

	//setup msg queue
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
        pcbTimer = 0;
	timeCheck = childInterval;

	for(i = 0; i < 1000; i++){
		blocked[i].pid = 0;
		blocked[i].resource = 0;
	}	


	// prime process table entries with 0 values, for some reason they would not always be 0 else
	for(i = 0; i < 20;i++){
                processTable[i].check = 0;
                processTable[i].pid = 0;
                processTable[i].secs = 0;
                processTable[i].nans = 0;
                processTable[i].blocked = 0;
                processTable[i].blockedSecs = 0;
                processTable[i].blockedNans = 0;
		processTable[i].queue = 0;
		q0[i].pid = 0;
		q1[i].pid = 0;
		q2[i].pid = 0;
		blocked[i].pid = 0;
		for(j = 0; j < 64; j++){
			processTable[i].pageTable[j] = 0;
		}
	}

        for(i = 0; i < 256;i++){
                frameTable[i].page = 0;
                frameTable[i].secondChance = 0;
                frameTable[i].dirtyBit = 0;
        }


	//open log
	FILE *fp = fopen(fileName, "w");
	if (fp == NULL) 
    	{ 
        	printf("Could not open file"); 
        	return 0; 
     	}

	//main program while loop, checks total children <= total child limit
	//while(m < n || sc > 0){ // slight edit to allow better child exit
 	while(1){              
		//increment clock by adding to nanosecs of sim clock
		int clockInc = 1000;
		*clockNans += clockInc;
                timeCheck += clockInc;
                pcbTimer += clockInc;

                //Fisr check clock for nanosecs >= 1 sec
		//dec nans to add sec
		if(*clockNans > 1000000000){
                        *clockNans -= 1000000000;
                        *clockSecs += 1;
                }

		//failsafe
		if(sc > 18){
			printf("TOO MANY KIDS BEING MADE\n");
			exit(1);
		};

		// check if child has terminated
		pid_t pid = waitpid(-1,&status,WNOHANG);	

		// if return pid clear entry in process table
		if(pid > 0){
                        printf("Worker PID: %d PPID: %d SysClock(secs): %d SysClock(Nans): %d", pid, getpid(), *clockSecs, *clockNans);
                        printf(" --TERMINATING\n");
			lfprintf(fp,"Worker PID: %d PPID: %d SysClock(secs): %d SysClock(Nans): %d", pid, getpid(), *clockSecs, *clockNans);
        		lfprintf(fp," --TERMINATING\n");
			//printf("%d SC--\n", pid);
			for( i = 0 ; i < 20 ; i++){
				if(processTable[i].pid == pid){
			                processTable[i].check = 0;
			                processTable[i].pid = 0;
			                processTable[i].secs = 0;
			                processTable[i].nans = 0;
			                processTable[i].blocked = 0;
			                processTable[i].blockedSecs = 0;
			                processTable[i].blockedNans = 0;
			                processTable[i].queue = 0;
					processTable[i].resource = 0;
				}//clear resource entries
				if(pid == r1[i].pid){r1[i].pid=0;r1[i].check=0;resources[0]--;}
                                if(pid == r2[i].pid){r2[i].pid=0;r2[i].check=0;resources[1]--;}
				if(pid == r3[i].pid){r3[i].pid=0;r3[i].check=0;resources[2]--;}
                                if(pid == r4[i].pid){r4[i].pid=0;r4[i].check=0;resources[3]--;}
				if(pid == r5[i].pid){r5[i].pid=0;r5[i].check=0;resources[4]--;}
                                if(pid == r6[i].pid){r6[i].pid=0;r6[i].check=0;resources[5]--;}
				if(pid == r7[i].pid){r7[i].pid=0;r7[i].check=0;resources[6]--;}
                                if(pid == r8[i].pid){r8[i].pid=0;r8[i].check=0;resources[7]--;}
				if(pid == r9[i].pid){r9[i].pid=0;r9[i].check=0;resources[8]--;}
                                if(pid == r10[i].pid){r10[i].pid=0;r10[i].check=0;resources[9]--;}
			}
			sc--;
			//break;
		}

		// possibly launch new children 
		//if total launched < max then launch new process
		int childPid = 0;
		if(m < n && sc < s && timeCheck > childInterval && sc < 18){ //addtional check to allow children up to sc == 18
                        timeCheck = 0;
			childPid = fork(); // This is where the child process splits from the parent
			if (childPid == 0) {
			        time_t getTime;
			        srand(getpid() + 1234);

				//init child hang time based on args
				//int childTimeSec = (rand() % (t + 1));
				//int childTimeNan = (rand() % 1000000000);
				printf("Worker PID: %d PPID: %d SysClockSecs: %d SysClockNans: %d  --STARTING\n", getpid(), getppid(), *clockSecs, *clockNans);
				lfprintf(fp,"Worker PID: %d PPID: %d SysClockSecs: %d SysClockNans: %d  --STARTING\n", getpid(), getppid(), *clockSecs, *clockNans);
				char* args[] = {"./worker"};
				//asprintf(&args[1],"%d",childTimeSec);
				//asprintf(&args[2],"%d",childTimeNan);
				args[1] = NULL;
				execvp(args[0], args);
				lfprintf(stderr,"Exec failed ERRNO: %d\n", errno);
				exit(1);	
			} else if(childPid > 0){ // else then parent process, update simul counter and total counter 
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
				//update q0 with newest child
		                //printf("Process %d beginning\n", childPid);
                		//fprintf(fp,"Process %d beginning\n", childPid);
				//enqueue(q0, childPid);
			}
		}

		//if no children running, and launched == max children, break loop end program
		if(sc == 0 && m == n || m > 100){
			printf("CHILD CONDITIONS MET: BREAK\n");
                        lfprintf(fp,"CHILD CONDITIONS MET: BREAK\n");
			break;
		}

		//check pcb timer for half sec increments to print pcb
		if(pcbTimer >= 5000000){
			printf("\nPROCESS TABLE:\n");
			printf("Entry\tCheck\tPID\tSec\tNan\tBlock\tResc\n");
			lfprintf(fp,"\nPROCESS TABLE:\n");
                        lfprintf(fp,"Entry\tCheck\tPID\tSec\tNan\tBlock\tResc\n");
			for( i = 0 ; i < 20 ; i++){
                		printf("%d \t%d \t%d \t%d \t%d \t%d \t%d\n",i, processTable[i].check,processTable[i].pid,processTable[i].secs,(int)(processTable[i].nans/10000),processTable[i].blocked,processTable[i].resource);
                                lfprintf(fp,"%d \t%d \t%d \t%d \t%d \t%d \t%d\n",i, processTable[i].check,processTable[i].pid,processTable[i].secs,(int)(processTable[i].nans/10000),processTable[i].blocked,processTable[i].resource);
			}
			printf("\nFRAME TABLE\n");
                        lfprintf(fp,"\nFRAME TABLE\n");
			for(i=0;i<256;i++){
				printf("Frame %d  ", i + 1);
				printf("\tpage#=%d : ", frameTable[i].page);
				printf("\tSC#=%d : ", frameTable[i].secondChance);
				printf("\tDB#=%d : ", frameTable[i].dirtyBit);
				printf("\n");
			}
			pcbTimer = 0;
			printf("\n");
                        lfprintf(fp,"\n");
			//exit(0);
		}

		//recieving message buffer
		msgbuffer rcvbuf;

		//check blocked for free resources
		for(i = 0;i < 1000;i++){//runthrough block queue
			if(blocked[i].pid > 0){//if find pid
				printf("%d UNBLOCK %d FOR PAGE %d\n",i, blocked[i].pid, blocked[i].resource);
				buf.mtype = blocked[i].pid;
				printf("%d,%d,%d\n",buf.mtype,  blocked[i].pid, blocked[i].resource);
				if(blocked[i].resource > 0){//write
							for(j = 0;j < 20; j++){
								if( processTable[j].pid == blocked[i].pid ){
									processTable[j].pageTable[(blocked[i].resource -1023) / 1024] = blocked[i].resource;
									break;
								}
							}
                                			//processTable[i].pageTable[(rcvbuf.intData -1023) / 1024] = blocked[i].resource;
                                                        for(j = 0; j < 256; j++){
                                                                if(frameTable[j].page == 0){
                                                                        frameTable[j].page = blocked[i].resource;
                                                                        printf("WRITE TO FRAME TABLE\n");
                                                                        printf("FRAME: %d, PAGE: -%d-\n", i, frameTable[j].page);
                                                                        break;
                                                                }
                                                        }
							//buf.mtype = blocked[i].pid;
							printf("%d,%d,%d\n",buf.mtype, blocked[i].pid, blocked[i].resource);
                                                        if (msgsnd(msqid,&buf,sizeof(msgbuffer)-sizeof(long),0) == -1) {
                                                                perror("msgsnd to child failed\n");
                                                                exit(1);
                                                        }
			                                blocked[i].pid = 0;
			                                blocked[i].resource = 0;
				}else if(blocked[i].resource < 0){//read
                                                        for(j = 0;j < 20; j++){
                                                                if( processTable[j].pid == blocked[i].pid ){
                                                                        processTable[j].pageTable[(blocked[i].resource -1023) / 1024] = blocked[i].resource;
                                                                        break;
                                                                }
                                                        }
                                                        //processTable[i].pageTable[(rcvbuf.intData -1023) / 1024] = blocked[i].resource;
                                                        for(j = 0; j < 256; j++){
                                                                if(frameTable[j].page == 0){
                                                                        frameTable[j].page = blocked[i].resource;
                                                                        printf("WRITE TO FRAME TABLE\n");
                                                                        printf("FRAME: %d, PAGE: -%d-\n", i, frameTable[j].page);
                                                                        break;
                                                                }
                                                        }
                                                        //buf.mtype = blocked[i].pid;
							printf("%d,%d,%d\n",buf.mtype, blocked[i].pid, blocked[i].resource);
                                                        if (msgsnd(msqid,&buf,sizeof(msgbuffer)-sizeof(long),0) == -1) {
                                                                perror("msgsnd to child failed\n");
                                                                exit(1);
                                                        }
                                                        blocked[i].pid = 0;
                                                        blocked[i].resource = 0;
				}

				blocked[i].pid = 0;
				blocked[i].resource = 0;
				//break;
			}
			//break;
		}


		//CHECK MAILBOX
		if (msgrcv(msqid, &rcvbuf,sizeof(msgbuffer), getpid(),IPC_NOWAIT) == -1) {
			if(errno == ENOMSG){
				//printf("Got no message so maybe do nothing?\n");
			}else{
				printf("Got an error from msgrcv\n");
				perror("msgrcv");
				exit(1);
			}
		}else{
			//YOU GOT MAIL
   			printf("*** RECIEVED (%d : %d) FROM PROCESS %d\n",rcvbuf.intData, rcvbuf.request, rcvbuf.pData);
			lfprintf(fp,"*** RECIEVED (%d : %d) FROM PROCESS %d\n",rcvbuf.intData, rcvbuf.request, rcvbuf.pData);
			//if intData > 0 then we recieved a request, 1 is demand, 2 is release
			if(rcvbuf.request == 0 && rcvbuf.intData > 0){			
	                        printf("*** RECIEVED READ REQUEST (%d : %d) FROM PROCESS %d\n",rcvbuf.intData, rcvbuf.request, rcvbuf.pData);
	                        lfprintf(fp,"*** RECIEVED READ REQUEST (%d : %d) FROM PROCESS %d\n",rcvbuf.intData, rcvbuf.request, rcvbuf.pData);
				buf.mtype = rcvbuf.pData;
				//if (msgsnd(msqid,&buf,sizeof(msgbuffer)-sizeof(long),0) == -1) {
                                //        perror("msgsnd to child failed\n");
                                //        exit(1);
                                //}
                                for(i = 0; i < 20; i++){
                                        if(rcvbuf.pData == processTable[i].pid){
                                                if(processTable[i].pageTable[(rcvbuf.intData -1023) / 1024] == 0){
                                                        printf("READ BLANKPAGE\n");
                                                        //printf("-%d-\n", frameTable[0].page);

                                                        enqueue(blocked, rcvbuf.pData, rcvbuf.intData * -1);

                                                        //processTable[i].pageTable[(rcvbuf.intData -1023) / 1024] = rcvbuf.intData;
                                                        //frameTable[0].page = rcvbuf.intData;
                                                        //printf("-%d-\n", frameTable[0].page);
							break;
                                                }else{
                                                        printf("READ PAGEFOUND\n");
                                			if (msgsnd(msqid,&buf,sizeof(msgbuffer)-sizeof(long),0) == -1) {
                                			        perror("msgsnd to child failed\n");
                			                        exit(1);
			                                }
							//printf("-%d-\n", frameTable[0].page);
							break;
                                                }
                                        }
                                }
			}else if(rcvbuf.request == 1 && rcvbuf.intData > 0){
                                printf("*** RECIEVED WRITE REQUEST (%d : %d) FROM PROCESS %d\n",rcvbuf.intData, rcvbuf.request, rcvbuf.pData);
                                lfprintf(fp,"*** RECIEVED WRITE REQUEST(%d : %d) FROM PROCESS %d\n",rcvbuf.intData, rcvbuf.request, rcvbuf.pData);
                                buf.mtype = rcvbuf.pData;
				//if (msgsnd(msqid,&buf,sizeof(msgbuffer)-sizeof(long),0) == -1) {
                                //        perror("msgsnd to child failed\n");
                                //        exit(1);
                                //}
				for(i = 0; i < 20; i++){
					if(rcvbuf.pData == processTable[i].pid){
						if(processTable[i].pageTable[(rcvbuf.intData -1023) / 1024] == 0){
							printf("WRITE BLANKPAGE\n");
							//printf("-%d-\n", frameTable[0].page);

							enqueue(blocked, rcvbuf.pData, rcvbuf.intData);
								
							//processTable[i].pageTable[(rcvbuf.intData -1023) / 1024] = rcvbuf.intData;

							//for(j = 0; i < 256; i++){
							//	if(frameTable[j].page == 0){
							//		frameTable[j].page = rcvbuf.intData;
							//		printf("WRITE TO FRAME TABLE\n");
                                                        //		printf("FRAME: %d, PAGE: -%d-\n", i, frameTable[j].page);
							//		break;
							//	}
							//}

							//iprintf("-%d-\n", frameTable[0].page);
							break;
						}else{
							printf("WRITE PAGEFOUND\n");
                                                        if (msgsnd(msqid,&buf,sizeof(msgbuffer)-sizeof(long),0) == -1) {
                                                                perror("msgsnd to child failed\n");
                                                                exit(1);
                                                        }
							//printf("-%d-\n", frameTable[0].page);
							break;
						}
					}
				}
			}
			clockInc == 14000000;
	                *clockNans += clockInc;
	                timeCheck += clockInc;
	                pcbTimer += clockInc;

		}






	}//end of main loop
	//system("ps");
	
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
	//printf("FINAL TOTAL CHILDREN %d\n", m);
	return 0;;
}

void enqueue(struct queue q[], int pid, int r){
	int i;
	for(i = 0; i < 20; i++){
		if( q[i].pid == 0){
			q[i].resource = r;
			q[i].pid = pid;
			return;
		}
	}
}

int lfprintf(FILE *stream,const char *format, ... ) {
    static int lineCount = 0;
    lineCount++;

    if (lineCount > 10000)
        return 1;

    va_list args;
    va_start(args, format);
    vfprintf(stream,format, args);
    va_end(args);

    return 0;
}

