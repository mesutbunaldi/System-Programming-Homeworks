
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

    char cDir2[1024];
    if (getcwd(cDir2, sizeof(cDir2)) != NULL) {


        if (argc==3 && strcmp(argv[1], ">") == 0) {

            int file = open(argv[2], O_CREAT | O_RDONLY | O_WRONLY, 0644);
            if (file < 0) return 1;
            if (dup2(file, STDOUT_FILENO) < 0) return 1;
            close(file);
        }

        fprintf(stdout, "\nCurrent working directory : %s\n", cDir2);


    } else
        perror("pwd error");

    return (0);


}