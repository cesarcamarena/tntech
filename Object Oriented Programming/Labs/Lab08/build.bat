@echo off
cls

set DRIVE_LETTER=%1:

::DO THIS
::set the second parameter on the command line to NUM_PLAYERS
set NUM_PLAYERS=%2:

set PATH=%DRIVE_LETTER%\Java\bin;%DRIVE_LETTER%\Java\ant-1.9.9\bin;c:\Windows

::DO THIS
::modify to allow NUM_PLAYERS to be passed to ant as num-players
::ant run -Ddrive-letter=%DRIVE_LETTER% -Dnum-players=%NUM_PLAYERS%

::DO THIS
::use your robot task instead
ant robot -Ddrive-letter=%DRIVE_LETTER% -Dnum-players=%NUM_PLAYERS%