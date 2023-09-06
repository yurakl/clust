#define LEN[100]
#define FNLEN[100]
#define PATHLEN[300]
typedef struct ClustQueue {
	pid_t pid;
	char	owner[LEN];
	char	workingFolder[PATHLEN];
	char	inputFile[FNLEN];
	char	logFile[FNLEN];
	int	nproc;
}

char HomeFolderName[]	= "~/.clust";
char HostFileName[]	= "/etc/hosts";

