# Exercice 1

## What was used

Everything that was in the `pid.h` library was put directly in the `pid.c` file as a header.

- `allocate_map()` uses the `malloc` function to allocate a memory space. However this allocate space was not initialized to 0; so I have to initialize it to 0. Must not forget to `free` this memory space.
- `allocate_pid()` uses the bitmap method. If an available slot was found in the memory space, then it becomes unavailable for others. This is the critical section. 
- `release_pid()` is pretty straight-forward. If the memory space at index=pid is not available, then set it to 0, so that it becomes available again.

## Running the code 

Open the terminal and run this code normally.

```bash
gcc -o pid pid.c
./pid
```
Since a `main` function was not used, I used one to debug and visualize everything. Also, max and min need to be changed to make the debugging process easier. 

