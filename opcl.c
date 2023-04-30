#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
 void main(){
 
 	int fd = open("Test.txt", O_RDONLY | O_CREAT);
 	printf("Opened the file with fd = %d\n", fd);
 	printf("Simulating work\n");
 	fflush(stdout);
 	sleep(2);
 	printf("Opened the file with fd = %d\n", fd);
 	if (close(fd) < 0){
 		perror("Error");
 		exit(1);
 	}
 	printf("Closed the file\n");
 
 }
