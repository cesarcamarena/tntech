@echo off
cls

set DRIVE_LETTER=%1:
set PATH=%DRIVE_LETTER%\Java\bin;%DRIVE_LETTER%\Java\ant-1.9.9\bin;c:\Windows

::ant run-command-line -Ddrive-letter=%DRIVE_LETTER%

ant run-gui -Ddrive-letter=%DRIVE_LETTER%