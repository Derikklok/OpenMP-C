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

### 3. **NP4C** - Finding Maximum Value with Critical Section

#### `program.c` - Parallel Maximum Finder with Synchronization
**What it does:**
- Finds the maximum value in an array using 4 parallel threads
- Uses `#pragma omp critical` to prevent data race conditions
- Demonstrates thread synchronization and shared variable protection
- Array: {4, 2, 3, 1, 5, 6, 7, 8, 9, 10} → Maximum: 10

**Key Concepts:**
- `#pragma omp parallel for num_threads(4)` - Creates exactly 4 threads and distributes loop iterations
- `#pragma omp critical` - **CRITICAL SECTION**: Only one thread can execute this code block at a time
- **RACE CONDITION**: Without critical section, multiple threads could read/write max simultaneously causing incorrect results
- **SHARED VARIABLE**: `max` is shared among all threads and needs protection

**Build & Run:**
```bash
gcc -fopenmp program.c -o np4
./np4
```

**Expected Output:**
```
max = 10
```

---

## **Backend Execution Logic - Step by Step**

### **Without Critical Section (WRONG - Race Condition):**
```
Thread 0: Reads max=4, num_array[0]=4, 4>4? NO, doesn't update
Thread 1: Reads max=4, num_array[1]=2, 2>4? NO, doesn't update
Thread 2: Reads max=4, num_array[2]=3, 3>4? NO, doesn't update
Thread 3: Reads max=4, num_array[3]=1, 1>4? NO, doesn't update
Thread 0: Reads max=4, num_array[4]=5, 5>4? YES, sets max=5
Thread 1: Reads max=5, num_array[5]=6, 6>5? YES, sets max=6 (BUT BOTH READ 4 FIRST!)
  ↑ RACE CONDITION: Multiple threads access/modify max simultaneously
```

### **With Critical Section (CORRECT - Thread Safe):**
```
Timeline of Execution with 4 Threads:
─────────────────────────────────────────────────────────────────────────

INITIALIZATION PHASE:
- max = num_array[0] = 4 (all threads share this value)
- Array = {4, 2, 3, 1, 5, 6, 7, 8, 9, 10}
- Loop iterations 0-9 divided among 4 threads
  - Thread 0: indices 0, 4, 8      (elements: 4, 5, 9)
  - Thread 1: indices 1, 5, 9      (elements: 2, 6, 10)
  - Thread 2: indices 2, 6         (elements: 3, 7)
  - Thread 3: indices 3, 7         (elements: 1, 8)

PARALLEL EXECUTION (Order can vary, but critical ensures one at a time):

Step 1 - Thread 0 enters critical section:
  Reads max=4, compares with num_array[0]=4 → 4>4? NO, skip
  Exits critical section

Step 2 - Thread 1 enters critical section:
  Reads max=4, compares with num_array[1]=2 → 2>4? NO, skip
  Exits critical section

Step 3 - Thread 2 enters critical section:
  Reads max=4, compares with num_array[2]=3 → 3>4? NO, skip
  Exits critical section

Step 4 - Thread 3 enters critical section:
  Reads max=4, compares with num_array[3]=1 → 1>4? NO, skip
  Exits critical section

Step 5 - Thread 0 enters critical section (re-enters for iteration 4):
  Reads max=4, compares with num_array[4]=5 → 5>4? YES
  Updates max = 5
  Exits critical section

Step 6 - Thread 1 enters critical section (for iteration 5):
  Reads max=5, compares with num_array[5]=6 → 6>5? YES
  Updates max = 6
  Exits critical section

Step 7 - Thread 2 enters critical section (for iteration 6):
  Reads max=6, compares with num_array[6]=7 → 7>6? YES
  Updates max = 7
  Exits critical section

Step 8 - Thread 3 enters critical section (for iteration 7):
  Reads max=7, compares with num_array[7]=8 → 8>7? YES
  Updates max = 8
  Exits critical section

Step 9 - Thread 0 enters critical section (for iteration 8):
  Reads max=8, compares with num_array[8]=9 → 9>8? YES
  Updates max = 9
  Exits critical section

Step 10 - Thread 1 enters critical section (for iteration 9):
  Reads max=9, compares with num_array[9]=10 → 10>9? YES
  Updates max = 10
  Exits critical section

SYNCHRONIZATION BARRIER (Implicit at end of parallel for):
- All threads wait here until every thread completes
- Ensures main thread doesn't print result before all comparisons done

FINAL PHASE:
- Main thread continues
- Prints: max = 10 ✓ (Correct answer!)
```

---

## **Why Critical Section is Essential:**

| Without Critical | With Critical |
|-----------------|---------------|
| ❌ Multiple threads read old max value before update | ✅ Each thread reads latest max value |
| ❌ Multiple threads write max simultaneously (lost updates) | ✅ Only one thread writes at a time |
| ❌ Result might be incorrect (e.g., 7 instead of 10) | ✅ Result is always correct |
| ❌ Unpredictable behavior (changes each run) | ✅ Consistent, deterministic output |

---

#### `program_1.c` - Barrier Synchronization
**What it does:**
- Creates 4 threads that simulate different amounts of work
- Uses `#pragma omp barrier` to synchronize all threads
- Demonstrates thread waiting and synchronization points
- Each thread has a different sleep time to simulate varied workloads

**Key Concepts:**
- `#pragma omp parallel num_threads(4)` - Creates exactly 4 threads
- `Sleep()` - Simulates work by making threads wait for different durations
- `#pragma omp barrier` - Creates a synchronization point where all threads must wait
- Thread timing and coordination demonstration

**Build & Run:**
```bash
gcc -fopenmp program_1.c -o barrier
./barrier
```

**Expected Output:**
```
Thread 0: Starting work
Thread 1: Starting work
Thread 2: Starting work
Thread 3: Starting work
Thread 0: Finished work        (after 1 second)
Thread 1: Finished work        (after 2 seconds)
Thread 2: Finished work        (after 3 seconds)
Thread 3: Finished work        (after 4 seconds)
Thread 0: All threads have finished!
Thread 1: All threads have finished!
Thread 2: All threads have finished!
Thread 3: All threads have finished!
```

**Backend Execution Timeline:**
```
Time(s) │ Thread 0   │ Thread 1   │ Thread 2   │ Thread 3
────────┼───────────┼───────────┼───────────┼──────────
   0    │ START     │ START     │ START     │ START
   1    │ FINISH    │    ⋮      │    ⋮      │    ⋮
        │ (WAIT)    │           │           │
   2    │ (WAIT)    │ FINISH    │    ⋮      │    ⋮
        │           │ (WAIT)    │           │
   3    │ (WAIT)    │ (WAIT)    │ FINISH    │    ⋮
        │           │           │ (WAIT)    │
   4    │ (WAIT)    │ (WAIT)    │ (WAIT)    │ FINISH
        │           │           │           │
   4+   │ CONTINUE  │ CONTINUE  │ CONTINUE  │ CONTINUE
```

**Why Use Barriers?**
1. **Data Dependency**: When later calculations need results from all threads
2. **Coordination**: When all threads must complete a phase before moving on
3. **Resource Management**: Ensure all resources are ready before proceeding
4. **Synchronization**: Prevent race conditions in multi-phase algorithms

**Real-World Analogy:**
Think of a meeting point where friends agree to wait for everyone before entering a movie theater:
- Fast friends (Thread 0, 1) arrive early but must wait
- Slower friends (Thread 2, 3) take longer to arrive
- Only when everyone arrives (barrier) does the group move forward
- After the barrier, all friends (threads) move together

## Learning Path

|--------|---------|
| `#pragma omp parallel` | Create a parallel region |
| `#pragma omp for` | Parallelize a for loop |
| `#pragma omp parallel for` | Combined parallel + for |
| `#pragma omp critical` | Mutual exclusion (one thread at a time) |
| `#pragma omp barrier` | Synchronization point |

## Compilation Tips

### OpenMP Programs
- Always compile with `-fopenmp` flag (GCC/Clang)
- On MSVC: `/openmp` flag
- Set thread count via `OMP_NUM_THREADS` environment variable before running

### MPI Programs (Message Passing Interface)

#### Setup Instructions for Windows:
1. **Download and Install Microsoft MPI**:
   - Download both files from Microsoft MPI website:
     - MS-MPI Runtime (msmpisetup.exe)
     - MS-MPI SDK (msmpisdk.msi)
   - Install both packages

2. **Environment Setup**:
   - Add MPI to your system PATH:
     ```
     C:\Program Files\Microsoft MPI\Bin
     C:\Program Files (x86)\Microsoft SDKs\MPI
     ```

#### Running MPI Programs:

**Compilation**:
```powershell
# Using GCC with MPICH:
mpicc program.c -o program

# Using Microsoft Visual Studio:
cl program.c /I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib
```

**Execution**:
```powershell
# Run with 4 processes:
mpiexec -n 4 ./program

# Run with different number of processes:
mpiexec -n 8 ./program  # 8 processes
```

#### MPI vs OpenMP:
- **OpenMP**: Shared memory parallelism (threads share memory)
- **MPI**: Distributed memory parallelism (processes have separate memory)
- **OpenMP**: Single machine, multiple threads
- **MPI**: Can run across multiple machines/nodes