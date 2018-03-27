#ifndef __HEXDUMP_H__	//__HEXDUMP_H__
#define __HEXDUMP_H__

#include <stdio.h>

/************************************************************************
 *						Const var define.
 ***********************************************************************/
 
#define BUFFER_SIZE 	0x200			/* the fixed mem buffer size */


#define MAX_LINE 		0x10			/* mem buffer max line */
#define MAX_WITH 		0x20			/* mem buffer max with */

#define ASSIC_0  		0x30			/* ASSIC CODE 0	*/
#define ASSIC_9  		0x39			/* ASSIC CODE 9 */
#define ASSIC_A  		0x41			/* ASSIC CODE A */
#define ASSIC_F  		0x46			/* ASSIC CODE F */

#define ASSIC_START 	0x20 			/* ASSIC CODE start */
#define ASSIC_OVER	0x7E			/* ASSIC CODE over  */

/*
 *	The FLAG number for the next behavier to to.If Flag equl -1, This show the stream is over.
 */
#define FLAG_EOF		(char)(-1)
#define FLAG_COT		(char)(0)

#define LINE_REAST	((char)(0))
#define BLANK			((char)' ')

/***********************************************************************
 *						The static var define.
 **********************************************************************/
 
static char 			mem_buffer[BUFFER_SIZE];		/* we just use the 512 bytes mem to read one time */

static char			Flag;							/* see  Macro FLAG_EOF and FLAG_COT */

static unsigned int 	page_n;						/* the page_n init var is -1, it's the number of page.*/

/**********************************************************************
 *					The internal function interface.
 **********************************************************************/
 
static void 			show_buffer			(unsigned int block_no);
static unsigned int  	read_file_to_buffer	(FILE *fp);
static void			show_line				(unsigned int line_n, unsigned int rest_n);    
static void 			show_line_no			(unsigned int line_n);
static void 			show_hex				(unsigned char number);

#endif 	//__HEXDUMP_H__
