
/*

	NAME 		: MESUT
	SURNAME 	: BUNALDI
	STUDENT ID 	: 111044077
	HOMEWORK 	: 3

*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>
#include <dirent.h>




int main(int argc,char  *argv[]) {


	DIR *midir;
	struct dirent *info_archivo;
	struct stat fileStat;
	char fullpath[256];

	if ((midir = opendir(".")) == NULL) {

		perror("Error in opendir");
		exit(-1);
	}



	if (argc == 3 && (strcmp(argv[1], ">") == 0)) {
		int file = open(argv[2], O_CREAT | O_RDONLY | O_WRONLY,0644);
		if (file < 0) return 1;
		if (dup2(file, STDOUT_FILENO) < 0) return 1;
		close(file);

	}


	fprintf(stdout, "\nFile Type\tFile Permissions\tFile Size\tFile Name\n");
	while ((info_archivo = readdir(midir)) != 0) {
		if (stat(info_archivo->d_name, &fileStat) < 0)
			return 1;
		fprintf(stdout, (S_ISDIR(fileStat.st_mode)) ? "Directory" : "");
		fprintf(stdout, (S_ISCHR(fileStat.st_mode)) ? "CS - File" : "");
		fprintf(stdout, (S_ISBLK(fileStat.st_mode)) ? "BS - File" : "");
		fprintf(stdout, (S_ISREG(fileStat.st_mode)) ? "Regular  " : "");
		fprintf(stdout, (S_ISFIFO(fileStat.st_mode)) ? "FIFO-Pipe" : "");
		fprintf(stdout, (S_ISLNK(fileStat.st_mode)) ? "SLink    " : "");
		fprintf(stdout, "\t");
		fprintf(stdout, (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
		fprintf(stdout, (fileStat.st_mode & S_IRUSR) ? "r" : "-");
		fprintf(stdout, (fileStat.st_mode & S_IWUSR) ? "w" : "-");
		fprintf(stdout, (fileStat.st_mode & S_IXUSR) ? "x" : "-");
		fprintf(stdout, (fileStat.st_mode & S_IRGRP) ? "r" : "-");
		fprintf(stdout, (fileStat.st_mode & S_IWGRP) ? "w" : "-");
		fprintf(stdout, (fileStat.st_mode & S_IXGRP) ? "x" : "-");
		fprintf(stdout, (fileStat.st_mode & S_IROTH) ? "r" : "-");
		fprintf(stdout, (fileStat.st_mode & S_IWOTH) ? "w" : "-");
		fprintf(stdout, (fileStat.st_mode & S_IXOTH) ? "x" : "-");
		fprintf(stdout, "\t");
		fprintf(stdout, "\t%d", (int)fileStat.st_size);
		fprintf(stdout, "\t");
		fprintf(stdout, "\t%s", info_archivo->d_name);
		fprintf(stdout, "\n");
	}


	closedir(midir);
	return 0;

}
   