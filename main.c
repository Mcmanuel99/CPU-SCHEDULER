#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

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

	//printf("\n%s, %s", jobsFile, resultFile);

	do{
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

		switch(choice){

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

		}//switch case

	} while (choice != 6);
	
		return 0;
	}
