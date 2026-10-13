#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>

void help() {
  printf("Please enter as './mathwait filename.txt # # # ...'\n");
  printf("The options for this program are: \n");
  printf("-h Help\n");
  printf("-n Set next int as pair search value.\n");
}

//found it much cleaner to push integer checking out to a function, main was getting long
bool intcheck(char **checkme, int pos){
	int j;
	for(j = 0; j < strlen(checkme[pos]); j++){
		// check for the first character of argv as '-', this allows negative ints
		if((checkme[pos][j] == '-') && (j == 0)){
			// continue on to next loop interation
			continue;
		}
		// check for non integer inputs of characters in argv, except as above
		if(isdigit(checkme[pos][j]) == 0){
			// end program, call help for correct user input
			printf("Non integer error\n");
			return false;
		}
	}
	return true;
}
