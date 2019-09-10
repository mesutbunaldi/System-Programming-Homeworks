

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
    if (argc == 2 ) {

        if(chdir(argv[1])==0) {
            char cDir2[1024];
            getcwd(cDir2, sizeof(cDir2));
            printf("\n%s", cDir2);
        }else{
            printf("Dont find file!!!\n");
        }

    }
    return (0);


}
