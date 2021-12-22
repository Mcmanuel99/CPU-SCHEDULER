#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char **argv){
	
	int c;
	printf("This is the beginning of CPU SCHEDULER PROJECT");
	
	FILE *inputFile = NULL;

	while((c = getopt (argc, argv, "f:0:") != -1)){

		switch (c){
			case 'f':
				printf("an input file has been provided");
				break;
			case 'o':
				printf("an outputfile has been provided");
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
	}//while

	

	return 0;
}
