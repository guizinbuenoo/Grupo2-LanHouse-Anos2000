@echo off
if not exist data mkdir data
gcc -std=c99 -Wall -Wextra -Wpedantic -Iinclude src\main.c src\lanhouse.c src\storage.c -o lanhouse.exe
if errorlevel 1 (echo ERRO NA COMPILACAO & exit /b 1)
echo Compilado com sucesso. Execute lanhouse.exe nesta pasta.
