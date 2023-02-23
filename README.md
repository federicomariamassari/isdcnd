# Udacity Intro to Self-Driving Cars Nanodegree

My Udacity Intro to Self-Driving Cars Nanodegree projects, in Python and C++.

## Certification

![Certificate of Completion](certificate-of-completion.png)

## Project 3 (Optional): Optimize Histogram Filter

### How to Compile and Run the Project

We suppose the project resides at address `/home/$whoami/workspace/udacity-isdcnd/projects/p3/optimized`, with `$whoami` the username of the current user (verify on console).

```bash
cd /home/$whoami/workspace/udacity-isdcnd/projects/p3/optimized
g++ -std=c++11 main.cpp blur.cpp initialize_beliefs.cpp move.cpp normalize.cpp print.cpp sense.cpp zeros.cpp
./a.out
```

### Unoptimized Starting Code

Unoptimized starting code from Udacity is also included for comparison purposes (in the "unoptimized" folder). It is hosted here because, to the best of my knowledge, no official repository for the code is available online. The code is compiled and run the same way the optimized code is.

### Output

Running on Macbook Pro M1 Max prints out the following output (slightly varying among trials):

| Metric | Unoptimized | Optimized | Relative Improvement |
|----------|------:|------:|------:|
| Number of iterations | 10000 | 10000 | - |
| Duration milliseconds `initialize_beliefs.cpp` | 58.514 | 23.583 | 60% |
| Duration milliseconds `sense.cpp` | 48.234 | 14.519 | 70% |
| Duration milliseconds `blur.cpp` | 83.812 | 29.275 | 65% |
| Duration milliseconds `normalize.cpp` | 46.425 | 13.760 | 70% |
| Duration milliseconds `move.cpp` | 39.099 | 11.598 | 70% |
