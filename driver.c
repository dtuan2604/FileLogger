#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void helpmenu(char* driver){
	printf("This program is used to test the functionality\n");
	printf("of logging library. This program will read a set\n");
	printf("of messages from a file call 'message.txt' and output\n");
	printf("the respective message in another form.\n");
	printf("%s [-h] [-t sec] [logfile]\n",driver);
	printf("\t [-h]: print help menu.\n");
	printf("\t [-t sec]: specify the time sleep between each logging\n");
	printf("\t [logfile]: specify the output file\n");

}

int validSec(char* sec){
	int size = strlen(sec);
	int i = 0;
	while(i < size){
		if(!isdigit(sec[i]))
			return 0;
		i++;		
	}
	return 1;
}

int main(int argc, char** argv){
	int option;
	int sec;
	while((option = getopt(argc, argv, "ht:")) !=-1){
		switch(option){
			case 'h':
				helpmenu(argv[0]);
				return 1; 
			case 't':
				if(validSec(optarg)){
					sec = atoi(optarg);
					printf("Received sec valued: %d\n",sec);
				}else{
					fprintf(stderr,"Error: %s is not a valid number\n",optarg);
					return EXIT_FAILURE;
				}
				break;
			case '?':
				if(optopt == 't')
					fprintf(stderr,"-%c without argument\n",optopt);
				else
					fprintf(stderr, "Unrecognized option: -%c\n", optopt);
				return EXIT_FAILURE;
			default: 
				printf("From default");
		}
	}
	printf("\nDone while loop");
	return EXIT_SUCCESS;
}
