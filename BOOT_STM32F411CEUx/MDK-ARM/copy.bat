@echo off
chcp 1251
:: Папка, где лежит батник
set "batdir=%~dp0"
:: Исходный файл: LPP.hex рядом в подпапке LPP
set "source=%batdir%BOOT_STM32F411CEUx\BOOT_STM32F411CEUx.hex"
:: Целевая папка: подняться на 3 уровня до \, потом в DELPHI_PROJEKT\...
set "destination=%batdir%..\..\..\DELPHI_PROJEKT\XE7\bin\update\STM32F411CEUx\!STM32F411CEUx_boot.hex"
:: Копируем с новым именем
copy "%source%" "%destination%" /Y
echo File copied and renamed successfully.
