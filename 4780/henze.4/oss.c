// ADAM HENZE
// project 4
// 4780 opsys
// Mark Hauschild
// 3/22/2024

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
//structs------------------------------------------
typedef struct msgbuffer {
	long mtype;
	int intData;
	int pData;
} msgbuffer;

struct PCB {
	int check;
	int pid;
	int secs;
	int nans;
	int blocked;
	int blockedSecs;
	int blockedNans;
	int queue;
} processTable[20];

struct queue {
	int pid;
} q0[20],q1[20],q2[20],blocked[20];
//protos-------------------------------------------------
int nextChild();
void enqueue(struct queue[], int);
int dequeue(struct queue[]);
void help();
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
	int childInterval = 0;
	const int sh_key = 161803;
	char *fileName = "log.txt";
	int shm_id = shmget( sh_key , sizeof(int) * 2, IPC_CREAT|0666);
        int pcbTimer;
        int timeCheck;
	int qNum;

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
	}

	//open log
	FILE *fp = fopen(fileName, "w");
	if (fp == NULL) 
    	{ 
        	printf("Could not open file"); 
        	return 0; 
     	}

	//main program while loop, checks total children <= total child limit
	while(m < n || sc > 0){
                
		//increment clock by adding to nanosecs of sim clock
		int clockInc = 1000;
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
			                processTable[i].blocked = 0;
			                processTable[i].blockedSecs = 0;
			                processTable[i].blockedNans = 0;
			                processTable[i].queue = 0;
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
			        srand(getpid() + 1234);

				//init child hang time based on args
				int childTimeSec = (rand() % (t + 1));
				int childTimeNan = (rand() % 1000000000);
				printf("WORKER PID: %d PPID: %d SYSCLOCK: %d SYSCLOCKNANO: %d TERMTIME: %d TERMTIMENANO: %d --STARTING\n", 
						getpid(), 
						getppid(), 
						*clockSecs, 
						*clockNans, 
						*clockSecs + childTimeSec, 
						*clockNans + childTimeNan );
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
				//update q0 with newest child
		                printf("Process %d entering Q0\n", childPid);
                		fprintf(fp,"Process %d entering Q0\n", childPid);
				enqueue(q0, childPid);
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
		//get next pid, gets 0 if none
		buf.mtype = nextChild();
                //gets current queue of child to address, checks for pcb match
		for(i = 0; i < 20; i++){
                        if(processTable[i].pid == buf.mtype){
                                qNum = processTable[i].queue;
                        }
                }

		//checks for match in pcb with current child, increments childs queue, 
		//as child was automatically enqueued to the next queue once grabbed
		//moved here to keep nextchild func clean
        	for( i = 0; i < 20; i++){
                	if(buf.mtype == processTable[i].pid && buf.mtype > 0){
                        	if( processTable[i].queue < 2){
                        	        processTable[i].queue += 1;
                	        }
        	        }
	        }

		//MSG SELECETED CHILD		
		msgbuffer rcvbuf;
		if(buf.mtype > 0){
			// send message to child, data based on queue
			if(qNum == 0){
				buf.intData = 10000000;
			}else if(qNum == 1){
				buf.intData = 20000000;
			}else{
				buf.intData = 40000000;
			}
                        printf("Parent sending message to %d from Q%d @ %d:%d\n", buf.mtype, qNum,*clockSecs,*clockNans);
			fprintf(fp,"Parent sending message to %d from Q%d @ %d:%d\n", buf.mtype, qNum,*clockSecs,*clockNans);
			if (msgsnd(msqid, &buf, sizeof(msgbuffer)-sizeof(long), 0) == -1) {
				perror("msgsnd to child 1 failed\n");
				exit(1);
			}
			//recieve message back from child
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

		//begin handling based on data from child
		//if time usef > quantum and positive, then entered IO block
		if(rcvbuf.intData < buf.intData && rcvbuf.intData > 0){
			printf("Process %d entering BLOCKED condition @ %d:%d\n", rcvbuf.pData, *clockSecs,*clockNans);
                        fprintf(fp,"Process %d entering BLOCKED condition @ %d:%d\n", rcvbuf.pData, *clockSecs,*clockNans);
                        //setup blocked conditions, remove from queues, based on pid matches
			for( i = 0 ; i < 20 ; i++){
                                if(processTable[i].pid == rcvbuf.pData){
                                        //processTable[i].check = 0;
                                        //processTable[i].pid = 0;
                                        //processTable[i].secs = 0;
                                        //processTable[i].nans = 0;
                                        processTable[i].blocked = 1;
                                        processTable[i].blockedSecs = *clockSecs + 1;
                                        processTable[i].blockedNans = *clockNans;
                                        processTable[i].queue = 3;
					//enqueue in blocked
					//note: skips returns of zero, prevents infinte loops once rcvbuf reset to 0
					enqueue(blocked, processTable[i].pid);
                                }
                                if(q0[i].pid == rcvbuf.pData){
                                        q0[i].pid = 0;
                                }
                                if(q1[i].pid == rcvbuf.pData){
                                        q1[i].pid = 0;
                                }
                                if(q2[i].pid == rcvbuf.pData){
                                        q2[i].pid = 0;
                                }
				//inc clock
				clockInc = rcvbuf.intData;
                        	*clockNans += clockInc;
                        	timeCheck += clockInc;
                        	pcbTimer += clockInc;
				//now removed from q0 q1 and q2, in blocked queue
                        }
			//reset buf
			rcvbuf.intData = 0;
		}else if(rcvbuf.intData < 0){
			//if any negative value returned then process terminated either on time or prematurely.
			printf("Process %d preparing to end @ %d:%d\n", rcvbuf.pData, *clockSecs,*clockNans);
			fprintf(fp,"Process %d preparing to end @ %d:%d\n", rcvbuf.pData, *clockSecs,*clockNans);
			sc--;	
			//REMOVE FROM PCB and queues
                        for( i = 0 ; i < 20 ; i++){
                                if(processTable[i].pid == rcvbuf.pData){
					processTable[i].check = 0;
                                        processTable[i].pid = 0;
                                        processTable[i].secs = 0;
                                        processTable[i].nans = 0;
                			processTable[i].blocked = 0;
                			processTable[i].blockedSecs = 0;
                			processTable[i].blockedNans = 0;
                			processTable[i].queue = 0;
				}
				//note: because processes are auto enqueued to the next queue, 
				//they should alwyas be removed from the back of a queue, keeping queues compressed
				if(q0[i].pid == rcvbuf.pData){
					q0[i].pid = 0;
				}
                                if(q1[i].pid == rcvbuf.pData){
                                        q1[i].pid = 0;
                                }
                                if(q2[i].pid == rcvbuf.pData){
                                        q2[i].pid = 0;
                                }
                        }
			//inc clock wait for terminate reset buf
                        clockInc = rcvbuf.intData * -1;
                        *clockNans += clockInc;
                        timeCheck += clockInc;
                        pcbTimer += clockInc;
			wait(0);
			rcvbuf.intData = 0;
		}else{
			//if here recieved full quantum back, inc clock
			clockInc = rcvbuf.intData;
                	*clockNans += clockInc;
                	timeCheck += clockInc;
                	pcbTimer += clockInc;
		}

		//check blocked queue for unblock conditions
		for(i = 0;i < 20; i++){
			if(processTable[i].blocked > 0){
				//if over secs
				if(processTable[i].blockedSecs < *clockSecs){
					printf("Process %d leaving BLOCKED condition @ %d:%d\n", processTable[i].pid, *clockSecs,*clockNans);
                        		fprintf(fp,"Process %d leaving BLOCKED condition @ %d:%d\n", processTable[i].pid, *clockSecs,*clockNans);
					processTable[i].blocked = 0;
                                        processTable[i].blockedSecs = 0;
                                        processTable[i].blockedNans = 0;
                                        processTable[i].queue = 0;
					//if conditions good, remove from blocked enqueue to q0, same below
					enqueue(q0, processTable[i].pid);
					for(j = 0; j < 20; j++){
						if(blocked[j].pid == processTable[i].pid){
							blocked[j].pid = 0;
							break;
						}
					}
				//if over nans and equal secs
				}else if(processTable[i].blockedSecs <= *clockSecs && processTable[i].blockedNans < *clockNans){
                                        printf("Process %d leaving BLOCKED condition @ %d:%d\n", processTable[i].pid, *clockSecs,*clockNans);
                                        fprintf(fp,"Process %d leaving BLOCKED condition @ %d:%d\n", processTable[i].pid, *clockSecs,*clockNans);
                                        processTable[i].blocked = 0;
                                        processTable[i].blockedSecs = 0;
                                        processTable[i].blockedNans = 0;
                                        processTable[i].queue = 0;
                                        enqueue(q0, processTable[i].pid);
                                        for(j = 0; j < 20; j++){
                                                if(blocked[j].pid == processTable[i].pid){
                                                        blocked[j].pid = 0;
                                                        break;
                                                }
                                        }
				}
			}
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
	return 0;;
}

int dequeue(struct queue q[]){
	int pid, i;
	pid = q[0].pid;
	for(i = 0; i < 20; i++){
		if(q[i].pid > 0){
			q[i].pid = q[i + 1].pid;
		}
	}
	return pid;
}

void enqueue(struct queue q[], int pid){
	int i;
	for(i = 0; i < 20; i++){
		if( q[i].pid == 0){
			q[i].pid = pid;
			return;
		}
	}
}

int nextChild(){
	int pid, i;
	if( q0[0].pid > 0 ){
		pid = dequeue(q0);
		enqueue(q1,pid);
		//printf("Process %d entering Q1\n", q0[i].pid);
                //fprintf(fp,"Process %d entering Q1\n", q0[i].pid);
	} else if( q1[0].pid > 0 ){
                pid = dequeue(q1);
		enqueue(q2,pid);
                //printf("Process %d entering Q2\n", q0[i].pid);
                //fprintf(fp,"Process %d entering Q2\n", q0[i].pid);
        } else if( q2[0].pid > 0 ){
                pid = dequeue(q2);
		enqueue(q2,pid);
	} else {
		pid =  0;
	}		
	return pid;
}
