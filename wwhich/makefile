# This Windows which(wwhich) tools Makefile.

# ---------------Set the Build Flag---------------------
MACRO=
CC=CL
CCFLAG=/c /O2 
LD=LINK
LDFLAG=/DEFAULTLIB:MSVCRT.LIB /NODEFAULTLIB:LIBC.LIB

# ------------------------------------------------------
wwhich.exe : wwhich.obj
    $(LD) $(LDFLAG) wwhich.obj /out:wwhich.exe

wwhich.obj : wwhich.c
    $(CC) $(CCFLAG) $(MACRO) wwhich.c

clean:
    del *.obj *.exe