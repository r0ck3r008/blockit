#ifndef UTILS_H
#define UTILS_H

#ifdef NEED_ARGS
	#include"cargparse/cargparse.h"

	int init_args(struct arg *, int, char **);
	char *find_arg(struct arg *, char *);
#endif

void wrt(int, char *, char *);
int rd(int, char *, char *);

#endif
