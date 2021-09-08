#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "log.h"
#include <errno.h>

extern int errno;
char* withfatal[] = {"I This program has bug",
			"W Bug on line 3",
			"E Cannot find an error",
			"W Another bug on line 6",
			"F The program has to be stopped",
			"I Need to update C version"};
char* withoutfatal[] = {"I This program has bug",
                        "W Bug on line 3",
                        "E Cannot find an error",
                        "W Another bug on line 6",
                        "I Need to update C version",
                        "E An error on line 456"};

#define n_array (sizeof(withfatal)/sizeof(char*))

void helpmenu(char* driver){
	printf("This program is used to test the functionality\n");
	printf("of logging library. This program will generate a set\n");
	printf("of messages and output the respective message in another\n");
	printf("form.\n");
	printf("%s [-h] [-t sec] [logfile]\n",driver);
	printf("\t [-h]: print help menu.\n");
	printf("\t [-t sec]: specify the time sleep between each logging. If\n");
	printf("\t user doesn't specify this option, the time will automatically\n");
	printf("\t be set to 2.\n");
	printf("\t [logfile]: specify the output file. If user doesn't specify this\n");
	printf("\t option, the output file will automatically be set to 'message.log'\n");

}

void printmes(char** msg, int size){
	int i = 0;
	while(i < size){
		printf("\t%s.\n",msg[i]);
		i++;
	}
}

int validNum(char* sec){
	int size = strlen(sec);
	int i = 0;
	while(i < size){
		if(!isdigit(sec[i]))
			return 0;
		i++;		
	}
	return 1;
}

int generaterand(int sec){
	srand(time(0));
	int num = (rand() % (2*sec + 1));
	return num;
}

int main(int argc, char** argv){
	int option;
	int sec = 2;
	int i = 0;
	int delay;
	
	char type;
	char line[60] = {"\0"};
	char msg[58] = {"\0"}; 
	char* logfile = NULL;
	char userinput;
	char** message;
	

	while(optind < argc){
		if((option = getopt(argc, argv, "ht:")) !=-1){
			switch(option){
				case 'h':
					helpmenu(argv[0]);
					return 1; 
				case 't':
					if(validNum(optarg)){
						sec = atoi(optarg);
					}else{
						fprintf(stderr,"%s: ERROR: %s is not a valid number\n",argv[0],optarg);
						return EXIT_FAILURE;
					}
					break;
				case '?':
					if(optopt == 't')
						fprintf(stderr,"%s: ERROR: -%c without argument\n",argv[0],optopt);
					else
						fprintf(stderr, "%s: ERROR: Unrecognized option: -%c\n",argv[0],optopt);
					return EXIT_FAILURE;
			}
		}else{
			if(logfile == NULL){
				logfile = argv[optind];
			}
			else{
				fprintf(stderr,"Error: There are too many file name\n");
				return EXIT_FAILURE;
			}
			optind++;		
		}
		
	}
	
	if(logfile == NULL)
		logfile = "message.log";
	delay = generaterand(sec);
 
	printf("The log file is: %s.\n",logfile);
	printf("Currently, we have two set of messages. One includes fatal\n");
	printf("message. The other one doesn't. Look at two set of messages below\n");
	printf("and enter the number of the set message you want to choose.\n");
	printf("Set 1, no fatal message:\n");
	printmes(withoutfatal, n_array);
	printf("Set 2, with fatal message: \n");
	printmes(withfatal, n_array);
	
	do{
		printf("Please enter the set of messages you want to choose (1 or 2): ");
		scanf(" %c",&userinput);
	}while((userinput!= '1') && (userinput != '2'));

	if(userinput == '1')
		message = withoutfatal;
	else
		message = withfatal;
	
	printf("Processing...\n");
	while(i<n_array){
		memset(line, 0, strlen(line));
		memset(msg, 0, strlen(msg));
		strcpy(line, message[i]);	
		type = line[0];
		strcpy(msg, &line[2]);
		int check = addmsg(type,msg);
		if(check == -1){
			fprintf(stderr,"%s: ",argv[0]);
			perror("Error");
			return EXIT_FAILURE;
		}else if(check == 1){
			if(savelog(logfile) == -1){
		                fprintf(stderr,"%s: ",argv[0]);
                		perror("Error");
                		return EXIT_FAILURE;
        		}
			printf("Fatal message added, program is terminated.\n");
			exit(1);
			
		}
		i++;
		sleep(delay);
	}
	printf("Saving message in %s.\n",logfile);
	if(savelog(logfile) == -1){
       		fprintf(stderr,"%s: ",argv[0]);
                perror("Error");
                return EXIT_FAILURE;
       	}
	sleep(2);
	printf("Finish saving message in %s.\n",logfile);	
	
	return EXIT_SUCCESS;
}
