# include "sloppy-counter.h"

void ellapsedTime (TIMEV* diffTime, TIMEV* startTime, TIMEV* endTime) {
	if (endTime->tv_usec < startTime->tv_usec) {
		endTime->tv_sec--;
		endTime->tv_usec += 1000000;
	}
	diffTime->tv_sec = endTime->tv_sec - startTime->tv_sec;
	diffTime->tv_usec = endTime->tv_usec - startTime->tv_usec;
}

void printTime(TIMEV time) {
	printf("%ld.%06ld sec\n", time.tv_sec, time.tv_usec);
}


void* mythread(void* arg) {
	int i;
	mystruct* ptr = (mystruct*) arg;

	for(i = 0; i < ITR; i++)
		increment(ptr->counter_ptr,*(ptr->threadID_ptr) % 4);
	return NULL;
}


void Nthreads(int n, int threshold) {
	pthread_t p[n];
	counter_t c;
	mystruct arguments;
	TIMEV start, end, diff;
	int i;

	init(&c, threshold);
	gettimeofday(&start, NULL);

	for(i = 0; i < n; i++) {
		arguments.counter_ptr = &c;
		arguments.threadID_ptr = &p[i];
		Pthread_create(&p[i], NULL, mythread, (void*)&arguments);
	}
	for(i = 0; i < n; i++)
		Pthread_join(p[i], NULL);
	
	gettimeofday(&end, NULL);
	ellapsedTime(&diff, &start, &end);

	printf("For %d threads, total ellapsed time : ", n);
	printTime(diff);
	printf("Value : %d\n", get(&c));
}


