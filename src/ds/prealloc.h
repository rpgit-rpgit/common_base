#ifndef __PREALLOC_H__
#define __PREALLOC_H__

char * pa_blk_init(int node_size, int node_max);

char * pa_getblk(char *pabuf);
int pa_relblk(char *pabuf, char *blk);
int pa_getfree(char *pabuf);



#endif
