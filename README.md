# OpenMP Learning with C

A practice repository for learning OpenMP (Open Multi-Processing) concepts in C.

## Build Command

```bash
gcc -fopenmp <program_name>.c -o <program_name>
```

## Implementations

### 1. **NP-1** - C++ Parallel Program
- Basic C++ parallel programming example
- Located in: `NP-1/program.cpp`

### 2. **NP-2-C** - OpenMP Basics with C

#### `program.c` - Basic Parallel Region
**What it does:**
- Creates a parallel region using `#pragma omp parallel`
- Each thread prints its thread ID and total number of threads
- Demonstrates basic thread identification

**Key Concepts:**
- `#pragma omp parallel` - Creates a parallel block where all threads execute the enclosed code
- `omp_get_thread_num()` - Returns the ID of the current thread (0-indexed)
- `omp_get_num_threads()` - Returns the total number of threads in the team

**Build & Run:**
```bash
gcc -fopenmp program.c -o program
./program
```

**Expected Output:** (example with 4 threads)
```
Thread 0 of 4 says hello
Thread 1 of 4 says hello
Thread 2 of 4 says hello
Thread 3 of 4 says hello
```

---

#### `settings.c` - Setting Thread Count
**What it does:**
- Explicitly sets the number of threads using `omp_set_num_threads(4)`
- All threads execute the parallel block
- Demonstrates thread count configuration

**Key Concepts:**
- `omp_set_num_threads(n)` - Sets the number of threads for subsequent parallel regions
- Useful for controlling parallelism level regardless of system CPU count

**Build & Run:**
```bash
gcc -fopenmp settings.c -o settings
./settings
```

**Expected Output:**
```
Runs in 4 threads
Runs in 4 threads
Runs in 4 threads
Runs in 4 threads
```

---

#### `For_Loop_1.c` - Parallel For Loop with Iteration Distribution
**What it does:**
- Uses `#pragma omp parallel for` to parallelize a for loop
- Distributes loop iterations (1 to 10) among available threads
- Each thread executes different iterations simultaneously
- Accumulates the sum of all iterations (1+2+3+...+10 = 55)

**Key Concepts:**
- `#pragma omp parallel for` - Combines parallel region creation with automatic loop iteration distribution
- Loop iterations are automatically divided among threads
- **Important:** Each thread executes one iteration at a time
- Iterations are NOT guaranteed to execute in order (due to thread scheduling)

**Build & Run:**
```bash
gcc -fopenmp For_Loop_1.c -o forloop
./forloop
```

**Example Output:**
```
Iteration 2, executed by thread 1 
Iteration 4, executed by thread 3
Iteration 5, executed by thread 4
Iteration 3, executed by thread 2
Iteration 6, executed by thread 5
Iteration 7, executed by thread 6
Iteration 8, executed by thread 7 
Iteration 9, executed by thread 8
Iteration 1, executed by thread 0
Iteration 10, executed by thread 9
Total is        :-       55
```

**Detailed Explanation of Output:**

| Aspect | Explanation |
|--------|-------------|
| **Order is Random** | Iterations don't execute in order (1,2,3...). You might see 2,4,5,3,6... This is because threads are scheduled independently by the OS |
| **Different Threads** | Each iteration is handled by a different thread (thread 0 does iteration 1, thread 1 does iteration 2, etc.) |
| **Thread IDs** | Threads are numbered from 0 to N-1 (0-indexed). With 10 threads: 0,1,2,3,4,5,6,7,8,9 |
| **Loop Variable** | "Iteration %d" shows the loop variable value (i=1 to 10), NOT the execution order |
| **Thread Assignment** | "executed by thread %d" shows which thread handles that particular iteration |
| **Sum Calculation** | Each iteration adds its value to sum: 1+2+3+4+5+6+7+8+9+10 = 55 |
| **Total Output** | The final sum appears after ALL iterations complete (synchronization happens automatically) |

**How It Works Step-by-Step:**
1. OpenMP creates 10 threads (by default, one per loop iteration or based on system)
2. Each thread gets assigned one or more loop iterations
3. Threads execute their iterations in parallel (not necessarily in order)
4. Each thread prints its iteration number and thread ID
5. All threads synchronize at the end of the loop (implicit barrier)
6. Main thread prints the total sum

**Why is the sum correct (55) despite random order?**
- Even though iterations execute out of order, each iteration executes exactly ONCE
- All values 1 through 10 are added to sum
- Mathematical result is always the same: 1+2+3+...+10 = 55

---



1. **Start with `program.c`** - Understand basic parallel regions and thread identification
2. **Then `settings.c`** - Learn to control thread count explicitly
3. **Next steps** - Explore work-sharing constructs (for loops, sections), synchronization, and data sharing

## Useful OpenMP Pragmas Reference

| Pragma | Purpose |
|--------|---------|
| `#pragma omp parallel` | Create a parallel region |
| `#pragma omp for` | Parallelize a for loop |
| `#pragma omp parallel for` | Combined parallel + for |
| `#pragma omp critical` | Mutual exclusion (one thread at a time) |
| `#pragma omp barrier` | Synchronization point |

## Compilation Tips

- Always compile with `-fopenmp` flag (GCC/Clang)
- On MSVC: `/openmp` flag
- Set thread count via `OMP_NUM_THREADS` environment variable before running