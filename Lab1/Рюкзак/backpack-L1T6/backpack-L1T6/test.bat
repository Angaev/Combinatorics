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
fc.exe "%TEMP%\backPack.txt" "test-data\out1.txt" >nul
if ERRORLEVEL 1 goto err

rem 10 предметов ценой 1 и весом 1, рюкзак вместимостью 10, в результате возьмет все 
%PROGRAM% 10 10.txt > "%TEMP%\10.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\10.txt" "test-data\out2.txt" >nul
if ERRORLEVEL 1 goto err

rem все предметы слишком большие для рюкзака
%PROGRAM% 0 set.txt > "%TEMP%\backPack.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\backPack.txt" "test-data\out3.txt" >nul
if ERRORLEVEL 1 goto err

rem  Дорогой предмет (100 , вес >= 1/2 грузоподъемности), и другие (вес > 1/2 рюкзака, цена дешевка), 
rem в результате в рюкзаке будет один дорогой предмет и пустое место
%PROGRAM% 30 set4.txt > "%TEMP%\backPack.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\backPack.txt" "test-data\out4.txt" >nul
if ERRORLEVEL 1 goto err

rem Это не жадный алгоритм (в out5.txt жадное поведение)
%PROGRAM% 80 set5.txt > "%TEMP%\backPack.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\backPack.txt" "test-data\out5.txt" >nul
if not ERRORLEVEL 1 goto err

echo Testing pass!
exit 0

:err
echo Program testing failed
exit 1