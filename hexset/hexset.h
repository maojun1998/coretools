#ifndef __HEXSET__ // hexset.h
#define __HEXSET__


//  HEXSET
//  ======
//  hexset is tools for edit file as hex nummer.
//
//  cmmond args
//  ===========
//  * hexset -config [conf filename] -o [filename]
//    if filename is exit. print error message. else creat file.
//  * hexset -f [filename] -b addr -e number
//    filename is a file that need edit. -b is begin from, -e is the hexnumber.

#define ASSIC_0     ('0')
#define ASSIC_9     ('9')
#define ASSIC_A     ('A')
#define ASSIC_F     ('F')

#define HEX_0       (0)
#define HEX_9       (9)
#define HEX_A       (10)
#define HEX_F       (15)


static int  trans2int(char *s);
static void hexset_trans(char *configfile, char *transfile);
static void hexset_edit(char *transfile, int begin, char *buffer);

static char errormessage[] =    "\nUse error: see doc.\n"
                                "\thexset -config [conf filename] -o [filename]\n"
                                "\thexset -f [filename] -b addr -e number\n\n";

#endif __HEXSET__ //hexset.h