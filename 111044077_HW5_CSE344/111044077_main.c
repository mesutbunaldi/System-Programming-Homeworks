

/*
 *  MESUT BUNALDI
 *  111044077
 *  SYSTEM PROGRAMMING
 *  HOMEWORK 5
 *
 * NOT:
 * THREADLER ARASI CONDITION VARIABLE VE MUTEX GEÇİŞLERİ TAM MANASIYLA SAĞLIKLI ÇALIŞMADIĞINDAN
 * ÖDEV İSTENEN ÇIKTIYI TAM OLARAK VERMEMEKTEDİR.
 * */








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
#include <fcntl.h>
#include <sys/types.h>
#include <math.h>


typedef struct Client{
    char name[32];
    double xPosition;
    double yPosition;
    char flower[32];
}Client;

typedef struct Florist{
    char name[32];
    double xPosition;
    double yPosition;
    char flowers[3][32];
    double speed;

}Florist;

int waiting=0,linecounter=0,clientcounter=0;
double deliveredTime;
char takenName[32],deliveredFlowerName[32],deliverName[32];
pthread_mutex_t my_mutex;
pthread_cond_t florist_c,client_c;

Florist florists[3];
Client clients[1024];// sonraki satır sayısına göre de init edilebilir

void *florist1_thread();
void *florist2_thread();
void *florist3_thread();
void *main_thread(void *i);



void main(int argc, char *argv[]) {


    const char *fileName = argv[1];

    FILE *file = fopen(fileName, "r");
    size_t buffer_size = 80;
    char *buffer = malloc(buffer_size * sizeof(char));
    char *temp;


    pthread_t florist_1, florist_2, florist_3, main_;
    int florist_1_ID, florist_2_ID, florist_3_ID, i, mainID;
    pthread_mutex_lock(&my_mutex);
    while (-1 != getline(&buffer, &buffer_size, file)) {

        if (linecounter < 3) {
            temp = strtok(buffer, " ,;:");
            strcpy(florists[linecounter].name, temp);
            temp = strtok(NULL, " ,;:()");
            florists[linecounter].xPosition = atof(temp);
            temp = strtok(NULL, " ,;:()");
            florists[linecounter].yPosition = atof(temp);
            temp = strtok(NULL, " ,;:()");
            florists[linecounter].speed = atof(temp);
            temp = strtok(NULL, " ,;:()");
            strcpy(florists[linecounter].flowers[0], temp);
            temp = strtok(NULL, " ,;:()");
            strcpy(florists[linecounter].flowers[1], temp);
            temp = strtok(NULL, " ,;:()\n");
            strcpy(florists[linecounter].flowers[2], temp);

        } else if (linecounter > 3 && buffer[0] != '\n') {
            temp = strtok(buffer, " ,;:");
            strcpy(clients[clientcounter].name, temp);
            temp = strtok(NULL, " ,;:()");
            clients[clientcounter].xPosition = atof(temp);
            temp = strtok(NULL, " ,;:()");
            clients[clientcounter].yPosition = atof(temp);
            temp = strtok(NULL, " ,;:()\n");
            strcpy(clients[clientcounter].flower, temp);
            clientcounter++;
        } else
            temp = strtok(buffer, " ,;:");

        linecounter++;
    }

    fclose(file);
    pthread_mutex_unlock(&my_mutex);
    printf("Florist application initializing from file: %s\n3 florists have been created\nProcessing requests\n",
           fileName);

    --linecounter;
    int count = 0;


    pthread_mutex_init(&my_mutex, 0);
    pthread_cond_init(&client_c, 0);
    pthread_cond_init(&florist_c, 0);
    pthread_mutex_lock(&my_mutex);
    while (waiting != 0) pthread_cond_wait(&client_c, &my_mutex);
    waiting = 1;
    florist_1_ID = pthread_create(&florist_1, NULL, florist1_thread, NULL);
     florist_2_ID = pthread_create(&florist_2, NULL, florist2_thread, NULL);
     florist_2_ID = pthread_create(&florist_3, NULL, florist3_thread, NULL);

    printf("\n");
    for (int k = 0; k < clientcounter; ++k) {//clients
        for (int j = 0; j < 3; j++) {               //florists
            double times[3] = {1000, 1000, 1000};
            for (int l = 0; l < 3; ++l) {    // florist flowers
                if (strcmp(clients[k].flower, florists[j].flowers[l]) == 0) {

                    double time = sqrt(pow((clients[k].xPosition - florists[j].xPosition), 2) +
                                       pow((clients[k].yPosition - florists[j].yPosition), 2)) / florists[j].speed;
                    printf("%s nin %s çiçeğini %s satıyor %3.2f ms de yetiştirebilir.\n", clients[k].name,
                          clients[k].flower, florists[j].name, time);
                    times[j] = time;//burada 1. 2. veya 3. florist in en kısa zamanda götürebilecek olanına zamanı atıyoruz


                    deliveredTime = time;
                    strcpy(deliverName,florists[j].name);
                    strcpy(takenName, clients[k].name);
                    strcpy(deliveredFlowerName, clients[k].flower);
                    pthread_mutex_unlock(&my_mutex);
                }
            }
            if (times[0] < times[1] && times[0] < times[2]) {
                //florist 1 in thread ine sinyal gönder
                pthread_mutex_lock(&my_mutex);
                pthread_cond_signal(&florist_c);
                pthread_mutex_unlock(&my_mutex);

            } else if (times[1] < times[0] && times[1] < times[2]) {
                //florist 2 nin threadine sinyal gönder
                 pthread_mutex_lock(&my_mutex);
                 pthread_cond_signal(&florist_c);
                 pthread_mutex_unlock(&my_mutex);
            } else if (times[2] < times[1] && times[2] < times[0]) {
                //florist 3 ün threadine sinyal gönder
                 pthread_mutex_lock(&my_mutex);
                 pthread_cond_signal(&florist_c);
                 pthread_mutex_unlock(&my_mutex);
            }

        }
    }


    pthread_cond_signal(&florist_c);
    pthread_mutex_unlock(&my_mutex);


    pthread_join(florist_1, 0);
     pthread_join(florist_2, 0);
     pthread_join(florist_3, 0);



    pthread_cond_destroy(&client_c);
    pthread_cond_destroy(&florist_c);
    pthread_mutex_destroy(&my_mutex);


}




void *florist1_thread(){

   //while(1) {
       pthread_mutex_lock(&my_mutex);
       while (waiting == 0)
           pthread_cond_wait(&florist_c, &my_mutex);
       waiting = 1;

       //burada florist1 in hazırlama ve teslimat işlemlerini kontrol et
       //ve gerçekleştir.
       printf("Florist %s has delivered a %s to %s in %3.2f ms\n",deliverName,deliveredFlowerName,takenName,deliveredTime);

       pthread_cond_signal(&client_c);
       pthread_mutex_unlock(&my_mutex);


  // }
    pthread_exit(0);

 }
void *florist2_thread(){
  //while(1) {
       pthread_mutex_lock(&my_mutex);
       while (waiting == 0) pthread_cond_wait(&florist_c, &my_mutex);
       waiting = 1;

       //burada florist1 in hazırlama ve teslimat işlemlerini kontrol et
       //ve gerçekleştir.
    printf("Florist %s has delivered a %s to %s in %3.2f ms\n",deliverName,deliveredFlowerName,takenName,deliveredTime);
       pthread_cond_signal(&client_c);
       pthread_mutex_unlock(&my_mutex);


  // }
    pthread_exit(0);
 }

void *florist3_thread(){
  // while(1) {
       pthread_mutex_lock(&my_mutex);
       while (waiting == 0) pthread_cond_wait(&florist_c, &my_mutex);
       waiting = 1;

       //burada florist1 in hazırlama ve teslimat işlemlerini kontrol et
       //ve gerçekleştir.
    printf("Florist %s has delivered a %s to %s in %3.2f ms\n",deliverName,deliveredFlowerName,takenName,deliveredTime);
       pthread_cond_signal(&client_c);
       pthread_mutex_unlock(&my_mutex);


  // }
    pthread_exit(0);
 }





void  INThandler(int sig) {
    signal(sig, SIG_IGN);


    exit(0);

}