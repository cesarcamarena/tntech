@echo off
cls

set MAIN_PATH="%~dp0.."
set PATH=%MAIN_PATH%\Java\bin;%MAIN_PATH%\Java\ant-1.9.9\bin;c:\Windows

ant run -Ddrive-letter=%MAIN_PATH%

