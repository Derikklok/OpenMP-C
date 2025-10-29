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

## Learning Path

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