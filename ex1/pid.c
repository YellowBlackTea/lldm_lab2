#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define MIN_PID 300
#define MAX_PID 5000

int* pid_map;   // pointer for the mapping

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
        // if find an available slot, then block this slot so that others can't use it
        if(pid_map[i] == 0){
            //printf("pid %d needs to be allocated\n", i+MIN_PID);
            pid_map[i] = 1;
            //printf("dans allocate_pid, print du PID et de son statue: %d, %d\n", i+MIN_PID, pid_map[i]);
            return i+MIN_PID;
        }
    i++;
    }

    return -1;
}

// Releases a pid
void release_pid(int pid){

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
}

// debugg purpose
int main(){

    allocate_map();
    printf("Initializing.\n");
    for(int i = 0; i < MAX_PID - MIN_PID +1; i++){
        printf("available %d - PID %d\n", pid_map[i], i+MIN_PID);
    }
    
    free(pid_map);
    return 0;
}
