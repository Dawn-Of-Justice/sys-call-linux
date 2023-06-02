/*This program assumes that there is no ideal time between processes*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#define MAX 1000;

void Display(int turnaroundtime[], int waitingtime[], int num){
	
	printf("--------------------------------------\n");
	printf("|Process|Turnaround time|Waiting time|\n");
	printf("--------------------------------------\n");
	for(int i=0;i<num;i++){
		printf("|   %d   |       %02d      |     %02d     |\n",i+1,turnaroundtime[i],waitingtime[i]);
	}
	printf("--------------------------------------\n");
	
}

void sortChart(int num, int* processnum, int* completetime){
	
	//sorting done using bubble sort
	int temp_time,temp_number;
	for(int i=0;i<num;i++) {
		for(int j=0;j<(num-i-1);j++) {
			if(completetime[j]>completetime[j+1]){
				temp_time = completetime[j];
				temp_number = processnum[j];
				
				completetime[j] = completetime[j+1];
				processnum[j] = processnum[j+1];
				
				completetime[j+1] = temp_time;
				processnum[j+1] = temp_number;
			}
		}
	}	
}

void sortArrival(int num,int* processnum,int* arrival,int* burst,int* priority){

	//sorting done using bubble sort
	int temp_number,temp_arrival,temp_burst,temp_priority;
	for(int i=0;i<num;i++) {
		for(int j=0;j<(num-i-1);j++) {
			if(arrival[j]>arrival[j+1]){
				temp_arrival = arrival[j];
				temp_number = processnum[j];
				temp_burst = burst[j];
				temp_priority = priority[j];
				
				arrival[j] = arrival[j+1];
				processnum[j] = processnum[j+1];
				burst[j] = burst[j+1];
				priority[j] = priority[j+1];
				
				arrival[j+1] = temp_arrival;
				processnum[j+1] = temp_number;
				burst[j+1] = temp_burst;
				priority[j+1] = temp_priority;
			}
		}
	}
}

void gchart(int num,int processnum[], int completetime[]){

	sortChart(num,processnum,completetime);//used to sort the values according to completetime
	
	int current_time=0;//used to keep track of current time
	int diff;
	int i,j;
	printf(" ");
	for(i=0; i<num; i++) {
        for(j=0; j<completetime[i]; j++){
        	printf("--");
        }
        printf(" ");
    }
    printf("\n|");
	
	for(i=0; i<num; i++) {
        for(j=0; j<completetime[i]-1; j++) printf(" ");
        printf("P%d", processnum[i]);
        for(j=0; j<completetime[i]-1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    
     for(i=0; i<num; i++) {
        for(j=0; j<completetime[i]; j++) printf("--");
        printf(" ");
    }
    printf("\n");
    
    printf("0");
    for(i=0; i<num; i++) {
        for(j=0; j<completetime[i]; j++) printf("  ");
        if(completetime[i] > 9) printf("\b"); // backspace : remove 1 space
        printf("%d", completetime[i]);
 
    }
    printf("\n");
    
}

int FCFS(int num,int processnum[], int arrival[], int burst[]){
	
	int completetime[num]; //array used to store completion time
	int diff; //used to calculate the time difference if some process comes after cpu is idle
	completetime[0] = arrival[0] + burst[0];
	int time = arrival[0];//time till the execution of i th process
	
	//completion time calculation
	for(int i=1;i<num;i++){
		time += arrival[i];
		if(completetime[i-1]<time){
			diff = arrival[i] - completetime[i-1];
			completetime[i] = completetime[i-1]+burst[i]+diff;
		}else{
			completetime[i] = completetime[i-1]+burst[i];
		}	
	}
	
	//turnaround time calculation
	int turnaroundtime[num]; //array used to store turn around time
	for(int j=0;j<num;j++){
		turnaroundtime[j] = completetime[j] - arrival[j];
	}
	
	//waiting time calculation
	int waitingtime[num]; // array used to store waiting time
	for (int k=0;k<num;k++){
		waitingtime[k] = turnaroundtime[k] - burst[k];
	}
	
	printf("\nScheduling algorithm: FCFS\n");
	Display(turnaroundtime,waitingtime,num);
	printf("\nGantt Chart\n");
	gchart(num,processnum,completetime);
	return 1;
}

int RoundRobin(int num, int arrival[], int burst[]){

	int qtime; //time quantum
	printf("Enter the time quantum for Round Robin: ");
	scanf("%d",&qtime);
	int current_time=0;//used to track current time
	int Total_Time=0;//Total time of execution
	
	int BT[num];//used to store duplicate of Burst Time to calculate waiting time
	for(int i=0;i<num;i++){
		BT[i] = burst[i];
		Total_Time = Total_Time + burst[i]; //used to calcualted total execution time for all process
	}
	
	//completion time calculation
	int completetime[num]; //array used to store completion time
	int j=0;	
	
	while(current_time != Total_Time){
		if(burst[j]!=0){
			if((burst[j]-qtime)<0){
				current_time += burst[j];
				burst[j] = 0;
			}else{
				current_time += qtime;
				burst[j] -= qtime;
			}
			if(burst[j]==0){
				completetime[j]=current_time;
			}
		}
		j = (j + 1) % num;
		
	}
	
	//turnaround time calculation
	int turnaroundtime[num]; //array used to store turn around time
	for(int j=0;j<num;j++){
		turnaroundtime[j] = completetime[j] - arrival[j];
	}
	
	//waiting time calculation
	int waitingtime[num]; // array used to store waiting time
	for (int k=0;k<num;k++){
		waitingtime[k] = turnaroundtime[k] - BT[k];
	}
	
	printf("\nScheduling algorithm: Round Robin\n");
	Display(turnaroundtime,waitingtime,num);
	return 1;
	
}

int SJF(int num,int processnum[], int arrival[], int burst[]){
	
	int completetime[num]; //array used to store completion time
	int diff; //used to calculate the time difference if some process comes after cpu is idle
	completetime[0] = arrival[0] + burst[0];
	int prev = completetime[0];
	int current_time = burst[0];//used to keep track of current time
	int sburst;//used to find the shortest process
	int sindex;//used to keep track of the index of the shortest process
	
	int BT[num];//used to store duplicate of Burst Time to calculate waiting time
	for(int i=0;i<num;i++){
		BT[i] = burst[i];
	}
	
	//Calculation of completion time
	for(int i=1;i<num;i++){
		sindex=-1;
		sburst=MAX;
		for(int j=1;j<num;j++){
			if(sburst>burst[j] && burst[j]<=current_time && burst[j]!= -1){
				sburst = burst[j];	
				sindex = j;
			}
		}
		if (sindex != -1){
			burst[sindex] = -1;
			completetime[sindex] = prev + sburst;
			prev = completetime[sindex];
			current_time += sburst;
		}
	}
	
	//turnaround time calculation
	int turnaroundtime[num]; //array used to store turn around time
	for(int j=0;j<num;j++){
		turnaroundtime[j] = completetime[j] - arrival[j];
	}
	
	//waiting time calculation
	int waitingtime[num]; // array used to store waiting time
	for (int k=0;k<num;k++){
		waitingtime[k] = turnaroundtime[k] - BT[k];
	}
	
	printf("\nScheduling algorithm: SJF\n");
	Display(turnaroundtime,waitingtime,num);
	printf("\nGantt Chart\n");
	gchart(num,processnum,completetime);
	return 1;
	
} 

int Priority(int num,int arrival[],int burst[], int priority[]){

	int completetime[num]; //array used to store completion time
	completetime[0] = arrival[0] + burst[0];
	int current_time = burst[0];//used to keep track of current time
	int current_priority;//used to keep track of the current highest priority process's burst time
	int prev = completetime[0];
	int pindex;
	int flag=-1;
	int current_burst;
	
	int BT[num];//used to store duplicate of Burst Time to calculate waiting time
	for(int i=0;i<num;i++){
		BT[i] = burst[i];
	}
	
	//Calculating completion time
	for(int i=1;i<num;i++){
		flag=-1;
		current_priority = MAX;
		for(int j=1;j<num;j++){
			if(arrival[j] <= current_time && current_priority > priority[j] && burst[j]!= -1){
				current_priority = priority[j];
				current_burst = burst[j];
				pindex = j;
				flag=1;
			}
		}
		
		if (flag != -1){
			burst[pindex] = -1;
			completetime[pindex] = prev + current_burst;
			prev = completetime[pindex];
			current_time += current_burst;
		}
	}
	
	//turnaround time calculation
	int turnaroundtime[num]; //array used to store turn around time
	for(int j=0;j<num;j++){
		turnaroundtime[j] = completetime[j] - arrival[j];
	}
	
	//waiting time calculation
	int waitingtime[num]; // array used to store waiting time
	for (int k=0;k<num;k++){
		waitingtime[k] = turnaroundtime[k] - BT[k];
	}
	
	printf("\nScheduling algorithm: Priority\n");
	Display(turnaroundtime,waitingtime,num);
	return 1;

}

void main(){
	
	int status_1,status_2,status_3,status_4;
	int num; //num is the number of process
	printf("Enter number of process: ");
	scanf("%d",&num);
	int processnum[num]; // used to store process number
	int arrival[num],burst[num],priority[num];
	
	for(int i=0;i<num;i++){
		processnum[i] = i+1;
		printf("\nProcess-%d\n",i+1);
		printf("Enter the arrival time: ");
		scanf("%d",&arrival[i]);
		printf("Enter the burst time: ");
		scanf("%d",&burst[i]);
		printf("Enter the priority: ");
		scanf("%d",&priority[i]);
	}
	
	sortArrival(num,processnum,arrival,burst,priority);
	
	//Exectuing as child process beacuse otherwise it causes error in the output
	pid_t pid1=fork();
	if (pid1 == 0){
		status_1 = FCFS(num,processnum,arrival,burst);
		exit(0);
	}
	waitpid(pid1, NULL, 0);
	
	pid_t pid2=fork();
	if (pid2 == 0){
		status_2 = SJF(num,processnum,arrival,burst);
		exit(0);
	}
	waitpid(pid2, NULL, 0);
	
	pid_t pid3=fork();
	if (pid3 == 0){
		status_3 = RoundRobin(num,arrival,burst);
		exit(0);
	}
  	waitpid(pid3, NULL, 0);
  	
  	pid_t pid4=fork();
  	if (pid4 == 0){
		status_4 = Priority(num,arrival,burst,priority);
		exit(0);
	}
  	waitpid(pid4, NULL, 0);
	
	printf("\nProgram executed succesfully\n");
	
}
