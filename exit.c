#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void main(){
	
	pid_t pid;
	pid = fork();
	if(pid == 0){
		
		printf("\nFound exit in child process\n");
		exit(0);
		printf("\nThis is from child process\n");
		printf("Child Process id: %d\n", getpid());	
		printf("Parent Process id: %d\n", getppid());	
		
	}	
	else{
		printf("\nThis is from Parent process\n");
		printf("Child Process id: %d\n", getpid());	
		printf("Parent Process id: %d\n", getppid());	
	}
		
}
