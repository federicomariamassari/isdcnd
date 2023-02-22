# Udacity Intro to Self-Driving Cars Nanodegree

My Udacity Intro to Self-Driving Cars Nanodegree projects, in Python and C++.

## Certification

![Certificate of Completion](certificate-of-completion.png)

## Project 3: Optimize Histogram Filter

### How to Compile and Run the Project

We suppose the project resides at address `/home/$whoami/workspace/udacity-isdcnd/projects/p3`, with `$whoami` the username of the current user (verify on console).

```bash
cd /home/$whoami/workspace/udacity-isdcnd/projects/p3
g++ -std=c++11 main.cpp blur.cpp initialize_beliefs.cpp move.cpp normalize.cpp print.cpp sense.cpp zeros.cpp
./a.out
```

### Output



| Metric | Unoptimized | Optimized |
|----------|------:|------:|
| Number of iterations | 10000 | 10000 |
| Duration initialize beliefs* | 23.583 | |



```zsh
number of iterations: 10000 
duration milliseconds initialize beliefs 23.583
duration milliseconds sense 14.519
duration milliseconds blur 29.275
duration milliseconds normalize 13.76
duration milliseconds move 11.598
```

By comparison, the unoptimized code produces:

```zsh

```
