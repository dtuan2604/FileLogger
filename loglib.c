#include <stdlib.h> 
#include <string.h>
#include "log.h"
#include <time.h>
#include <errno.h>
#include <stdio.h> 

typedef struct list_struct{
	data_t item;
	struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;
static int logsize = 0; 

int addmsg(const char type, const char* msg){
	time_t t = time(NULL);	
	log_t *newnode;
	int nodesize;
	
	nodesize = sizeof(log_t) + strlen(msg) + 2;
	if((newnode = (log_t *)(malloc(nodesize))) == NULL)
		return -1; //couldn't add node, malloc will automatically set errno
	
	newnode->item.time = t;
	newnode->item.type = type;
	newnode->item.string = (char *)newnode + sizeof(log_t);
	strcpy(newnode->item.string, msg);
	newnode->next = NULL;

	if(headptr == NULL)
		headptr = newnode;
	else
		tailptr->next = newnode;
	tailptr = newnode;
	logsize = logsize + strlen(msg) + 41;	
	return 0; //if successfull 

}

void clearlog(void){
}

char *getlog(void){
	char* result;
	time_t t;
	struct tm* local;
	log_t *temptr = headptr;
	if((result = (char* )malloc(logsize)) == NULL)
		return NULL;
	//temptr = NULL;//test errno
	if(temptr == NULL){
		errno = EADDRNOTAVAIL;
		return NULL;
	}
	while(temptr != NULL){
		char time[30] = {"\0"};
		char *msg;
		char type[10] = {"\0"};
		char temp = temptr->item.type;
		if((msg = (char* )malloc((strlen(temptr->item.string)+1)*sizeof(char))) == NULL)
			return NULL;
		t = temptr->item.time;
		local = localtime(&t);
		strcpy(time,asctime(local));
		time[strlen(time)-1] = '\0';
		strcpy(msg,temptr->item.string);
		if(temp == 'I')
			strcpy(type, ": INFO: ");
		else if(temp == 'W')
			strcpy(type, ": WARN: ");	
		else if(temp == 'E')
			strcpy(type, ": ERROR: ");
		else
			strcpy(type, ": FATAL: ");
		strcat(result,time);
		strcat(result,type);
		strcat(result,msg);
		strcat(result,"\n");
		temptr = temptr->next;				
	}
	return result;
}

int savelog(char *filename){
	return 0;
}
