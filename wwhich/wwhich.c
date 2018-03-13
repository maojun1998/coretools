#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

const static information[] = 
"wwhich(0.01) is windows which for search the execable file in ENV var.\n"
"usage: [--version] [excfile].\n"
"--version for showing version.\n"
"excfile for search execable file path.\n";

const static error_message[] = 
"Use age error.\n"
"usage: [--version] [excfile].\n";


static struct _PATH_STATE {
	unsigned int pointer;
	unsigned int pathsate;
	unsigned int len;
} path_state;

#define PATH_STATE_FINISH 	(0x01)
#define PATH_STATE_NOFINISH	(0x00)

#define MAX_PATH_LENG		(0xff)

static char per_path[MAX_PATH_LENG]
static char *path;
static void search_exec(char *filename, char *path);
static int get_path_state(void);
static char *get_next_path(void);

int main(int argc, char *argv[])
{
	path = getenv("PATH");
	
	if (argc == 1) {
		if (!strcmp(argv[1], "--version")) {
			printf("%s\n", information);
		} else {
			search_exec(argv[1], path);
		}
	
	} else  printf("%s\n", error_message);

	return 0;
}

static void search_exec(char *filename)
{
	char *path;
	while (get_path_state() != PATH_STATE_FINISH) {
		
		path = get_next_path();
		if (if_path(path) == PATH_FIND) {
			printf("%s\n", path);
			exit(0);
		}
		free(path);
	}

}

static inline int get_path_state(void)
{

	return path_state.pathsate;

}

static inline char *get_next_path(void)
{


	return per_path;
}

static char if_path(char *path)
{


}