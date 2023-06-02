#include<stdio.h>
#define MAX 100
//Example reference : 3 2 1 3 4 1 6 2 4 3 4 2 1 4 5 2 1 3 4

void FIFO(int frame_num,int reference[],int numCount){
	
	int miss = 0;
	int hit = 0;
	int memory[frame_num];//simulating main memory
	int i=0;
	int location = 0;//used to track the location of which frame to replace
	
	//initializing memory with -1
	for(int k=0;k<frame_num;k++){
		memory[k] = -1;
	}
	
	while(i != numCount){
	
		int flag = 0;
		for(int j=0;j<frame_num;j++){
			if(memory[j] == reference[i]){
				hit++;
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			miss++;
			memory[location] = reference[i];
			location = ((location+1) % frame_num);
		}
		i++;
	}
	
	printf("\nPage Replacement alogorithm: First In First Out\n");
	printf("The number of page fault: %d\n",miss);
	printf("Hit ratio: %d/%d\n",hit,(miss+hit));
}

void LRU(int frame_num,int reference[],int numCount){
	
	int miss = 0;
	int hit = 0;
	int memory[frame_num];//simulating main memory
	int i=0;
	int longest=0;//used to track the longest frame
	
	//initializing memory with -1
	for(int k=0;k<frame_num;k++){
		memory[k] = -1;
	}
	
	while(i != numCount){
	
		int flag = 0;
		for(int j=0;j<frame_num;j++){
			if(memory[j] == reference[i]){
				hit++;
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			miss++;
			memory[longest] = reference[i];
			if(i<(frame_num+1)){
				longest = ((longest+1) % frame_num);
			}else{
				longest = ((longest+2) % frame_num);
			}
		}
		i++;
	}
	
	printf("\nPage Replacement alogorithm: Least Recently Used\n");
	printf("The number of page fault: %d\n",miss);
	printf("Hit ratio: %d/%d\n",hit,(miss+hit));
	
}

void LFU(int frame_num,int reference[],int numCount){
	
	int miss = 0;
	int hit = 0;
	int memory[frame_num];//simulating main memory
	int i=0;
	int unused;//used to track the longest unused page
	
	//initializing memory with -1
	for(int k=0;k<frame_num;k++){
		memory[k] = -1;
	}
	
	while(i != numCount){
		unused = 0;
		int flag = 0;
		for(int j=0;j<frame_num;j++){
			if(memory[j] == reference[i]){
				printf("Hit %d",reference[i]);
				hit++;
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			miss++;
			if(i<(frame_num+1)){
				memory[i]= reference[i];
			}else{
				for(int s=numCount-1;s>=i;s--){
					for(int r=0;r<frame_num;r++){
						if(memory[r] == reference[s]){
							unused = r;
						}
					}
				}
				for(int p=0;p<frame_num;p++){
					if(unused == memory[p]){
						memory[p] = reference[i];
					}
				}
			}
		}
		i++;
	}
	
	printf("\nPage Replacement alogorithm: Least Frequently Used\n");
	printf("The number of page fault: %d\n",miss);
	printf("Hit ratio: %d/%d\n",hit,(miss+hit));
	
}

void main(){
	
	int frame_num;
	int reference[MAX];
	int numCount = 0;
	char ch;
	printf("Enter the number of frames: ");
	scanf("%d",&frame_num);
	printf("Enter the reference string with space in between each: ");
	
	//used to read the reference string
    while (numCount < MAX && scanf("%d", &reference[numCount]) == 1) {
        numCount++;
        ch = getchar();
        if (ch == '\n') {
            break;
        }
    }
	
	//FIFO(frame_num,reference,numCount);
	//LRU(frame_num,reference,numCount);
	LFU(frame_num,reference,numCount);
		
}
