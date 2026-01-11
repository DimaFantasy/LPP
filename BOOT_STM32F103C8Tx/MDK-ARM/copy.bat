@echo off
chcp 1251 >nul
:: Папка, где лежит батник
set "batdir=%~dp0"
:: Исходный файл
set "source=%batdir%BOOT_STM32F103C8Tx\BOOT_STM32F103C8Tx.hex"
:: Первая целевая папка
set "destination1=%batdir%..\..\..\DELPHI_PROJEKT\XE7\bin\update\STM32F103C8Tx\!STM32F103C8Tx_boot.hex"
:: Копируем в оба места
copy "%source%" "%destination1%" /Y >nul
echo File copied successfully to both destinations.
