#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#ifdef __WWHICH_DEBUG__	//wwhich debug macro.
							// nothing here, just for introdution the debug macro.
#endif 					//wwhich debug macro end.

const static char information[] = 
"wwhich(0.01) is windows which for search the execable file in ENV var.\n"
"usage: [--version] [excfile].\n"
"--version for showing version.\n"
"excfile for search execable file path.\n";

const static char error_message[] = 
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

#define PATH_FIND				(0x00)
#define PATH_NOFIND			(0x01)
#define MAX_PATH_LENG			(0xff)

static char *target;
static void search_exec(char *filename);
static int get_path_state(void);
static char *get_next_path(void);
static char if_path(char *path, char *filename);
static void init_path_state();

int main(int argc, char *argv[])
{
	char *path;
	if (argc == 2) {
		if (!strcmp(argv[1], "--version")) {
			printf("%s\n", information);
		} else {
			path = getenv("PATH");
			
			#ifdef __WWHICH_DEBUG__	//wwhich debug macro.
			printf("\n%s\n\n", path);
			#endif 
			
			if ((target = (char *)malloc(strlen(path) + 1)) == NULL) {
				printf("malloc target error.\n");
				exit(-1);
			}
			memcpy((char *)target , path, strlen(path) + 1);
			
			
			#ifdef __WWHICH_DEBUG__	//wwhich debug macro.
			printf("\n%s\n", target);
			#endif 
			
			
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
		
		#ifdef __WWHICH_DEBUG__
		printf("\nin the fun search_exec()next_path:\n%s\n\n", next_path);
		#endif
		
		if (if_path(next_path, filename) == PATH_FIND) {
			printf("\n\"%s.exe\" in:\n\n\t%s\n\n", filename, next_path);
			free(target);
			exit(0);
		}
	}
	printf("No scuh File \"%s.exe\"\n", filename);
}

static int get_path_state(void)
{
	#ifdef __WWHICH_DEBUG__
	printf("\n in the function get_path_state(), the return no :%d", path_state.strno - path_state.currentno);
	#endif
	
	return ((((signed int)(path_state.strno - path_state.currentno)) >= 1)
		? (PATH_STATE_NOFINISH) : (PATH_STATE_FINISH));

}

static char *get_next_path(void)
{
	int counter;
	if (path_state.currentno == 0) {
		path_state.currentno++;
		path_state.pointer += strlen(path_state.pointer) + 1;
		return target;
	}
	if (((signed int)(path_state.strno - path_state.currentno)) < 1) {
		return NULL;
	}
	for (counter = 0; path_state.pointer[counter] != '\0'; counter++) 
		;

	path_state.currentno++;
	path_state.pointer += counter + 1;
	return path_state.pointer;
}

static char if_path(char *path, char *filename)
{
	char *str_malloc;
	WIN32_FIND_DATA date_info;
	HANDLE FILE_HANDLE;
	if (path == NULL) 
		return PATH_NOFIND;
	else {
		str_malloc = (char *)malloc(strlen(path) + strlen(filename) + 6);
		memcpy(str_malloc, path, strlen(path) + 1);
		if (str_malloc[strlen(str_malloc) - 1] != '\\') {
			strcat(str_malloc, "\\");
			
			#ifdef __WWHICH_DEBUG__
			printf("\nadd \\ sysbol the str:%s\n", str_malloc);
			#endif
			
		}
		strcat(str_malloc, filename);
		strcat(str_malloc, ".exe");
		
		
		#ifdef __WWHICH_DEBUG__
		printf("\nint if_path,str_malloc: %s\n\n", str_malloc);
		#endif 
		
		
		FILE_HANDLE = FindFirstFile(str_malloc, &date_info);
		free(str_malloc);
		FindClose(FILE_HANDLE);
		if (FILE_HANDLE == INVALID_HANDLE_VALUE) {
			#ifdef __WWHICH_DEBUG__
			printf("\nLast error :%d\n", GetLastError());
			#endif
			return 	PATH_NOFIND;
		} else {
			return PATH_FIND;
		}
	}

}

static void init_path_state(void)
{
	int counter;
	int len;
	len = strlen(target);
	
	#ifdef __WWHICH_DEBUG__
	printf("int init_path_state.\n");
	#endif
	
	path_state.strno = 0;
	path_state.currentno = 0;
	path_state.pointer = target;
	path_state.pathsate = PATH_STATE_NOFINISH;

	for (counter = 0; counter < len; counter++) {
		if (target[counter] == ';') {
			path_state.strno++;
			target[counter] = '\0';
		}
		#ifdef __WWHICH_DEBUG__
		printf("%c", target[counter]);
		#endif
	}
	#ifdef __WWHICH_DEBUG__
	printf("\nout init_path_state, strno:%d\n", path_state.strno);
	#endif
	return;
}