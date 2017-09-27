#include<stdio.h>
#include<stdlib.h>
#include"common.h"

#define DEBUG printf

#define CHECK_RET_INT(func, ret) \
	{											\
	if (ret) {										\
		printf("\n " #func "() Success: "	#ret " = %d", (ret));	\
	} else {										\
		printf("\n " #func "() Failed: "	#ret " = %d\n", (ret));	\
	}											\
	}
#define CHECK_RET_PTR(func, retp) \
	{											\
	if (retp) {										\
		printf("\n " #func "() Success: "	#retp " = %x", (unsigned)(retp));	\
	} else {										\
		printf("\n " #func "() Failed: "	#retp " = %x\n", (unsigned)(retp));	\
	}											\
	}
#define CHECK_PTR_ARG(argp) \
	{											\
	if (! argp) {										\
		printf("\n<%s>: Wrong argument, " #argp " = %x\n", __func__, (unsigned)(argp));	\
		return(0);									\
	}											\
	}

typedef struct {
	int node_size;
	int max_node;
	char *freelist;
	char *buf;
} pa_buf;

/* Preallocates buffer structure
|<---pa_buf---->|<--------------------------------------buf------------------------------------->|
                |<-------blk1----->|<-------blk2------->|...............|<-----blk_max_node----->|
		|<--node--><-nfree->|<--node--><--nfree-->|

	nfree = points to next free blk
*/
void * pa_blk_init(int node_size, int max_node)
{
	pa_buf *pb = NULL;
	char *buf = NULL;
	int node_ptr_size = sizeof(char *);
	int ttl_size = -1, blk_size = -1, i; // each blk contains one node

	if (node_size < 1 || max_node < 1) {
		printf("\n<%s>: Wrong arguments.. node_size = %d, max_node = %d", 
			__func__, node_size, max_node);
		return(pb);
	}
	blk_size = node_size + node_ptr_size;
	ttl_size = sizeof(pa_buf) + blk_size * max_node;
	pb = (pa_buf *)malloc(ttl_size);
	buf = (char *)pb + sizeof(pa_buf);
	pb->node_size = node_size;
	pb->max_node = max_node;
	pb->buf = buf;
	pb->freelist = buf;

	buf += node_size;
	for (i=1; i<max_node; i++) {
		//*(char **)buf = buf + blk_size;
		*(char **)buf = buf + node_ptr_size;
		buf += blk_size;
	}
	*(char **)buf = NULL;

	return(pb);
}

int pa_blk_dest(void *pbh)
{
	CHECK_PTR_ARG(pbh);
	
	free(pbh);
	return(1);
}
	
char * pa_getnode(void *pbh)
{
	pa_buf *pb = (pa_buf *)pbh;
	char *nodep = NULL;
	//char *next = NULL;
	char **nextpp = NULL;
	
	nodep = pb->freelist;
	if (nodep) {
		//pb->freelist = *(char *)(nodep + pb->node_size);
		//next = *(char *)(nodep + pb->node_size);
		nextpp = (char **)(nodep + pb->node_size);
		pb->freelist = *nextpp;
		*nextpp = NULL;
		
	}

	return(nodep);

}

int pa_relnode(void *pbh, char *nodep)
{
	pa_buf *pb = (pa_buf *)pbh;
	char **nextpp = NULL;

	if (!pbh || !nodep) {
		printf("\n<%s>: Wrong arguments.. pbh = %x, nodep = %x", 
			__func__, (unsigned)pbh, (unsigned)nodep);
		return(0);
	}
	nextpp = (char **)(nodep + pb->node_size);
	if (*nextpp != NULL) {
		printf("\n<%s>: Request node (nodep = %x) already free", __func__, (unsigned)nodep);
		return(0);
	}
	*nextpp = pb->freelist;
	pb->freelist = nodep;
	printf("\n<%s>: freelist = %x", __func__, (unsigned)pb->freelist);
	return(1);
}
	

