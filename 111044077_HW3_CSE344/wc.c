

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
    //argv[1] adında bir dosya var mı kontrol et
    int countOfLine = 0;
    if (argc == 4 && (strcmp(argv[2], ">") == 0)) {
        int file = open(argv[3], O_CREAT | O_RDONLY | O_WRONLY, 0644);
        if (file < 0) return 1;
        if (dup2(file, STDOUT_FILENO) < 0) return 1;
        close(file);
    }

    FILE *f = fopen(argv[1], "r");      // open the specified file
    if (f != NULL) {
        int c;
        while ((c = fgetc(f)) != EOF)     // read character from file until EOF
        {                            // output character

            if (c == '\n') {
                countOfLine++;
            }

        }
        fclose(f);
        fprintf(stdout, "Count of line : %d", countOfLine);
    }

    return (0);


}
