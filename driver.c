#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "log.h"
#include <errno.h>

extern int errno;
char* message[] = {"I This program has bug",
			"W Bug on line 3",
			"E Cannot find an error",
			"W Another bug on line 6",
			"I Need to update C version",
			"F The program has to be stopped"};
#define n_array (sizeof(message)/sizeof(char*))

void helpmenu(char* driver){
	printf("This program is used to test the functionality\n");
	printf("of logging library. This program will generate a set\n");
	printf("of messages and output the respective message in another\n");
	printf("form.\n");
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
	int i = 0;
	char line[60] = {"\0"};
	char type;
	char msg[58] = {"\0"}; 
	char* logfile = NULL;
	char* log;
	while(optind < argc){
		if((option = getopt(argc, argv, "ht:")) !=-1){
			switch(option){
				case 'h':
					helpmenu(argv[0]);
					return 1; 
				case 't':
					if(validSec(optarg)){
						sec = atoi(optarg);
						printf("Received sec value: %d\n",sec);
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
			}
		}else{
			if(logfile == NULL){
				logfile = argv[optind];
				printf("The file name is: %s\n",logfile);
			}
			else{
				fprintf(stderr,"Error: There are too many file name\n");
				return EXIT_FAILURE;
			}
			optind++;		
		}
		
	}

	while(i<n_array){
		memset(line, 0, strlen(line));
		memset(msg, 0, strlen(msg));
		strcpy(line, message[i]);	
		type = line[0];
		strcpy(msg, &line[2]);
		if(addmsg(type,msg) == -1){
			fprintf(stderr,"%s: ",argv[0]);
			perror("Error");
			return EXIT_FAILURE;
		}
		i++;
	}	
	log = getlog();
	if(log == NULL){
		fprintf(stderr,"%s: ",argv[0]);
                perror("Error");
                return EXIT_FAILURE;
	}else
		printf("%s", log);		

	return EXIT_SUCCESS;
}
