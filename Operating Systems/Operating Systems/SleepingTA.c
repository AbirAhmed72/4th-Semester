/* sleeping TA problem 
A university computer science department has a teaching assistant (TA) who helps 
undergraduate students with their programming assignments during regular office 
hours. The TA's office is rather small and has room for only one desk with a 
chair and computer. There are three chairs in the hallway outside the office 
where students can sit and wait if the TA is currently helping another student. 
When there are no students who need help during office hours, the TA sits at the 
desk and takes a nap. If a student arrives during office hours and finds the TA 
sleeping, the student must awaken the TA to ask for help. If a student arrives 
and finds the TA currently helping another student, the student sits on one of 
the chairs in the hallway and waits. If no chairs are available, the student will 
come back at a later time.

Solution:
Using Pthreads, n students are created. Each student, as well as the TA, run as a 
separate thread. Student threads alternate between programming for a period of 
time and seeking help from the TA. If the TA is available, they obtain help. 
Otherwise, they either sit in a chair in the hallway, or if no chairs are 
available, resume programming and seek help at a later time. If a student arrives 
and notices that the TA is sleeping, the student notifies the TA using a semaphore.
When the TA finishes helping a student, the TA checks to see if there are students
waiting for help in the hallway. If so, the TA helps each of these students in 
turn. If no students are present, the TA returns to napping.

The TA and each student thread print their state and threadID (student number).

The program can take 0 or 1 command line parameters. The number of 
students present can be specified as a command line parameter. If this parameter 
is not included, the number of students defaults to 5.
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> // memset 
#include <pthread.h> // pthread_t, pthread_create, pthread_join 
#include <semaphore.h> // sem_init, sem_wait, sem_post 
#include <time.h> 
#include <unistd.h>
#define NUM_SEAT 3 
  
#define SLEEP_MAX 5 
  
 //sematphores 
 sem_t sem_stu; 
 sem_t sem_ta; 
  
 //sem_t mutex; 
 pthread_mutex_t mutex; 
  
 int chair[3]; 
 int count = 0; //number of waiting students 
 int next_seat = 0; 
 int next_teach = 0; 
  
 void rand_sleep(void); 
 void* stu_programming(void* stu_id); 
 void* ta_teaching(); 
  
 int main(int argc, char **argv){ 
 
    //thread(s) 
    pthread_t *students; 
    pthread_t ta; 
     
    int* student_ids; 
    int student_num; 
     
    //index 
    int i; 
 
    //get number of students from user 
    printf("How many students? "); 
    scanf("%d", &student_num); 

if (student_num==0)
{
printf ("TA sleeping, no students! \n");
exit(-1);
}

    //initialize 
    students = (pthread_t*)malloc(sizeof(pthread_t) * student_num); 
    student_ids = (int*)malloc(sizeof(int) * student_num); 
    memset(student_ids, 0, student_num); 

    sem_init(&sem_stu,0,0); 
    sem_init(&sem_ta,0,1); 
     
    //set random 
    srand(time(NULL)); 
  
    //sem_init(&mutex,0,1); 
    pthread_mutex_init(&mutex,NULL); 
  
    //create thread 
    pthread_create(&ta,NULL,ta_teaching,NULL); 
 
    //create threads 
    for(i=0; i<student_num; i++) 
    { 
        student_ids[i] = i+1; 
        pthread_create(&students[i], NULL, stu_programming, (void*) &student_ids[i]); 
    }  
     
    pthread_join(ta, NULL); 
     
    for(i=0; i<student_num;i++) 
    { 
        pthread_join(students[i],NULL); 
    }    
     
    return 0; 
 } 
  
 void* stu_programming(void* stu_id) 
 { 
    int id = *(int*)stu_id; 
  
    printf("[stu] student %d is leaving for TA office\n",id);        
     
    while(1) 
    { 
        rand_sleep(); 
  
        //sem_wait(&mutex); 
        pthread_mutex_lock(&mutex); 
 
 
if(count < NUM_SEAT)     
        { 
            chair[next_seat] = id; 
            count++; 
             
            printf("    [stu] student %d is waiting seated at hallway\n",id); 
            printf("waiting students : [1] %d [2] %d [3] %d\n",chair[0],chair[1],chair[2]); 
            next_seat = (next_seat+1) % NUM_SEAT; 
             
            //sem_post(&mutex); 
            pthread_mutex_unlock(&mutex); 
     
            //wakeup ta 
            sem_post(&sem_stu); 
            sem_wait(&sem_ta); 
            return;
        } 
        else //no more chairs 
        { 
            //sem_post(&mutex); 
            pthread_mutex_unlock(&mutex); 
             
            printf("[stu] no more chairs. student %d is outside hallway and will be back later\n",id);       
        } 
    }                
 } 
 
 
 void* ta_teaching() 
 { 
    while(1) 
    { 
        sem_wait(&sem_stu);  
         
        //sem_wait(&mutex); 
        pthread_mutex_lock(&mutex); 
         
        printf("        [ta] TA is teaching student %d\n",chair[next_teach]);    
        chair[next_teach]=0; 
        count--; 
         
        printf("waiting students : [1] %d [2] %d [3] %d\n",chair[0],chair[1],chair[2]); 
        next_teach = (next_teach + 1) % NUM_SEAT; 
         
        rand_sleep(); 
 
 
        printf("        [ta] teaching finish.\n");   
 
 
        //sem_post(&mutex); 
        pthread_mutex_unlock(&mutex); 
 
 
        sem_post(&sem_ta); 

        sem_wait(&sem_ta);
        if(count==0)
        {
            printf("TA falls asleep");
        }
        sem_post(&sem_ta);
    }    
 } 
 
 
 void rand_sleep(void){ 
    int time = rand() % SLEEP_MAX + 1; 
    sleep(time); 
 }/* sleeping TA problem 
A university computer science department has a teaching assistant (TA) who helps 
undergraduate students with their programming assignments during regular office 
hours. The TA's office is rather small and has room for only one desk with a 
chair and computer. There are three chairs in the hallway outside the office 
where students can sit and wait if the TA is currently helping another student. 
When there are no students who need help during office hours, the TA sits at the 
desk and takes a nap. If a student arrives during office hours and finds the TA 
sleeping, the student must awaken the TA to ask for help. If a student arrives 
and finds the TA currently helping another student, the student sits on one of 
the chairs in the hallway and waits. If no chairs are available, the student will 
come back at a later time.

Solution:
Using Pthreads, n students are created. Each student, as well as the TA, run as a 
separate thread. Student threads alternate between programming for a period of 
time and seeking help from the TA. If the TA is available, they obtain help. 
Otherwise, they either sit in a chair in the hallway, or if no chairs are 
available, resume programming and seek help at a later time. If a student arrives 
and notices that the TA is sleeping, the student notifies the TA using a semaphore.
When the TA finishes helping a student, the TA checks to see if there are students
waiting for help in the hallway. If so, the TA helps each of these students in 
turn. If no students are present, the TA returns to napping.

The TA and each student thread print their state and threadID (student number).

The program can take 0 or 1 command line parameters. The number of 
students present can be specified as a command line parameter. If this parameter 
is not included, the number of students defaults to 5.
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> // memset 
#include <pthread.h> // pthread_t, pthread_create, pthread_join 
#include <semaphore.h> // sem_init, sem_wait, sem_post 
#include <time.h> 
#include <unistd.h>
#define NUM_SEAT 3 
  
#define SLEEP_MAX 5 
  
 //sematphores 
 sem_t sem_stu; 
 sem_t sem_ta; 
  
 //sem_t mutex; 
 pthread_mutex_t mutex; 
  
 int chair[3]; 
 int count = 0; //number of waiting students 
 int next_seat = 0; 
 int next_teach = 0; 
  
 void rand_sleep(void); 
 void* stu_programming(void* stu_id); 
 void* ta_teaching(); 
  
 int main(int argc, char **argv){ 
 
    //thread(s) 
    pthread_t *students; 
    pthread_t ta; 
     
    int* student_ids; 
    int student_num; 
     
    //index 
    int i; 
 
    //get number of students from user 
    printf("How many students? "); 
    scanf("%d", &student_num); 

if (student_num==0)
{
printf ("TA sleeping, no students! \n");
exit(-1);
}

    //initialize 
    students = (pthread_t*)malloc(sizeof(pthread_t) * student_num); 
    student_ids = (int*)malloc(sizeof(int) * student_num); 
    memset(student_ids, 0, student_num); 

    sem_init(&sem_stu,0,0); 
    sem_init(&sem_ta,0,1); 
     
    //set random 
    srand(time(NULL)); 
  
    //sem_init(&mutex,0,1); 
    pthread_mutex_init(&mutex,NULL); 
  
    //create thread 
    pthread_create(&ta,NULL,ta_teaching,NULL); 
 
    //create threads 
    for(i=0; i<student_num; i++) 
    { 
        student_ids[i] = i+1; 
        pthread_create(&students[i], NULL, stu_programming, (void*) &student_ids[i]); 
    }  
     
    pthread_join(ta, NULL); 
     
    for(i=0; i<student_num;i++) 
    { 
        pthread_join(students[i],NULL); 
    }    
     
    return 0; 
 } 
  
 void* stu_programming(void* stu_id) 
 { 
    int id = *(int*)stu_id; 
  
    printf("[stu] student %d is leaving for TA office\n",id);        
     
    while(1) 
    { 
        rand_sleep(); 
  
        //sem_wait(&mutex); 
        pthread_mutex_lock(&mutex); 
 
 
if(count < NUM_SEAT)     
        { 
            chair[next_seat] = id; 
            count++; 
             
            printf("    [stu] student %d is waiting seated at hallway\n",id); 
            printf("waiting students : [1] %d [2] %d [3] %d\n",chair[0],chair[1],chair[2]); 
            next_seat = (next_seat+1) % NUM_SEAT; 
             
            //sem_post(&mutex); 
            pthread_mutex_unlock(&mutex); 
     
            //wakeup ta 
            sem_post(&sem_stu); 
            sem_wait(&sem_ta); 
            return;
        } 
        else //no more chairs 
        { 
            //sem_post(&mutex); 
            pthread_mutex_unlock(&mutex); 
             
            printf("[stu] no more chairs. student %d is outside hallway and will be back later\n",id);       
        } 
    }                
 } 
 
 
 void* ta_teaching() 
 { 
    while(1) 
    { 
        sem_wait(&sem_stu);  
         
        //sem_wait(&mutex); 
        pthread_mutex_lock(&mutex); 
         
        printf("        [ta] TA is teaching student %d\n",chair[next_teach]);    
        chair[next_teach]=0; 
        count--; 
         
        printf("waiting students : [1] %d [2] %d [3] %d\n",chair[0],chair[1],chair[2]); 
        next_teach = (next_teach + 1) % NUM_SEAT; 
         
        rand_sleep(); 
 
 
        printf("        [ta] teaching finish.\n");   
 
 
        //sem_post(&mutex); 
        pthread_mutex_unlock(&mutex); 
 
 
        sem_post(&sem_ta); 

        sem_wait(&sem_ta);
        if(count==0)
        {
            printf("TA falls asleep");
        }
        sem_post(&sem_ta);
    }    
 } 
 
 
 void rand_sleep(void){ 
    int time = rand() % SLEEP_MAX + 1; 
    sleep(time); 
 }