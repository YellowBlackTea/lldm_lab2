# Exercice 2

## What was used

The code for exercice 1 was copied and I just modified/added some functions.

- add `pthread.h` library to be able to use thread.
- add `unistd.h` library to be able to use sleep().
- `randomTime()` is the function returning a random time between 1 sec to 10 sec. `time.h` library must be add.
- `*myTread()` is the (sub)routine of thrad. Each thread will request a pid, sleep and then release this pid. 
- `createProcess())` is the function creating a process. It will create each thread and join them.

## Running the code 

Open the terminal and run this code as following:

```bash
gcc ex2.c -lpthread -o ex2
./ex2
```
This file does compile evne though there is a warning. This is due to the last argument of pthread_create. The type of the agument is not correct, but I could not change it, since I needed each iteration=thread.

As for debugging and visualizing purpose, I changed the numbers of threads, max_pid and min_pid. 

To stop the program, CTRL + C.