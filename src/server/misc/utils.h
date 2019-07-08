#ifndef UTILS_H
#define UTILS_H

#ifdef NEED_ARGS
	#include"cargparse/cargparse.h"

	void init_args(struct arg *, int, char **);
	struct arg *arguments_glbl;
#endif

void wrt(int, char *, char *);
int rd(int, char *, char *);
FILE *openf(char *, int);
char *fetch_url();

#endif
