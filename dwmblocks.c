#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>

#define LENGTH(X)               (sizeof(X) / sizeof (X[0]))
#define CMDLENGTH       50


#ifndef NO_X
#include<X11/Xlib.h>
#endif

#include "blocks.h"

static Display *dpy;
static int screen;
static Window root;


static int block_length = LENGTH(blocks);
char* output; 

int setupX(){
     dpy = XOpenDisplay(NULL);
     if (!dpy) {
         fprintf(stderr, "dwmblocks: Failed to open display\n");
         return 0;
     }
     screen = DefaultScreen(dpy);
     root = RootWindow(dpy, screen);
     return 1;
 }

void block_check(){
	int cursor = 0;

	for(int i=0; i < block_length;i++){	
		Block block = blocks[i];
		
		
		/*Icon*/
		strcpy(output+cursor,block.icon);
		cursor += strlen(block.icon);
		/*Func*/
		char* command = block.command();	
		strcpy(output+cursor,command);
		cursor += strlen(command);
		if(i+1 != block_length){

			/*Delim*/
			char* delim = " | ";
			strcpy(output+cursor,delim);
			cursor += strlen(delim);
		}
	}
	
	output[cursor++] = '\0';
	XStoreName(dpy, root, output);	
	XFlush(dpy);	
}

void statusloop(){
	
	while(1){
		block_check();
		sleep(1.0);
	}

}

int main(){
	if(!setupX()){
		return 1;
	}
	output = malloc(50 * block_length * sizeof(char));
	statusloop();


	XCloseDisplay(dpy);
	free(output);
	return 0;
}
