@echo off
cls

set DRIVE_LETTER=%1:
set MODE=%2:
set PATH=%DRIVE_LETTER%\Java\bin;%DRIVE_LETTER%\Java\ant-1.9.9\bin;c:\Windows

ant run -Dmode=%MODE% -Ddrive-letter=%DRIVE_LETTER% 
