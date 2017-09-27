#ifndef __COMMON_HDR__
#define __COMMON_HDR__

#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>

#define SUCCESS					1
#define FAILURE					0

// Program Exit Codes 
#define	EXC_SUCCESS				0
#define	EXC_FAILURE				1
#define	EXC_ERR1				2
#define	EXC_ERR2				3
#define	EXC_ERR3				4

// Function Return Codes
#define RC_SUCCESS				1
#define RC_FAILURE				0

#define RC_QUEUE_FULL			5
#define RC_QUEUE_EMPTY 			6

#define IP_ADDRESS_LEN			16
#define MAX_HOST_LEN			100
#define MAX_SERVICE_LEN			10

//Common Macros
#define FMT	"\nID: %s(%d: %0x:	PGID = %d):\t\n%s:\t"
#define FMTVAR	__func__, getpid(), (int)pthread_self(), getpgrp(), __func__

#define PRINTARGS(n,a)									\
	{													\
		printf("Input Arguments\n");					\
		printf("\tNo. of args = %d\n", (n));			\
		if ((n) > 0) {									\
			int i;										\
			for (i=0; i<n; i++) {						\
				printf("\targ[%d] = %s\n", i, a[i]);	\
			}											\
		}												\
		printf("\n");									\
	}

#define PRINT(f, v)										\
	{													\
		printf(FMT f, FMTVAR, v);						\
	}

#define PROG_START											\
	{ 														\
		printf(FMT "\n\n", FMTVAR);							\
		printf("*********\tW E L C O M E\t**********\n\n");	\
	}

#define	DEBUG(t, v)														\
	{																	\
		printf (FMT "DEBUG:\t" #v " = " t "\n" , FMTVAR, v);			\
	}

#define EXIT(c)															\
	{																	\
		printf (FMT "Exiting - code = %d\n" , FMTVAR, c);				\
		exit (c);														\
	}

#define PRINT_FUNC_ENTERED												\
	{																	\
		printf (FMT "Entered\n" , FMTVAR);							\
	}

#define PRINT_ERR(msg, ecode)											\
	{																	\
		printf (FMT "ERR: "msg"\t%s\n" , FMTVAR, strerror(ecode));		\
	}
		
#define PRINT_THREAD_START(msg) 										\
	{ 																	\
		printf (FMT "THREAD STARTED -\t" msg"\n" , FMTVAR);				\
	}

#endif
