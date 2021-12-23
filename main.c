#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char **argv){
	
	int c;
	char *jobsFile = NULL, *resultFile = NULL;

	printf("This is the beginning of CPU SCHEDULER PROJECT\n");
	
	FILE *inputFile = NULL;

	while((c = getopt (argc, argv, "f:o:")) != -1)

		switch (c){
			case 'f':
				jobsFile = optarg;
				break;
			case 'o':
				resultFile = optarg;
				break;
			case '?':
				if(optopt == 'f' || optopt == 'o')
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				else if(isprint (optopt))
					fprintf(stderr, "Unknown option: -%c\n", optopt);
				return 1;
			default:
				abort ();
		}//switch


	printf("\n%s, %s", jobsFile, resultFile);
	return 0;
}
