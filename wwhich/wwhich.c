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
	char *pointer;
	unsigned int pathsate;
	unsigned int currentno;
	unsigned int strno;
} path_state;

#define PATH_STATE_FINISH 	(0x01)
#define PATH_STATE_NOFINISH	(0x00)

#define PATH_FIND		(0x00)
#define PATH_NOFIND		(0x01)
#define MAX_PATH_LENG		(0xff)

static char *target;
static void search_exec(char *filename);
static int get_path_state(void);
static char *get_next_path(void);
static char if_path(char *path);
static void init_path_state();

int main(int argc, char *argv[])
{
	char *path;
	if (argc == 1) {
		if (!strcmp(argv[1], "--version")) {
			printf("%s\n", information);
		} else {
			path = getenv("PATH");
			target = malloc(strlen(path) + 1)
			memcpy((char *)target , path, strlen(path) + 1);
			init_path_state();
			search_exec(argv[1]);
			free(target);
		}
	
	} else  printf("%s\n", error_message);

	return 0;
}

static void search_exec(char *filename)
{
	char *next_path;
	while (get_path_state() != PATH_STATE_FINISH) {
		
		next_path = get_next_path();
		if (if_path(next_path) == PATH_FIND) {
			printf("%s\n", path);
			free(target);
			exit(0);
		}
	}
	printf("No scuh File /"%s.exe/"\n", filename);
}

static inline int get_path_state(void)
{

	return ((((signed int)(path_state.strno - path_state.currentno)) >= 0)
		? (PATH_STATE_NOFINISH) : (PATH_STATE_FINISH));

}

static char *get_next_path(void)
{
	int counter;
	if (path_state.currentno == 0) {
		return target;
	}
	if (((signed int)(path_state.strno - path_state.currentno)) < 0) {
		return NULL;
	}
	for (counter = 0; pointer[counter] != '\0'; counter++) 
		;

	path_state.currentno++;
	path_state.pointer += counter + 1;
	return path_state.pointer;
}

static char if_path(char *path)
{
	if (path == NULL) 
		return PATH_NOFIND;
	else {
		
	}

}

static void init_path_state()
{
	int counter;
	path_state.strno = 0;
	path_state.currentno = 0;
	path_state.pointer = target;
	path_state.pathsate = PATH_STATE_NOFINISH;

	for (counter = 0; counter < strlen(target); i++) {
		if (target[counter] == ';' && (++path_state.strno) && target[counter] = '\0')
			;
	}
	return 0;
}