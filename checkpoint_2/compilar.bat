@echo off
gcc -std=c99 -Wall -Wextra -Wpedantic -Iinclude src\main.c src\lanhouse.c -o lanhouse_cp2.exe
if errorlevel 1 (echo ERRO NA COMPILACAO & exit /b 1)
echo Compilado com sucesso. Execute lanhouse_cp2.exe
