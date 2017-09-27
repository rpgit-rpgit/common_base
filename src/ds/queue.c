/*
 * queue.c
 *
 * Author			XYZ
 * Date				DD MMM YYYY
 * Description		Simple queue implementation
 */

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<stdint.h>
#include<inttypes.h>

#include "queue.h"
#include "../../inc/common.h"

#define NON_NULL_ARG_CHK(arg) 		\
do {										\
	if (!(arg)) { 							\
		return;		 				\
	}										\
} while (0);

#define NON_NULL_ARG_CHK_RET(arg,retcode) 		\
do {										\
	if (!(arg)) { 							\
		return retcode;		 				\
	}										\
} while (0);

/*
 *************************************************************
 ****************** F U N C T I O N S ************************
 *************************************************************
 */

/*
 * Function			q_new()
 *
 * Description		Initializes a new queue
 * Returns			NULL		On failure
 *					queue *		On Success
 */

queue *q_new(int maxelem, int elem_len)
{
	queue *q = NULL;

	q = (queue *) calloc (sizeof(queue), 1);

	if(q) {
		q->hdr.nelem = 0;
		q->hdr.maxelem = maxelem;
		q->hdr.elem_len = elem_len;
		q->next = NULL;
	}
	return q;
}

/*
 * Function			q_enqueue()
 *
 * Description		Enqueues the given element into queue
 * Returns			FAILURE			On error
 *					RC_QUEUE_FULL	Queue full condition
 *					SUCCESS			On Success
 */

int q_enqueue(queue *q, void *elem)
{
	qnode *new_qn = NULL, *qn = NULL;

	NON_NULL_ARG_CHK_RET(q,FAILURE);
	NON_NULL_ARG_CHK_RET(elem,FAILURE);

/*	if (!q || !elem) {
		printf ("\n<%s>: wrong argument: q = %p, elem = %lu", 
			__func__, (void *)q, (unsigned long)elem);
		return FAILURE;
	}*/
	if (q->hdr.nelem == q->hdr.maxelem) {
		printf ("\nQueue full: nelem(%d) == maxelem(%d)", 
			q->hdr.nelem, q->hdr.maxelem);
		return RC_QUEUE_FULL;
	}

	new_qn = (qnode *) calloc (sizeof(qnode), 1);
	if (!new_qn) {
		printf ("\n<%s>: error allocating for new node: %s", 
			__func__, strerror(errno));
		return FAILURE;
	}

	new_qn->data = calloc (q->hdr.elem_len, 1);
	if (!new_qn->data) {
		printf ("\n<%s>: error allocating for new node data: %s", 
			__func__, strerror(errno));
		free (new_qn);
		return FAILURE;
	}
	memcpy (new_qn->data, elem, q->hdr.elem_len);

	new_qn->next = NULL;
	if (q->next) {
		qn = q->next;
		while (qn->next) {
			qn = qn->next;
		}
		qn->next = new_qn;
	} else {
		q->next	= new_qn;
	}

	q->hdr.nelem++;
	return SUCCESS;
}

/*
 * Function			q_dequeue()
 *
 * Description		Enqueues the given element into queue
 * Returns			FAILURE		On failure
 *					queue *		On Success
 */

int q_dequeue(queue *q, void **elem)
{

	NON_NULL_ARG_CHK_RET(q,FAILURE);
	NON_NULL_ARG_CHK_RET(elem,FAILURE);

	/*if (!q || !elem) {
		printf ("\n<%s>: wrong argument: q = %p, elem = %lu", 
			__func__, (void *)q, (uintptr_t)elem);
		return FAILURE;
	}*/

	if (q->next) {
		*elem = q->next->data;
		q->next = q->next->next;
		q->hdr.nelem--;
		printf ("\n<%s>: Dequeued: nelem = %d", __func__, q->hdr.nelem);
	} else {
		printf ("\n<%s>: Queue empty: nelem = %d", __func__, q->hdr.nelem);
		return RC_QUEUE_EMPTY;
	}

	return SUCCESS;
}

/*
 * Function			q_show()
 *
 * Description		Enqueues the given element into queue
 * Returns			FAILURE		On failure
 *					queue *		On Success
 */
void q_show(queue const *q)
{
	NON_NULL_ARG_CHK(q);

	printf ("\n\n<%s>: Qhdr info:", __func__);
	printf ("\n<%s>: \tnelem = %d", __func__, q->hdr.nelem);
	printf ("\n<%s>: \tmaxelem = %d", __func__, q->hdr.maxelem);
	printf ("\n<%s>: \telem_len = %d", __func__, q->hdr.elem_len);

	return;
}	
	
