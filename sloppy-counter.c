# include "sloppy-counter.h"


void Pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start_routine)(void*), void* arg) {
	int rc = pthread_create(thread, attr, start_routine, arg);
	assert(rc == 0);
}

void Pthread_join(pthread_t thread, void** value_ptr) {
	int rc = pthread_join(thread, value_ptr);
	assert(rc == 0);
}

void Pthread_mutex_init(pthread_mutex_t* ptr_lock) {
        int rc = pthread_mutex_init(ptr_lock, NULL);
        assert(rc == 0);
}

void Pthread_mutex_lock(pthread_mutex_t* ptr_lock) {
	int rc = pthread_mutex_lock(ptr_lock);
	assert(rc == 0);
}

void Pthread_mutex_unlock(pthread_mutex_t* ptr_lock) {
	int rc = pthread_mutex_unlock(ptr_lock);
	assert(rc == 0);
}

void init(counter_t* c, int threshold) {
	c->threshold = threshold;

	c->global = 0;
	Pthread_mutex_init(&c->glock);

	for( int i = 0; i < NUMCPUS; i++) {
		c->local[i] = 0;
		Pthread_mutex_init(&c->llock[i]);
	}
}

void increment(counter_t* c, int threadID) {
	threadID %= 4;
	Pthread_mutex_lock(&c->llock[threadID]);
	c->local[threadID]++;
	if (c->local[threadID] == c->threshold) {
		Pthread_mutex_lock(&c->glock);
		c->global += c->threshold;
		Pthread_mutex_unlock(&c->glock);
		c->local[threadID] = 0;
	}
	
	Pthread_mutex_unlock(&c->llock[threadID]);
}

int get(counter_t* c) {
	return c->global;
}


