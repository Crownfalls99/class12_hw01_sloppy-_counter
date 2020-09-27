# ifndef MY_HEADER
# define MY_HEADER

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <assert.h>
# include <sys/time.h>
# include <pthread.h>

# define ITR 10000000
# define NUM_THREADS 12
# define NUMCPUS 4
# define THRESHOLD 2048

typedef struct timeval TIMEV;

void ellapsedTime(TIMEV* diffTime, TIMEV* startTime, TIMEV* endTime);
void printTime(TIMEV time);

void* mythread(void* arg);
void Nthreads(int n, int threshold);

void Pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*strat_routine)(void*), void* arg);
void Pthread_join(pthread_t thread, void** value_ptr);


void Pthread_mutex_init(pthread_mutex_t* ptr_lock);
void Pthread_mutex_lock(pthread_mutex_t* ptr_lock);
void Pthread_nutex_unlock(pthread_mutex_t* ptr_lock);

typedef struct __counter_t {
	int global;
	pthread_mutex_t glock;
	int local[NUMCPUS];
	pthread_mutex_t llock[NUMCPUS];
	int threshold;
} counter_t;

typedef struct __mystruct {
	counter_t* counter_ptr;
	long unsigned int* threadID_ptr;
} mystruct;

void init(counter_t* c, int threshold);
void increment(counter_t* c, int threadID);
int get(counter_t* c);

# endif


