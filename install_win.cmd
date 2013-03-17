@echo off
setlocal

set effects=%appdata%\REAPER\Effects
if not exist "%effects%" goto :eof

xcopy /-y /i Tale\*.* "%effects%\Tale"
