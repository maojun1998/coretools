#include <windows.h>
#include <stdio.h>

#define MAX_PATH_LENGTH		(0xFFFF)

int main(int argc, char *argv[])
{
		DWORD 	status;
		char	LPathName[MAX_PATH_LENGTH] = {0x00};
	
		status = GetCurrentDirectory(
						MAX_PATH_LENGTH,
						LPathName
					);
				
		if (status) 
				printf("The Current Directory is : \n\n\t%s\n", LPathName);
		else
				printf("Error code %d.\n\n", GetLastError());
		
	
		return 0;
}