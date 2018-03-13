#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE	33
#define ASSIC_ZERO	'0'
#define ASSIC_ONE		'1'
#define EXEC_FAIL		0
#define EXEC_OK			1


static char copyleft[] = "\n\tThis bin to hex tools. It's just conver bin to hex. The max number is just 32 byte.\n";

char test_vaild(char *buffer, unsigned int leng);

int main(int argc, char *argv[])
{
    int leng, counter;
    unsigned int number = 0;
	
	if (argc < 2) {
		printf("%s", copyleft);
		return 0;
	}
	leng = strlen(argv[1]);
	if (test_vaild(argv[1], leng) == EXEC_FAIL) {
		printf("\n\tInput string error.\n");
		return -1;
	}
	
    for (counter = 0; counter < leng; counter++) {
        number += ((argv[1][leng - counter - 1] - ASSIC_ZERO) << counter);
    }
    printf("The result is : 0x%0x\n", number);
    return 0;

}

char test_vaild(char *buffer, unsigned int leng)
{
	unsigned int counter;
	for (counter = 0; counter < leng; counter++) {
		if (buffer[counter] != ASSIC_ZERO && buffer[counter] != ASSIC_ONE) {
			return EXEC_FAIL;
		}
	}
	return EXEC_OK;
}