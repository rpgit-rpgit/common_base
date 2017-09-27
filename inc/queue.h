#ifndef __QUEUE_HDR__
#define __QUEUE_HDR__

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

typedef struct qnode_t {
	struct qnode_t *next;
	void *data;
} qnode;

typedef struct {
	int nelem;
	int maxelem;
	int elem_len;
	void (*print_fp)(void *data);
} qhdr;

typedef struct {
	qnode *next;
	qhdr hdr;
} queue;

//Returns:	NULL	failure
queue *q_new(int maxelem, int elem_len);
int q_enqueue(queue *q, void *elem);
int q_dequeue(queue *q, void **elem);
void q_show(queue const *q);

#endif
