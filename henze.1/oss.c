// ADAM HENZE
// project 1
// 4780 opsys
// Mark Hauschild
// 2/6/2024

#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

int main(int argc, char** argv) {

	//variable declares
	int option; // arg options
	int i; //counter
	int s = 1; //max simultaneous children
	int n = 1; //total children to launch
	int m = 0; //total process so far
	int sc = 0; //current simultaneous children
	char* t = "1"; //child iteration count 


	//options switch to handle arguments
	while ((option = getopt(argc, argv, "hn:s:t:")) != -1) {
		//switch case assigns updated option arguments to params
		switch(option) {
			case 'h':
     				help();
     				return 0;
     				break;
    			case 'n':
				//defaults to one
				n = atoi(optarg);
				continue;
			case 's':
				//defaults to one
				s = atoi(optarg);
     				continue;
			case 't':
				//defaults to one
				t = optarg;
				continue;
			default:
     				help();
     				return 0;
   		}
	}

	//main program while loop, checks total children <= total child limit
	while(m <= n){
		//if total launched < max then launch new process
		if(m < n){
			pid_t childPid = fork(); // This is where the child process splits from the parent
			if (childPid == 0) {

				//IF I REMOVE THIS PRINT STATEMENT THEN EXECVP WILL FAIL TO EXECUTE
				// I HAVE NO IDEA WHY THIS OCCURS
				printf("CHILD PROCESS CREATED; PID: %d\tPPID: %d\n", getpid(), getppid());

				char* args[] = {"./user", t};
				
				execvp(args[0], args);
				
				fprintf(stderr,"Exec failed, terminating\n");
				exit(1);	
			} else { // else then parent process, update simul counter and total counter 
				sc++;
				m++;
			}
		}

		//if no children running, and launched == max children, break loop end program
		if(sc == 0 && m == n){
			break;
		}
		//if simul children at limit, and more process to run, wait 
                if(sc == s && m < n){
                        wait(0);
                        sc--;
                }
		//if at max children to launch, but still have children running, wait
		//the two wait checks were seperated to check error handling and flag waits independently
		if(sc > 0 && m == n ){
			wait(0);
			sc--;
		}

	}
	//wait for final children to end 
	wait(0);
	//count final total children, end program
	printf("FINAL TOTAL CHILDREN %d\n", m);
	return 0;
}

