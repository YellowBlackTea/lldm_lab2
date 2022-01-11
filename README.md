# Laboratory 2

An operating system's *pid manager* is responsible for managing process identifiers. When a process is first created, it is assigned a unique pid by the pid manager. The pid is returned to the pid manager when the process completes execution, and the manager may later reassign this pid. Process identifiers were discussed in the "Process Management" section of our Lecture 2 and are also discussed more in-depth in Section 3.3 of the book. What is most important here is to recognize that process identifiers must be unique, no two active processes can have the same pid. 

## Excercise 1

Write your *own code* in C language that implements a *pid manager*. You don't have to worry about creating the processes or anything related to that, your focus should be exclusively on the component of managing the pids. This means that you need to work with the structure you think is the most appropriate to solve this problem and any surrounding code to achieve your solution.

Use the following constants to identify the range of possible pid values: 
```c
#define MIN_PID 300 
#define MAX_PID 5000
```
You may use any data structure of your choice to represent the availability of process identifiers. One strategy is to adopt what Linux has done and use a bitmap in which a value of 0 at position i indicates that a process id of value i is available and a value of 1 indicates that the process id is currently in use. 

Implement the following API for obtaining and releasing a pid:

- Creates and initializes a data structure for representing pids; returns -1 if unsuccessful, 1 if successful.
```c
int allocate_map (void)
```

- Allocates and returns a pid; returns -1 if unable to allocate a pid (all pids are in use) 
```c
int allocate_pid (void)
```

- Releases a pid 
```c
void release_pid (int pid)
```

You can use the files `pid.h` and `pid.c` as a starting point.


## Excercise 2

Write your *own code* in C language that tests your pid manager by relying on threads. You will create a number of threads (e.g. 100) and each thread will request a pid, sleep for a random period of time, and then release the pod. On UNIX and Linux systems, sleeping is accomplished through the sleep() function, which is passed an integer value representing the number of seconds to sleep.

This program should test two cases:
- That all pids are used and unique. Since you are using threads, race conditions can and will occur.
- That pids rotate once you go beyond the maximum amount of available pids. When pids are released they should be reused immediately or eventually, depends on the implementation but both options are correct.

You can use the file `lab2.c` as a starting point.

You can compile it by running:
```shell
gcc -o lab2 lab2.c
./lab2
```
It has been compiled and tested in MacOS X. 

Alternatively, you can run it in Ubuntu 22.04 with Docker:
```shell
docker run --rm -ti -v $(pwd)/:/root/lab ubuntu:22.04 /bin/bash -c "cd /root/lab; apt update; apt install -y build-essential; gcc -o lab lab2.c; ./lab"
```
Or directly (and easier) with the GCC image which runs on Debian Bullseye with Docker:
```shell
docker run --rm -ti -v $(pwd)/:/root/lab gcc:11.2.0-bullseye /bin/bash -c "cd /root/lab; gcc -o lab lab2.c; ./lab"
```

## Excercise 3

Modify the lab by ensuring that the data structure used to represent the availability of the pids is safe from race conditions. Use Pthreads mutex locks.

Keep in mind that the critical section should be minimal as discussed in class (Lecture 3).

## Grading

- Plagiarism with another student and/or the internet, immediate 0 in the lab.
- Instructions on how to compile it ... 10pts
- Compiles? ... 20pts
- Exercise 1 ... 20pts
- Exercise 2 ... 30pts
- Exercise 3 ... 20pts