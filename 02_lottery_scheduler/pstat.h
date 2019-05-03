#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"

struct pstat {
	int inuse[NPROC]; 
	int tickets[NPROC]; 
	int pid[NPROC]; 
	long ticks[NPROC]; 
};

#endif
