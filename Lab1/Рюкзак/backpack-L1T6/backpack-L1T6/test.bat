rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в 
set PROGRAM="%~1"

rem При запуске без параметров ожидается ненулевой код 
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem Размер рюкзака - 15, список вещей - set
%PROGRAM% 15 set.txt > "%TEMP%\backPack.txt"
if ERRORLEVEL 1 goto err


echo Testing pass!
exit 0


:err
echo Program testing failed
exit 1