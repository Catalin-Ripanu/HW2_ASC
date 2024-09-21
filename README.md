# HW2_ASC

## Organization

The assignment involves implementing a matrix operation using 3 distinct methods to compare execution time and cache memory usage, based on input datasets of the form *input_*. 

- Implementation time: Approximately 1 day and 5 hours
- Optimization focus: Found in the *solver_opt.c* file (took longer)
- Performance measurement: Used *custom_extended_input* file containing 14 tests

## Implementation

### General Optimizations

- Notation: A' -> A transposed
- Iteration indices *k* have different start and end values to avoid calculations that represent simple multiplications by 0
- Highlight that matrix A is *upper triangular*
- These optimizations appear in *solver_neopt.c* and *solver_opt.c*

### Specific Calculations

1. **BA_t = B * A'**
   - Traverse A by rows to increase cache hits due to spatial locality of data
   - For BA_t[i][j], sum products of elements on row i of B with elements on row j of A, starting from column j

2. **ABA_t = A * B * A'**
   - Similar to BA_t operation
   - Iteration index k starts from i, not 0, to avoid processing null elements

3. **B_tB_t = B' * B'**
   - No specific optimization as B is an arbitrary square matrix

## Versions and Performance

### Blas Version

- Uses specialized functions from the BLAS library
- Allocates memory for matrices to store intermediate results
- Uses optimizations like cblas_dtrmm() for multiplying an upper triangular matrix with an arbitrary matrix

Running times:
```
N = 400: Time = 0.039051
N = 520: Time = 0.082263
N = 640: Time = 0.150279
N = 760: Time = 0.248679
N = 880: Time = 0.383806
N = 1000: Time = 0.557041
N = 1120: Time = 0.736165
N = 1240: Time = 1.007427
N = 1360: Time = 1.331663
N = 1480: Time = 1.715105
N = 1520: Time = 1.835016
N = 1580: Time = 2.062585
N = 1590: Time = 2.114121
N = 1600: Time = 2.169437
```

### Neopt Version

- Classical approach for matrix multiplication
- Considers A as an upper triangular matrix
- Separate function for each operation in calculating matrix C

Running times:
```
N = 400: Time = 1.104875
N = 520: Time = 2.427099
N = 640: Time = 5.561833
N = 760: Time = 7.442277
N = 880: Time = 11.474910
N = 1000: Time = 16.781019
N = 1120: Time = 25.995712
N = 1240: Time = 32.177250
N = 1360: Time = 43.591892
N = 1480: Time = 56.415199
N = 1520: Time = 62.512680
N = 1580: Time = 70.806465
N = 1590: Time = 76.373138
N = 1600: Time = 80.531036
```

### Opt_m Version

Optimizations:
- Traverse A by rows to reduce cache misses
- Eliminate index calculations (j * N + i) using incrementing references
- Reduce CPU operations by avoiding multiplications involving N
- Store multiplication information in CPU registers

Running times:
```
N = 400: Time = 0.276390
N = 520: Time = 0.576796
N = 640: Time = 1.524378
N = 760: Time = 1.806661
N = 880: Time = 2.721285
N = 1000: Time = 3.941125
N = 1120: Time = 6.827338
N = 1240: Time = 7.688742
N = 1360: Time = 11.320905
N = 1480: Time = 13.950172
N = 1520: Time = 16.152508
N = 1580: Time = 18.188416
N = 1590: Time = 20.713333
N = 1600: Time = 23.733250
```

## Cachegrind Analysis

- BLAS: Lowest number of I_refs, D_refs, and LL_refs, indicating high performance and efficient cache usage
- Neopt: Highest I_refs, suggesting inefficiency
- Opt_m: Fewer memory accesses compared to Neopt, showing optimization effects
- BLAS: Lowest number of Branches, indicating simpler flow control and better branch prediction

## Graph Study

- BLAS version is most performant, efficiently using cache for matrix traversal
- Neopt version shows approximately exponential shape for sizes exceeding 900

## Resources Used

1. [BLAS (Basic Linear Algebra Subprograms)](https://netlib.org/blas/)
2. [Valgrind Cachegrind Manual](https://valgrind.org/docs/manual/cg-manual.html)
3. [StackOverflow: Optimized Matrix Multiplication in C](https://stackoverflow.com/questions/1907557/optimized-matrix-multiplication-in-c)
