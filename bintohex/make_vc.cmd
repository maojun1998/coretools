@echo off
set CCFLAG=/c /O2
set CC=cl
set LD=link
set LDFLAG=/DEFAULTLIB:MSVCRT.LIB /NODEFAULTLIB:LIBCMT.LIB
@echo on
%CC% %CCFLAG% bth.c 
%LD% %LDFLAG% bth.obj /out:bth.exe