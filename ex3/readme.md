# Exercice 3

## What was used

The code for exercice 2 was copied and I just modified/added some functions.

- the `lock` of mutex lock must be add as a global variable.
- mutex lock has to be add on two functions. The critical section that was mentionned in exercice 1; so in the `allocate_pid`. But also in the `release_pid`. 
- after using a `pthread_mutex_lock`, this lock must be destroyed.

## Running the code 

Open the terminal and run this code as following:

```bash
gcc ex3.c -lpthread -o ex3
./ex3
```
This file does compile even though there is a warning. This is due to the last argument of pthread_create. The type of the agument is not correct, but I could not change it, since I needed each iteration=thread.

As for debugging and visualizing purpose, I changed the numbers of threads, max_pid and min_pid. 

To stop the program, CTRL + C.