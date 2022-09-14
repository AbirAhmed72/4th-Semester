#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<semaphore.h>

int readcount=0, writecount=0, count=0;
sem_t rmutex, wmutex, readTry, resource;

pthread_t writerThreads[1000], readerThreads[1000];

void *reader(void *val){
    int readerNumber = *(int*)val;

    sem_wait(&readTry);
    sem_wait(&rmutex);

    readcount++;

    if (readcount == 1)          //checks if you are first reader
        sem_wait(&resource);    //if you are first reader, lock  the resource

    sem_post(&rmutex);            //release entry section for other readers
    sem_post(&readTry); 

    printf("Reader no.%d is reading count %d\n", readerNumber, count);       //critical section

    sem_wait(&rmutex);

    readcount--;                 //indicate you're leaving

    if (readcount == 0)          //checks if you are last reader leaving
        sem_post(&resource);          //if last, you must release the locked resource

    sem_post(&rmutex); 

}

void *writer(void *val){
    int writerNumber = *(int*)val;

    sem_wait(&wmutex);                  //reserve entry section for writers - avoids race conditions

    writecount++;                //report yourself as a writer entering

    if (writecount == 1)         //checks if you're first writer
        sem_wait(&readTry);

    sem_post(&wmutex);

    sem_wait(&resource);
    count++;
    printf("Writer no.%d is writing count %d\n", writerNumber, count);    //critical section
    sem_post(&resource);

    sem_wait(&wmutex);                  //reserve exit section
    writecount--;                //indicate you're leaving

    if (writecount == 0)         //checks if you're the last writer
        sem_post(&readTry);              //if you're last writer, you must unlock the readers. Allows them to try enter CS for reading

    sem_post(&wmutex); 

}
int main(){
    
	int n;
    printf("Enter the number of readers/writers: ");
    scanf("%d",&n);

    sem_init(&rmutex, 0, 1);
    sem_init(&wmutex, 0, 1);
    sem_init(&readTry, 0, 1);
    sem_init(&resource, 0, 1);
	
	clock_t begin_time = clock();
	
	for(int i=0; i<n; i++){
    		int *save_i = (int*)malloc(sizeof(int));
    		*save_i=i;
    		pthread_create(&writerThreads[i], NULL, writer, (void*)save_i);
            pthread_create(&readerThreads[i], NULL, reader, (void*)save_i);
	}
	
	for(int i=0; i<n; i++){
	    pthread_join(writerThreads[i], NULL);
        pthread_join(readerThreads[i], NULL);
	}
	
	clock_t end_time = clock();
	
	printf("Number of 1's(Using Synchronization): %d\n Time taken=%.2lf\n",count, (double)(end_time-begin_time)/CLOCKS_PER_SEC);
	
    sem_destroy(&rmutex);
    sem_destroy(&wmutex);
    sem_destroy(&readTry);
    sem_destroy(&resource);

	return 0;
}