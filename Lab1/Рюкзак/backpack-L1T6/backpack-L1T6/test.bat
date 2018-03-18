rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � 
set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ��������� ��� 
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem ������ ������� - 15, ������ ����� - set
%PROGRAM% 15 set.txt > "%TEMP%\backPack.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\backPack.txt" "test-data\out1.txt" >nul
if ERRORLEVEL 1 goto err

rem 10 ��������� ����� 1 � ����� 1, ������ ������������ 10, � ���������� ������� ��� 
%PROGRAM% 10 10.txt > "%TEMP%\10.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\10.txt" "test-data\out2.txt" >nul
if ERRORLEVEL 1 goto err

rem ��� �������� ������� ������� ��� �������
%PROGRAM% 0 set.txt > "%TEMP%\backPack.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\backPack.txt" "test-data\out3.txt" >nul
if ERRORLEVEL 1 goto err

rem  ������� ������� (100 , ��� >= 1/2 ����������������), � ������ (��� > 1/2 �������, ���� �������), 
rem � ���������� � ������� ����� ���� ������� ������� � ������ �����
%PROGRAM% 30 set4.txt > "%TEMP%\backPack.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\backPack.txt" "test-data\out4.txt" >nul
if ERRORLEVEL 1 goto err

rem ��� �� ������ �������� (� out5.txt ������ ���������)
%PROGRAM% 80 set5.txt > "%TEMP%\backPack.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\backPack.txt" "test-data\out5.txt" >nul
if not ERRORLEVEL 1 goto err

echo Testing pass!
exit 0

:err
echo Program testing failed
exit 1