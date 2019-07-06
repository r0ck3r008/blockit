#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<regex.h>
#include<errno.h>

#include"parse.h"
#include"mem/h_map.h"
#include"mem/mem_mgr.h"

void file_handle(char *fname)
{
	FILE *f=NULL;
	if((f=fopen(fname, "r"))==NULL){
		fprintf(stderr, "[-]Error in opening file: %s\n",
			strerror(errno));
		return;
	}

	char *rd_buf=alloc("char", 200);
	rd_buf=fgets(rd_buf, 200*sizeof(char), f);
	int size;
	while(rd_buf!=NULL){
		size=process_rd_buf(&rd_buf);
		rd_buf=fgets(rd_buf, size*sizeof(char), f);
	}
}

int process_rd_buf(char **rd_buf_ptr)
{
	char *line, *line_bk=NULL;
	int size=200;

	if(!strcmp(*rd_buf_ptr, "\n"))
		return size;

	line=strtok(*rd_buf_ptr, "\n");
	while(line!=NULL){
		if(regex_chk(line))
			process_line(line);
		line_bk=line;
		line=strtok(NULL, "\n");
	}

	explicit_bzero(*rd_buf_ptr, sizeof(char)*200);
	sprintf(*rd_buf_ptr, "%s", line_bk);

	return (size-strlen(line_bk));
}

void process_line(char *line)
{
	char *part=strtok(line, " ");
	part=strtok(NULL, " ");
	printf("%s\n", part);
}

int regex_chk(char *str)
{
	int stat, ret=1;
	regex_t reg;

	stat=regcomp(&reg, "^0.0.0.0", 0);
	if(stat!=0){
		fprintf(stderr, "[-]Error in compiling regexp: %s\n",
			strerror(stat));
		goto exit;
	}

	stat=regexec(&reg, str, 0, NULL, 0);
	if(stat==REG_NOMATCH){
		ret=0;
	}

exit:
	if(!ret)
		regfree(&reg);
	return ret;
}


