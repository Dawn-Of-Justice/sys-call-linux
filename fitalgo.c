#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void Display(int num,int unit,int allocation[][num],int Memory[],int Process[]) {

    printf("Memory\n");
    for(int j=0;j<unit;j++){
    	printf("----- MemoryBlock-%d\n", j + 1);
    	printf("| %d | Free\n", Memory[j]);
    	for(int i=0;i<num;i++){
    		if(allocation[j][i]!=-1){
    			printf("| %d | Process number\n", i+1);
    		}
    	}	
    }      
}


int FirstFit(int unit,int num,int Memory[],int Process[]){
	
	int allocation[unit][num];
	int remaining;
	
	//Used to initialize everything to -1 initially
	for(int i=0;i<num;i++){
		for(int j=0;j<unit;j++){
			allocation[j][i]=-1; //used in display function to distinguish the process number
		}
	}
	
	for(int i=0;i<num;i++){
		for(int j=0;j<unit;j++){
			remaining = Memory[j]-Process[i];
			if(remaining>=0){ //to check if the memory has enough space to allocate the required process
				allocation[j][i] = Process[i];
				Memory[j] = remaining;
				break; //goes to the next process
			}
		}
	}
	
	printf("\n\nFirst Fit\n");
	Display(num,unit,allocation,Memory,Process);
	return 1;
	
}

int BestFit(int unit,int num,int Memory[],int Process[]){

	int allocation[unit][num];
	int remaining,smallest,index;
	
	//Used to initialize everything to -1 initially
	for(int i=0;i<num;i++){
		for(int j=0;j<unit;j++){
			allocation[j][i]=-1; //used in display function to distinguish the process number
		}
	}
	
	for(int i=0;i<num;i++){
		smallest = 10000;//used to initallize small to a large number
		index = -1; // used so check if no allocation to a process is made
		for(int j=0;j<unit;j++){
			remaining = Memory[j]-Process[i];
			if (Memory[j] >= Process[i] && smallest>remaining){ //think you will get it... eventually
				index = j;
				smallest = remaining;
			}
		}
		if(index!=-1){ 
				allocation[index][i] = Process[i];
				Memory[index] = smallest;
			}
	}
	
	printf("\n\nBest Fit\n");
	Display(num,unit,allocation,Memory,Process);
	return 1;

}

int WorstFit(int unit,int num,int Memory[],int Process[]){

	int allocation[unit][num];
	int remaining,largest,index;
	
	//Used to initialize everything to -1 initially
	for(int i=0;i<num;i++){
		for(int j=0;j<unit;j++){
			allocation[j][i]=-1; //used in display function to distinguish the process number
		}
	}
	
	for(int i=0;i<num;i++){
		largest = -1;//used to initallize largest to a small number
		index = -1; // used so check if no allocation to a process is made
		for(int j=0;j<unit;j++){
			remaining = Memory[j]-Process[i];
			if (Memory[j] >= Process[i] && largest<remaining){ //think you will get it... eventually
				index = j; // j = 2 i = 3
				largest = remaining; //30
			}
		}
		if(index!=-1){ 
				allocation[index][i] = Process[i];
				Memory[index] = largest;
			}
	}
	
	printf("\n\nWorst Fit\n");
	Display(num,unit,allocation,Memory,Process);
	return 1;
	
}

void main(){

	int unit,num,status_1,status_2,status_3; 
	//unit to store the number of memeory block.
	//num to store the number of process.
	printf("Enter the number of Memory blocks:");
	scanf("%d",&unit);
	printf("Enter the number of processes:");
	scanf("%d",&num);
	
	int Memory[unit],Process[num];
	
	//initializing memory blocks.
	for(int i=0;i<unit;i++){
		printf("Enter the storage of Memory block-%d:",i+1);
		scanf("%d",&Memory[i]);
	}
	
	//initializing process.
	for(int j=0;j<num;j++){
		printf("Enter the storage required for process-%d:",j+1);
		scanf("%d",&Process[j]);
	}
	
	
	//Exectuing as child process beacuse otherwise it causes error in the output
	pid_t pid1=fork();
	if (pid1 == 0){
		status_1 = FirstFit(unit,num,Memory,Process);
		exit(0);
	}
	
	waitpid(pid1, NULL, 0);
	
	pid_t pid2=fork();
	
	if (pid2 == 0){
		status_2 = BestFit(unit,num,Memory,Process);
		exit(0);
	}
	
	waitpid(pid2, NULL, 0);
	
	pid_t pid3=fork();
	
	if (pid3 == 0){
		status_3 = WorstFit(unit,num,Memory,Process);
		exit(0);
	}
	
  waitpid(pid3, NULL, 0);
	
	
	printf("\nProgram executed succesfully\n"); //used to check if the program control reached to main() successfully
	
}











