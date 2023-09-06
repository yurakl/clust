#include <stdio.h>
#include <unistd.h>
#include "common.h"

int main(int argc, char *argv[]) 
{
	FILE *file;
	ClustQueue task;
	getcwd(task.workingFolder, PATHLEN);
	
	int has_n = 0;
	int has_i = 0;
	int has_o = 0;
	
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-n") == 0) {
			has_n = 1;
		} else if (strcmp(argv[i], "-i") == 0) {
			has_i = 1;
		} else if (strcmp(argv[i], "-o") == 0) {
			has_o = 1;
		}
	}
	
	if (!(has_n && has_i && has_o)) {
		fprintf(stderr, "Error: Missing a required option (-n, -i, -o)\n");
		return 1;
	}
	
	for (int i = 1; i < argc; i++) 
	{
		if (strcmp(argv[i], "-n") || strcmp(argv[i], "-np")) {
			if (i + 1 < argc) {
				task.nproc = atoi(argv[i + 1]);
				i++;
			} else {
				printf("Error: -n option requires a value.\n");
				return 1;
			}
		} else if (strcmp(argv[i], "-i")) {
			if (i + 1 < argc) {
				memset(task.inputFile, 0, FNLEN);
				strcpy(task.inputFile, argv[i + 1]);
				i++;
			} else {
				printf("Error: -i option requires a value.\n");
				return 1;
			}
		} else if (strcmp(argv[i], "-l")) {
			if (i + 1 < argc) {
				memset(task.logFile, 0, FNLEN);
				strcpy(task.logFile, argv[i + 1]);
				i++;
			} else {
				printf("Error: -l option requires a value.\n");
				return 1;
			}
		} else if (strcmp(argv[i], "-o")) {
			if (i + 1 < argc) {
				memset(task.owner, 0, LEN);
				strcpy(task.owner, argv[i + 1]);
				i++;
			} else {
				printf("Error: -o option requires a value.\n");
				return 1;
			}
		}
	}
	
	return 0;
}
