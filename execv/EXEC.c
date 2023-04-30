#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void main(){
	
	printf("I am EXEC.c\n");
	char *args[]={"./execvDemo",NULL};
	execv(args[0],args);	
	
}
