@echo off
cls

set DRIVE_LETTER=%1:
set IP_ADDR=%2
set PORT_NUM=%3
set PATH=%DRIVE_LETTER%\Java\bin;%DRIVE_LETTER%\Java\ant-1.9.9\bin;c:\Windows

ant client -Ddrive-letter=%DRIVE_LETTER% -Dip-address=%IP_ADDR% -Dport-num=%PORT_NUM%  

