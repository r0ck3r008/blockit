#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<regex.h>
#include<errno.h>

#include"mem/h_map.h"
#include"mem/mem_mgr.h"
#include"misc/utils.h"
#include"parse.h"

struct h_map_t *file_handle(char *fname)
{
	FILE *f=openf(fname, 0);

	struct h_map_t *h_map=h_map_create(20000);

	char *rd_buf=alloc("char", 200);
	rd_buf=fgets(rd_buf, 200*sizeof(char), f);
	int size;
	while(rd_buf!=NULL){
		size=process_rd_buf(&rd_buf, h_map);
		rd_buf=fgets(rd_buf+(sizeof(char)*(200-size)),
				size*sizeof(char), f);
	}

	free(rd_buf);

	return h_map;

}

int process_rd_buf(char **rd_buf_ptr, struct h_map_t *h_map)
{
	char *line, *line_bk=NULL;
	int size=200;

	if(!strcmp(*rd_buf_ptr, "\n"))
		return size;

	line=strtok(*rd_buf_ptr, "\n");
	while(line!=NULL){
		if(regex_chk(line))
			process_line(line, h_map);
		line_bk=line;
		line=strtok(NULL, "\n");
	}

	explicit_bzero(*rd_buf_ptr, sizeof(char)*200);
	sprintf(*rd_buf_ptr, "%s", line_bk);

	return (size-strlen(line_bk));
}

void process_line(char *line, struct h_map_t *h_map)
{
	char *part=strtok(line, " ");
	part=strtok(NULL, " ");

	find_ip(part, h_map);
}

void find_ip(char *hostname, struct h_map_t *h_map)
{
	//TODO despirately need to inc the spped of this function!!
	struct addrinfo hints, *infoptr;
	explicit_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family=AF_UNSPEC;
	hints.ai_protocol=0;
	hints.ai_socktype=SOCK_STREAM;

	int result=getaddrinfo(hostname, NULL, &hints, &infoptr);
	if(result)
		fprintf(stderr, "[-]Error in finding IP for %s: %s\n",
			hostname, gai_strerror(result));

	char *host=alloc("char", 512);
	struct addrinfo *ptr=infoptr;
	for(ptr; ptr!=NULL; ptr=ptr->ai_next){
		getnameinfo(infoptr->ai_addr, infoptr->ai_addrlen, host,
			    sizeof(char)*512, NULL, 0, NI_NUMERICHOST);
		h_map_insert(h_map, host);
		explicit_bzero(host, sizeof(char)*512);
	}
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
