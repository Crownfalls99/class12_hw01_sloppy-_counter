all : sloppy-counter

sloppy-counter : sloppy-counter.o analysis.o main.o
	gcc -O2 -o sloppy-counter sloppy-counter.o analysis.o main.o -l pthread

sloppy-counter.o : sloppy-counter.c sloppy-counter.h
	gcc -O2 -c -o sloppy-counter.o sloppy-counter.c -l pthread

analysis.o : analysis.c sloppy-counter.h
	gcc -O2 -c -o analysis.o analysis.c -l pthread

main.o : main.c sloppy-counter.h
	gcc -O2 -c -o main.o main.c -l pthread

clean:
	rm -f sloppy-counter *.o



