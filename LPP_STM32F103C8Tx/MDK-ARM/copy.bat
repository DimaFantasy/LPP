@echo off
chcp 1251
:: Папка, где лежит батник
set "batdir=%~dp0"
:: Исходный файл: LPP.hex рядом в подпапке LPP
set "source=%batdir%LPP_STM32F103C8Tx\LPP_STM32F103C8Tx.hex"
:: Целевая папка: подняться на 3 уровня до \, потом в DELPHI_PROJEKT\...
set "destination=%batdir%..\..\..\DELPHI_PROJEKT\Bin\update\STM32F103C8Tx\!STM32F103C8Tx_app.hex"
:: Копируем с новым именем
copy "%source%" "%destination%" /Y
echo File copied and renamed successfully.
