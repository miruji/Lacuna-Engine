@echo off
cls

setlocal enabledelayedexpansion

set /p path_choice="choose project (1;2): "

if "%path_choice%"=="1" (
    set "project=Kingso"
) else if "%path_choice%"=="2" (
    set "project=Margo"
) else (
    echo "no".
    exit
)

"Lacuna Engine.exe" 0 "G~projects\%project%\~F~1280~768"

endlocal