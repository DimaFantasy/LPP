@echo off
chcp 1251
:: Папка, где лежит батник
set "batdir=%~dp0"
:: Исходный файл: LPP_STM32G431Cx.hex рядом в подпапке LPP_STM32G431Cx.hex
set "source=%batdir%LPP_STM32G431Cx\LPP_STM32G431Cx.hex"
:: Целевая папка: подняться на 3 уровня до D:\LPP\, потом в DELPHI_PROJEKT\...
set "destination=%batdir%..\..\..\DELPHI_PROJEKT\XE7\bin\update\STM32G431Cx\STM32G431Cx_app.hex"
:: Копируем с новым именем
copy "%source%" "%destination%" /Y
echo File copied and renamed successfully.
:: Запускаем counter.bat (он в той же папке, что и этот бат)
call "%batdir%counter.bat"
