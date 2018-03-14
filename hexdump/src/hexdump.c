#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hexdump.h"

const char *copyright = "\nThe program was written by Hacking.\nReport bug or have a good ideal,please sent Email \
to maojun@whatsmath.cn.\nYou can use the source code anytime.\n\n";


int main(int argc, char *argv[])
{
    FILE 			*fp;
	int 			get_key;
	unsigned int 	read_byte_n;
	
    if (argc < 2) {
        printf("%s", copyright);
        return 0;
    }

    if ((fp = fopen(argv[1], "rb+")) == NULL) {
        printf("No such file \"%s\" or open fail.\n", argv[1]);
        return 0;
    }
	page_n = -1;
	get_key = 0;
	
	while (get_key != 'q') {
		
		read_byte_n = read_file_to_buffer(fp);
		show_buffer(read_byte_n);
		
		if (Flag == FLAG_EOF)
			break;
		
		printf("\n\tPlease input any key to contine or put q to quit.\n");
		
		get_key = getchar();		/* if the get_key equl 'q', we exit the function */
		
		fflush(stdin);
	}
	
	fclose(fp);
    return 0;
}

/*
**
**		@In 		FILE *fp		:   File's HANDLE.
**		@Return		u_int read_n	:	The number of bytes we read.
**
**		@Function Describe 			: 	We one time just read 512 bytes to mem_buffer, if the number is not equl to 512,
**							 			Then we set Flag equl to FLAG_EOF. It represent the File which we read finished.							
**
*/
static unsigned int read_file_to_buffer(FILE *fp)
{
	unsigned int read_n;
	
	if ((read_n = fread(mem_buffer, 1, BUFFER_SIZE, fp)) != BUFFER_SIZE) {
		Flag = FLAG_EOF;
	}
	page_n++;
	return read_n;
}

/*
**
**		@In 		u_int block_no	:   The size of bytes we should show in stdin.
**		@NoReturn
**
**		@Function Describe 			: 	The stub function, then call show_line to show each line.
**															
**
*/
static void show_buffer(unsigned int block_no)
{
	int line_n = 0;
	while (block_no  >= MAX_LINE) {
		show_line(line_n, MAX_LINE);
		block_no -= MAX_LINE;
		line_n++;
	}
	
	if (block_no != 0) {
		show_line(line_n, block_no);
	}
}

/*
**
**		@In 		u_int line_n	:   The line number.
**		@In 		u_int rest_n	:   The rest number we should show.
**		@NoReturn
**
**		@Function Describe 			: 	Show one line.
**							 								
**
*/

static void	show_line(unsigned int line_n, unsigned int rest_n)
{
	unsigned int		i;
	unsigned int 		addr;
	
	show_line_no(line_n);
	
	for (i = 0; i < rest_n; i++) {
		addr = (line_n << 4) + i;
		show_hex(mem_buffer[addr]);
	}
	
	for (; i < MAX_LINE; i++) {
		printf("   ");
	}
	
	printf("  ");
	
	for (i = 0; i < rest_n; i++) {
		addr = (line_n << 4) + i;
		if (mem_buffer[addr] <= ASSIC_OVER && 
				mem_buffer[addr] >= ASSIC_START) {
			putchar(mem_buffer[addr]);
		} else {
			putchar('.');
		}
	}
	
	putchar('\n');
}

static void show_line_no(unsigned int line_n)
{
	unsigned int 	total_line_n;
	unsigned int 	i;
	unsigned int 	counter;
	char 			buffer[11];
	
	total_line_n = (page_n << 5) + line_n;
	buffer[10] = LINE_REAST;
	buffer[9] = BLANK;
	buffer[8] = BLANK;
	buffer[7] = '0';
	
	for (i = 0; i < 7; i++) {
		counter = total_line_n % MAX_LINE;
		total_line_n  >>= 4;
		
		if (counter < 10) {
			buffer[6 - i] = counter + ASSIC_0;
		} else {
			buffer[6 - i] = counter - 10 + ASSIC_A;
		}
	}
	
	printf("%s", buffer);
}
static void show_hex(unsigned char number)
{
	char 			d_byte[4];
	unsigned int 	j;
	
	d_byte[3] = LINE_REAST;
	d_byte[2] = BLANK;
	
	j = number % MAX_LINE;
	number >>= 4;
	
	if (j < 10) {
		d_byte[1] = j + ASSIC_0;
	} else {
		d_byte[1] = j - 10 + ASSIC_A;
	}
	
	j = number % MAX_LINE;
	if (j < 10) {
		d_byte[0] = j + ASSIC_0;
	} else {
		d_byte[0] = j - 10 + ASSIC_A;
	}
	
	printf("%s", d_byte);
}
