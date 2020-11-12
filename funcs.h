#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const double gigabyte = 1024 * 1024 * 1024;
char BUF[80]= "";

/*********
 * DATE 
 * *******/
char* date(){
	time_t t ; 
    time( &t ); 
      
    struct tm *tmp = localtime( &t );   
	strftime(BUF,80,"%a %b %d %H:%M", tmp);
	return BUF;
}



/*********
 * MEMORY 
 * *******/
int start_with(FILE* fp,char* match,int ps){
	char c;
	do{
	  c = fgetc(fp);
	  if(*match != c) return -1;
	
	}while(*(++match) != '\0');
	
	if(fgetc(fp) != ':') return -1;
	return ps;
}

long int str_to_long(FILE* fp){
	long int total = 0;
	char c;
	while((c = fgetc(fp) ) < 48 || c > 57) ;
	
	do{
	  total *= 10;
	  total += c - 48;
	}while((c = fgetc(fp)) > 47 && c < 58 );
	
	return total;
}

char* memory(){
	FILE *fptr;
	fptr = fopen("/proc/meminfo","r");
	if(fptr == NULL){
	  return "Error";
	}
	
	char c;
	char* fields[4] ={
		"MemTotal","MemFree","Buffers","Cached"
	};
	int values[4]; 
	
	while(1){
		// loop over fields
		for(int i=0;i < 4;i++){
			long int fps = ftell(fptr);
			short ps = start_with(fptr,fields[i],i); // -1 means no match 0-3 is position of match in fields
			if(ps != -1){
			  values[ps] = str_to_long(fptr);
			  break;
			}
			// if noMatch reset and try
			fseek(fptr,fps,SEEK_SET);
		}
		//next Line OR end of file
		while( (c = fgetc(fptr)) != EOF && c != '\n');
		if(c == '\n') continue; // next Line
		if(c == EOF) break; // break this shit
	}
  	fclose(fptr); // close file
  	double gb= 1024 * 1024;
	sprintf(
			BUF,
			"%.2f/%.1f",
			(values[0]-values[1]-values[2]-values[3])/gb,
			values[0]/gb);  
  	return BUF;
}



/*********
 * BATTERY
 * *******/



FILE *fptr;

long int file_to_long(const char* filename){
	fptr = fopen(filename,"r");
	if(fptr == NULL){
	  return 0;
	}

	long int total = 0;
	char c;
	
	while((c = fgetc(fptr)) > 47 && c < 58 ){
	  total *= 10;
	  total += c - 48;
	}
	fclose(fptr);
	return total;
}
int long ch_full = -1;

char* bat(){
	if(ch_full == -1){
		ch_full = file_to_long("/sys/class/power_supply/BAT0/charge_full");	
	}

	int long ch_now = file_to_long("/sys/class/power_supply/BAT0/charge_now");	
	char* icon;

	fptr = fopen("/sys/class/power_supply/BAT0/status","r");
	if(fptr == NULL){
	  return 0;
	}

	char c = fgetc(fptr);
	fclose(fptr);

	if(c == 'F'){	//Full
		icon = "";
	}else if( c == 'C'){ // Charging
		icon = "";
	}else if(c == 'N'){ // Nor charging
		icon = " ";
	}else if(c == 'D'){ // Discharging
		icon = "";
	}else if(c == 'U'){ // Unkown
		icon = "";
	}else{
		icon = "";
	}
	
	int batper =(ch_now * 100)/ch_full;
	sprintf(BUF," %s %lu%%",icon,batper + 4);
	
  	
	return BUF;
}
