@echo off
echo Compilando proyecto de contactos...

gcc src\*.c -Iheaders -o main.exe

if %errorlevel% neq 0 (
    echo Error en la compilacion.
    exit /b %errorlevel%
) else (
    echo Compilacion exitosa.
)

pause
