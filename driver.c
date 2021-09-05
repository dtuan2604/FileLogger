#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>


int main(int argc, char** argv){
	int option;
	int sec;
	while((option = getopt(argc, argv, "ht:")) !=-1){
		switch(option){
			case 'h': printf("help menu");
				break;
			case 't':
				sec = atoi(optarg);
				printf("Receive parameter sec = %d",sec);
				break;
			case '?':
				if(optopt == 't')
					fprintf(stderr,"-%c without argument\n",optopt);
				else
					fprintf(stderr, "Unrecognized option: -%c\n", optopt);
				return EXIT_FAILURE;

		}
	}
	printf("\nDone while loop");
	return EXIT_SUCCESS;
}
