@echo off
chcp 1251
rem Задаем путь к файлу counter.txt
set "counter_file=%~dp0counter.txt"
rem Проверяем, существует ли файл counter.txt
if not exist "%counter_file%" (
    echo 1 > "%counter_file%"
)
rem Читаем значение из counter.txt
for /f "usebackq tokens=*" %%i in ("%counter_file%") do set /a old_counter=%%i
rem Увеличиваем значение на 1
set /a counter=old_counter+1
rem Записываем новое значение обратно в counter.txt
echo %counter% > "%counter_file%"
rem Генерируем файл counter.h
set "header_file=%~dp0..\My_Libraries\counter.h"
(
    echo #ifndef COUNTER_H
    echo #define COUNTER_H
    echo #define APP_VERSION %counter%U
    echo #endif
) > "%header_file%"

rem Выводим старую и новую версию
echo Version: %old_counter%
echo New Version: %counter%
:: Запускаем copy.bat (он в той же папке, что и этот бат)
call "copy.bat"
