#Flag.

CC=cl 
CCFLAG=/c /O2 /MD
LD=link
LDFLAG=
RM=DEL

all: hexset.exe

hexset.exe : hexset.obj 
    $(LD) $(LDFLAG) hexset.obj 
    
hexset.obj : hexset.c hexset.h 
    $(CC) $(CCFLAG) hexset.c

clean:
    $(RM) *obj *.exe *log *.hex
    