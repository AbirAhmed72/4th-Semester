/**
 * Matrix (N*N) multiplication with multiple threads.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

const int N;
int matrix1[10][10], matrix2[10][10], ans[10][10];

void *multi(void *arg) {
	int r = *(int *) arg;

	for(int i = 0; i < 9; i++) {
		int tot = 0;
		for(int j = 0; j < 9; j++) {
			tot += matrix1[r][j] * matrix2[j][i];
		}
		ans[r][i] = tot;
	}
}

int main() {
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			matrix1[i][j] = 1;
		}
	}
	
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			matrix2[i][j] = 2;
		}
	}


  int i;
  double sum = 0;
  struct timeval tstart, tend;
  double exectime;
  pthread_t  threads[10];
  int *tid;

  gettimeofday( &tstart, NULL );
  for ( i = 0; i < 9; ++i ) {
    	*tid = i;
    	pthread_create( &threads[i], NULL, multi, (void *)tid );
	//pthread_join( threads[i], NULL );
  }

  for ( i = 0; i < 9; ++i ) {
    pthread_join( threads[i], NULL );
  }
  gettimeofday( &tend, NULL );


  exectime = (tend.tv_sec - tstart.tv_sec) * 1000.0; // sec to ms
  exectime += (tend.tv_usec - tstart.tv_usec) / 1000.0; // us to ms   

  printf( "Number of threads: %d\tExecution time:%.3lf sec\n", 9, exectime/1000.0);


	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			printf("%d ", matrix1[i][j]);
		}	
		printf("\n");
	}
	
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			printf("%d ", matrix2[i][j]);
		}	
		printf("\n");
	}


	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			printf("%d ", ans[i][j]);
		}	
		printf("\n");
	}

  return 0;
}























