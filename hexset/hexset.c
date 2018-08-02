#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "hexset.h"


int main(int argc, char *argv[]) 
{
    char transfile[256];
    int  begin;
    
    transfile[0] = 0;
    
    if (argc >= 3) {
        if (!strcmp("-config", argv[1])) {
            if (argc == 5 && !strcmp("-o", argv[3])) {
                hexset_trans(argv[2], argv[4]);
            } else {
                strcat(transfile, argv[2]);
                strcat(transfile, ".hex");
                hexset_trans(argv[2], transfile);
               
            }
        } else if (argc == 7 && !strcmp("-f", argv[1])
                        && !strcmp("-b", argv[3]) && !strcmp("-e", argv[5])) {
            if ((begin = (trans2int(argv[4]))) != -1) {
                hexset_edit(argv[2], begin, argv[6]);
            } else {
                printf("\nThe aruments -e %s specil is not right.\n\n", argv[4]);
            }
        } else {
            puts(errormessage);
        }
    } else {
        puts(errormessage);
    }
    


    
    return 0;

}

static int trans2int(char *s) 
{
    int i = 0;
    
    int sum = 0;
    
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        for (i = 2; s[i] != 0; i++) {
            if (ASSIC_0 <= s[i] && s[i] <= ASSIC_9) {
                sum = (sum << 4) + (s[i] - ASSIC_0 + HEX_0);
            } else if (ASSIC_A <= s[i] && s[i] <= ASSIC_F){
                sum = (sum << 4) + (s[i] - ASSIC_A + HEX_A ) << 4;
            } else {
                return -1;
            }
        }
        return sum;
    } else {
        for (i = 0; s[i] != 0; i++) {
            if (ASSIC_0 <= s[i] && s[i] <= ASSIC_9) {
                sum = sum * 10 + s[i] - ASSIC_0 + HEX_0;
            } else {
                return -1;
            }
        }
        return sum;
    }
    
}
static void hexset_trans(char *configfile, char *transfile)
{
    FILE *trans, *config;
    char buffer[1024];
    char buffer2int[512];
    int  bufferp = 0;
    int  buffer2intp = 0;
    int  buffersize = 0;

    
    char temp = 0;
    
    char flag = 0;
    
    config = fopen(configfile, "r");
    if (!config) {
        printf("OpenFile %s false because: %s\n\n", configfile, strerror(errno));
        exit(-1);
    }
    
    trans = fopen(transfile, "w");
    if (!trans) {
        printf("OpenFile %s false because: %s\n\n", transfile, strerror(errno));
        exit(-1);
    }
    while ((buffersize = fread(buffer, 1, 1024, config))) {
        
        
        
        for (bufferp = 0; bufferp < buffersize; bufferp++) {
            
            if (ASSIC_0 <= buffer[bufferp] && buffer[bufferp] <= ASSIC_9) {
                
                temp = buffer[bufferp] - ASSIC_0 + HEX_0;
                
                
            } else if (ASSIC_A <= buffer[bufferp] && buffer[bufferp] <= ASSIC_F) {
                temp = buffer[bufferp] - ASSIC_A + HEX_A;
                
            } else {
               
                continue;
            }
            
            if (flag) {
               
                buffer2int[buffer2intp] = (buffer2int[buffer2intp] << 4) + temp;
                buffer2intp++;
                flag = 0;
            } else {
                
                buffer2int[buffer2intp] = temp;
               
                flag = 1;
            }
            
            if (buffer2intp == 512) {
                fwrite(buffer2int, 1, 512, trans);
                buffer2intp = 0;
            }
        }
        
    }
    
    fwrite(buffer2int, 1, buffer2intp, trans);
    
    
errno_handle:
     fclose(trans);
     fclose(config);
}
static void hexset_edit(char *transfile, int begin, char *buffer)
{
    FILE *trans;
    int bufferp;
    int buffersize;

    char buffer2int[512];
    char flag = 0;
    int  buffer2intp = 0;
    char temp;
    
    trans = fopen(transfile, "r+");
    if (!trans) {
        printf("Open File flase : %s\n", strerror(errno));
        return;
    }

    if (fseek(trans, (long)begin, SEEK_SET)) {
        printf("fseek false: %s\n", strerror(errno));
        return;
    }
    buffersize = strlen(buffer);
    
    for (bufferp = 0; bufferp < buffersize; bufferp++) {
        
        if (ASSIC_0 <= buffer[bufferp] && buffer[bufferp] <= ASSIC_9) {
                temp = buffer[bufferp] - ASSIC_0 + HEX_0;
                
                
            } else if (ASSIC_A <= buffer[bufferp] && buffer[bufferp] <= ASSIC_F) {
                temp = buffer[bufferp] - ASSIC_A + HEX_A;
                
            } else {
                
                continue;
            }
            
            if (flag) {
                
                buffer2int[buffer2intp] = (buffer2int[buffer2intp] << 4) + temp;
                buffer2intp++;
                flag = 0;
            } else {
                
                buffer2int[buffer2intp] = temp;
                
                flag = 1;
            }
            
            if (buffer2intp == 512) {
                fwrite(buffer2int, 1, 512, trans);
                buffer2intp = 0;
            }
    }
    
    fwrite(buffer2int, 1, buffer2intp, trans);
    
    fclose(trans);
}
