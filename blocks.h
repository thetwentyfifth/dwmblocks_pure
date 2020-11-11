#include <sys/sysinfo.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

typedef struct {
	char* icon;
	char* (*command)();
	unsigned int interval;
	unsigned int signal;
} Block;






static const Block blocks[] = {
	/*Icon*/ /*Func*/   /*interval*/  /*Signal*/
	{"  ",     bat,           30,           0},
	{"  ",     memory,        30,           0},
	{"  ",     date,          30,           0}




};



