#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>         // for the sleep()

#include <pthread.h>
#include <time.h>

#include <sys/types.h>
#define MIN_PID 300
#define MAX_PID 5000

#define NUM_THREADS 1000

int* pid_map;   // pointer for the mapping

pthread_mutex_t lock;

// Creates and initializes a data structure for representing pids; 
// returns -1 if unsuccessful, 1 if successful.
int allocate_map(void){
    int i = 0;
    pid_map = (int*) malloc((MAX_PID - MIN_PID +1) * sizeof(int));

    //initiliazing the allocate memory to 0
    while(i < MAX_PID - MIN_PID+1){
        pid_map[i] = 0;
        i++;
    }

    if(pid_map == NULL)     // if empty memory location then it means it was unsuccesful
        return -1;
    return 1;
}

// Allocates and returns a pid;
// returns -1 if unable to allocate a pid (all pids are in use) 
int allocate_pid(void){
   
    int i = 0;
    
    // bitmap method
    // check each index of the memory space, if available ok
    while(i < MAX_PID - MIN_PID+1){
        if(pid_map[i] == 0){
            pthread_mutex_lock(&lock);
            pid_map[i] = 1;
            pthread_mutex_unlock(&lock);
            return i+MIN_PID;
        }
        i++;
    }

    return -1;
}

// Releases a pid
void release_pid(int pid){

    pthread_mutex_lock(&lock);
    // condition of errors
    if(pid < MIN_PID){
        printf("Error PID %d does not exist.\n", pid);
    }
    if(pid > MAX_PID){
        printf("Error PID %d does not exist.\n", pid);
    } 
    if(pid == -1){
        printf("Error PID does not exist.\n\n");
    }

    // minus MIN_PID because index of mapping area start at 0
    pid_map[pid-MIN_PID] = 0;
    //printf("should be re-initialize to 0\n");
    pthread_mutex_unlock(&lock);
}

// returns a random time in the range of 1 to 10
int randomTime(){
    time_t time_seed;
    srand((unsigned) time(&time_seed));
    return 1+rand()%10;
}

// corresponding to the routine for pthread_create
// each thread will request a pid, sleep and released the pid.
void *myThread(void* threadID){
    int tid = (int) threadID;
    int pid;

    while(1){
        // request pid
        pid = allocate_pid();
        if(pid == -1){
            break;     // error
        }

    printf("Thread %d - PID %d allocated.\n", tid, pid);

    // sleep for 1 to 10 secs
    sleep(randomTime());

    // release the pid
    release_pid(pid);
    printf("Thread %d - PID %d released.\n", tid, pid);

    }
    // after a pid release, make this pid available again
    pthread_exit(NULL);
}

// the whole process of creating multithreading 
int createProcess(){
    int i = 0;
    int b1, b2;     // boolean to test if there is an error
    pthread_t thread_id[NUM_THREADS];

    while(i < NUM_THREADS){
        b1 = pthread_create(&thread_id[i], NULL, myThread,(void*)i+1);

        if(b1 != 0){
            printf("Error: thread %d could not be created.\n", i+1);
            return -1;
        }
        i++;
    }

    i = 0; 

    while(i < NUM_THREADS){
        b2 = pthread_join(thread_id[i], NULL);

        if(b2 != 0){
            printf("Error: thread %d could not be joined.\n", i+1);
            return -1;
        }
        i++;
    }

    return 0;
}

int main(){

    allocate_map();

    for(int i = 0; i < MAX_PID - MIN_PID +1; i++){
        printf("available %d - PID %d\n", pid_map[i], i+MIN_PID);
    }
    printf("------------------\n");
    printf("------------------\n");
    createProcess();
    
    pthread_mutex_destroy(&lock);
    free(pid_map);
    return 0;
}
