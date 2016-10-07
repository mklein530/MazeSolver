#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLENGTH 3

void readArray(char *, int *, char **, int);
void writeArray(char *, int *, int);
void bubbleSort(int *, int);

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	char* outputFile = "output.txt";
	int size = atoi(argv[2]);
	int levels = atoi(argv[3]);
	int *arr = (int*) malloc(size*sizeof(int));
	char **integers = (char**)malloc(size*sizeof(char *)); //string array for reading in integers from file
	//allocate space for string array
	int i;
	for (i = 0; i < size; i++) {
		integers[i] = malloc( (MAXLENGTH + 1)*sizeof(char) );
	}
	
	readArray(fileName, arr, integers, size);
	bubbleSort(arr, size);
	writeArray(outputFile, arr, size);

	return 0;
}

/****************Reads data as strings and converts each line to integer********************/
void readArray(char* fileName, int *arr, char **integers, int size) {
	FILE *input;
	int i = 0;
	if ( (input = fopen(fileName, "r")) == NULL ) {
		printf("Can't open %s", fileName);
		return;
	}

	//use string array to get data from file
	while ( (fgets(integers[i], MAXLENGTH+1, input)) != NULL) {
		/* get rid of ending \n from fgets */
		if (integers[i][strlen(integers[i]) - 1] == '\n' )
			integers[i][strlen(integers[i]) - 1] = '\0';
		i++;
	}

	//convert each string in the string array to integers and store in integer array
	for (i = 0; i < size; i++) {
		arr[i] = atoi(integers[i]);
	}
}

/**********Writes the data to the output file********************/
void writeArray(char* fileName, int *arr, int size) {
	FILE *output;
	int i = 0;

	if ((output = fopen(fileName, "w")) == NULL) {
		printf("Can't write to %s", fileName);
		return;
	}

	for (i = 0; i < size; i++) {
		fprintf(output, "%d\n", arr[i]);
	}
}

/***************Standard bubble sort routine*********************/
void bubbleSort(int *arr, int size) {
	int i, j, temp;

	for (i = 0; i < size - 1; i++) {
		for (j = 0; j < size - i - 1; j++) {
			if (arr[j + 1] > arr[j]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void generate_kid(int res) {
	pid_t kid1, kid2;
	int status1, status2;

	if (res > 0){
		if ((kid1 = fork()) == 0) {
			// child
			printf("I am %d, my father is %d\n", getpid(), getppid());
			// generate half remaining rounded up for odd processes
			generate_kid((res - 1) / 2);
		}
		else if (kid1 > 0) {
			// parent - create second child
			if (res > 1){
				if ((kid2 = fork()) == 0) {
					// child 2
					printf("I am %d, my father is %d\n", getpid(), getppid());
					// generate half remaining processes
					generate_kid((res - 2) / 2);
				}
				else if (kid2 > 0){
					// parent 2
					waitpid(kid2, &status2, 0);
				}
			}
			waitpid(kid1, &status1, 0);
		}
	}
}