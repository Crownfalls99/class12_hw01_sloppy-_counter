# include "sloppy-counter.h"

int main(int argc, char* argv[])
{
	int n;

	assert(argc == 2);

	for(n = 1; n <= NUM_THREADS; n++)
		Nthreads(n, atoi(argv[1]));

	return 0;
}


