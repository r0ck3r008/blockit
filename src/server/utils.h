#ifndef UTILS_H
#define UTILS_H

#ifdef NEED_ARGS
	#include"cargparse/cargparse.h"

	void init_args(struct arg *, int, char **);
#endif

void wrt(int, char *, char *);
int rd(int, char *, char *);

#endif
