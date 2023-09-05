#define LEN[100]

typedef struct ClustQueue {
	pid_t pid;
	char	owner[LEN];
	int	nproc;
}

char HomeFolderName[]	= "~/.clust";
char HostFileName[]	= "/etc/hosts";

