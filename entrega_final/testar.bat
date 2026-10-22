@echo off
if not exist data mkdir data
gcc -std=c99 -Wall -Wextra -Wpedantic -Iinclude tests\test_core.c src\lanhouse.c src\storage.c -o test_final.exe
if errorlevel 1 (echo ERRO NA COMPILACAO DOS TESTES & exit /b 1)
test_final.exe
if errorlevel 1 (echo TESTES FALHARAM & exit /b 1)
echo TODOS OS TESTES UNITARIOS PASSARAM.
