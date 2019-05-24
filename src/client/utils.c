#define NEED_ARGS

#include"utils.h"

int init_args(struct arg *arguments, int argc, char **argv)
{
	add_argument(arguments, "-u", "--uds_sock", "The URI of uds socket",
			1);
	add_argument(arguments, "-m", "--mirror_file", "The mirror list file",
			1);

	if(argc!=3){
		show_help(arguments);
		return 0;
	}

	parse_args(arguments, argc, argv);

	return 1;
}
