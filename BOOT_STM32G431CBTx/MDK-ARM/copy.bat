@echo off
chcp 1251 >nul
:: Папка, где лежит батник
set "batdir=%~dp0"
:: Исходный файл
set "source=%batdir%BOOT_STM32G431CBTx\BOOT_STM32G431CBTx.hex"
:: папка
set "destination1=%batdir%..\..\..\DELPHI_PROJEKT\XE7\bin\update\STM32G431CBTx\!STM32G431CBTx_boot.hex"
:: Копируем в оба места
copy "%source%" "%destination1%" /Y >nul
echo File copied successfully to both destinations.
