
/*

	NAME 		: MESUT
	SURNAME 	: BUNALDI
	STUDENT ID 	: 111044077
	HOMEWORK 	: 2

*/

#include <stdio.h>
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
#include <signal.h>
#include <time.h>

#define PI 3.14159265


int main(int argc,char  *argv[]) {
   

	
	srand(time(NULL));


	if(argc==7){
		
		if( (strcmp(argv[1],"-N")!=0) || (strcmp(argv[3],"-X")!=0) || (strcmp(argv[5],"-M")!=0) || ((atoi(argv[2])<1)) || ((atoi(argv[6])<1)) ){

			printf("Wrong parameter...\n");
			

		}else{

			int n=atoi(argv[2]);//sonlu dizinin eleman sayisi
			char filename[strlen(argv[4])];//dosya adi
			strcpy(filename,argv[4]);
			int m=atoi(argv[6]);//dosyaya yazilabilecek maksimum dizi sayisi
			pid_t pid; //proccess id
			int fd1,fd2,size[1];
			size[0]=0;
			struct flock lock;
			memset(&lock,0,sizeof(lock));	
				
			fd1=open(filename,O_CREAT | O_RDWR | O_TRUNC | S_IRUSR | S_IWUSR ,0640);
			close(fd1);
			fd1=open(filename,O_RDWR);
			fd2=dup(fd1);
		

			int fdC=open("size.dat",O_CREAT | O_RDWR | O_TRUNC | S_IRUSR | S_IWUSR ,0640);
			close(fdC);

			fdC=open("size.dat",O_RDWR | S_IRUSR | S_IWUSR ,0640);
			write(fdC,size,sizeof(int));
			


			pid=fork();//iki proses işlem yapmaya başladı
			

		
			//child proccess Proccess B
			if(pid==0){
					
					char emptyLine[sizeof(int)*n];
					memset(emptyLine,' ',sizeof(int)*n);
					double tmp;
					int lineSize2[1];
					double function[n];
    								
				for (;; ){
					
					lock.l_type=F_WRLCK;
					fcntl(fdC,F_SETLKW,&lock);
					fcntl(fd1,F_SETLKW,&lock);	
					fcntl(fd2,F_SETLKW,&lock);						
					lseek(fdC,0,SEEK_SET);
					read(fdC,lineSize2,sizeof(int));
					
					if (*lineSize2>0)
					{
						lseek(fd2,sizeof(double)*n*(lineSize2[0]-1),SEEK_SET);						

						printf("Process B: the dft of line %d (",*lineSize2);
						for (int i = 0; i < n; ++i)
						{
							
							read(fd2,&tmp,sizeof(double));						
							function[i]=tmp;
							printf(" %2.1f ", tmp);
						}
						printf(") : " );
						double pi2 =  2*PI;
						double angleTerm,cosineA,sineA;
						double invs = 1.0 / n;
						double output_seq1[n] ;
						double output_seq2[n];
						for(unsigned int y = 0;y < n;y++) {
							 output_seq1[y] = 0;
							output_seq2[y] = 0;
							for(unsigned int x = 0;x < n;x++) {
								angleTerm = pi2 * y * x * invs;
								cosineA = cos(angleTerm);
								sineA = sin(angleTerm);
								output_seq1[y] += function[x] * cosineA ;
								output_seq2[y] -= function[x] * sineA;
							}
							
						}
						
						for (int i = 0; i < n; ++i)
						{
							printf("%2.2f+%2.2fi ",output_seq1[i],output_seq2[i]);
							
						}
						
						printf("\n" );   

						lseek(fd2,sizeof(double)*n*(lineSize2[0]-1),SEEK_SET);
						write(fd2,emptyLine,sizeof(double)*n);

						lineSize2[0]=lineSize2[0]-1;
						lseek(fdC,0,SEEK_SET);
						write(fdC,lineSize2,sizeof(int));
					}					

				lock.l_type=F_UNLCK;
				fcntl(fdC,F_SETLKW,&lock);
				fcntl(fd1,F_SETLKW,&lock);	
				fcntl(fd2,F_SETLKW,&lock);	
				}		
			}
			
			else{//parent proccess Proccess A	
				double tmp,seq[n];
				int lineSize[1];
				for (; ; )
				{


			
					lock.l_type=F_WRLCK;
					fcntl(fdC,F_SETLKW,&lock);
					fcntl(fd1,F_SETLKW,&lock);	
					fcntl(fd2,F_SETLKW,&lock);				
					lseek(fdC,0,SEEK_SET);				
					read(fdC,lineSize,sizeof(int));
					

					if (*lineSize!=m)
								{
									
									printf("Process A: i’m producing a random sequence for line %d :",*lineSize+1);
									for (int i = 0; i < n; ++i)
										{
											tmp=rand()%100;
											seq[i]=tmp;
											printf(" %2.1f ",tmp );	
											
														
										}
									
									printf("\n");
									lseek(fd1,sizeof(double)*n*(lineSize[0]),SEEK_SET);
									write(fd1,seq,sizeof(double)*n);
									lineSize[0]=(*lineSize)+1;
									lseek(fdC,0,SEEK_SET);
									write(fdC,lineSize,sizeof(int));
									
								}			
					
					
						
					lock.l_type=F_UNLCK;
					fcntl(fdC,F_SETLKW,&lock); 
					fcntl(fd1,F_SETLKW,&lock);	
					fcntl(fd2,F_SETLKW,&lock);	
				}
					
				

			}
		close(fd1);
		close(fd2);
		close(fdC);

		}

}else
	printf("Missing parameter...\n");
	return 0;

}

