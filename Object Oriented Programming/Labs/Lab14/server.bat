@echo off
cls

set DRIVE_LETTER=%1:
set PORT_NUM=%2
set NUM_PLAYERS=%3
set PATH=%DRIVE_LETTER%\Java\bin;%DRIVE_LETTER%\Java\ant-1.9.9\bin;c:\Windows

ant server -Ddrive-letter=%DRIVE_LETTER% -Dport-num=%PORT_NUM% -Dnum-players=%NUM_PLAYERS%  

