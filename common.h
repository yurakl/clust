#include <string.h>
#include <fcntl.h>
#include <sys/file.h>

#define LEN 	100
#define FNLEN 	100
#define PATHLEN 300 

#define QFORMAT(T) "%u %d %s %s %s %s\n", T.pid, T.nproc, T.inputFile, T.logFile, T.owner, T.workingFolder

typedef struct{
	pid_t	pid;
	char	owner[LEN];
	char	workingFolder[PATHLEN];
	char	inputFile[FNLEN];
	char	logFile[FNLEN];
	int		nproc;
} ClustQueue;

char HomeFolderName[]	= "/home/mpiuser/.clust";
char QueueFile[PATHLEN];

char HostFileName[]		= "/etc/hosts";

int lockFile(int fd) {
    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        perror("Error while locking Queue file");
        return 0;
    }
    return 1;
} 

int unlockFile(int fd) {
    if (flock(fd, LOCK_UN) == -1) {
        perror("Error while unlocking Queue file");
        return 0;
    }
    return 1;
}
