#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

//global variables
#define SIZE 1024
char *jobsFile = NULL, *resultFile = NULL;

struct process
{
	int burstTime, arrivalTime, priority, serviceTime,waitingTime, id;
	float turnArroundTime;
	struct process *next;
} *jobs = NULL;

//funtions
void readFile(char *fileName);
void schedulingMethod();
void FirstComeFirstServe();
void swap(struct process *current, struct process *next);
void bubbleSort(struct process *head);
void ShortestJobFirst(struct process *header);
void PriorityScheduling();
void calculateWaitingTime();
void RoundRobinScheduling(int time_quantum);

struct process *new_process(int a, int b, int c, int pid)
{
	struct process *temp;
	temp = (struct process *)malloc(sizeof(struct process));
	temp->burstTime = a;
	temp->arrivalTime = b;
	temp->priority = c;
	temp->id=pid;
	return temp;
}

struct process *insertBack(struct process *header, int a, int b, int c, int pid)
{
	struct process *temp, *headertemp;
	temp = new_process(a, b, c, pid);
	if (header == NULL)
	{
		header = temp;
		return header;
	}
	headertemp = header;
	while (headertemp->next != NULL)
		headertemp = headertemp->next;
	headertemp->next = temp;
	return header;
}



void display(struct process *header)
{
	if (header == NULL)
		printf("\nList is empty\n");

	struct process *temp = header;

	while (temp != NULL)
	{
		printf("%d %d Waiting Time: %d\n", temp->burstTime, temp->arrivalTime, temp->waitingTime);
		temp = temp->next;
	}
	printf("\n");
}

int main(int argc, char **argv)
{

	int c, choice,quantum;

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

void schedulingMethod()
{

	int option, quantum;
	printf("\n--------------------CPU Scheduler Simulator--------------------\n");
	printf("1) First come, first served scheduling.                     \n");
	printf("2) Shortest-Job-First scheduling.                           \n");
	printf("3) Priority Scheduling.                                     \n");
	printf("4) Round Robin Scheduling.                                  \n");
	printf("5) Show Result.                                             \n");
	printf("6) Terminate.                                               \n");
	printf("---------------------------------------------------------------\n");
	printf("Please enter your option: ");
	scanf("%d", &option);

	switch (option)
	{

	case 1:
		printf("\nFCFS method selected");
		FirstComeFirstServe(jobs);
		break;

	case 2:
		printf("\nShortest Job First method selected");
		ShortestJobFirst(jobs);
		break;

	case 3:
		printf("\nPriority method selected");
		PriorityScheduling();
		break;

	case 4:
		printf("\nRound Robin method selected");
		printf("\nEnter the time Quantum: ");
		scanf("%d",&quantum);
		RoundRobinScheduling(quantum);
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

void readFile(char *fileName)
{
	FILE *fp;
	char line[SIZE];
	int num[3];
	if ((fp = fopen(optarg, "r")) == NULL)
	{
		fprintf(stderr, "unable to open file %s\n", fileName);
	}
	else
	{
		int pid =1;
		while (fgets(line, SIZE, fp) != NULL)
		{
			sscanf(line, "%d:%d:%d\n", &num[0], &num[1], &num[2]);
			//printf("num1=%u num2=%u num3=%u\n",num[0],num[1],num[2]);
			jobs = insertBack(jobs, num[0], num[1], num[2],pid);
			pid++;
		}
	}
	fclose(fp);
}

void writeTofile(){

}

void FirstComeFirstServe(struct process *header)
{
	int prevWaitingTime = 0;
	int prevBurstTime = 0;
	int totalWaitingTime=0;
	int i;
	struct process *temp = header;
	FILE *f = fopen(resultFile, "a");
	fprintf(f, "\nScheduling Method: First Come First Served\nProcess Waiting Times: \n");
	printf("\nScheduling Method: First Come First Served\nProcess Waiting Times: \n");
	//display(temp);
	if (jobs == NULL)
	{
		printf("\njob list is empty!!");
	}
	else
	{
		
		i = 0;
		while (temp != NULL)
		{
			if (temp->arrivalTime == 0)
			{
				
				temp->serviceTime = 0;
				//printf("%d ",temp->arrivalTime);
				prevBurstTime = temp->burstTime;
				prevWaitingTime = temp->serviceTime;
				//printf("\nFirst Job waitinTime: %f", temp->waitingTime);
				
			}
			else
			{
				
				temp->serviceTime = (prevBurstTime+prevWaitingTime);
				prevBurstTime = temp->burstTime;
				prevWaitingTime = temp->serviceTime;
				//printf("\nJob %d serviceTime: %d, arrivalTime: %d",i+1, temp->serviceTime, temp->arrivalTime);
			}
			
			temp->waitingTime=temp->serviceTime - temp->arrivalTime;
			printf("P%d: %d ms\n",i+1, temp->waitingTime);
			fprintf(f,"P%d: %d ms\n",i+1, temp->waitingTime);
			totalWaitingTime = totalWaitingTime+temp->waitingTime;
			i++;
			temp = temp->next;
			
		}
		
	}
	printf("Average waiting Time: %d ms",totalWaitingTime/i);
	fprintf(f, "Average waiting Time: %d ms",totalWaitingTime/i);
	fclose(f);
	//display(temp);
}

void bubbleSort(struct process *head) {
    int swapped;
    struct process *current = head;
    struct process *tmp = NULL;
    do
    {
        swapped = 0;
        current = head;
        while (current->next != tmp)
        {
            if ((current->arrivalTime > current->next->arrivalTime) || (current->arrivalTime == current->next->arrivalTime && current->burstTime > current->next->burstTime))
            {
                swap(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        tmp = current;
    } while (swapped);
}


void swap(struct process *current, struct process *next) {
    int burstTime = current->burstTime;
    int arrivalTime = current->arrivalTime;
    int serviceTime = current->serviceTime;
    int waitingTime = current->waitingTime;
    float turnArroundTime = current->turnArroundTime;
    current->burstTime = next->burstTime;
    current->arrivalTime = next->arrivalTime;
    current->serviceTime = next->serviceTime;
    current->waitingTime = next->waitingTime;
    current->turnArroundTime = next->turnArroundTime;
    next->burstTime = burstTime;
    next->arrivalTime = arrivalTime;
    next->serviceTime = serviceTime;
    next->waitingTime = waitingTime;
    next->turnArroundTime = turnArroundTime;
}

void ShortestJobFirst(struct process *header){
	struct process *temp = header;
	int totalWaitingTime=0;
	bubbleSort(temp);
	// display(temp);
	// display(jobs);
	FILE *f = fopen(resultFile, "a");
	int clock =0;
	fprintf(f, "\nScheduling Method: Shortest Job First Served\nProcess Waiting Times: \n");
	printf("\nScheduling Method:  Shortest Job First\nProcess Waiting Times: \n");
	int i=1;
	while (temp!=NULL)
	{
		temp->waitingTime = clock-temp->arrivalTime;
		clock = clock+temp->burstTime;
		fprintf(f,"P%d: %d ms\n",temp->id, temp->waitingTime);
		printf("P%d: %d ms\n", temp->id, temp->waitingTime);
		totalWaitingTime = totalWaitingTime+temp->waitingTime;
		i++;
		temp = temp->next;
	}
	printf("Average waiting Time: %d ms",totalWaitingTime/i);
	fprintf(f, "Average waiting Time: %d ms",totalWaitingTime/i);
	fclose(f);
}

void PriorityScheduling() {
    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        struct process *current = jobs;
        struct process *prev = NULL;
        while (current != NULL && current->next != NULL) {
            struct process *next = current->next;
            if (next->priority > current->priority) {
                if (prev == NULL) {
                    jobs = next;
                } else {
                    prev->next = next;
                }
                current->next = next->next;
                next->next = current;
                prev = next;
                sorted = 0;
            } else {
                prev = current;
                current = next;
            }
        }
    }
	 calculateWaitingTime();
    // Print waiting time of all jobs
    struct process *p = jobs;
    while (p != NULL) {
        printf("Process with priority %d has waiting time %d\n", p->priority, p->waitingTime);
        p = p->next;
    }
}

void calculateWaitingTime() {
    struct process *p = jobs;
    int service_time = 0;
    while (p != NULL) {
        service_time += p->burstTime;
        p->waitingTime = service_time - p->arrivalTime - p->burstTime;
        p = p->next;
    }
}

void RoundRobinScheduling(int time_quantum) {
    struct process *current = jobs;
    int service_time = 0;
    while (current != NULL) {
        if (current->burstTime > time_quantum) {
            current->burstTime -= time_quantum;
        } else {
            current->burstTime = 0;
        }
        service_time += time_quantum;
        current = current->next;
    }

    current = jobs;
    while (current != NULL) {
        if (current->burstTime == 0) {
            current->waitingTime = service_time - (current->arrivalTime + current->burstTime);
            printf("Process with priority %d has waiting time %d\n", current->priority, current->waitingTime);
            struct process *temp = current;
            if (current == jobs) {
                jobs = current->next;
            }
            current = current->next;
            free(temp);
        } else {
            struct process *prev = current;
            current = current->next;
            while (current != NULL && current->burstTime == 0) {
                current->waitingTime = service_time - (current->arrivalTime + current->burstTime);
                printf("Process with priority %d has waiting time %d\n", current->priority, current->waitingTime);
                struct process *temp = current;
                current = current->next;
                free(temp);
                prev->next = current;
            }
        }
    }
}
