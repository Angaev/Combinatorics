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


echo Testing pass!
exit 0


:err
echo Program testing failed
exit 1