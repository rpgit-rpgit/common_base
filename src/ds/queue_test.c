#include<stdio.h>
#include<stdlib.h>

#include <common.h>
#include <queue.h>

int main (int argc, char *argv[])
{
	queue *Q = NULL;
	int x, *p = NULL;

	printf(FMT "Started\n", FMTVAR);

	PRINTARGS(argc, argv);

	Q = q_new(10, sizeof(int));
	if (!Q) {
		printf(FMT "q_new() failed. Exiting..\n", FMTVAR);
		return 1;
	}

	x = 10;
	if (q_enqueue(Q, &x) == FAILURE) {
		printf(FMT "q_enqueue() failed. Exiting..\n", FMTVAR);
		return 1;
	}

	if (q_dequeue(Q, (void **)&p) == FAILURE) {
		printf(FMT "q_dequeue() failed. Exiting..\n", FMTVAR);
		return 1;
	}
		
	printf(FMT "dequeue value = %d\n", FMTVAR, *p);

	return 0;
}	
