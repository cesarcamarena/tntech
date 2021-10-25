@echo off
cls

set DRIVE_LETTER=%1:
set PATH=%DRIVE_LETTER%\Java\bin;%DRIVE_LETTER%\Java\ant-1.9.9\bin;c:\Windows

::ant build -Ddrive-letter=%DRIVE_LETTER%
ant test -Ddrive-letter=%DRIVE_LETTER%