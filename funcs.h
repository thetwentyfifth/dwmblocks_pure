#include <sys/sysinfo.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct sysinfo sys_info;
const double gigabyte = 1024 * 1024 * 1024;
char BUF[80]= "";


char* bat(){
	char* result = "100%";
	return result;
}

char* date(){
	time_t t ; 
    time( &t ); 
      
    struct tm *tmp = localtime( &t );   
	strftime(BUF,80,"%a %b %d %H:%M", tmp);
	return BUF;
}

char* memory(){
	if(sysinfo(&sys_info) != 0)
    	perror("sysinfo");
	sprintf(
			BUF,
			"%.2f/%.0f",
			
			(sys_info.totalram - sys_info.freeram - sys_info.bufferram)/gigabyte,
			sys_info.totalram/gigabyte  );
	return BUF;
}

