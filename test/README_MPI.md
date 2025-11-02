# Running the MPI Hello World Program

## About the Program
This MPI program demonstrates basic MPI concepts:
- Process initialization
- Getting total number of processes
- Getting each process's rank
- Getting processor name
- MPI environment cleanup

## Code Explanation
```c
MPI_Init(NULL, NULL);                    // Initialize MPI environment
MPI_Comm_size(MPI_COMM_WORLD, &size);    // Get total number of processes
MPI_Comm_rank(MPI_COMM_WORLD, &rank);    // Get current process rank (ID)
MPI_Get_processor_name(name, &name_len);  // Get processor name
MPI_Finalize();                          // Clean up MPI environment
```

## Steps to Run

1. **First Time Setup**:
   ```powershell
   # Download and install MS-MPI from Microsoft's website
   # Both runtime and SDK are needed
   ```

2. **Compilation**:
   ```powershell
   # Using Microsoft MPI
   cl program3.c /I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib

   # OR using MPICH if installed
   mpicc program3.c -o program3
   ```

3. **Running**:
   ```powershell
   # Run with 4 processes
   mpiexec -n 4 program3
   ```

## Expected Output
```
Hello from processor Computer1, rank 0 out of 4 processors
Hello from processor Computer1, rank 1 out of 4 processors
Hello from processor Computer1, rank 2 out of 4 processors
Hello from processor Computer1, rank 3 out of 4 processors
```

## Common Issues and Solutions
1. **"mpicc not found"**: 
   - Make sure MPI is installed
   - Check if MPI bin directory is in PATH

2. **"mpi.h not found"**:
   - Make sure MPI SDK is installed
   - Check include path points to MPI headers

3. **"program runs but only shows one process"**:
   - Make sure to use mpiexec to run the program
   - Check -n parameter for number of processes

4. **"Error running program"**:
   - Make sure MS-MPI runtime is installed
   - Check if the program was compiled correctly