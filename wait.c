#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void main(){

	pid_t pid;
	pid = fork();
	if (pid == 0){
	
		printf("Child Process Started with id: %d\n",getpid());
		sleep(5);
		printf("Child Process Finished\n");
		exit(0);	
		
	}else if (pid>0){
	
		printf("Parent Process:%d waiting for child to finish\n",getpid());
		int status;
		wait(&status);
		printf("Child Process has terminated with status %d\n", status);	
		
	}else{
	
		printf("Fork Failed");
	
	}
	
}
