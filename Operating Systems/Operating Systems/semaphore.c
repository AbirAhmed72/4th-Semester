#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<semaphore.h>

#define row 3
#define column 9000000

sem_t semaphore;
int count; 
pthread_t threads[row];

int matrix[row][column];

void *workerSemaphore(void *val){

    int ROW = *(int*)val;
    
// 	sem_wait(&semaphore);
	
    for(int i=0; i<column; i++){
        
        sem_wait(&semaphore);
        
        if(matrix[ROW][i]==1){
   	   	count++;    
   	}
   	
   	sem_post(&semaphore);
    }
    
// 	sem_post(&semaphore);
}

int main(){
    
	for(int i=0; i<row; i++){
    		for(int j=0; j<column; j++){
        		matrix[i][j]=1;
    		}
	}
	
	sem_init(&semaphore, 0, 1);
	
	clock_t begin_time = clock();
	
	for(int i=0; i<row; i++){
    		int *save_i = (int*)malloc(sizeof(int));
    		*save_i=i;
    		pthread_create(&threads[i], NULL, workerSemaphore, (void*)save_i);
	}
	
	for(int i=0; i<row; i++){
	    pthread_join(threads[i], NULL);
	}
	
	clock_t end_time = clock();
	
	printf("Number of 1's(Using Synchronization): %d\n Time taken=%.2lf\n",count, (double)(end_time-begin_time)/CLOCKS_PER_SEC);
	
	return 0;
}
