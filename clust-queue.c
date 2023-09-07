#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


#include "common.h"

int main(int argc, char *argv[]) 
{
	int file_descriptor;

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
		if (strcmp(argv[i], "-n") == 0) {
			if (i + 1 < argc) {
				task.nproc = atoi(argv[i + 1]);
				i++;
			} else {
				printf("Error: -n option requires a value.\n");
				return 1;
			}
		} else if (strcmp(argv[i], "-i") == 0) {
			if (i + 1 < argc) {
				memset(task.inputFile, 0, FNLEN);
				strcpy(task.inputFile, argv[i + 1]);
				i++;
			} else {
				printf("Error: -i option requires a value.\n");
				return 1;
			}
		} else if (strcmp(argv[i], "-l") == 0) {
			if (i + 1 < argc) {
				memset(task.logFile, 0, FNLEN);
				strcpy(task.logFile, argv[i + 1]);
				i++;
			} else {
				printf("Error: -l option requires a value.\n");
				return 1;
			}
		} else if (strcmp(argv[i], "-o") == 0) {
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
	
	if (access(HomeFolderName, F_OK) == -1) {
		if (mkdir(HomeFolderName, 0777) == 0) {
			printf("%s is created\n", HomeFolderName);
		} else {
			perror(HomeFolderName);
		return 1;
		}
	} 
	
	snprintf(QueueFile, PATHLEN, "%s/%s", HomeFolderName, "Queue");
	
	file_descriptor = open(QueueFile, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
	
	if (file_descriptor == -1) {
		perror(QueueFile);
		return 1;
	}
	
	task.pid = 0;
	
	printf("pid: %u\tnproc: %d\nInput: %s\tLog: %s\nOwner: %s\tFolder %s\n", task.pid, task.nproc, task.inputFile, task.logFile, task.owner, task.workingFolder);
	
	char QueueWrite[10 * LEN];
	
	snprintf(QueueWrite, 10 * LEN - 1, QFORMAT(task));
	ssize_t bytes_written = write(file_descriptor, QueueWrite, strlen(QueueWrite));
	
	if (bytes_written == -1) {
		perror(QueueFile);
	}
	
	close(file_descriptor);
	  
	return 0;
}
