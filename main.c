#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

//global variables
#define SIZE 1024

//funtions 
void readFile( char *fileName);
void schedulingMethod();

struct process{
	int burstTime,arrivalTime, priority;
	float waitingTime, turnArroundTime;
	struct process *next;
}*jobs = NULL;

struct process * new_process(int a, int b, int c){
	struct process * temp;
	temp=(struct process *)malloc(sizeof(struct process));
	temp->burstTime=a;
	temp->arrivalTime=b;
	temp->priority=c;
	return temp;
}

struct process * insertBack(struct process *header, int a, int b, int c){
	struct process *temp, *headertemp;
	temp=new_process(a,b,c);
	if(header==NULL)
	{
		header=temp;
		return header;
	}
	headertemp=header;
	while(headertemp->next!=NULL)
		headertemp=headertemp->next;
	headertemp->next=temp;
	return header;
}

void display(struct process *header)
{
    if (header == NULL)
        printf("\nList is empty\n");
        
    struct process *temp = header;

    while (temp != NULL)
    {
        printf("%d %d %d-->",temp->burstTime,temp->arrivalTime,temp->burstTime);
        temp=temp->next;
    }
    printf("\n");
}

int main(int argc, char **argv)
{

	int c, choice;
	char *jobsFile = NULL, *resultFile = NULL;

	printf("This is the beginning of CPU SCHEDULER PROJECT\n");

	FILE *inputFile = NULL;

	while ((c = getopt(argc, argv, "f:o:")) != -1)

		switch (c)
		{
		case 'f':
			jobsFile = optarg;
			readFile(jobsFile);
			break;
		case 'o':
			resultFile = optarg;
			break;
		case '?':
			if (optopt == 'f' || optopt == 'o')
				fprintf(stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint(optopt))
				fprintf(stderr, "Unknown option: -%c\n", optopt);
			return 1;
		default:
			abort();
		} //switch

	printf("\n%s, %s\n", jobsFile, resultFile);

	do
	{
		printf("\n--------------------CPU Scheduler Simulator--------------------\n");
		printf("1) Scheduling Method (None)                     			\n");
		printf("2) Preemptive Mode (off)                       				   \n");
		printf("3) Show Result                                     \n");
		printf("4) End Program                                 \n");
		printf("---------------------------------------------------------------\n");
		printf("Please enter your option: ");
		scanf("%d", &choice);

		switch (choice)
		{

		case 1:
			printf("\nNon-preemptive mode Selected");
			schedulingMethod();
			break;

		case 2:
			printf("\nPreemptive mode has been turned off");
			break;

		case 3:
			printf("\nDisplaying result...");
			break;

		case 4:
			printf("Terminating programe ...\n");
			sleep(1);
			break;

		default:
			printf("wrong choise has been made, please select again");
			break;

		} //switch case

	} while (choice != 4);


	return 0;
}

void schedulingMethod(){

		int choice;
		printf("\n--------------------CPU Scheduler Simulator--------------------\n");
		printf("1) First come, first served scheduling.                     \n");
		printf("2) Shortest-Job-First scheduling.                           \n");
		printf("3) Priority Scheduling.                                     \n");
		printf("4) Round Robin Scheduling.                                  \n");
		printf("5) Show Result.                                             \n");
		printf("6) Terminate.                                               \n");
		printf("---------------------------------------------------------------\n");
		printf("Please enter your option: ");
		scanf("%d", &choice);

		switch (choice)
		{

		case 1:
			printf("\nFCFS method selected");
			break;

		case 2:
			printf("\nSJF method selected");
			break;

		case 3:
			printf("\nPriority method selected");
			break;

		case 4:
			printf("\nRound Robin method selected");
			break;

		case 5:
			printf("\nthis are the results");
			break;

		case 6:
			printf("Terminating programe ...\n");
			sleep(1);
			break;

		default:
			printf("wrong choise has been made, please select again");
			break;

		} //switch case
}

void readFile( char *fileName){
	FILE *fp; char line[SIZE]; int num[3];
	if ((fp = fopen(optarg, "r")) == NULL){
		fprintf (stderr, "unable to open file %s\n", fileName);
	}else{
		while (fgets(line, SIZE, fp) != NULL) {
			sscanf(line,"%d:%d:%d\n",&num[0],&num[1],&num[2]);
			//printf("num1=%u num2=%u num3=%u\n",num[0],num[1],num[2]);
			jobs = insertBack(jobs, num[0], num[1], num[2]);
		}
	}
	fclose(fp);
	display(jobs);
}