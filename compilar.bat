@echo off
gcc -std=c99 -Wall -Wextra -Wpedantic src\main.c -o lanhouse_cp1.exe
if errorlevel 1 (echo ERRO NA COMPILACAO & exit /b 1)
echo Compilado com sucesso. Execute lanhouse_cp1.exe
