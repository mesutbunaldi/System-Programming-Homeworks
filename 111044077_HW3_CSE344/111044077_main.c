
/*

	NAME 		: MESUT
	SURNAME 	: BUNALDI
	STUDENT ID 	: 111044077
	HOMEWORK 	: 3

*/
#define _GNU_SOURCE
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

char *buffer;
volatile sig_atomic_t done = 0;
char cDir[1024];
int countBack;
void term(int signum) {
    free(buffer);
    printf("Exit from shell!\n");
    done = 1;
    exit(0);
}

int main(int argc,char  *argv[]) {

    signal(SIGTERM, term);
    char *inputArr[1000];
    int commandCounter = 0;
    char *bufferCollection[1000];
    size_t bufsize = 32;
    int characters;
    pid_t pid;

    if (getcwd(cDir, sizeof(cDir)) != NULL)

    while (!done) {



        printf("%s:$", cDir);

        characters = getline(&buffer, &bufsize, stdin);
        if (characters != 1) {

            inputArr[commandCounter] = buffer;//komut gecmisi
            int counter = 0;
            //komut satirini parcala ve arguman arrayine donustur
            bufferCollection[counter] = strtok(buffer, " \n");

            while (bufferCollection[counter] != NULL) {
                bufferCollection[++counter] = strtok(NULL, " \n");
            }
            ///////////////////////////////////////////////////////


            if (strcmp("ls", bufferCollection[0]) == 0) {
                printf("\n\nbuffer coll last item : %s   %d is counter\n\n",bufferCollection[counter],counter);
                pid = fork();
                if (pid == 0) {//child

                    int check = execvp("./ls", bufferCollection);

                    if (check == -1)
                        exit(-1);
                } else if (pid > 0) {//parent


                }
            } else if (strcmp("pwd", bufferCollection[0]) == 0) {
                pid = fork();
                if (pid == 0) {//child

                    int check = execvp("./pwd", bufferCollection);

                    if (check == -1)
                        exit(-1);
                } else if (pid > 0) {//parent


                }


            } else if (strcmp("cd", bufferCollection[0]) == 0) {//fork+exec


                pid = fork();
                if (pid == 0) {//child

                    int check = execvp("./cd", bufferCollection);

                    if (check == -1)
                        exit(-1);
                } else if (pid > 0) {//parent


                }




            } else if (strcmp("help", bufferCollection[0]) == 0) {
                printf("Supported Commands : \n-cd\n-ls\n-pwd\n-cat\n-wc\n-help\n-exit\n");

            } else if (strcmp("cat", bufferCollection[0]) == 0) {//fork+exec
                pid = fork();
                if (pid == 0) {//child

                    int check = execvp("./cat", bufferCollection);
                    if (check == -1)
                        exit(-1);
                } else if (pid > 0) {//parent


                }

            } else if (strcmp("wc", bufferCollection[0]) == 0) {//fork+exec
                pid = fork();
                if (pid == 0) {//child

                    int check = execvp("./wc", bufferCollection);
                    if (check == -1)
                        exit(-1);
                } else if (pid > 0) {//parent


                }


            } else if (strcmp("exit", bufferCollection[0]) == 0) {
                exit(0);

            }else if (strcmp("history", bufferCollection[0]) == 0) {


            }

            else {
                printf("Ignored command!!!\n");
            }

            commandCounter++;


            // &&&&  &&
        }
    }


    return 0;

}
   