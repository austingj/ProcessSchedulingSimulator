/**
README
Name: Austin Jeffery
How to Compile: Copy this lab4.c file into a directory along with a text file saved as input.txt
Then open the terminal where these two files are located in and run the command
"gcc -g lab4.c -o run" after it has compiled you should be able to run it by 
using the command ./run
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
int numberofproc[0];
int copynumberofproc[100];
int maxproc = 0;
int Q = 0;
int turntime = 0;
//For input.txt, only first two lines are different since first = numberofproc, second line = Q
//Every line after the second will be CPU burst
void readfile(){
	FILE *inputfile = fopen("input.txt", "r");
	int number;
	int nop;
	int i =0;
	bool firstline = true;
	bool secondline = true;
	bool thirdline = false;
	if( !inputfile){
	printf("File cannot be read\n");
	exit(-1);
	}
	char buf[100];
	while(fscanf(inputfile, "%s", buf) ==1){
	number = atoi(buf);
	if(number != 0){
		if(firstline == true){
			//insert into numberofproc array
			numberofproc[number];
			copynumberofproc[number];
			maxproc = number;
			//printf("MAXPROC : %d", maxproc); Check values
			//printf("Number of proc: %d", number);
			firstline = false;
		}
		else if(secondline == true){
			Q = number;
			secondline = false;
			thirdline = true;
		}
		else if(thirdline == true){//insert rest of CPU bursts
			numberofproc[i] = number;
			i++;
		}
	}	

}

}
void print(){
	printf("processes: %d", maxproc);
	printf("\n");
	for(int i =0;i<maxproc;i++){
	printf("P%d", i+1);
	printf("\t");
	printf("%d", numberofproc[i]);
	printf("\n");
	}
}
void printWaitAndTurnaround(int procwait[], int turnaround[]){
	double totalwait = 0;
	double turntime = 0;
	for(int i = 0;i<maxproc; i++){
	totalwait = totalwait + procwait[i];
	turntime = turntime + turnaround[i];
	}
	printf("Total wait time:\t%f", totalwait);
	printf("\n");
	printf("Avg Wait time:  \t%f", totalwait/maxproc);
	printf("\n");
	printf("Turnaround Total Time:\t%f", turntime);
	printf("\n");
	printf("Turnaround Average:\t%f", turntime/maxproc);
	
}
void calAvgWait(){
	double turntime = 0;
	int turnaround[5];
	int waittime = 0;
	int count = 0;
	int avgwait[100];
	int procwait[100];
	int start[100];
	int finish[100];
	for(int i =0;i<100;i++){
	avgwait[i]= 0;
	procwait[i] = 0;
	start[i] = 0;
	finish[i] =0;	
	}
	bool checks[maxproc];
	for(int i = 0; i<maxproc;i++){
	checks[i] = true;
	turnaround[i] = 0;	
	}
	int j = 0;
	int cpuburst;
	bool ans = true;
	printf("Q: %d", Q);
	printf("\n");
	printf("\n");
	start[j] = waittime;
	while(ans == true){
		//calculate p0 wait
		for(int i = 0; i<maxproc;i++){
			if(checks[i] == true){
				start[i] = waittime;
				cpuburst = numberofproc[i];	//cpuburst = 14
				cpuburst = cpuburst - Q;	//9
				if(cpuburst <=0){
					while(cpuburst < 0){ //if cpu burst is 3, -Q(5) = -2
					cpuburst++;		//bring back cpuburst to 0
					count++;
					}
				checks[i] = false;
				}
				waittime = waittime + Q - count; //Q-Count is only if cpu burst was
				count = 0; 			 //less than Q, otherwise count = 0
				avgwait[i] = start[i] - finish[i];
				finish[i] = waittime;
				turnaround[i] = finish[i];
				procwait[i] = procwait[i] + avgwait[i]; //procwait[] will hold wait for each proccess
				numberofproc[i] = cpuburst;//14 set to 9
				j++;
			}
		}
	ans = false;  //checks will be set to false if their process cpuburst is = 0, then exit loop
	for(int i =0;i<maxproc;i++){
		if(checks[i] == true){ //if any havent been sent to false, ans still = true
			ans =true;			
			}	
		}
	}	
	printWaitAndTurnaround(procwait, turnaround);
}

void calthroughput(){
	double throughput;
	for(int i =0;i<maxproc;i++){
		throughput = throughput + numberofproc[i];
}
	throughput = throughput / maxproc;
	printf("\nThroughput = %f", throughput);
	printf("\n");
}
void printChart(){
	int waittime = 0;
	int count = 0;
	int order[100];
	int avgwait[100];
	int procwait[100];
	int start[100];
	int finish[100];
	for(int i =0;i<100;i++){
	avgwait[i]= 0;
	order[i] = -1;
	procwait[i] = 0;
	start[i] = 0;
	finish[i] =0;	
	}
	bool checks[maxproc];
	for(int i = 0; i<maxproc;i++){
	checks[i] = true;	
	}
	int j = 0;
	int cpuburst;
	bool ans = true;
	printf("\n");
	printf("\n");
	start[j] = waittime;
	printf("~~~~~~~~~~~~~~~~SCHEDULE~~~~~~~~~~~~~~~~\n\n");
	while(ans == true){
		for(int i = 0; i<maxproc;i++){
			if(checks[i] == true){
				start[i] = waittime;
				cpuburst = numberofproc[i];	
				cpuburst = cpuburst - Q;	
				if(cpuburst <=0){
					while(cpuburst < 0){
					cpuburst++;
					count++;
					}
				checks[i] = false;
				}
				waittime = waittime + Q - count;
				count = 0;
				printf("-----");
				printf("%-3d", waittime);
				avgwait[i] = start[i] - finish[i];
				finish[i] = waittime;
				procwait[i] = procwait[i] + avgwait[i];
				order[j] = i;
				numberofproc[i] = cpuburst;
				j++;
			}
		}
	ans = false;
	for(int i =0;i<maxproc;i++){
		if(checks[i] == true){
			ans =true;			
			}	
		}
	

	}
		printf("\n");
	for(int i = 0; i< 100; i++){
	if(order[i] >= 0){
		printf("  P");
		printf("%-3d",order[i]);
		printf("\t");
		}	
	}
	printf("\n");
	for(int i = 0; i <100; i ++){
	if(order[i] >= 0){
		printf("--------");	
		}
	}
	
}
void fillcopy(){
for(int i =0; i<maxproc; i++){
	copynumberofproc[i] = numberofproc[i];
	}
}
void refill(){
for(int i =0; i<maxproc; i++){
	numberofproc[i] = copynumberofproc[i];
	}
}
int main(void)

{
	//step 1 read file and store input
	//step 2 implement algorithm
	//calculate wait, turnaround ...
	//print chart
	readfile();
	fillcopy();
	print();
	calthroughput();
	calAvgWait();
	refill();
	printf("\n");
	printChart();
	printf("\n");
	printf("\nEND\n");
	
}
