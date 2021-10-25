@echo off
cls

set DRIVE_LETTER=%1:
set PATH=%DRIVE_LETTER%\TDM-GCC-64\bin;c:\windows\system32;c:\windows
set PROJECT_PATH=.

::windres resource.rc -O coff -o resource.o
mingw32-make DRIVE_LETTER="%DRIVE_LETTER%" PROJECT_DIR="%PROJECT_PATH%"

