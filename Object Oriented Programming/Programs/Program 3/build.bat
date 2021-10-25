@echo off
cls

set DRIVE_LETTER=%1:
set PATH=%DRIVE_LETTER%\Program Files\Java\jdk1.8.0_221\bin;%DRIVE_LETTER%\ant-1.9.16\bin;c:\Windows

ant run -Ddrive-letter=%DRIVE_LETTER%

