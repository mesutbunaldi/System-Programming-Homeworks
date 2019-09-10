#define _GNU_SOURCE
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/mman.h>
#include <signal.h>
typedef struct shared{
    sem_t sem,sem2;
    int statementOfDessert;
    int r; //represents couple of elements (random)
}Shared;

static pid_t pids[6];
static Shared * shared;
void     INThandler(int);

int main() {

    signal(SIGINT, INThandler);
    shared = mmap(NULL, sizeof(shared), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *&shared->statementOfDessert = 0;
    int sem1=sem_init(&shared->sem, 1, 1);//dönüş değerlerini kontrol et
    int sem2=sem_init(&shared->sem2, 1, 0);
    shared->r = -1;
    if(sem1==0 && sem2==0) {
        pid_t parent = getpid();
        for (int i = 0; i < 6; i++)
            if (fork() == 0) {
                pids[i] = getpid();
                break;
            }

        while (1) {
            //proccess for wholesaler
            if (parent == getpid()) {
                sem_wait(&(shared->sem));

                //rasgele 2 sayı üret 0 ile 3 arasında bu sayılar eksik malzemeleri temsil edicek
                if (*&shared->statementOfDessert == 1) {
                    fprintf(stdout, "wholesaler has obtained the dessert and left to sell it\n");
                    fflush(stdout);
                    *&shared->statementOfDessert = 0;
                }
                srand(time(NULL));
                int tmp=shared->r;
                *&shared->r = rand() % 6;
                while(tmp==shared->r){
                    *&shared->r = rand() % 6;
                }
                sem_post(&(shared->sem2));
                //proccess for chief 2
            } else if (pids[1] == getpid()) {
                sem_wait(&(shared->sem2));
                if (*&shared->r != 3)
                    fprintf(stdout, "chef2 is waiting for flour and butter\n");
                else if (shared->r == 3) {
                    fprintf(stdout, "wholesaler delivers flour and butter\n");
                    fprintf(stdout, "chef2 has taken the flour\n");
                    fprintf(stdout, "wholesaler is waiting for the dessert\n");
                    fprintf(stdout, "chef2 has taken the butter\n");
                    if (*&shared->statementOfDessert == 0) {
                        fprintf(stdout, "chef2 is preparing the dessert\n");
                        *&shared->statementOfDessert = 1;
                        fprintf(stdout, "chef2 has delivered the dessert to the wholesaler\n");
                    }
                }
                fflush(stdout);
                sem_post(&(shared->sem));
                //proccess for chief 3
            } else if (pids[2] == getpid()) {
                sem_wait(&(shared->sem2));
                if (*&shared->r != 2)
                    fprintf(stdout, "chef3 is waiting for eggs and sugar\n");
                else if (*&shared->r == 2) {
                    fprintf(stdout, "wholesaler delivers eggs and sugar\n");
                    fprintf(stdout, "chef3 has taken the eggs\n");
                    fprintf(stdout, "wholesaler is waiting for the dessert\n");
                    fprintf(stdout, "chef3 has taken the sugar\n");
                    if (*&shared->statementOfDessert == 0) {
                        fprintf(stdout, "chef3 is preparing the dessert\n");
                        *&shared->statementOfDessert = 1;
                        fprintf(stdout, "chef3 has delivered the dessert to the wholesaler\n");
                    }
                }
                fflush(stdout);
                sem_post(&(shared->sem));
                //proccess for chief 5
            } else if (pids[4] == getpid()) {
                sem_wait(&(shared->sem2));
                if (*&shared->r != 4)
                    fprintf(stdout, "chef5 is waiting for flour and sugar\n");
                else if (*&shared->r == 4) {
                    fprintf(stdout, "wholesaler delivers flour and sugar\n");
                    fprintf(stdout, "chef5 has taken the flour\n");
                    fprintf(stdout, "wholesaler is waiting for the dessert\n");
                    fprintf(stdout, "chef5 has taken the sugar\n");
                    if (*&shared->statementOfDessert == 0) {
                        fprintf(stdout, "chef5 is preparing the dessert\n");
                        *&shared->statementOfDessert = 1;
                        fprintf(stdout, "chef5 has delivered the dessert to the wholesaler\n");
                    }
                }
                fflush(stdout);
                sem_post(&(shared->sem));
                //proccess for chief 6
            } else if (pids[5] == getpid()) {
                sem_wait(&(shared->sem2));
                if (*&shared->r != 5)
                    fprintf(stdout, "chef6 is waiting for butter and sugar\n");
                else if (shared->r == 5) {
                    fprintf(stdout, "wholesaler delivers butter and sugar\n");
                    fprintf(stdout, "chef6 has taken the flour\n");
                    fprintf(stdout, "wholesaler is waiting for the dessert\n");
                    fprintf(stdout, "chef6 has taken the sugar\n");
                    if (*&shared->statementOfDessert == 0) {
                        fprintf(stdout, "chef6 is preparing the dessert\n");
                        *&shared->statementOfDessert = 1;
                        fprintf(stdout, "chef6 has delivered the dessert to the wholesaler\n");
                    }
                }
                fflush(stdout);
                sem_post(&(shared->sem));

                //proccess for chief 1
            } else if (pids[0] == getpid()) {
                sem_wait(&(shared->sem2));
                if (*&shared->r != 0)
                    fprintf(stdout, "chef1 is waiting for eggs and flour\n");
                else if (*&shared->r == 0) {
                    fprintf(stdout, "wholesaler delivers eggs and flour\n");
                    fprintf(stdout, "chef1 has taken the eggs\n");
                    fprintf(stdout, "wholesaler is waiting for the dessert\n");
                    fprintf(stdout, "chef1 has taken the flour\n");
                    if (*&shared->statementOfDessert == 0) {
                        fprintf(stdout, "chef1 is preparing the dessert\n");
                        *&shared->statementOfDessert = 1;
                        fprintf(stdout, "chef1 has delivered the dessert to the wholesaler\n");
                    }
                }
                fflush(stdout);
                sem_post(&(shared->sem));
            } else if (pids[3] == getpid()) {
                sem_wait(&(shared->sem2));
                if (*&shared->r != 1)
                    fprintf(stdout, "chef4 is waiting for eggs and butter\n");
                else if (*&shared->r == 1) {
                    fprintf(stdout, "wholesaler delivers eggs and butter\n");
                    fprintf(stdout, "chef4 has taken the eggs\n");
                    fprintf(stdout, "wholesaler is waiting for the dessert\n");
                    fprintf(stdout, "chef4 has taken the butter\n");
                    if (*&shared->statementOfDessert == 0) {
                        fprintf(stdout, "chef4 is preparing the dessert\n");
                        *&shared->statementOfDessert = 1;
                        fprintf(stdout, "chef4 has delivered the dessert to the wholesaler\n");
                    }
                }
                fflush(stdout);
                sem_post(&(shared->sem));
            }
        }
    }else
        perror("Semaphores unsuccessfull!");
    return 0;
}

void  INThandler(int sig) {
    signal(sig, SIG_IGN);
    sem_destroy(&shared->sem);
    sem_destroy(&shared->sem2);
    exit(0);

}